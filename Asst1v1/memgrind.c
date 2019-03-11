/* 
 * Created by Tom Burns and Andrew Dulichan
 * CS 214 – Systems Programming, Asst 1
 * memgrind.c test file for Asst 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mymalloc.h"

void test() {
	char * c[50];
	int numAllocs = 0;
	int numFrees = 0;
	while (numFrees < 50 || numAllocs < 50) {
		if (rand() % 2 == 0  && numAllocs < 50) {
			printf("ALLOCATING\n");
			c[numAllocs] = (char *)malloc(1);
			printMemory();
			numAllocs++;
		    	printf("number of allocations: %d\n", numAllocs);
		    	printf("\n"); 
		}
		else if (numFrees < 50 && numAllocs > 0 && numAllocs > numFrees) {
			printf("FREEING\n");
		    	free(c[numFrees]);
		    	printMemory();
		    	numFrees++;
		    	printf("number of frees: %d\n", numFrees);
		    	printf("\n");
		}
	}
}
void failureCase1() {
	char * y = (char*)malloc(4097);
	free(y);
}
void failureCase2() {
	char* p = (char*)malloc(4096-METADATA_SIZE);
	char * q = (char*)malloc(1);
	
	free(p);
	free(q);
}
void failureCase3() {
	char * p = (char*)malloc(4096);
	char * q = (char*)malloc(1);
	
	free(p);
	free(q);
}

void workloadA() {
	int i;
	
	for (i = 0; i < 150; i++) {
		char * a = (char*)malloc(1);
		free(a);
	}
	
}

void workloadB() {
	int b;
	for (b = 0; b < 3; b++) {
		int i, j;
		char * b[50];
		for (i = 0; i < 50; i++) {
			b[i] = malloc(1);
		}
		for (i = 0; i < 50; i++) {
			free(b[i]);
		}
	}
}

void workloadC() {
	char * c[50];
	int numAllocs = 0;
	int numFrees = 0;
	while (numFrees < 50 || numAllocs < 50) {
		if (rand() % 2 == 0  && numAllocs < 50) {
			c[numAllocs] = (char *)malloc(1);
			numAllocs++; 
		}
		else if (numFrees < 50 && numAllocs > 0 && numAllocs > numFrees) {
		    	free(c[numFrees]);
		    	numFrees++;
		}
	}
}

void workloadD() {
	char * d[50];
	int numAllocs = 0;
	int numFrees = 0;
	while (numFrees < 50 || numAllocs < 50) {
		if (rand() % 2 == 0  && numAllocs < 50) {
		    	d[numAllocs] = (char *)malloc((rand() % 64) + 1);
		    	numAllocs++;
		}
		else if (numFrees < 50 && numAllocs > 0 && numAllocs > numFrees) {
		    	free(d[numFrees]);
		    	numFrees++;
		}
	}
}


void workloadE() {
	int i;
	for (i = 0; i < 150; i++) {
		char * a = (char*)malloc(4090);
		free(a);
	}
}

void workloadF() {
	char * f[256];
	int i;
	for (i = 0; i < 255; i++) {
		f[i] = (char*)malloc(10);
	}
	//f[255] = (char*)malloc(11);
	f[255] = (char*)malloc(8);
	for (i = 0; i < 256; i++) {
		if (i % 2 == 0) {
			free(f[i]);
		}
	}
	for (i = 0; i < 256; i++) {
		if (i % 2 == 1) {
			free(f[i]);
		}
	}
}

int main() {

	srand(time(NULL));
	struct timeval startTime;
	struct timeval endTime;
	double elapsedTime;
	int i;
	
	// TESTING/DEBUGGING
	//printf("%d\n",sizeof(metadata));
	//test();
	//failureCase1();
	//failureCase2();
	//failureCase3();
	//workloadA();
	//workloadB();
	//workloadC();
	//workloadF();
	//printMemory();
	
	
	printf("\n");
	printf("--------------------WORKLOAD A----------------------\n\n");
	gettimeofday(&startTime, 0);
	for (i = 0; i < 100; i++) {
	    	workloadA();
	}
	gettimeofday(&endTime, 0);
	elapsedTime = 1000000*endTime.tv_sec + endTime.tv_usec - 1000000*startTime.tv_sec + startTime.tv_usec;
	printf("Average Run Time: %f microseconds\n", elapsedTime/100);
	printf("\nMemory after run:\n");
	printMemory();
	printf("\n----------------------------------------------------\n\n");
	
	printf("--------------------WORKLOAD B----------------------\n\n");
	gettimeofday(&startTime, 0);
	for (i = 0; i < 100; i++) {
	    	workloadB();
	}
	gettimeofday(&endTime, 0);
	elapsedTime = 1000000*endTime.tv_sec + endTime.tv_usec - 1000000*startTime.tv_sec + startTime.tv_usec;
	printf("Average Run Time: %f microseconds\n", elapsedTime/100);
	printf("\nMemory after run:\n");
	printMemory();
	printf("\n----------------------------------------------------\n\n");
	
	
	printf("--------------------WORKLOAD C----------------------\n\n");
	gettimeofday(&startTime, 0);
	for (i = 0; i < 100; i++) {
	    	workloadC();
	}
	gettimeofday(&endTime, 0);
	elapsedTime = 1000000*endTime.tv_sec + endTime.tv_usec - 1000000*startTime.tv_sec + startTime.tv_usec;
	printf("Average Run Time: %f microseconds\n", elapsedTime/100);
	printf("\nMemory after run:\n");
	printMemory();
	printf("\n----------------------------------------------------\n\n");
	
	printf("--------------------WORKLOAD D----------------------\n\n");
	gettimeofday(&startTime, 0);
	for (i = 0; i < 100; i++) {
	    	workloadD();
	}
	gettimeofday(&endTime, 0);
	elapsedTime = 1000000*endTime.tv_sec + endTime.tv_usec - 1000000*startTime.tv_sec + startTime.tv_usec;
	printf("Average Run Time: %f microseconds\n", elapsedTime/100);
	printf("\nMemory after run:\n");
	printMemory();
	printf("\n----------------------------------------------------\n\n");
	
	printf("--------------------WORKLOAD E----------------------\n\n");
	gettimeofday(&startTime, 0);
	for (i = 0; i < 100; i++) {
	    	workloadE();
	}
	gettimeofday(&endTime, 0);
	elapsedTime = 1000000*endTime.tv_sec + endTime.tv_usec - 1000000*startTime.tv_sec + startTime.tv_usec;
	printf("Average Run Time: %f microseconds\n", elapsedTime/100);
	printf("\nMemory after run:\n");
	printMemory();
	printf("\n-----------------------------------------------\n\n");
	
	printf("--------------------WORKLOAD F----------------------\n\n");
	gettimeofday(&startTime, 0);
	for (i = 0; i < 100; i++) {
	    	workloadF();
	}
	gettimeofday(&endTime, 0);
	elapsedTime = 1000000*endTime.tv_sec + endTime.tv_usec - 1000000*startTime.tv_sec + startTime.tv_usec;
	printf("Average Run Time: %f microseconds\n", elapsedTime/100);
	printf("\nMemory after run:\n");
	printMemory();
	printf("\n----------------------------------------------------\n\n");
	
	
	return 0;
}
