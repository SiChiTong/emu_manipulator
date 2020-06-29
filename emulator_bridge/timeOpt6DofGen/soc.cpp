//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: soc.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "soc.h"
#include "addAeqConstr.h"
#include "addBoundToActiveSetMatrix_.h"
#include "driver1.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xnrm2.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *Hessian
//                const emxArray_real_T *grad
//                e_struct_T *TrialState
//                c_struct_T *memspace
//                h_struct_T *WorkingSet
//                i_struct_T *QRManager
//                k_struct_T *CholManager
//                g_struct_T *QPObjective
//                const b_struct_T qpoptions
// Return Type  : bool
//
bool soc(const emxArray_real_T *Hessian, const emxArray_real_T *grad, e_struct_T
         *TrialState, c_struct_T *memspace, h_struct_T *WorkingSet, i_struct_T
         *QRManager, k_struct_T *CholManager, g_struct_T *QPObjective, const
         b_struct_T qpoptions)
{
  bool success;
  emxArray_real_T *y;
  int nWIneq_old;
  int nWLower_old;
  int nWUpper_old;
  int nVar;
  int mConstrMax;
  int mLB;
  int idx_Aineq;
  int k;
  emxArray_int32_T *workspace_int;
  int mEq;
  int mIneq;
  int idxIneqOffset;
  int idx;
  int iy;
  int idx_upper;
  int ix;
  double c;
  int idx_Partition;
  emxInit_real_T(&y, 2);
  nWIneq_old = WorkingSet->nWConstr[2];
  nWLower_old = WorkingSet->nWConstr[3];
  nWUpper_old = WorkingSet->nWConstr[4];
  nVar = WorkingSet->nVar - 1;
  mConstrMax = WorkingSet->mConstrMax - 1;
  mLB = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = TrialState->xstarsqp->size[1];
  emxEnsureCapacity_real_T(y, mLB);
  idx_Aineq = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
  for (mLB = 0; mLB < idx_Aineq; mLB++) {
    y->data[mLB] = TrialState->xstarsqp->data[mLB];
  }

  for (k = 0; k <= nVar; k++) {
    y->data[k] = TrialState->xstarsqp_old->data[k];
  }

  mLB = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
  TrialState->xstarsqp->size[0] = y->size[0];
  TrialState->xstarsqp->size[1] = y->size[1];
  emxEnsureCapacity_real_T(TrialState->xstarsqp, mLB);
  idx_Aineq = y->size[0] * y->size[1];
  for (mLB = 0; mLB < idx_Aineq; mLB++) {
    TrialState->xstarsqp->data[mLB] = y->data[mLB];
  }

  for (k = 0; k <= nVar; k++) {
    TrialState->socDirection->data[k] = TrialState->xstar->data[k];
  }

  for (k = 0; k <= mConstrMax; k++) {
    TrialState->lambda_old->data[k] = TrialState->lambda->data[k];
  }

  emxInit_int32_T(&workspace_int, 1);
  mLB = workspace_int->size[0];
  workspace_int->size[0] = TrialState->workingset_old->size[0];
  emxEnsureCapacity_int32_T(workspace_int, mLB);
  idx_Aineq = TrialState->workingset_old->size[0];
  for (mLB = 0; mLB < idx_Aineq; mLB++) {
    workspace_int->data[mLB] = TrialState->workingset_old->data[mLB];
  }

  mEq = WorkingSet->sizes[1] - 1;
  mIneq = WorkingSet->sizes[2];
  idxIneqOffset = WorkingSet->isActiveIdx[2];
  if (WorkingSet->sizes[1] > 0) {
    for (idx = 0; idx <= mEq; idx++) {
      WorkingSet->beq->data[idx] = -TrialState->cEq->data[idx];
    }

    idx_Aineq = WorkingSet->ldA;
    if (WorkingSet->nVar != 0) {
      iy = 0;
      mLB = WorkingSet->ldA * (WorkingSet->sizes[1] - 1) + 1;
      for (idx_upper = 1; idx_Aineq < 0 ? idx_upper >= mLB : idx_upper <= mLB;
           idx_upper += idx_Aineq) {
        ix = 0;
        c = 0.0;
        idx_Partition = (idx_upper + WorkingSet->nVar) - 1;
        for (k = idx_upper; k <= idx_Partition; k++) {
          c += WorkingSet->Aeq->data[k - 1] * TrialState->searchDir->data[ix];
          ix++;
        }

        WorkingSet->beq->data[iy] += c;
        iy++;
      }
    }

    for (k = 0; k <= mEq; k++) {
      WorkingSet->bwset->data[k] = WorkingSet->beq->data[k];
    }
  }

  for (idx = 0; idx < mIneq; idx++) {
    WorkingSet->bineq->data[idx] = -TrialState->cIneq->data[idx];
  }

  idx_Aineq = WorkingSet->ldA;
  if (WorkingSet->nVar != 0) {
    iy = 0;
    mLB = WorkingSet->ldA * (WorkingSet->sizes[2] - 1) + 1;
    for (idx_upper = 1; idx_Aineq < 0 ? idx_upper >= mLB : idx_upper <= mLB;
         idx_upper += idx_Aineq) {
      ix = 0;
      c = 0.0;
      idx_Partition = (idx_upper + WorkingSet->nVar) - 1;
      for (k = idx_upper; k <= idx_Partition; k++) {
        c += WorkingSet->Aineq->data[k - 1] * TrialState->searchDir->data[ix];
        ix++;
      }

      WorkingSet->bineq->data[iy] += c;
      iy++;
    }
  }

  idx_Aineq = 1;
  iy = WorkingSet->sizes[2] + 1;
  idx_upper = (WorkingSet->sizes[2] + WorkingSet->sizes[3]) + 1;
  mLB = WorkingSet->nActiveConstr;
  for (idx = idxIneqOffset; idx <= mLB; idx++) {
    ix = WorkingSet->Wlocalidx->data[idx - 1];
    switch (WorkingSet->Wid->data[idx - 1]) {
     case 3:
      idx_Partition = idx_Aineq;
      idx_Aineq++;
      WorkingSet->bwset->data[idx - 1] = WorkingSet->bineq->data[ix - 1];
      break;

     case 4:
      idx_Partition = iy;
      iy++;
      break;

     default:
      idx_Partition = idx_upper;
      idx_upper++;
      break;
    }

    workspace_int->data[idx_Partition - 1] = ix;
  }

  mLB = TrialState->workingset_old->size[0];
  TrialState->workingset_old->size[0] = workspace_int->size[0];
  emxEnsureCapacity_int32_T(TrialState->workingset_old, mLB);
  idx_Aineq = workspace_int->size[0];
  for (mLB = 0; mLB < idx_Aineq; mLB++) {
    TrialState->workingset_old->data[mLB] = workspace_int->data[mLB];
  }

  emxFree_int32_T(&workspace_int);
  for (k = 0; k <= nVar; k++) {
    TrialState->xstar->data[k] = y->data[k];
  }

  emxFree_real_T(&y);
  b_driver(Hessian, grad, TrialState, memspace, WorkingSet, QRManager,
           CholManager, QPObjective, qpoptions);
  while ((WorkingSet->mEqRemoved > 0) && (WorkingSet->indexEqRemoved->
          data[WorkingSet->mEqRemoved - 1] >= TrialState->iNonEq0)) {
    addAeqConstr(WorkingSet, WorkingSet->indexEqRemoved->data
                 [WorkingSet->mEqRemoved - 1]);
    WorkingSet->mEqRemoved--;
  }

  for (idx = 0; idx <= nVar; idx++) {
    c = TrialState->socDirection->data[idx];
    TrialState->socDirection->data[idx] = TrialState->xstar->data[idx] -
      TrialState->socDirection->data[idx];
    TrialState->xstar->data[idx] = c;
  }

  success = (b_xnrm2(nVar + 1, TrialState->socDirection) <= 2.0 * b_xnrm2(nVar +
              1, TrialState->xstar));
  mEq = WorkingSet->sizes[1] - 1;
  mIneq = WorkingSet->sizes[2];
  mLB = WorkingSet->sizes[3];
  if (WorkingSet->sizes[1] > 0) {
    for (idx = 0; idx <= mEq; idx++) {
      WorkingSet->beq->data[idx] = -TrialState->cEq->data[idx];
      WorkingSet->bwset->data[idx] = WorkingSet->beq->data[idx];
    }
  }

  for (idx = 0; idx < mIneq; idx++) {
    WorkingSet->bineq->data[idx] = -TrialState->cIneq->data[idx];
  }

  if (!success) {
    idx_Aineq = (WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1]) + 1;
    iy = WorkingSet->nActiveConstr;
    for (idx_upper = idx_Aineq; idx_upper <= iy; idx_upper++) {
      WorkingSet->isActiveConstr->data[(WorkingSet->isActiveIdx[WorkingSet->
        Wid->data[idx_upper - 1] - 1] + WorkingSet->Wlocalidx->data[idx_upper -
        1]) - 2] = false;
    }

    WorkingSet->nWConstr[2] = 0;
    WorkingSet->nWConstr[3] = 0;
    WorkingSet->nWConstr[4] = 0;
    WorkingSet->nActiveConstr = WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1];
    for (idx = 0; idx < nWIneq_old; idx++) {
      idx_Aineq = TrialState->workingset_old->data[idx];
      WorkingSet->nWConstr[2]++;
      WorkingSet->isActiveConstr->data[(WorkingSet->isActiveIdx[2] + idx_Aineq)
        - 2] = true;
      WorkingSet->nActiveConstr++;
      WorkingSet->Wid->data[WorkingSet->nActiveConstr - 1] = 3;
      WorkingSet->Wlocalidx->data[WorkingSet->nActiveConstr - 1] = idx_Aineq;
      iy = WorkingSet->ldA * (idx_Aineq - 1);
      idx_upper = WorkingSet->ldA * (WorkingSet->nActiveConstr - 1);
      ix = WorkingSet->nVar;
      for (k = 0; k < ix; k++) {
        idx_Partition = k + 1;
        WorkingSet->ATwset->data[(idx_upper + idx_Partition) - 1] =
          WorkingSet->Aineq->data[(iy + idx_Partition) - 1];
      }

      WorkingSet->bwset->data[WorkingSet->nActiveConstr - 1] = WorkingSet->
        bineq->data[idx_Aineq - 1];
    }

    for (idx = 0; idx < nWLower_old; idx++) {
      addBoundToActiveSetMatrix_(WorkingSet, 4, TrialState->workingset_old->
        data[idx + mIneq]);
    }

    for (idx = 0; idx < nWUpper_old; idx++) {
      addBoundToActiveSetMatrix_(WorkingSet, 5, TrialState->workingset_old->
        data[(idx + mIneq) + mLB]);
    }

    for (k = 0; k <= mConstrMax; k++) {
      TrialState->lambda->data[k] = TrialState->lambda_old->data[k];
    }
  } else {
    sortLambdaQP(TrialState->lambda, WorkingSet->nActiveConstr,
                 WorkingSet->sizes, WorkingSet->isActiveIdx, WorkingSet->Wid,
                 WorkingSet->Wlocalidx, memspace->workspace_double);
  }

  return success;
}

//
// File trailer for soc.cpp
//
// [EOF]
//
