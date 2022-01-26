/* test_my_math.c
 * Tests all routines in my_math.h
 * Stephanie Taylor
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "my_math.h"

/* Functions that test each my_math function, printing the
 * result to the screen
 *
 * MAth checked with https://www.wolframalpha.com/
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


void test_distance(){
    float x1 = 19.0;
    float y1 = -6.0;

    float x2 = 1.0;
    float y2 = 3.0;

    float dist;

    double startT, endT, totalT, avgT;

    //loop through the function 1000 times to test time time
    for(int i = 0; i<1000; i++){
        startT = clock();
        dist = distance(x1,y1,x2,y2);
        endT = clock();
        totalT += (endT-startT);
    }

    //calculate the average time
    avgT = totalT/1000;

    printf("The euclidean distance between (%f,%f) and (%f,%f) = %f and should be ≈20.1246 (avg time: %f)\n",x1,y1,x2,y2,dist,avgT);
}


void test_distanceSlow(){
    float x1 = 19.0;
    float y1 = -6.0;

    float x2 = 1.0;
    float y2 = 3.0;

    float dist;

    double startT, endT, totalT, avgT;

    //loop through the function 1000 times to test time time
    for(int i = 0; i<1000; i++){
        startT = clock();
        dist = distance(x1,y1,x2,y2);
        endT = clock();
        totalT += (endT-startT);
    }

    //calculate the average time
    avgT = totalT/1000;

    printf("The euclidean distance (slow) between (%f,%f) and (%f,%f) = %f and should be ≈20.1246 (avg time: %f)\n",x1,y1,x2,y2,dist,avgT);
}

void test_isOdd(){
    int odd_pos = 19;
    int odd_neg = -1;
    int even_pos = 12;
    int even_neg = -44;
    int zero = 0;

    int res1, res2, res3, res4, res5;


    float dist;

    double startT, endT, totalT, avgT;

    //loop through the function 1000 times to test time time
    for(int i = 0; i<1000; i++){
        startT = clock();
        res1 = isOdd(odd_pos);
        res2 = isOdd(odd_neg);
        res3 = isOdd(even_pos);
        res4 = isOdd(even_neg);
        res5 = isOdd(zero);
        endT = clock();
        totalT += (endT-startT);
    }

    //calculate the average time
    avgT = totalT/1000;

    printf("The results of isOdd: %d:%d , %d:%d , %d:%d , %d:%d , %d:%d (avg time 5 compares: %f)\n",odd_pos,res1,
           odd_neg,res2,even_pos,res3,even_neg,res4,zero,res5,avgT);
}

void test_isEven(){
    int odd_pos = 19;
    int odd_neg = -1;
    int even_pos = 12;
    int even_neg = -44;
    int zero = 0;

    int res1, res2, res3, res4, res5;


    float dist;

    double startT, endT, totalT, avgT;

    //loop through the function 1000 times to test time time
    for(int i = 0; i<1000; i++){
        startT = clock();
        res1 = isEven(odd_pos);
        res2 = isEven(odd_neg);
        res3 = isEven(even_pos);
        res4 = isEven(even_neg);
        res5 = isEven(zero);
        endT = clock();
        totalT += (endT-startT);
    }

    //calculate the average time
    avgT = totalT/1000;

    printf("The results of isEven: %d:%d , %d:%d , %d:%d , %d:%d , %d:%d (avg time 5 compares: %f)\n",odd_pos,res1,
           odd_neg,res2,even_pos,res3,even_neg,res4,zero,res5,avgT);
}

void test_countNans(){

    float test_arr1[10] = {10,2,41,132,0.123,4,45,1,7,0.1222};
    float test_arr2[10] = {NAN,2,41,132,0.123,NAN,45,1,7,NAN};
    int cnt1,cnt2;
    double startT, endT, totalT, avgT;

    //loop through the function 1000 times to test time time
    for(int i = 0; i<1000; i++){
        startT = clock();
        cnt1 =  countNans(test_arr1,10);
        cnt2 =  countNans(test_arr2,10);
        endT = clock();
        totalT += (endT-startT);
    }
    //calculate the average time
    avgT = totalT/1000;

    printf("result of countNans(test_arr1) = %d (should be 0) (avg time: %f)\n",cnt1,avgT );



    printf("result of countNans(test_arr2) = %d (should be 3) (avg time: %f)\n", cnt2,avgT);

}


void test_other_funcs(){

    int N = 20;
    float* test_arr = createArrayTesting(N);
//    display(test_arr, N);

    //finding the max of the array
    printf("The max of the array is %f and should be  587129344.000000\n", max(test_arr,N));


    //finding the std of the array because it relies on mean which relies on sum
    printf("The std of the array is %f and should be  404133132.38483\n", std(test_arr,N));
}

/* Main function */
// Just comment out any line that runs a test you don't want to run.
int main(int argc, char* argv[]) {
  test_norm(); 
  test_swapScalar();
  test_distance();
  test_distanceSlow();
  test_isOdd();
  test_isEven();
  test_countNans();
  test_other_funcs();
} // main

