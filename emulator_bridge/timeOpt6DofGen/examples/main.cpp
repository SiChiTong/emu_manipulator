//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

//***********************************************************************
// This automatically generated example C++ main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************

// Include Files
#include "main.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxAPI.h"
#include "timeOpt6DofGen_terminate.h"

// Function Declarations
static void argInit_1x6_real_T(double result[6]);
static emxArray_real_T *argInit_6xUnbounded_real_T();
static double argInit_real_T();
static void main_timeOpt6DofGen();

// Function Definitions

//
// Arguments    : double result[6]
// Return Type  : void
//
static void argInit_1x6_real_T(double result[6])
{
  int idx1;

  // Loop over the array to initialize each element.
  for (idx1 = 0; idx1 < 6; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real_T();
  }
}

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *argInit_6xUnbounded_real_T()
{
  emxArray_real_T *result;
  int idx0;
  int idx1;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result = emxCreate_real_T(6, 2);

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 6; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result->data[idx0 + 6 * idx1] = argInit_real_T();
    }
  }

  return result;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_timeOpt6DofGen()
{
  emxArray_real_T *w;
  emxArray_real_T *qr;
  double v_max_tmp[6];
  double cost_out;
  double flag;
  emxInitArray_real_T(&w, 2);

  // Initialize function 'timeOpt6DofGen' input arguments.
  // Initialize function input argument 'qr'.
  qr = argInit_6xUnbounded_real_T();

  // Initialize function input argument 'v_max'.
  argInit_1x6_real_T(v_max_tmp);

  // Initialize function input argument 'a_max'.
  // Call the entry-point 'timeOpt6DofGen'.
  timeOpt6DofGen(qr, v_max_tmp, v_max_tmp, argInit_real_T(), w, &cost_out, &flag);
  emxDestroyArray_real_T(w);
  emxDestroyArray_real_T(qr);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. 
  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_timeOpt6DofGen();

  // Terminate the application.
  // You do not need to do this more than one time.
  timeOpt6DofGen_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
