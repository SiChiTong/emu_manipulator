//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: maxConstraintViolation.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
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
double b_maxConstraintViolation(h_struct_T *obj, const emxArray_real_T *x)
{
  double v;
  int mLB;
  int mUB;
  int mFixed;
  int mEq;
  int offsetEq2;
  int idx;
  double u1;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  switch (obj->probType) {
   case 2:
    v = 0.0;
    mEq = obj->sizes[1] - 1;
    for (offsetEq2 = 0; offsetEq2 < 12; offsetEq2++) {
      obj->maxConstrWorkspace->data[offsetEq2] = obj->bineq[offsetEq2];
    }

    c_xgemv(obj->nVarOrig, obj->Aineq, obj->ldA, x, obj->maxConstrWorkspace);
    for (idx = 0; idx < 12; idx++) {
      obj->maxConstrWorkspace->data[idx] -= x->data[obj->nVarOrig + idx];
      if ((!(v > obj->maxConstrWorkspace->data[idx])) && (!rtIsNaN
           (obj->maxConstrWorkspace->data[idx]))) {
        v = obj->maxConstrWorkspace->data[idx];
      }
    }

    for (offsetEq2 = 0; offsetEq2 <= mEq; offsetEq2++) {
      obj->maxConstrWorkspace->data[offsetEq2] = obj->beq->data[offsetEq2];
    }

    xgemv(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x,
          obj->maxConstrWorkspace);
    offsetEq2 = (obj->nVarOrig + obj->sizes[1]) + 12;
    for (idx = 0; idx <= mEq; idx++) {
      obj->maxConstrWorkspace->data[idx] = (obj->maxConstrWorkspace->data[idx] -
        x->data[(obj->nVarOrig + idx) + 12]) + x->data[offsetEq2 + idx];
      u1 = std::abs(obj->maxConstrWorkspace->data[idx]);
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
    break;

   default:
    v = 0.0;
    mEq = obj->sizes[1] - 1;
    for (offsetEq2 = 0; offsetEq2 < 12; offsetEq2++) {
      obj->maxConstrWorkspace->data[offsetEq2] = obj->bineq[offsetEq2];
    }

    c_xgemv(obj->nVar, obj->Aineq, obj->ldA, x, obj->maxConstrWorkspace);
    for (idx = 0; idx < 12; idx++) {
      if ((!(v > obj->maxConstrWorkspace->data[idx])) && (!rtIsNaN
           (obj->maxConstrWorkspace->data[idx]))) {
        v = obj->maxConstrWorkspace->data[idx];
      }
    }

    for (offsetEq2 = 0; offsetEq2 <= mEq; offsetEq2++) {
      obj->maxConstrWorkspace->data[offsetEq2] = obj->beq->data[offsetEq2];
    }

    xgemv(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x,
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

  if (obj->sizes[4] > 0) {
    for (idx = 0; idx < mUB; idx++) {
      u1 = x->data[obj->indexUB->data[idx] - 1] - obj->ub->data[obj->
        indexUB->data[idx] - 1];
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
  }

  if (obj->sizes[0] > 0) {
    for (idx = 0; idx < mFixed; idx++) {
      offsetEq2 = obj->indexFixed->data[idx] - 1;
      u1 = std::abs(x->data[offsetEq2] - obj->ub->data[offsetEq2]);
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
  }

  return v;
}

//
// Arguments    : h_struct_T *obj
//                const emxArray_real_T *x
//                int ix0
// Return Type  : double
//
double maxConstraintViolation(h_struct_T *obj, const emxArray_real_T *x, int ix0)
{
  double v;
  int mLB;
  int mUB;
  int mFixed;
  int mEq;
  int k;
  int offsetEq2;
  double u1;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  switch (obj->probType) {
   case 2:
    v = 0.0;
    mEq = obj->sizes[1] - 1;
    for (k = 0; k < 12; k++) {
      obj->maxConstrWorkspace->data[k] = obj->bineq[k];
    }

    d_xgemv(obj->nVarOrig, obj->Aineq, obj->ldA, x, ix0, obj->maxConstrWorkspace);
    for (k = 0; k < 12; k++) {
      obj->maxConstrWorkspace->data[k] -= x->data[((ix0 + obj->nVarOrig) + k) -
        1];
      if ((!(v > obj->maxConstrWorkspace->data[k])) && (!rtIsNaN
           (obj->maxConstrWorkspace->data[k]))) {
        v = obj->maxConstrWorkspace->data[k];
      }
    }

    for (k = 0; k <= mEq; k++) {
      obj->maxConstrWorkspace->data[k] = obj->beq->data[k];
    }

    e_xgemv(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x, ix0,
            obj->maxConstrWorkspace);
    offsetEq2 = (obj->nVarOrig + obj->sizes[1]) + 11;
    for (k = 0; k <= mEq; k++) {
      obj->maxConstrWorkspace->data[k] = (obj->maxConstrWorkspace->data[k] -
        x->data[((ix0 + obj->nVarOrig) + k) + 11]) + x->data[(ix0 + offsetEq2) +
        k];
      u1 = std::abs(obj->maxConstrWorkspace->data[k]);
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
    break;

   default:
    v = 0.0;
    mEq = obj->sizes[1] - 1;
    for (k = 0; k < 12; k++) {
      obj->maxConstrWorkspace->data[k] = obj->bineq[k];
    }

    d_xgemv(obj->nVar, obj->Aineq, obj->ldA, x, ix0, obj->maxConstrWorkspace);
    for (k = 0; k < 12; k++) {
      if ((!(v > obj->maxConstrWorkspace->data[k])) && (!rtIsNaN
           (obj->maxConstrWorkspace->data[k]))) {
        v = obj->maxConstrWorkspace->data[k];
      }
    }

    for (k = 0; k <= mEq; k++) {
      obj->maxConstrWorkspace->data[k] = obj->beq->data[k];
    }

    e_xgemv(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x, ix0,
            obj->maxConstrWorkspace);
    for (k = 0; k <= mEq; k++) {
      u1 = std::abs(obj->maxConstrWorkspace->data[k]);
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
    break;
  }

  if (obj->sizes[3] > 0) {
    for (k = 0; k < mLB; k++) {
      u1 = -x->data[(ix0 + obj->indexLB->data[k]) - 2] - obj->lb->data
        [obj->indexLB->data[k] - 1];
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
  }

  if (obj->sizes[4] > 0) {
    for (k = 0; k < mUB; k++) {
      u1 = x->data[(ix0 + obj->indexUB->data[k]) - 2] - obj->ub->data
        [obj->indexUB->data[k] - 1];
      if ((!(v > u1)) && (!rtIsNaN(u1))) {
        v = u1;
      }
    }
  }

  if (obj->sizes[0] > 0) {
    for (k = 0; k < mFixed; k++) {
      u1 = std::abs(x->data[(ix0 + obj->indexFixed->data[k]) - 2] - obj->
                    ub->data[obj->indexFixed->data[k] - 1]);
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
