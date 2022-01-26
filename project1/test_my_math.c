/* test_my_math.c
 * Tests all routines in my_math.h
 * Stephanie Taylor
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "my_math.h"

/* Functions that test each my_math function, printing the
 * result to the screen
 */

void test_norm() {
  printf("\nTesting Norm\n");
  float n = norm(0.1, 0.1);
  printf("norm(0.1,0.1) is %f, and should be 0.141421\n",n);
  n = norm(0.0,0.0);
  printf("norm(0.0,0.0) is %f, and should be 0.000000\n",n);
  n = norm(-1.0,0.1);
  printf("norm(-1.0,0.1) is %f, and should be 1.004988\n",n);
}

void test_swapScalar() {
  float a = 5.0;
  float b = 6.0;
  printf("Before swap, a=%f and b=%f\n",a,b);
  swapScalar(&a,&b);
  printf("After swap, a=%f and b=%f\n",a,b);
}

/* Main function */
// Just comment out any line that runs a test you don't want to run.
int main(int argc, char* argv[]) {
  test_norm(); 
  test_swapScalar();
} // main

