//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeComplError.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "computeComplError.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const emxArray_real_T *fscales_cineq_constraint
//                int mIneq
//                const emxArray_real_T *cIneq
//                int mLB
//                const emxArray_real_T *lambda
//                int iL0
// Return Type  : double
//
double computeComplError(const emxArray_real_T *fscales_cineq_constraint, int
  mIneq, const emxArray_real_T *cIneq, int mLB, const emxArray_real_T *lambda,
  int iL0)
{
  double nlpComplError;
  int mNonlinIneq;
  int idx;
  double u0;
  double u1;
  double b_u1;
  nlpComplError = 0.0;
  mNonlinIneq = fscales_cineq_constraint->size[0];
  if (mIneq + mLB > 0) {
    for (idx = 0; idx < mNonlinIneq; idx++) {
      u0 = std::abs(cIneq->data[idx]);
      u1 = lambda->data[(iL0 + idx) - 1];
      if ((u0 < u1) || rtIsNaN(u1)) {
        b_u1 = u0;
      } else {
        b_u1 = u1;
      }

      u0 = std::abs(cIneq->data[idx] * u1);
      if ((u0 < b_u1) || rtIsNaN(b_u1)) {
        u1 = u0;
      } else {
        u1 = b_u1;
      }

      if ((!(nlpComplError > u1)) && (!rtIsNaN(u1))) {
        nlpComplError = u1;
      }
    }

    for (idx = 0; idx < mLB; idx++) {
      abort();
    }
  }

  return nlpComplError;
}

//
// File trailer for computeComplError.cpp
//
// [EOF]
//
