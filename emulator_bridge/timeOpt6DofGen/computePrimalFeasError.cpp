//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computePrimalFeasError.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "computePrimalFeasError.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include <cmath>

// Function Definitions

//
// Arguments    : int mLinIneq
//                int mNonlinIneq
//                const emxArray_real_T *cIneq
//                int mLinEq
//                int mNonlinEq
//                const emxArray_real_T *cEq
//                int mLB
// Return Type  : double
//
double computePrimalFeasError(int mLinIneq, int mNonlinIneq, const
  emxArray_real_T *cIneq, int mLinEq, int mNonlinEq, const emxArray_real_T *cEq,
  int mLB)
{
  double feasError;
  int mEq;
  int mIneq;
  int idx;
  double u1;
  feasError = 0.0;
  mEq = mNonlinEq + mLinEq;
  mIneq = mNonlinIneq + mLinIneq;
  for (idx = 0; idx < mEq; idx++) {
    u1 = std::abs(cEq->data[idx]);
    if ((!(feasError > u1)) && (!rtIsNaN(u1))) {
      feasError = u1;
    }
  }

  for (idx = 0; idx < mIneq; idx++) {
    if ((!(feasError > cIneq->data[idx])) && (!rtIsNaN(cIneq->data[idx]))) {
      feasError = cIneq->data[idx];
    }
  }

  for (idx = 0; idx < mLB; idx++) {
    abort();
  }

  return feasError;
}

//
// File trailer for computePrimalFeasError.cpp
//
// [EOF]
//
