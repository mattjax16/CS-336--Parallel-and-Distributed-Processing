/* my_math.c:
 * math routines to support circadian simulation code
 */
#include <math.h>

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

