//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computePrimalFeasError.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef COMPUTEPRIMALFEASERROR_H
#define COMPUTEPRIMALFEASERROR_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern double computePrimalFeasError(const emxArray_real_T *x, const double
  cIneq[12], int mLinEq, int mNonlinEq, const emxArray_real_T *cEq, const
  emxArray_int32_T *finiteLB, int mLB, const emxArray_real_T *lb, const
  emxArray_int32_T *finiteUB, int mUB);

#endif

//
// File trailer for computePrimalFeasError.h
//
// [EOF]
//
