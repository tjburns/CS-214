/* 
 * Created by Tom Burns and Andrew Dulichan
 * CS 214 – Systems Programming, Asst 1
 * mymalloc.h header file for Asst 1
 */

#ifndef MYMALLOC_H
#define MYMALLOC_H

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

typedef struct metadata {
    char inuse;
    short magicnumber;
    short size;
} metadata;

#define METADATA_SIZE sizeof(metadata)
#define MEM_SIZE 4096

static char myblock[MEM_SIZE];

void* mymalloc(short size, __FILE__, __LINE__);

void myfree(void* ptr, __FILE__, __LINE__);

#endif