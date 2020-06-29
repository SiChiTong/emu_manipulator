//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: maxConstraintViolation.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "maxConstraintViolation.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "xgemv.h"
#include <cmath>

// Function Definitions

//
// Arguments    : h_struct_T *obj
//                const emxArray_real_T *x
// Return Type  : double
//
double maxConstraintViolation(h_struct_T *obj, const emxArray_real_T *x)
{
  double v;
  int mLB;
  int mIneq;
  int mEq;
  int offsetEq1;
  int idx;
  double u1;
  mLB = obj->sizes[3];
  switch (obj->probType) {
   case 2:
    v = 0.0;
    mIneq = obj->sizes[2] - 1;
    mEq = obj->sizes[1] - 1;
    for (offsetEq1 = 0; offsetEq1 <= mIneq; offsetEq1++) {
      obj->maxConstrWorkspace->data[offsetEq1] = obj->bineq->data[offsetEq1];
    }

    b_xgemv(obj->nVarOrig, obj->sizes[2], obj->Aineq, obj->ldA, x,
            obj->maxConstrWorkspace);
    for (idx = 0; idx <= mIneq; idx++) {
      obj->maxConstrWorkspace->data[idx] -= x->data[obj->nVarOrig + idx];
      if ((!(v > obj->maxConstrWorkspace->data[idx])) && (!rtIsNaN
           (obj->maxConstrWorkspace->data[idx]))) {
        v = obj->maxConstrWorkspace->data[idx];
      }
    }

    for (offsetEq1 = 0; offsetEq1 <= mEq; offsetEq1++) {
      obj->maxConstrWorkspace->data[offsetEq1] = obj->beq->data[offsetEq1];
    }

    b_xgemv(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x,
            obj->maxConstrWorkspace);
    offsetEq1 = obj->nVarOrig + obj->sizes[2];
    mIneq = offsetEq1 + obj->sizes[1];
    for (idx = 0; idx <= mEq; idx++) {
      obj->maxConstrWorkspace->data[idx] = (obj->maxConstrWorkspace->data[idx] -
        x->data[offsetEq1 + idx]) + x->data[mIneq + idx];
      u1 = std::abs(obj->maxConstrWorkspace->data[idx]);
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
    break;

   default:
    v = 0.0;
    mIneq = obj->sizes[2] - 1;
    mEq = obj->sizes[1] - 1;
    for (offsetEq1 = 0; offsetEq1 <= mIneq; offsetEq1++) {
      obj->maxConstrWorkspace->data[offsetEq1] = obj->bineq->data[offsetEq1];
    }

    b_xgemv(obj->nVar, obj->sizes[2], obj->Aineq, obj->ldA, x,
            obj->maxConstrWorkspace);
    for (idx = 0; idx <= mIneq; idx++) {
      if ((!(v > obj->maxConstrWorkspace->data[idx])) && (!rtIsNaN
           (obj->maxConstrWorkspace->data[idx]))) {
        v = obj->maxConstrWorkspace->data[idx];
      }
    }

    for (offsetEq1 = 0; offsetEq1 <= mEq; offsetEq1++) {
      obj->maxConstrWorkspace->data[offsetEq1] = obj->beq->data[offsetEq1];
    }

    b_xgemv(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x,
            obj->maxConstrWorkspace);
    for (idx = 0; idx <= mEq; idx++) {
      u1 = std::abs(obj->maxConstrWorkspace->data[idx]);
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
    break;
  }

  if (obj->sizes[3] > 0) {
    for (idx = 0; idx < mLB; idx++) {
      u1 = -x->data[obj->indexLB->data[idx] - 1] - obj->lb->data[obj->
        indexLB->data[idx] - 1];
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
  }

  return v;
}

//
// File trailer for maxConstraintViolation.cpp
//
// [EOF]
//
