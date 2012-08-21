// Copyright (C) 2012 thuxnder@dexlabs.org
// Based on the x86 version of pleed@dexlabs.org
//
// Licensed under the Apache License, Version 2.0 (the 'License');
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an 'AS IS' BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <jni.h>
#include <limits.h>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "emulator-detector", __VA_ARGS__))

void* polling_thread(void *);
void atomicallyIncreasingGlobalVarThread(void);
uint32_t * histogram;
uint32_t global_value = 0;
int breakLoop = 0;

void* polling_thread(void * data){
	int i = 0;
	//Make sure we dont overflow any entry of our histogram by using UINT_MAX
	for(i =0; i < UINT32_MAX; i++){
		//LOGI("value: 0x%x\n",global_value);
		histogram[global_value]++;
	}
	breakLoop = 1;
}

void atomicallyIncreasingGlobalVarThread(void){
	for(;;){
		__asm__ __volatile__ ("mov r0, %[global];"
		                      "mov r1, #1;"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      "add r1, r1, #1;" "str r1, [r0];"
		                      :
		                      :[global] "r" (&global_value)
		                      );
		if(breakLoop)
			break;
	}
}

void Java_com_fuzion_emulatordetection_EmulatorDetector_detectEmulator(JNIEnv* env, jobject javaThis) {
	pthread_t thread_data2;

	//Assume that we have ~75 asm increment instructions
	//so we know that we will have an index into histogram greater than 75
	histogram = malloc(sizeof(uint32_t) * 75);


	if(pthread_create(&thread_data2, NULL, polling_thread, NULL))
		perror("pthread_create()");

	atomicallyIncreasingGlobalVarThread();
  return;
}

