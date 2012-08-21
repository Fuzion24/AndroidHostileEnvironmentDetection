// Copyright (C) 2011 thuxnder@dexlabs.org
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
//


//gcc -o detect -lpthread detect-translation.c
//gcc -o detect-32 -m32 -lpthread detect-translation.c

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

void* thread2(void *) __attribute__ ((noreturn));
void thread1(void) __attribute__ ((noreturn));

#ifdef __amd64__
	uint64_t global_value = 0;
	#define PRINT "value: 0x%lx\n"
#else
	uint32_t global_value = 0;
	#define PRINT "value: 0x%x\n"
#endif

void* thread2(void * data){
	for(;;){
		printf(PRINT,global_value);
	}
}

void thread1(void){
	for(;;){
		//shift
		#ifdef __amd64__
			__asm__ __volatile__ ( "mov %0, %%rbx;"
				"movl $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"     "add $1, (%%rbx);"
				"add $1, (%%rbx);"
				:
				:"c"(&global_value)
				:
				);
		#else
			__asm__ __volatile__ ( "movl %0, %%ebx;"
				"movl $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				"add $1, (%%ebx);"
				:
				:"c"(&global_value)
				:
				);
			#endif
	}
}

int main(int argc, char* argv){
	pthread_t thread_data2;
	int status;
	
	status = pthread_create(&thread_data2, NULL, thread2, NULL);
	if(status)
		perror("pthread_create()");
	thread1();
}
