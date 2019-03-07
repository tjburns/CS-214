/* 
 * Created by Tom Burns and Andrew Dulichan
 * CS 214 – Systems Programming, Asst 1
 * mymalloc.h header file for Asst 1
 */

#ifndef MYMALLOC_H
#define MYMALLOC_H

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

static char myblock[4096];

void* mymalloc(short size, __FILE__, __LINE__);

void myfree(void* ptr, __FILE__, __LINE__);

#endif