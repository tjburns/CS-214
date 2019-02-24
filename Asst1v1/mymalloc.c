#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mymalloc.h"

// TODO write mymalloc/myfree
//      do error checking

(void*) mymalloc(short size, __FILE__, __LINE__) {

}

void myfree (void* ptr, __FILE__, __LINE__) 
{
    if (/* condition */)
    {
        /* code */
    }
    else if (/* condition */)
    {
        /* code */
    }
    // CASE C
    else if (ptr == NULL)
    {
        printf("Could not free %d in file %s at line %d: this pointer was already freed.", ptr, __FILE__, _LINE__);
        return -1;
    }
    else
    {
        ptr = NULL;
    }
    return;
}