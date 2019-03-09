/* 
 * Created by Tom Burns and Andrew Dulichan
 * CS 214 – Systems Programming, Asst 1
 * mymalloc.c implementation file for Asst 1
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mymalloc.h"

// TODO write mymalloc/myfree
//      do error checking

void printMemory() {
    metadata * curr = myblock;
    metadata * endOfMem = (metadata *)((char *)(myblock + MEM_SIZE));

    while (curr < endOfMem) {
        printf("Inuse: %d\tSize: %d\n", curr->inuse, curr->size);
        curr = (metadata *)((char *)(curr + METADATA_SIZE + curr->size));
    }
    if (endOfMem - curr != 0) {
        printf("SIZE MISMATCH: %d\n", endOfMem-curr);
    }
}

void* mymalloc(short size, __FILE__, __LINE__)
{
    if (size <= 0) {
        return NULL;
    }

    // FIRST MALLOC CALL SETUP
        // magic number in this implementation is 28
    short magicnumber = 28;
    if (*((short*)myblock) != magicnumber) {
        ((metadata*)(myblock+sizeof(magicnumber)))->inuse = 0;
        ((metadata*)(myblock+sizeof(magicnumber)))->size = MEM_SIZE-sizeof(magicnumber)-METADATA_SIZE;
        *((short*)myblock) = magicnumber;
    }

    // PERFORM MALLOC
        // set up initial vars
    metadata * curr = myblock;
    metadata * endOfMem = (metadata *)((char *)(myblock + MEM_SIZE));
    
    // find position for available space to be allocated
    while (TRUE) {
        if (curr->inuse == 0 && curr->size >= (size + METADATA_SIZE)) {
            break;
        }
        // reached the end of the array without finding appropriate space for allocation
        else {
            curr = (metadata *)((char *)(curr + METADATA_SIZE + curr->size));
            if (curr > endOfMem) {
                fprintf(stderr, "ERROR: No space for allocation. FILE: %s LINE: %d\n", __FILE__, __LINE__);
                return NULL;
            }
        }
    }

    // ALLOCATE the free space
    curr->size = size;
    curr->inuse = 1;

    // new UNALLOCATED metadata to be added to array -- AFTER CURRENT POSITION BEING ALLOCATED
    (metadata*)next = (metadata*)((char*)(curr + METADATA_SIZE + curr->size));
    (metadata*)nextnext = (metadata*)((char*)(next + METADATA_SIZE + next->size));
    next->size = nextnext - next - METADATA_SIZE;
    next->inuse = 0;

    return (curr + METADATA_SIZE);
}

void myfree(void* ptr, __FILE__, __LINE__) 
{

    // Error checking

    // CASE A
    if (/* condition */)
    {
        printf("Could not free %d in file %s at line %d: the memory address in question was not pointed to.", ptr, __FILE__, __LINE__);
        return -1;
    }
    // CASE B
    else if (/* condition */)
    {
        printf("Could not free %d in file %s at line %d: this pointer to the given memory space was not allocated by malloc().", ptr, __FILE__, __LINE__);
        return -2;
    }
    // CASE C
    else if (ptr == NULL)
    {
        printf("Could not free %d in file %s at line %d: this pointer was already freed.", ptr, __FILE__, __LINE__);
        return -3;
    }
    // Free the memory
    else
    {
        ptr = NULL;
    }
    return;
}