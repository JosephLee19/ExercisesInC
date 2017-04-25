/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void free_anything(int *p) {
    free(p);
}


int read_element(int *array, int index) {
    int x = array[index];
    return x;
}


int main ()
{
    int never_allocated;
    int *free_twice = malloc (sizeof (int));
    int *use_after_free = malloc (sizeof (int));
    int *never_free = malloc (sizeof (int));
    int array1[100];
    int *array2 = malloc (100 * sizeof (int));

    // valgrind does not bounds-check static arrays
    //read_element(array1, -1);//negative 1 is out of bounds
    read_element(array1, 99);

    // but it does bounds-check dynamic arrays
    //read_element(array2, -1);  -1 is still out of bounds
    read_element(array2, 99);

    // and it catches use after free
    /* this is in the wrong order, should use it before freeing
    free(use_after_free);
    *use_after_free = 17;
    */
    // never_free is definitely lost
    free(use_after_free);
    *never_free = 17;
//but not anymore
    free_anything(never_free);
    // the following line would generate a warning
    // free(&never_allocated);

    // but this one doesn't
    //free_anything(&never_allocated); no need to free something that hasn't been allocated
    
    free(free_twice);
   // free(free_twice);
    free(array2);
    return 0;
}
