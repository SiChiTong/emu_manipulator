//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factoryConstruct3.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "factoryConstruct3.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"

// Function Definitions

//
// Arguments    : int mIneq
//                int mEq
//                const emxArray_real_T *Aeq
//                int nVar
//                int nVarMax
//                int mConstrMax
//                h_struct_T *obj
// Return Type  : void
//
void d_factoryConstruct(int mIneq, int mEq, const emxArray_real_T *Aeq, int nVar,
  int nVarMax, int mConstrMax, h_struct_T *obj)
{
  emxArray_real_T *r;
  int k;
  int i;
  int obj_tmp[5];
  int i1;
  int x[6];
  int b_i;
  emxInit_real_T(&r, 1);
  k = mIneq + mEq;
  obj->mConstr = k;
  obj->mConstrOrig = k;
  obj->mConstrMax = mConstrMax;
  obj->nVar = nVar;
  obj->nVarOrig = nVar;
  obj->nVarMax = nVarMax;
  obj->ldA = nVarMax;
  i = obj->Aineq->size[0] * obj->Aineq->size[1];
  obj->Aineq->size[0] = nVarMax;
  obj->Aineq->size[1] = mIneq;
  emxEnsureCapacity_real_T(obj->Aineq, i);
  i = r->size[0];
  r->size[0] = mIneq;
  emxEnsureCapacity_real_T(r, i);
  for (i = 0; i < mIneq; i++) {
    r->data[i] = 1.7976931348623157E+308;
  }

  i = obj->bineq->size[0] * obj->bineq->size[1];
  obj->bineq->size[0] = r->size[0];
  obj->bineq->size[1] = 1;
  emxEnsureCapacity_real_T(obj->bineq, i);
  i = obj->Aeq->size[0] * obj->Aeq->size[1];
  obj->Aeq->size[0] = nVarMax;
  obj->Aeq->size[1] = mEq;
  emxEnsureCapacity_real_T(obj->Aeq, i);
  i = r->size[0];
  r->size[0] = mEq;
  emxEnsureCapacity_real_T(r, i);
  for (i = 0; i < mEq; i++) {
    r->data[i] = 1.7976931348623157E+308;
  }

  i = obj->beq->size[0] * obj->beq->size[1];
  obj->beq->size[0] = r->size[0];
  obj->beq->size[1] = 1;
  emxEnsureCapacity_real_T(obj->beq, i);
  i = obj->lb->size[0];
  obj->lb->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->lb, i);
  i = obj->ub->size[0];
  obj->ub->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->ub, i);
  i = obj->indexLB->size[0];
  obj->indexLB->size[0] = nVarMax;
  emxEnsureCapacity_int32_T(obj->indexLB, i);
  i = obj->indexUB->size[0];
  obj->indexUB->size[0] = nVarMax;
  emxEnsureCapacity_int32_T(obj->indexUB, i);
  i = obj->indexFixed->size[0];
  obj->indexFixed->size[0] = nVarMax;
  emxEnsureCapacity_int32_T(obj->indexFixed, i);
  obj->mEqRemoved = 0;
  i = obj->indexEqRemoved->size[0];
  obj->indexEqRemoved->size[0] = mEq;
  emxEnsureCapacity_int32_T(obj->indexEqRemoved, i);
  i = obj->ATwset->size[0] * obj->ATwset->size[1];
  obj->ATwset->size[0] = nVarMax;
  obj->ATwset->size[1] = mConstrMax;
  emxEnsureCapacity_real_T(obj->ATwset, i);
  i = obj->bwset->size[0];
  obj->bwset->size[0] = mConstrMax;
  emxEnsureCapacity_real_T(obj->bwset, i);
  obj->nActiveConstr = 0;
  i = obj->maxConstrWorkspace->size[0];
  obj->maxConstrWorkspace->size[0] = mConstrMax;
  emxEnsureCapacity_real_T(obj->maxConstrWorkspace, i);
  obj_tmp[0] = 0;
  obj_tmp[1] = mEq;
  obj_tmp[2] = mIneq;
  obj_tmp[3] = 0;
  obj_tmp[4] = 0;
  obj->sizesPhaseOne[0] = 0;
  obj->sizesPhaseOne[1] = mEq;
  obj->sizesPhaseOne[2] = mIneq;
  obj->sizesPhaseOne[3] = 1;
  obj->sizesPhaseOne[4] = 0;
  obj->sizesRegularized[0] = 0;
  obj->sizesRegularized[1] = mEq;
  obj->sizesRegularized[2] = mIneq;
  i = mIneq + (mEq << 1);
  obj->sizesRegularized[3] = i;
  obj->sizesRegularized[4] = 0;
  obj->sizesRegPhaseOne[0] = 0;
  obj->sizesRegPhaseOne[1] = mEq;
  obj->sizesRegPhaseOne[2] = mIneq;
  i1 = i + 1;
  obj->sizesRegPhaseOne[3] = i1;
  obj->sizesRegPhaseOne[4] = 0;
  x[0] = 1;
  x[1] = 0;
  x[2] = mEq;
  x[3] = mIneq;
  x[4] = 0;
  x[5] = 0;
  emxFree_real_T(&r);
  for (k = 0; k < 5; k++) {
    obj->sizes[k] = obj_tmp[k];
    obj->sizesNormal[k] = obj_tmp[k];
    x[k + 1] += x[k];
  }

  for (b_i = 0; b_i < 6; b_i++) {
    obj->isActiveIdx[b_i] = x[b_i];
    obj->isActiveIdxNormal[b_i] = x[b_i];
  }

  x[0] = 1;
  x[1] = 0;
  x[2] = mEq;
  x[3] = mIneq;
  x[4] = 1;
  x[5] = 0;
  for (k = 0; k < 5; k++) {
    x[k + 1] += x[k];
  }

  for (b_i = 0; b_i < 6; b_i++) {
    obj->isActiveIdxPhaseOne[b_i] = x[b_i];
  }

  x[0] = 1;
  x[1] = 0;
  x[2] = mEq;
  x[3] = mIneq;
  x[4] = i;
  x[5] = 0;
  for (k = 0; k < 5; k++) {
    x[k + 1] += x[k];
  }

  for (b_i = 0; b_i < 6; b_i++) {
    obj->isActiveIdxRegularized[b_i] = x[b_i];
  }

  x[0] = 1;
  x[1] = 0;
  x[2] = mEq;
  x[3] = mIneq;
  x[4] = i1;
  x[5] = 0;
  for (k = 0; k < 5; k++) {
    x[k + 1] += x[k];
  }

  for (b_i = 0; b_i < 6; b_i++) {
    obj->isActiveIdxRegPhaseOne[b_i] = x[b_i];
  }

  i = obj->isActiveConstr->size[0];
  obj->isActiveConstr->size[0] = mConstrMax;
  emxEnsureCapacity_boolean_T(obj->isActiveConstr, i);
  i = obj->Wid->size[0];
  obj->Wid->size[0] = mConstrMax;
  emxEnsureCapacity_int32_T(obj->Wid, i);
  i = obj->Wlocalidx->size[0];
  obj->Wlocalidx->size[0] = mConstrMax;
  emxEnsureCapacity_int32_T(obj->Wlocalidx, i);
  for (b_i = 0; b_i < 5; b_i++) {
    obj->nWConstr[b_i] = 0;
  }

  obj->probType = 3;
  obj->SLACK0 = 1.0E-5;
  for (k = 0; k < 12; k++) {
    for (b_i = 0; b_i < nVar; b_i++) {
      obj->Aeq->data[b_i + obj->Aeq->size[0] * k] = Aeq->data[k + 12 * b_i];
    }
  }
}

//
// File trailer for factoryConstruct3.cpp
//
// [EOF]
//
