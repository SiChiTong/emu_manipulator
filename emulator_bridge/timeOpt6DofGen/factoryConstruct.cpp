//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factoryConstruct.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "factoryConstruct.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"

// Function Definitions

//
// Arguments    : int nVarMax
//                int mConstrMax
//                int mIneq
//                int mEq
//                const int xShape[2]
//                int mNonlinIneq
//                int mNonlinEq
//                e_struct_T *obj
// Return Type  : void
//
void factoryConstruct(int nVarMax, int mConstrMax, int mIneq, int mEq, const int
                      xShape[2], int mNonlinIneq, int mNonlinEq, e_struct_T *obj)
{
  int i;
  obj->nVarMax = nVarMax;
  obj->mNonlinIneq = mNonlinIneq;
  obj->mNonlinEq = mNonlinEq;
  obj->mIneq = mIneq;
  obj->mEq = mEq;
  obj->iNonIneq0 = (mIneq - mNonlinIneq) + 1;
  obj->iNonEq0 = (mEq - mNonlinEq) + 1;
  obj->sqpFval = 0.0;
  obj->sqpFval_old = 0.0;
  i = obj->xstarsqp->size[0] * obj->xstarsqp->size[1];
  obj->xstarsqp->size[0] = 1;
  obj->xstarsqp->size[1] = xShape[1];
  emxEnsureCapacity_real_T(obj->xstarsqp, i);
  i = obj->xstarsqp_old->size[0] * obj->xstarsqp_old->size[1];
  obj->xstarsqp_old->size[0] = 1;
  obj->xstarsqp_old->size[1] = xShape[1];
  emxEnsureCapacity_real_T(obj->xstarsqp_old, i);
  i = obj->cIneq->size[0];
  obj->cIneq->size[0] = mIneq;
  emxEnsureCapacity_real_T(obj->cIneq, i);
  i = obj->cIneq_old->size[0];
  obj->cIneq_old->size[0] = mIneq;
  emxEnsureCapacity_real_T(obj->cIneq_old, i);
  i = obj->cEq->size[0];
  obj->cEq->size[0] = mEq;
  emxEnsureCapacity_real_T(obj->cEq, i);
  i = obj->cEq_old->size[0];
  obj->cEq_old->size[0] = mEq;
  emxEnsureCapacity_real_T(obj->cEq_old, i);
  i = obj->grad->size[0];
  obj->grad->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->grad, i);
  i = obj->grad_old->size[0];
  obj->grad_old->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->grad_old, i);
  obj->FunctionEvaluations = 0;
  obj->sqpIterations = 0;
  obj->sqpExitFlag = 0;
  i = obj->lambdasqp->size[0];
  obj->lambdasqp->size[0] = mConstrMax;
  emxEnsureCapacity_real_T(obj->lambdasqp, i);
  for (i = 0; i < mConstrMax; i++) {
    obj->lambdasqp->data[i] = 0.0;
  }

  i = obj->lambdasqp_old->size[0];
  obj->lambdasqp_old->size[0] = mConstrMax;
  emxEnsureCapacity_real_T(obj->lambdasqp_old, i);
  obj->steplength = 1.0;
  i = obj->delta_x->size[0];
  obj->delta_x->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->delta_x, i);
  for (i = 0; i < nVarMax; i++) {
    obj->delta_x->data[i] = 0.0;
  }

  i = obj->socDirection->size[0];
  obj->socDirection->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->socDirection, i);
  i = obj->lambda_old->size[0];
  obj->lambda_old->size[0] = mConstrMax;
  emxEnsureCapacity_real_T(obj->lambda_old, i);
  i = obj->workingset_old->size[0];
  obj->workingset_old->size[0] = mConstrMax;
  emxEnsureCapacity_int32_T(obj->workingset_old, i);
  i = obj->JacCineqTrans_old->size[0] * obj->JacCineqTrans_old->size[1];
  obj->JacCineqTrans_old->size[0] = nVarMax;
  obj->JacCineqTrans_old->size[1] = mNonlinIneq;
  emxEnsureCapacity_real_T(obj->JacCineqTrans_old, i);
  i = obj->JacCeqTrans_old->size[0] * obj->JacCeqTrans_old->size[1];
  obj->JacCeqTrans_old->size[0] = nVarMax;
  obj->JacCeqTrans_old->size[1] = mNonlinEq;
  emxEnsureCapacity_real_T(obj->JacCeqTrans_old, i);
  i = obj->gradLag->size[0];
  obj->gradLag->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->gradLag, i);
  i = obj->delta_gradLag->size[0];
  obj->delta_gradLag->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->delta_gradLag, i);
  i = obj->xstar->size[0];
  obj->xstar->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->xstar, i);
  obj->fstar = 0.0;
  i = obj->lambda->size[0];
  obj->lambda->size[0] = mConstrMax;
  emxEnsureCapacity_real_T(obj->lambda, i);
  for (i = 0; i < mConstrMax; i++) {
    obj->lambda->data[i] = 0.0;
  }

  obj->state = 0;
  obj->maxConstr = 0.0;
  obj->iterations = 0;
  i = obj->searchDir->size[0];
  obj->searchDir->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->searchDir, i);
}

//
// File trailer for factoryConstruct.cpp
//
// [EOF]
//
