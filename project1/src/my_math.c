/* my_math.c:
 * math routines to support circadian simulation code
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Return length of vector (x,y)
float norm(float x, float y) {
  return sqrt( pow(x,2) + pow(y,2) );
} // end norm

// swap the floats a and b
void swapScalar(float *a, float *b) {
  float tmp;
  tmp = *a; // stores the value of a
  *a = *b; // the new value of a is the value of b
  *b = tmp; // the value of b is tmp
}



// return the Euclidean distance from (x1,y1) to (x2,y2)
// does this faster by using no functions from math.h
float distance(float x1, float y1, float x2, float y2){
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

// return the Euclidean distance from (x1,y1) to (x2,y2)
// does this slower by using functions from math.h
float distanceSlow(float x1, float y1, float x2, float y2){
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}

// Return 1 if n is odd. Return 0 if n is not odd.
int isOdd( int n ){
    return (n&1);
}

// return 1 if n is even. Return 0 if n is not even.
int isEven( int n ){
    return !(n&1);
}

// return the number of Nans in the array.
int countNans(float *array, int N){
    int nanCnt = 0;
    for(int i = 0; i < N; i++) {
        if(isnan(array[i])){
            nanCnt += 1;
        }
    }
    return nanCnt;
}

// Return the maxium value in the array (of length N)
float max(float *array, int N){
    int i = 0;

    int arr_max = array[i];

    for (i++; i < N; i++)
        if (array[i] > arr_max)
            arr_max = array[i];

    return arr_max;
}

// Return the sum of the N floats in the array.
float sum(float *array, int N){
    float arr_sum = 0;

    for (int i = 0; i < N; i++){
        arr_sum += array[i];
    }
    return arr_sum;
}

// Return the mean value of N floats in the array.
float mean(float *array, int N){
    return (sum(array,N)/N);
}

// Return the standard deviation of N floats in the array.
// Note: This uses the Bessel correction.
float std(float *array, int N){
    float arr_std = 0;
    float arr_mean = mean(array,N);

    for (int i = 0; i < N; i++){
        arr_std += ((array[i] - arr_mean)*(array[i] - arr_mean));
    }

    arr_std = sqrt(arr_std/(N-1));

    return arr_std;
}

// swap the pointers a and b
void swapArrays(float **a, float **b){
    float* tmp;
    tmp = *a; // stores the value of a
    *a = *b; // the new value of a is the value of b
    *b = tmp; // the value of b is tmp
}

//function to create an ascending array
float *createAscendingArray(int N){
    float *ret = malloc(sizeof(float)*N);
    int i;
    for (i=0; i<N; i++)
        ret[i] = (float)i;
    return ret;
}

//function to create a descending array
float *createDescendingArray(int N){
    float *ret = malloc(sizeof(float)*N);
    int i;
    for (i=0; i<N; i++)
        ret[i] = (float)(N-i);
    return ret;
}

//function to create an array for testing
float *createArrayTesting(int N){
    float *ret = malloc(sizeof(float)*N);
    int i;
    srand(0);
    for (i=0; i<N; i++)
        ret[i] = (float)((i+1)*rand())*0.3;
    return ret;
}

// display the array
void display(float* array, int N) {
    for (int i = 0; i < N; i++) {
        if(i == N-1){
            printf("%f\n", array[i]);
        }
        else{
            printf("%f, ", array[i]);
        }
    }
}
