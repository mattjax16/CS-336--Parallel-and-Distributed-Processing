/**
 * benford_parallel_E_1.c
 * Matt Bass
 * CS333
 * Project 4 : Confirming Benford's Law with pthreads
 * task 2 E_1 (creating a 10*numthread array of padded int structs to prevent false sharing)
 *
 * Global Counter Array of Arrays, Grouped by Thread, no Mutex:
 * Use a global variable that is an array of ints with 10*NUM_THREADS entries.
 * The digit counts for each thread should be stored in that array.
 * For this version store the counts for all digits for a single thread together
 * (e.g. thread 0 uses entries 0 through 9, thread 1 uses entries 10 through 19, etc.).
 * Because each thread has its own section of the array, there is no need for a mutex!
 * After all the threads have joined, loop through this new array of arrays, and
 * sum the counts for each digit.
 */

/**
Medium Expected output on I9 10900k:
There are 3217 1's
There are 1779 2's
There are 1121 3's
There are 907 4's
There are 745 5's
There are 668 6's
There are 591 7's
There are 495 8's
There are 477 9's
It took 0.000209 seconds for the whole thing to run
Total numbers in file: 10000
Process finished with exit code 0
*/
/**
Long Expected output on I9 10900k:
There are 312705 1's
There are 177336 2's
There are 121034 3's
There are 92637 4's
There are 75909 5's
There are 65134 6's
There are 57202 7's
There are 51298 8's
There are 46745 9's
It took 0.002068 seconds for the whole thing to run
Total numbers in file: 1000000
*/
/**
Longer non benford Expected output on I9 10900k:
There are 111316 1's
There are 111213 2's
There are 111439 3's
There are 110671 4's
There are 110874 5's
There are 110761 6's
There are 111663 7's
There are 110801 8's
There are 111262 9's
It took 0.001408 seconds for the whole thing to run
Total numbers in file: 1000000
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
    int tid;
} threadData;

//making a padded data type
typedef struct _paddedCount{
    int count;

    //make array of 15 ints to take up other 60 bytes to hold up a whole cache line
    // in x86
    int padding[15];
}paddedCount;

// Global variables
paddedCount threads_global_counts[10*NUM_THREADS];

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

        //increment the global count array
            //one way with if statements
//        if(thr_data->tid == 0){
//            threads_global_counts[leading_digit]++;
//        } else{
//            threads_global_counts[(thr_data->tid*9)+leading_digit+thr_data->tid]++;
//        }
        threads_global_counts[(thr_data->tid*9)+leading_digit+thr_data->tid].count++;


    }
}


/* Main routine. */
int main(int argc, char* argv[]) 
{

    //Global function variables
    int numThreads = 8;
    // Load the data
    int succ;
     succ = loadData( "bin/longer_nonBenford.bin" );
//      succ = loadData( "bin/medium.bin" );
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
        thr_data[i].tid = i;
    }

    // create threads
    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, thrCount, &thr_data[i]);
    }

    // join threads
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }


    //combine the threads_global_counts into global counts array
    for (int i = 0; i < numThreads; i++) {
        for(int j = 0; j<10;j++){
            global_counts[j] += threads_global_counts[(i*9)+j+i].count;
        };
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


    return 0;
} // end main

