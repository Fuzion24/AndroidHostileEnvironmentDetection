package com.fuzion.emulatordetection;

public class EmulatorDetector {

	static {
		System.loadLibrary("emudetect");
	}
	
	public native static void detectEmulator();
	
	static void testNative()
	{
		detectEmulator();
	}
}
