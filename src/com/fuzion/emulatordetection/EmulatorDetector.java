package com.fuzion.emulatordetection;

import android.util.Log;

public class EmulatorDetector {

	static {
		System.loadLibrary("emudetect");
	}

	private native static double qemuFingerPrint();

	static boolean qemuDetection()
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
}
