/**
 * fish_production_stucs.c
 * Matt Bass
 * CS333
 * Project 6 :  Fish production line
 * Structs and methods for the fish production line
 * */

#include "fish_production_stucs.h"
#include "Linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

////creates a new fish struct, initializes it, and returns it
//Fish* fish_create(long unsigned int fid){
//    Fish* new_fish = (*Fish)malloc(sizeof(Fish));
//    new_fish->fish_id=fid;
//    new_fish->process_stage = 0;
//    return new_fish
//}
//
////creates a new workBuffer struct, initializes it, and returns it
workerBuffer* workerBuffer_create(long unsigned int max_cap){
    workerBuffer* new_wb = (workerBuffer*)malloc(sizeof(workerBuffer));
    new_wb->fish_in_buffer = ll_create();
    new_wb->max_capacity = max_cap;
    return new_wb;
}

/// function to destroy a workerBuffer and make sure there is no memory leak
void workerBuffer_destroy(workerBuffer* wb){

    /// free the worker buffers list
    ll_clear(wb->fish_in_buffer,free);

    ///free the word buffer
    free(wb);
}



/// Function to see if the worker buffer is empty
int workerBuffer_isEmpty(workerBuffer* wb){
    if(wb->fish_in_buffer->size == 0){
        return 1;
    }
    return 0;
}

/// Function to see if the worker buffer is full
int workerBuffer_isFull(workerBuffer* wb){
    if(wb->fish_in_buffer->size == wb->max_capacity){
        return 1;
    }
    return 0;
}