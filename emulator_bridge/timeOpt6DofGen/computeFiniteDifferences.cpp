//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeFiniteDifferences.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "computeFiniteDifferences.h"
#include "finDiffEvalAndChkErr.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include <cmath>

// Function Definitions

//
// Arguments    : d_struct_T *obj
//                double fCurrent
//                const emxArray_real_T *cIneqCurrent
//                int ineq0
//                const emxArray_real_T *cEqCurrent
//                int eq0
//                emxArray_real_T *xk
//                emxArray_real_T *gradf
//                emxArray_real_T *JacCineqTrans
//                int CineqColStart
//                emxArray_real_T *JacCeqTrans
//                int CeqColStart
//                const emxArray_real_T *c_runTimeOptions_FiniteDifferen
// Return Type  : bool
//
bool computeFiniteDifferences(d_struct_T *obj, double fCurrent, const
  emxArray_real_T *cIneqCurrent, int ineq0, const emxArray_real_T *cEqCurrent,
  int eq0, emxArray_real_T *xk, emxArray_real_T *gradf, emxArray_real_T
  *JacCineqTrans, int CineqColStart, emxArray_real_T *JacCeqTrans, int
  CeqColStart, const emxArray_real_T *c_runTimeOptions_FiniteDifferen)
{
  bool evalOK;
  int idx;
  emxArray_real_T *t0_nonlin_tunableEnvironment_f2;
  bool exitg1;
  double deltaX;
  coder_internal_ref *t0_nonlin_tunableEnvironment_f1;
  int t0_mEq;
  int loop_ub;
  double t0_nonlin_tunableEnvironment_f3[6];
  double t0_nonlin_tunableEnvironment_f5;
  double t0_nonlin_tunableEnvironment_f4[6];
  bool guard1 = false;
  evalOK = true;
  obj->numEvals = 0;
  idx = 0;
  emxInit_real_T(&t0_nonlin_tunableEnvironment_f2, 2);
  exitg1 = false;
  while ((!exitg1) && (idx <= obj->nVar - 1)) {
    deltaX = std::abs(xk->data[idx]);
    if (!(deltaX > 1.0)) {
      deltaX = 1.0;
    }

    deltaX *= c_runTimeOptions_FiniteDifferen->data[idx] * (1.0 - 2.0 *
      static_cast<double>((xk->data[idx] < 0.0)));
    t0_nonlin_tunableEnvironment_f1 = obj->nonlin.tunableEnvironment.f1;
    t0_mEq = t0_nonlin_tunableEnvironment_f2->size[0] *
      t0_nonlin_tunableEnvironment_f2->size[1];
    t0_nonlin_tunableEnvironment_f2->size[0] = 6;
    t0_nonlin_tunableEnvironment_f2->size[1] = obj->
      nonlin.tunableEnvironment.f2->size[1];
    emxEnsureCapacity_real_T(t0_nonlin_tunableEnvironment_f2, t0_mEq);
    loop_ub = obj->nonlin.tunableEnvironment.f2->size[0] *
      obj->nonlin.tunableEnvironment.f2->size[1];
    for (t0_mEq = 0; t0_mEq < loop_ub; t0_mEq++) {
      t0_nonlin_tunableEnvironment_f2->data[t0_mEq] =
        obj->nonlin.tunableEnvironment.f2->data[t0_mEq];
    }

    for (t0_mEq = 0; t0_mEq < 6; t0_mEq++) {
      t0_nonlin_tunableEnvironment_f3[t0_mEq] =
        obj->nonlin.tunableEnvironment.f3[t0_mEq];
    }

    for (t0_mEq = 0; t0_mEq < 6; t0_mEq++) {
      t0_nonlin_tunableEnvironment_f4[t0_mEq] =
        obj->nonlin.tunableEnvironment.f4[t0_mEq];
    }

    t0_nonlin_tunableEnvironment_f5 = obj->nonlin.tunableEnvironment.f5;
    loop_ub = obj->mIneq;
    t0_mEq = obj->mEq;
    evalOK = finDiffEvalAndChkErr(t0_nonlin_tunableEnvironment_f1,
      t0_nonlin_tunableEnvironment_f2, t0_nonlin_tunableEnvironment_f3,
      t0_nonlin_tunableEnvironment_f4, t0_nonlin_tunableEnvironment_f5, loop_ub,
      t0_mEq, &obj->f_1, obj->cIneq_1, obj->cEq_1, idx + 1, deltaX, xk);
    obj->numEvals++;
    guard1 = false;
    if (!evalOK) {
      deltaX = -deltaX;
      t0_nonlin_tunableEnvironment_f1 = obj->nonlin.tunableEnvironment.f1;
      t0_mEq = t0_nonlin_tunableEnvironment_f2->size[0] *
        t0_nonlin_tunableEnvironment_f2->size[1];
      t0_nonlin_tunableEnvironment_f2->size[0] = 6;
      t0_nonlin_tunableEnvironment_f2->size[1] =
        obj->nonlin.tunableEnvironment.f2->size[1];
      emxEnsureCapacity_real_T(t0_nonlin_tunableEnvironment_f2, t0_mEq);
      loop_ub = obj->nonlin.tunableEnvironment.f2->size[0] *
        obj->nonlin.tunableEnvironment.f2->size[1];
      for (t0_mEq = 0; t0_mEq < loop_ub; t0_mEq++) {
        t0_nonlin_tunableEnvironment_f2->data[t0_mEq] =
          obj->nonlin.tunableEnvironment.f2->data[t0_mEq];
      }

      for (t0_mEq = 0; t0_mEq < 6; t0_mEq++) {
        t0_nonlin_tunableEnvironment_f3[t0_mEq] =
          obj->nonlin.tunableEnvironment.f3[t0_mEq];
      }

      for (t0_mEq = 0; t0_mEq < 6; t0_mEq++) {
        t0_nonlin_tunableEnvironment_f4[t0_mEq] =
          obj->nonlin.tunableEnvironment.f4[t0_mEq];
      }

      t0_nonlin_tunableEnvironment_f5 = obj->nonlin.tunableEnvironment.f5;
      loop_ub = obj->mIneq;
      t0_mEq = obj->mEq;
      evalOK = finDiffEvalAndChkErr(t0_nonlin_tunableEnvironment_f1,
        t0_nonlin_tunableEnvironment_f2, t0_nonlin_tunableEnvironment_f3,
        t0_nonlin_tunableEnvironment_f4, t0_nonlin_tunableEnvironment_f5,
        loop_ub, t0_mEq, &obj->f_1, obj->cIneq_1, obj->cEq_1, idx + 1, deltaX,
        xk);
      obj->numEvals++;
      if (!evalOK) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      gradf->data[idx] = (obj->f_1 - fCurrent) / deltaX;
      t0_mEq = obj->mIneq;
      for (loop_ub = 0; loop_ub < t0_mEq; loop_ub++) {
        JacCineqTrans->data[idx + JacCineqTrans->size[0] * ((CineqColStart +
          loop_ub) - 1)] = (obj->cIneq_1->data[loop_ub] - cIneqCurrent->data
                            [(ineq0 + loop_ub) - 1]) / deltaX;
      }

      t0_mEq = obj->mEq;
      for (loop_ub = 0; loop_ub < t0_mEq; loop_ub++) {
        JacCeqTrans->data[idx + JacCeqTrans->size[0] * ((CeqColStart + loop_ub)
          - 1)] = (obj->cEq_1->data[loop_ub] - cEqCurrent->data[(eq0 + loop_ub)
                   - 1]) / deltaX;
      }

      idx++;
    }
  }

  emxFree_real_T(&t0_nonlin_tunableEnvironment_f2);
  return evalOK;
}

//
// File trailer for computeFiniteDifferences.cpp
//
// [EOF]
//
