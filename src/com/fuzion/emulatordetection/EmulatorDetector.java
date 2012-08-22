package com.fuzion.emulatordetection;

public class EmulatorDetector {

	static {
		System.loadLibrary("emudetect");
	}
	
	public native static double detectEmulator();
	
	static boolean isEmulator()
	{
		double entValue = detectEmulator();

		if(entValue < 0.05)
			return true;
		
		return false;
	}
}
