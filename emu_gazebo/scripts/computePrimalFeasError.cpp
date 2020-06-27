//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computePrimalFeasError.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "computePrimalFeasError.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const emxArray_real_T *x
//                const double cIneq[12]
//                int mLinEq
//                int mNonlinEq
//                const emxArray_real_T *cEq
//                const emxArray_int32_T *finiteLB
//                int mLB
//                const emxArray_real_T *lb
//                const emxArray_int32_T *finiteUB
//                int mUB
// Return Type  : double
//
double computePrimalFeasError(const emxArray_real_T *x, const double cIneq[12],
  int mLinEq, int mNonlinEq, const emxArray_real_T *cEq, const emxArray_int32_T *
  finiteLB, int mLB, const emxArray_real_T *lb, const emxArray_int32_T *finiteUB,
  int mUB)
{
  double feasError;
  int mEq;
  int idx;
  double u1;
  feasError = 0.0;
  mEq = mNonlinEq + mLinEq;
  for (idx = 0; idx < mEq; idx++) {
    u1 = std::abs(cEq->data[idx]);
    if ((!(feasError > u1)) && (!rtIsNaN(u1))) {
      feasError = u1;
    }
  }

  for (idx = 0; idx < 12; idx++) {
    if ((!(feasError > cIneq[idx])) && (!rtIsNaN(cIneq[idx]))) {
      feasError = cIneq[idx];
    }
  }

  for (idx = 0; idx < mLB; idx++) {
    u1 = lb->data[finiteLB->data[idx] - 1] - x->data[finiteLB->data[idx] - 1];
    if ((!(feasError > u1)) && (!rtIsNaN(u1))) {
      feasError = u1;
    }
  }

  for (idx = 0; idx < mUB; idx++) {
    u1 = x->data[finiteUB->data[idx] - 1] - rtInf;
    if ((!(feasError > u1)) && (!rtIsNaN(u1))) {
      feasError = u1;
    }
  }

  return feasError;
}

//
// File trailer for computePrimalFeasError.cpp
//
// [EOF]
//
