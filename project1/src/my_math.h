/* my_math.h:
 * math routines we need for fish simulation et al.
 */

#ifndef MY_MATH_H

#define MY_MATH_H

// Return length of vector (x,y)
float norm(float x, float y);

// swap the floats a and b
void swapScalar(float *a, float *b);

// return the Euclidean distance from (x1,y1) to (x2,y2)
// does this by using sqrt butr now from math.h
float distance(float x1, float y1, float x2, float y2);

// return the Euclidean distance from (x1,y1) to (x2,y2)
// does this slower by using functions from math.h
float distanceSlow(float x1, float y1, float x2, float y2);

// Return 1 if n is odd. Return 0 if n is not odd.
int isOdd( int n );

// return 1 if n is even. Return 0 if n is not even.
int isEven( int n );

// return the number of Nans in the array.
int countNans(float *array, int N);

// Return the maxium value in the array (of length N)
float max(float *array, int N);

// Return the sum of the N floats in the array.
float sum(float *array, int N);

// Return the mean value of N floats in the array.
float mean(float *array, int N);

// Return the standard deviation of N floats in the array.
// Note: This uses the Bessel correction.
float std(float *array, int N);

// swap the pointers a and b
void swapArrays(float **a, float **b);

//function to create an ascending array
float *createAscendingArray(int N);

//function to create a descending array
float *createDescendingArray(int N);

//function to create an array for testing
float *createArrayTesting(int N);

// display the array
void display(float* array, int N);

#endif
