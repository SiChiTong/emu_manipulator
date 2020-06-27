//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: updateWorkingSetForNewQP.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "updateWorkingSetForNewQP.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *xk
//                h_struct_T *WorkingSet
//                const double cIneq[12]
//                int mEq
//                int mNonlinEq
//                const emxArray_real_T *cEq
//                int mLB
//                const emxArray_real_T *lb
//                int mUB
//                int mFixed
// Return Type  : void
//
void b_updateWorkingSetForNewQP(const emxArray_real_T *xk, h_struct_T
  *WorkingSet, const double cIneq[12], int mEq, int mNonlinEq, const
  emxArray_real_T *cEq, int mLB, const emxArray_real_T *lb, int mUB, int mFixed)
{
  int nVar;
  int idx;
  int mLinEq;
  int iw0;
  int k;
  int b_k;
  int i;
  int ineqStart;
  nVar = WorkingSet->nVar - 1;
  for (idx = 0; idx < mEq; idx++) {
    WorkingSet->beq->data[idx] = -cEq->data[idx];
    WorkingSet->bwset->data[mFixed + idx] = WorkingSet->beq->data[idx];
  }

  mLinEq = mEq - mNonlinEq;
  iw0 = WorkingSet->ldA * (mFixed + mLinEq);
  mLinEq *= WorkingSet->ldA;
  for (idx = 0; idx < mNonlinEq; idx++) {
    for (k = 0; k <= nVar; k++) {
      b_k = k + 1;
      WorkingSet->ATwset->data[(iw0 + b_k) - 1] = WorkingSet->Aeq->data[(mLinEq
        + b_k) - 1];
    }

    iw0 += WorkingSet->ldA;
    mLinEq += WorkingSet->ldA;
  }

  for (idx = 0; idx < 12; idx++) {
    WorkingSet->bineq[idx] = -cIneq[idx];
  }

  for (idx = 0; idx < mLB; idx++) {
    WorkingSet->lb->data[WorkingSet->indexLB->data[idx] - 1] = -lb->
      data[WorkingSet->indexLB->data[idx] - 1] + xk->data[WorkingSet->
      indexLB->data[idx] - 1];
  }

  for (idx = 0; idx < mUB; idx++) {
    WorkingSet->ub->data[WorkingSet->indexUB->data[idx] - 1] = rtInf - xk->
      data[WorkingSet->indexUB->data[idx] - 1];
  }

  for (idx = 0; idx < mFixed; idx++) {
    mLinEq = WorkingSet->indexFixed->data[idx];
    WorkingSet->ub->data[WorkingSet->indexFixed->data[idx] - 1] = rtInf -
      xk->data[WorkingSet->indexFixed->data[idx] - 1];
    WorkingSet->bwset->data[idx] = rtInf - xk->data[mLinEq - 1];
  }

  i = mFixed + mEq;
  if (WorkingSet->nActiveConstr > i) {
    ineqStart = i + 1;
    i = WorkingSet->nActiveConstr;
    for (idx = ineqStart; idx <= i; idx++) {
      mLinEq = WorkingSet->Wlocalidx->data[idx - 1];
      switch (WorkingSet->Wid->data[idx - 1]) {
       case 4:
        WorkingSet->bwset->data[idx - 1] = WorkingSet->lb->data
          [WorkingSet->Wlocalidx->data[idx - 1] - 1];
        break;

       case 5:
        WorkingSet->bwset->data[idx - 1] = WorkingSet->ub->data
          [WorkingSet->Wlocalidx->data[idx - 1] - 1];
        break;

       default:
        WorkingSet->bwset->data[idx - 1] = WorkingSet->bineq[mLinEq - 1];
        if (mLinEq >= 12) {
          mLinEq = WorkingSet->ldA * (idx - 1);
          iw0 = WorkingSet->ldA * 11;
          for (k = 0; k <= nVar; k++) {
            b_k = k + 1;
            WorkingSet->ATwset->data[(mLinEq + b_k) - 1] = WorkingSet->
              Aineq->data[(iw0 + b_k) - 1];
          }
        }
        break;
      }
    }
  }
}

//
// Arguments    : const emxArray_real_T *xk
//                h_struct_T *WorkingSet
//                const double cIneq[12]
//                int mEq
//                int mNonlinEq
//                const emxArray_real_T *cEq
//                int mLB
//                const emxArray_real_T *lb
//                int mUB
//                int mFixed
// Return Type  : void
//
void updateWorkingSetForNewQP(const emxArray_real_T *xk, h_struct_T *WorkingSet,
  const double cIneq[12], int mEq, int mNonlinEq, const emxArray_real_T *cEq,
  int mLB, const emxArray_real_T *lb, int mUB, int mFixed)
{
  int nVar;
  int idx;
  int mLinEq;
  int iw0;
  int k;
  int b_k;
  nVar = WorkingSet->nVar;
  for (idx = 0; idx < mEq; idx++) {
    WorkingSet->beq->data[idx] = -cEq->data[idx];
    WorkingSet->bwset->data[mFixed + idx] = WorkingSet->beq->data[idx];
  }

  mLinEq = mEq - mNonlinEq;
  iw0 = WorkingSet->ldA * (mFixed + mLinEq);
  mLinEq *= WorkingSet->ldA;
  for (idx = 0; idx < mNonlinEq; idx++) {
    for (k = 0; k < nVar; k++) {
      b_k = k + 1;
      WorkingSet->ATwset->data[(iw0 + b_k) - 1] = WorkingSet->Aeq->data[(mLinEq
        + b_k) - 1];
    }

    iw0 += WorkingSet->ldA;
    mLinEq += WorkingSet->ldA;
  }

  for (idx = 0; idx < 12; idx++) {
    WorkingSet->bineq[idx] = -cIneq[idx];
  }

  for (idx = 0; idx < mLB; idx++) {
    WorkingSet->lb->data[WorkingSet->indexLB->data[idx] - 1] = -lb->
      data[WorkingSet->indexLB->data[idx] - 1] + xk->data[WorkingSet->
      indexLB->data[idx] - 1];
  }

  for (idx = 0; idx < mUB; idx++) {
    WorkingSet->ub->data[WorkingSet->indexUB->data[idx] - 1] = rtInf - xk->
      data[WorkingSet->indexUB->data[idx] - 1];
  }

  for (idx = 0; idx < mFixed; idx++) {
    mLinEq = WorkingSet->indexFixed->data[idx];
    WorkingSet->ub->data[WorkingSet->indexFixed->data[idx] - 1] = rtInf -
      xk->data[WorkingSet->indexFixed->data[idx] - 1];
    WorkingSet->bwset->data[idx] = rtInf - xk->data[mLinEq - 1];
  }

  mLinEq = mFixed + mEq;
  if (0 > mLinEq) {
    mLinEq++;
    for (idx = mLinEq; idx < 1; idx++) {
      abort();
    }
  }
}

//
// File trailer for updateWorkingSetForNewQP.cpp
//
// [EOF]
//
