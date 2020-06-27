//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeGradLag.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef COMPUTEGRADLAG_H
#define COMPUTEGRADLAG_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void computeGradLag(emxArray_real_T *workspace, int ldA, int nVar, const
  emxArray_real_T *grad, const emxArray_real_T *AineqTrans, int mEq, const
  emxArray_real_T *AeqTrans, const emxArray_int32_T *finiteFixed, int mFixed,
  const emxArray_int32_T *finiteLB, int mLB, const emxArray_int32_T *finiteUB,
  int mUB, const emxArray_real_T *lambda);

#endif

//
// File trailer for computeGradLag.h
//
// [EOF]
//
