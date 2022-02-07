/**
 * fish_production_single.c
 * Matt Bass
 * CS333
 * Project 6 :  Fish production line
 * task 1
 *
 * In this project, you will be simulating a production line that creates frozen fish dinners.
 * They are passed from worker to worker in a production line. Imagine that each worker needs
 * to do something to the fish so that it can be packaged into a somewhat palatable frozen entree.
 * The workers are lined up sequentially -- a fish first goes to worker 1, who then hands it off
 * to worker 2, etc. Between each pair of workers is a holding area for the fish. Each holding
 * area can hold just one fish. So if worker 2 is looking for work, it needs to wait until
 * there is a fish in the holding area between worker 1 and worker 2. When there is,
 * it removes it, does something to it (simulate actual fish-prep work by calling
 * sleep for 0, 1, or 2 seconds), then puts it into the buffer between worker 2 and
 * worker 3. Worker 2 can put the fish into this next buffer only when its becomes empty.
 *
 *
 * Your goal is to write multiple versions of the program and to compare the speed of execution
 * (let's measure that in the average time it takes for a fish to be entirely processed).
 *
 *
 * It should pass one fish at a time. The buffers between the workers can hold one fish.
 * Use condition variables to keep track of full and empty buffers,
 * just as one would in a producer-consumer problem.
 */

/// Importing needed libraries
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "fish_production_stucs.h"

/** Defining the global variables for the production*/

const long unsigned int NUM_FISH = 10000;
long unsigned int FISH_DONE = 0;
#define NUM_BUFFERS 4

int one_sec = 1;

workerBuffer *starting_bin, *worker_1_2_bin, *worker_2_3_bin, *final_bin;

///defining the number of threads
#define NUM_WORKERS 3 // this is the number of threads



/// Defining global variables for the threads
pthread_t thread[NUM_WORKERS];
// Defing the condition variables for the worker buffers
pthread_cond_t buffer_full_conds[NUM_BUFFERS];
pthread_cond_t buffer_empty_conds[NUM_BUFFERS];

//Create locks for the workers
pthread_mutex_t worker_locks[NUM_WORKERS];


/// thread data struct
typedef struct _threadData{
    int tid;
} threadData;


void process_fish(Fish* fish_for_work){
    /** A function to simulate a worker working on the fish*/
    int time_to_wait = (rand() % 3)+1;
    wait(&time_to_wait);
    fish_for_work->process_stage++;
}



void* thrProcess(void* arg){
    /** The Thread Process function
     * takes in a fish
     * The bin that the worker works in is based off its thread id (tid)*/

    ///KEEP running until all fish are done
    while (FISH_DONE < NUM_FISH){
        /// getting the fish from the thread data
        threadData *thr_data = (threadData *)arg;

        ///Using the thread id as a switch to identify the worker
        switch (thr_data->tid) {
            ///declaring the fish that the worker will process
            Fish* fish;


            ///first worker
            case 1 :

                /// Locking the mutex for the worker
                pthread_mutex_lock(&worker_locks[thr_data->tid-1]);

                ///get fish from the starting bin if there are still fish there
                if(starting_bin->fish_in_buffer->size > 0){
                    fish = (Fish*)ll_pop(starting_bin->fish_in_buffer);

                    ///do work on the fish
                    process_fish(fish);

                    /// wait until the buffer is empty
                    /// to put the fish in the next buffer
                    if(worker_1_2_bin->fish_in_buffer->size >= worker_1_2_bin->max_capacity){
                        printf("Waiting for worker_1_2_bin to be empty");
                        pthread_cond_wait(&buffer_empty_conds[thr_data->tid-1],&worker_locks[thr_data->tid-1]);
                    }
                    else{
                        printf("Worker 1 Putting Fish %lu in worker_1_2_bin \n",fish->fish_id);
                        /// put the fish into the bin
                        ll_push(worker_1_2_bin->fish_in_buffer,fish);
                        pthread_cond_signal(&buffer_empty_conds[thr_data->tid-1]);
                    }
                }
                /// RELEASING THE WORKER MUTEX LOCK
                pthread_mutex_unlock(&worker_locks[thr_data->tid-1]);
                break;

                ///second worker
            case 2 :
                /// Locking the mutex for the worker
                pthread_mutex_lock(&worker_locks[thr_data->tid-1]);

                /// wait until the buffer has a fish for the worker
                while(worker_1_2_bin->fish_in_buffer->size < worker_1_2_bin->max_capacity){
                    wait(&one_sec);
                }

                /// get the fish
                fish = (Fish*)ll_pop(worker_1_2_bin->fish_in_buffer);

                ///do work on the fish
                process_fish(fish);

                /// wait until the buffer is empty
                /// to put the fish in the next buffer
                while(worker_2_3_bin->fish_in_buffer->size >= worker_2_3_bin->max_capacity){
                    wait(&one_sec);
                }
                printf("Worker 2 Putting Fish %lu in worker_2_3_bin \n",fish->fish_id);
                /// put the fish into the bin
                ll_push(worker_2_3_bin->fish_in_buffer,fish);

                /// RELEASING THE WORKER MUTEX LOCK
                pthread_mutex_unlock(&worker_locks[thr_data->tid-1]);

                break;


                ///third worker
            case 3 :

                /// Locking the mutex for the worker
                pthread_mutex_lock(&worker_locks[thr_data->tid-1]);

                /// wait until the buffer has a fish for the worker
                while(worker_2_3_bin->fish_in_buffer->size < worker_2_3_bin->max_capacity){
                    wait(&one_sec);
                }

                /// get the fish
                fish = (Fish*)ll_pop(worker_2_3_bin->fish_in_buffer);

                ///do work on the fish
                process_fish(fish);

                printf("Worker 3 Putting Fish %lu in final_bin \n",fish->fish_id);


                /// put the fish into the bin
                ll_push(final_bin->fish_in_buffer,fish);

                /// increment fish done
                FISH_DONE++;

                /// RELEASING THE WORKER MUTEX LOCK
                pthread_mutex_unlock(&worker_locks[thr_data->tid-1]);

                break;
        }
    }
}





int main(int argc, char *argv[]) {
    ///Main function to run the fish processing simulation


    //create the buffers
    starting_bin = workerBuffer_create(NUM_FISH*2);
    final_bin = workerBuffer_create(NUM_FISH*2);
    worker_1_2_bin = workerBuffer_create(1);
    worker_2_3_bin = workerBuffer_create(1);




    ///setting up the initial amount of fish
    for(long unsigned int i = 0; i<NUM_FISH;i++){

        /// setting up the new fish
        Fish* new_fish = (Fish*) malloc(sizeof(Fish*));
        new_fish->process_stage=0;
        new_fish->fish_id = i;
        // putting the fish in thde starting bin
        ll_append(starting_bin->fish_in_buffer,new_fish);
    }

    //setting up the worker threads
    threadData thread_d[NUM_WORKERS];
    /// make the thread id for the threads (workers)
    // set array info fields for the different threads
    for (int i = 0; i < NUM_WORKERS; i++) {
        thread_d[i].tid = i+1;
    }

    // create threads
    for (int i = 0; i < NUM_WORKERS; i++) {
        pthread_create(&thread[i], NULL, thrProcess, &thread_d[i]);
    }

    // join threads
    for (int i = 0; i < NUM_WORKERS; i++) {
        pthread_join(thread[i], NULL);
    }


    printf("\nDone with all %lud fish",FISH_DONE);

}





