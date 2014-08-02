package com.fuzion.emulatordetection;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.lang.reflect.Method;

import android.content.Context;
import android.util.Log;

public class EmulatorDetector {

	static {
		System.loadLibrary("emudetect");
	}

	private native static double qemuFingerPrint();

	public static boolean shouldBail(Context ctx){
		if(
			qemuAtomicBasicBlockDetection()||
			qemuBuildProps(ctx) ||
			cpuInfoIsQemu() ||
			qemuFileExistance() ||
			isNotUserBuild(ctx) || 
			hasEth0Interface()
			) return true;
		
		return false;
				
	}
	
	public static boolean qemuAtomicBasicBlockDetection()
	{

	/*
		A physical CPU increases the program counter after each instruction such that the
		program counter is always up to date. Since the registers in the translated code are emulated
		in order to keep the program counter up to date after each instruction, the
		translator would have to increase the virtual program counter. This would results in
		at least one additional program counter increase for each source code instruction. However
		since the translated target code is executed natively, a correct virtual program counter
		is only necessary in cases where an instruction from the source code accesses
		it. Qemu handles these cases but otherwise does not update the program counter
		in the virtual CPU register as part of an optimization. As a consequence the
		virtual program counter often just points to the start of a basic block since it
		is updated after every branch.
	*/
		//http://www.dexlabs.org/blog/btdetect
		double entValue = qemuFingerPrint();
		Log.d("EmuDetect", String.valueOf(entValue));
	
		return entValue < 0.05 ? true : false;
	}

	public static boolean hasEth0Interface(){
		//Normal devices have no eth0 interface, check if that interface exists and bail
		try {
			for(Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
			  NetworkInterface intf = en.nextElement();
			  if(intf.getName().equals("eth0"))
			  	return true;
			}
		} catch (SocketException ex) { }
		return false;
	}
	public static boolean qemuBuildProps(Context ctx){
		
		if(
			"goldfish".equals(getProp(ctx,"ro.hardware")) || 
		    "generic".equals(getProp(ctx,"ro.product.device")) || 
		    "1".equals(getProp(ctx,"ro.kernel.qemu")) 
		   )
			return true;

		return false;
	}
	
	public static boolean isNotUserBuild(Context ctx){
		//Other builds of android that are not production usually have build types of "eng", "debug", etc... 
		//Although this doesn't denote having an emulator, there is a possibility that the user is more intelligent
		//than a normal Android user and thus increases the risk of getting caught .. avoid that situation

		return !getProp(ctx,"ro.build.type").equals("user");
	}

	public static boolean cpuInfoIsQemu(){
		try{
			BufferedReader cpuInfoReader = new BufferedReader(new FileReader("/proc/cpuinfo"));
			String line;
			while((line = cpuInfoReader.readLine()) != null){
				if(line.contains("Goldfish"))
					return true;
			}
		}catch(Exception e){}
		return false;
	}
	
	public static boolean qemuFileExistance(){
		if (
				(new File("/init.goldfish.rc")).exists() || 
				(new File("/sys/qemu_trace")).exists() 	
			)
			return true;
		
		return false;
	}

	private static String getProp(Context ctx, String propName){
		try{
			ClassLoader cl = ctx.getClassLoader();
			Class<?> AndroidOSProps = cl.loadClass("android.os.properties");
			Method getProp = AndroidOSProps.getMethod("get", String.class);
			Object[] params = {new String(propName)};
			return (String) getProp.invoke(AndroidOSProps, params);
		}catch(Exception e){
			e.printStackTrace();
			return "";
		}
	}
	
}
