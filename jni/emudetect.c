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
#include <math.h>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "emulator-detector", __VA_ARGS__))
#define DEBUG 0

void polling_thread(void);
void* atomicallyIncreasingGlobalVarThread(void *);
void printHistogram();
double calculatEntropyValue();
uint32_t * histogram;
uint32_t global_value = 0;
const int numberOfIncIns = 50;
int numberOfSamples = 0x100;//Make sure we dont overflow any entry of our histogram by using UINT_MAX

void polling_thread(void){
	int i = 0;
	for(i =0; i < numberOfSamples; i++){
		//LOGI("value: 0x%x\n",global_value);
		usleep(1);
		histogram[global_value]++;
	}
	if(DEBUG){
		printHistogram();
		LOGI("Entropy measurement: %f",calculatEntropyValue());
	}
}

void* atomicallyIncreasingGlobalVarThread(void * data){
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
		                      :
		                      :[global] "r" (&global_value)
		                      );
	}
}

double calculatEntropyValue(){
	double sum = 0.0, ent = 0.0;
	uint i = 0;
	for (i = 0; i < numberOfIncIns; i++)
	  sum += (double)histogram[i];

	for (i = 0; i < numberOfIncIns; i++){
		double pi = (double)histogram[i] / sum;
		if(pi == 0)
			continue;
	  	ent += pi* log(pi);
	}
	return -ent/log(sum);
}

void printHistogram(){
	int i;
	for(i = 0; i < numberOfIncIns; i++)
		LOGI("%d : %d", i, histogram[i]);
}

void initializeHistogram(){
	//Assume that we have ~numberOfIncIns asm increment instructions
	//so we know that we will have an index into histogram greater than numberOfIncIns
	histogram = malloc(sizeof(uint32_t) * (numberOfIncIns));
	int i;
	for(i =0; i < numberOfIncIns; i++)
		histogram[i] = 0;
}

jdouble Java_com_fuzion_emulatordetection_EmulatorDetector_qemuFingerPrint(JNIEnv* env, jobject javaThis) {
	initializeHistogram();

	pthread_t threadData;

	if(pthread_create(&threadData, NULL, atomicallyIncreasingGlobalVarThread, NULL))
		perror("pthread_create()");

	polling_thread();
	double entValue = calculatEntropyValue();
	//pthread_kill(threadData, SIGSTOP);
	free(histogram);

  	return entValue;
}