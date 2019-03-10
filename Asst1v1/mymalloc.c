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
    metadata * curr = (metadata*)myblock;
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
        // check first position of array to see if it is metadata
        // magic number in this implementation is 5218
    short magicnumber = 5218;
    if (((metadata*)myblock)->magicnumber != magicnumber) {
        ((metadata*)((char*)myblock))->inuse = 0;
        ((metadata*)((char*)myblock))->size = MEM_SIZE-sizeof(magicnumber)-METADATA_SIZE;
        ((metadata*)((char*)myblock))->mag = magicnumber;
    }

    // PERFORM MALLOC
        // set up initial vars
    metadata * curr = (metadata*)myblock;
    metadata * endOfMem = (metadata *)((char *)(myblock + MEM_SIZE));
    
    // find position for available space to be allocated
    while (1) {
        if (curr->inuse == 0 && (size + METADATA_SIZE) <= curr->size) {
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

    // check if block at end of size free is large enough to fit annother UNALLOCATED block
        // if not => that space should be coalesced
    if ((size + METADATA_SIZE + 1 + METADATA_SIZE) < curr->size){
        curr->size = curr->size - METADATA_SIZE;
        curr->inuse = 1;
        curr->magicnumber = magicnumber;

        return (curr + METADATA_SIZE);
    }

    // ALLOCATE the free space
    curr->size = size;
    curr->inuse = 1;
    curr->magicnumber = magicnumber;

    // new UNALLOCATED metadata to be added to array -- AFTER CURRENT POSITION BEING ALLOCATED
    (metadata*)next = (metadata*)((char*)(curr + METADATA_SIZE + curr->size));
    (metadata*)nextnext = (metadata*)((char*)(next + METADATA_SIZE + next->size));
    next->size = nextnext - next - METADATA_SIZE;
    next->inuse = 0;
    next->magicnumber = magicnumber;

    return (curr + METADATA_SIZE);
}

void myfree(void* ptr, __FILE__, __LINE__) {
    
    // CASE C of error checking in assignment description
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: Could not free NULL pointer %d. FILE: %s LINE: %d\n", ptr, __FILE__, __LINE__);
        return;
    }

    magicnumber = 5218;
    curr = (metadata*)((char*)(ptr-METADATA_SIZE));
    // CASE A and B of error checking in assignment description
        // freeing an address that is not a pointer
        // freeing an address that was not created by malloc (does not contain metadata we have created)
    if (curr->magicnumber != magicnumber) {
        fprintf(stderr, "ERROR: Could not free %d. The memory address not in memory block. FILE: %s LINE: %d\n", ptr, __FILE__, __LINE__);
        return;
    }
   
    // check if the address has already been freed and is available for use
    if (curr->inuse == 0) {
        fprintf(stderr, "ERROR: Could not free %d. The pointer has already been freed. FILE: %s LINE: %d\n", ptr, __FILE__, __LINE__);
        return;
    }

    // FREE THE MEMORY BLOCK
        // find the position of the previous and next blocks - in relation to the current block
    (metadata*) prev = NULL;
    (metadata*) loop = (metadata*)myblock;
    while (loop != curr) {
        prev = loop;
        loop = (metadata*)((char*)(loop + METADATA_SIZE + loop->size));
    }
    (metadata*) next = (metadata*)((char*)(loop + METADATA_SIZE + loop->size));
    (metadata*) nextnext = (metadata*)((char*)(next + METADATA_SIZE + next->size));

    (metadata*) head = (metadata*) myblock;
    (metadata*) tail = (metadata*)((char*)(myblock + MEM_SIZE));

    // free the current block
        // coalesce memory blocks accoring to the appropriate scenario faced in memory
    if (prev != NULL) {

        // last memory block in the array is being freed
        // the MAGIC NUMBER COULD ALSO BE CHECKED to see if it is metadata (in the array)
            // check if the previous block is unallocated => coalesce if so OR set current block to unallocated if not
        if (next > tail && prev->inuse = 1) {
            curr->inuse = 0;
        }
        else if (next > tail && prev->inuse = 0) {
            prev->size += curr->size + METADATA_SIZE
            curr->magicnumber = 0;
            curr->size = 0;
            curr-> inuse = 0;
            // this should be a catchall for the above anyway
            curr->NULL;
        }

        // previous and next blocks are BOTH allocated => make current block unallocated (don't need to wipe the memory that is 'used' in the allocated block)
        else if (prev->inuse == 1 && next->inuse == 1) {
            curr->inuse == 0;
        }
        // previous has unallocated space and next is allocated
        else if (prev->inuse == 0 && next->inuse == 1) {
            prev->size += curr->size + METADATA_SIZE;
            curr->magicnumber = 0;
            curr->inuse = 0;
            curr->size = 0;
            curr = NULL;
        }
        //previous is allocated and next is unallocated
        else if (prev->inuse = 1 && next->inuse == 0) {
            curr->size += next->size + METADATA_SIZE;
            next->inuse = 0;
            next->size = 0;
            next->magicnumber = 0;
            next = NULL;
        }

        // BOTH next and previous are unallocated => coalesce both and current into one block
        else if (prev->inuse == 0 && next->inuse == 0) {
            prev->size = curr->size + next->size + METADATA_SIZE + METADATA_SIZE;

            next->inuse = 0;
            next->size = 0;
            next->magicnumber = 0;
            next = NULL;

            curr->magicnumber = 0;
            curr->inuse = 0;
            curr->size = 0;
            curr = NULL;
        }
    }
    // beginning of the array is being freed
    else {

        // only two cases possible
            // next block is allocated
        if (next->inuse == 1) {
            curr->inuse = 0;
        }
        else if (next->inuse == 0) {
            curr->size += next->size + METADATA_SIZE;
            next->magicnumber = 0;
            next->size = 0;
            next-> inuse = 0;
            next = NULL;
        }
    }
}