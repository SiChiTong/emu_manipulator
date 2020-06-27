//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeComplError.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef COMPUTECOMPLERROR_H
#define COMPUTECOMPLERROR_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern double computeComplError(const emxArray_real_T *xCurrent, const double
  cIneq[12], const emxArray_int32_T *finiteLB, int mLB, const emxArray_real_T
  *lb, const emxArray_int32_T *finiteUB, int mUB, const emxArray_real_T *lambda,
  int iL0);

#endif

//
// File trailer for computeComplError.h
//
// [EOF]
//
