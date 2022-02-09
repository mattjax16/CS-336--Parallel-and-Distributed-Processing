/**
 * fish_production_stucs.h
 * Matt Bass
 * CS333
 * Project 6 :  Fish production line
 * Structs and methods for the fish production line
 * */

#ifndef PROJECT6_FISH_PRODUCTION_STUCS_H
#define PROJECT6_FISH_PRODUCTION_STUCS_H

#include <stdio.h>
#include "Linkedlist.h"

/// defining the structs for fish production
// a struct to act as a fish data type
typedef struct _fish{
    long unsigned int fish_id; //unique id of the fish
    int process_stage;//stage the fish is in, in its process
}Fish;


/// buffer struct to hold the fish
typedef struct _workerBuffer{
    LinkedList* fish_in_buffer;
    long unsigned int max_capacity;
} workerBuffer;

//creates a new fish struct, initializes it, and returns it
//Fish* fish_create(long unsigned int fid);

/// creates a new workBuffer struct, initializes it, and returns it
workerBuffer* workerBuffer_create(long unsigned int max_cap);


/// function to destroy a workerBuffer and make sure there is no memory leak
void workerBuffer_destroy(workerBuffer* wb);

/// Function to see if the worker buffer is empty
int workerBuffer_isEmpty(workerBuffer* wb);

/// Function to see if the worker buffer is full
int workerBuffer_isFull(workerBuffer* wb);




/// thread data struct
//typedef struct _threadData{
//    Fish* thread_fish;
//} threadData;



#endif //PROJECT6_FISH_PRODUCTION_STUCS_H
