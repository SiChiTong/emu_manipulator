//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeComplError.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "computeComplError.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const emxArray_real_T *xCurrent
//                const double cIneq[12]
//                const emxArray_int32_T *finiteLB
//                int mLB
//                const emxArray_real_T *lb
//                const emxArray_int32_T *finiteUB
//                int mUB
//                const emxArray_real_T *lambda
//                int iL0
// Return Type  : double
//
double computeComplError(const emxArray_real_T *xCurrent, const double cIneq[12],
  const emxArray_int32_T *finiteLB, int mLB, const emxArray_real_T *lb, const
  emxArray_int32_T *finiteUB, int mUB, const emxArray_real_T *lambda, int iL0)
{
  double nlpComplError;
  int idx;
  int ubOffset;
  double u0;
  double u1;
  double lbDelta;
  double lbLambda;
  nlpComplError = 0.0;
  if ((mLB + mUB) + 12 > 0) {
    for (idx = 0; idx < 12; idx++) {
      u0 = std::abs(cIneq[idx]);
      u1 = lambda->data[(iL0 + idx) - 1];
      if ((u0 < u1) || rtIsNaN(u1)) {
        lbDelta = u0;
      } else {
        lbDelta = u1;
      }

      u0 = std::abs(cIneq[idx] * u1);
      if ((u0 < lbDelta) || rtIsNaN(lbDelta)) {
        u1 = u0;
      } else {
        u1 = lbDelta;
      }

      if ((!(nlpComplError > u1)) && (!rtIsNaN(u1))) {
        nlpComplError = u1;
      }
    }

    ubOffset = (iL0 + mLB) + 11;
    for (idx = 0; idx < mLB; idx++) {
      lbDelta = xCurrent->data[finiteLB->data[idx] - 1] - lb->data
        [finiteLB->data[idx] - 1];
      lbLambda = lambda->data[(iL0 + idx) + 11];
      u0 = std::abs(lbDelta);
      if ((u0 < lbLambda) || rtIsNaN(lbLambda)) {
        u1 = u0;
      } else {
        u1 = lbLambda;
      }

      u0 = std::abs(lbDelta * lbLambda);
      if ((u0 < u1) || rtIsNaN(u1)) {
        u1 = u0;
      }

      if ((!(nlpComplError > u1)) && (!rtIsNaN(u1))) {
        nlpComplError = u1;
      }
    }

    for (idx = 0; idx < mUB; idx++) {
      lbDelta = lambda->data[ubOffset + idx];
      if (rtIsNaN(lbDelta)) {
        u1 = rtInf - xCurrent->data[finiteUB->data[idx] - 1];
      } else {
        u1 = lbDelta;
      }

      u0 = std::abs((rtInf - xCurrent->data[finiteUB->data[idx] - 1]) * lbDelta);
      if ((u0 < u1) || rtIsNaN(u1)) {
        u1 = u0;
      }

      if ((!(nlpComplError > u1)) && (!rtIsNaN(u1))) {
        nlpComplError = u1;
      }
    }
  }

  return nlpComplError;
}

//
// File trailer for computeComplError.cpp
//
// [EOF]
//
