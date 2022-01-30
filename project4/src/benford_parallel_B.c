/**
 * benford_parallel_B.c
 * Matt Bass
 * CS333
 * Project 4 : Confirming Benford's Law with pthreads
 * task 2 B
 *
 * Global Counter Array Protected by Array of Mutexes:
 * Use a global variable (array of 10 ints) to keep track of the total count of each digit (0 throug 9).
 * Since the count for each digit is independent of the count for every other digit, we can protect each
 * digit-counter with its own mutex. So, make a globa variable that contains an array of 10 mutex locks.
 * For each number the thread analyzes, it locks the appropriate lock, updates the corresponding counter,
 * and then unlocks the lock.
 */

/**
Medium Expected Output on I9 10900k:
There are 3217 1's
There are 1779 2's
There are 1121 3's
There are 907 4's
There are 745 5's
There are 668 6's
There are 591 7's
There are 495 8's
There are 477 9's
It took 0.000699 seconds for the whole thing to run
*/

/** Long Expected output on I9 10900k:
There are 312705 1's
There are 177336 2's
There are 121034 3's
There are 92637 4's
There are 75909 5's
There are 65134 6's
There are 57202 7's
There are 51298 8's
There are 46745 9's
It took 0.064591 seconds for the whole thing to run
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include "my_timing.h"

//defing the number of threads
#define NUM_THREADS 8

// thread data struct
typedef struct _threadData{
    double* start;
    int len;
} threadData;



//create the array of global mutex locks for each number in the
//global counts array
pthread_mutex_t num_locks_global[10];

// Global variables
int global_counts[10] = {0};
int N = 0;
double *data;




// Load data from a binary file that has an int and then
// a sequence of doubles. The value of the int should indicate
// the number of doubles in the sequence.
// Load the data into global variables N and data.
int loadData(char *filename) {
  FILE *fp;

  if(filename != NULL && strlen(filename))
    fp = fopen(filename, "r");
  else {
      printf("No file entered (filename = %s)\n", filename);
      return -1;
  }

  if (!fp){
      printf("File %s not found!\n", filename);
      return -1;
  }


  fread( &N, sizeof(int), 1, fp );
  data = (double*)malloc( sizeof(double)*N );
  fread( data, sizeof(double), N, fp );
  fclose( fp );
//   Uncomment this to verify the right data are being read in.
//   For super_short.bin, it should print out
//   data[0] = 97.137926;
//   data[1] = 24.639612;
//   data[2] = 55.692572;
//   int i;
//   for (i = 0; i < N; i++) {
//         printf( "data[%d] = %f\n", i, data[i] );
//   }
  return 1; // success
}

// Return the leading Digit of n.
int leadingDigit( double n ) {
    // This is not a particularly efficient approach.
    if (fabs(n) == 1.0)
        return 1;
    else if (fabs(n) == 0.0)
        return 0;
    else if (fabs(n) < 1.0) {
        // multiply it by 10 until you get a number that is at least 1.
        // Then chop off the fractional part. All that remains is the first digit.
        double tmp = fabs(n);
        while (tmp < 1.0) {
            tmp *= 10.0;
        }
        return (int)floor( tmp );
    }
    else {
        // Divide it by 10 until you get a number smaller than 10.
        // That number will be the first digit of the original number.
        long long unsigned in = (long long unsigned) floor(fabs(n));
        while (in > 9) {
            in /= 10;
        }
        return in;
    }
} // end leadingDigit


//The Thread count function
void* thrCount(void* arg){
    threadData *thr_data = (threadData *)arg;

    //loop through all the data in the thread info
    for(int i = 0; i<thr_data->len;i++){
        int leading_digit = leadingDigit(thr_data->start[i]);
        //lock the thread before modifying the shared global array
        pthread_mutex_lock(&num_locks_global[leading_digit]);
        //increment the global count array
        global_counts[leading_digit]++;

        //unlock the thread
        pthread_mutex_unlock(&num_locks_global[leading_digit]);
    }




    //exit the thread
    pthread_exit(NULL);
}




/* Main routine. */
int main(int argc, char* argv[]) 
{

    //Global function variables
    int numThreads = 8;
    // Load the data
    int succ;
    // succ = loadData( "bin/longer_nonBenford.bin" );
      succ = loadData( "bin/medium.bin" );
//    succ = loadData( "bin/longer.bin" );




    if (!succ) { return -1; }

    // Start the timer after we have loaded the data.
    double t1, t2;
    t1 = get_time_sec();

    // Do the parallel computation.

    //setting up an array for thread info arguments
    threadData thr_data[NUM_THREADS];
    //setting up threads
    pthread_t threads[numThreads];

    // set array info fields for the different thread data
    for (int i = 0; i < numThreads; i++) {
        int idx = i*N/numThreads;
        thr_data[i].start = &data[idx];
        thr_data[i].len = N/numThreads;
    }

    // create threads
    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, thrCount, &thr_data[i]);
    }

    // join threads
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }


    // End the timer
    t2 = get_time_sec();
  
    for (int i = 1; i < 10; i++) {
        printf( "There are %d %d's\n", global_counts[i], i );
    }
         
    printf("It took %f seconds for the whole thing to run\n",t2-t1);
    printf("Total numbers in file: %d",N);

    // We are responsible for calling loadData, so we are responsible
    // for freeing the data array.
    free( data );

    // destroy the mutex locks (we are done with it)
    int destroy_succes = pthread_mutex_destroy(num_locks_global);

    if(destroy_succes == -1){
        printf("Warring mutex locks not destroyed");
    }

    return 0;
} // end main

