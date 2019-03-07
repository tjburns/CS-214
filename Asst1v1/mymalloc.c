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


(void*) mymalloc(short size, __FILE__, __LINE__)
{
    
}

(void*) mymalloc(short size, __FILE__, __LINE__) 
{


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