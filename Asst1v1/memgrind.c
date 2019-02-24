#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mymalloc.h"


srand(time(NULL));
struct timeval tv;
time_t startTime;
time_t endTime;
int timeA[100];
int timeB[100];
int timeC[100];
int timeD[100];
int timeE[100];
//int timeF[100];
//int timeG[100];


int i, j, k;
for (i = 0; i < 100; i++) {

    // PART A
    startTime = tv.tv_sec;
    for (j = 0; j < 150; j++) {
        char * a = (char*)malloc(1);
        free(a);
    }
    endTime = tv.tv_sec;
    timeA[i] = endTime - startTime;

    // PART B
    startTime = tv.tv_sec;
    char * b[150];
    for (j = 0; j < 150; j++) {
        if ((j+1) % 50 == 0) {
            for (k = 0; k < 50; k++) {
                free(b[j]);
            }
        }
        else {
            b[j] = (char* )malloc(1);
        }
    }
    endTime = tv.tv_sec;
    timeB[i] = endTime - startTime;

    // PART C
    startTime = tv.tv_sec;
    char * c[50];
    int numAllocs = 0;
    int numFrees = 0;
    while (numFrees < 50 && numAllocs < 50) {
        if (rand() % 2 == 0  && numAllocs < 50) {
            c[numAllocs] = (char *)malloc(1);
            numAllocs++;
        }
        else if (numFrees < 50 && numAllocs > 0 && numAllocs > numFrees) {
            free(c[numFrees]);
            numFrees++;
        }
    }
    endTime = tv.tv_sec;
    timeC[i] = endTime - startTime;

    // PART D
    startTime = tv.tv_sec;
    char * d[50];
    numAllocs = 0;
    numFrees = 0;
    while (numFrees < 50 && numAllocs < 50) {
        if (rand() % 2 == 0  && numAllocs < 50) {
            d[numAllocs] = (char *)malloc((rand() % 64) + 1);
            numAllocs++;
        }
        else if (numFrees < 50 && numAllocs > 0 && numAllocs > numFrees) {
            free(d[numFrees]);
            numFrees++;
        }
    }
    endTime = tv.tv_sec;
    timeD[i] = endTime - startTime;

}

// PRINTING RUNTIME MEANS
totalTime = 0;
for (i = 0; i < 100; i++) {
    totalTime += timeA[i];
}
print("Runtime A MEAN: %f", totalTime/100.0);

totalTime = 0;
for (i = 0; i < 100; i++) {
    totalTime += timeB[i];
}
print("Runtime B MEAN: %f", totalTime/100.0);

totalTime = 0;
for (i = 0; i < 100; i++) {
    totalTime += timeC[i];
}
print("Runtime C MEAN: %f", totalTime/100.0);

totalTime = 0;
for (i = 0; i < 100; i++) {
    totalTime += timeD[i];
}
print("Runtime D MEAN: %f", totalTime/100.0);
