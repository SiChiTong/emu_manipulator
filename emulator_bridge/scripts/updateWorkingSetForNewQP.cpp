//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: updateWorkingSetForNewQP.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "updateWorkingSetForNewQP.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : h_struct_T *WorkingSet
//                int mIneq
//                int mNonlinIneq
//                const emxArray_real_T *cIneq
//                int mEq
//                int mNonlinEq
//                const emxArray_real_T *cEq
// Return Type  : void
//
void updateWorkingSetForNewQP(h_struct_T *WorkingSet, int mIneq, int mNonlinIneq,
  const emxArray_real_T *cIneq, int mEq, int mNonlinEq, const emxArray_real_T
  *cEq)
{
  int nVar;
  int idx;
  int iw0;
  int iEq0;
  int k;
  int b_k;
  int i;
  int iy0;
  nVar = WorkingSet->nVar - 1;
  for (idx = 0; idx < mEq; idx++) {
    WorkingSet->beq->data[idx] = -cEq->data[idx];
    WorkingSet->bwset->data[idx] = WorkingSet->beq->data[idx];
  }

  iw0 = WorkingSet->ldA * (mEq - mNonlinEq);
  iEq0 = iw0;
  for (idx = 0; idx < mNonlinEq; idx++) {
    for (k = 0; k <= nVar; k++) {
      b_k = k + 1;
      WorkingSet->ATwset->data[(iw0 + b_k) - 1] = WorkingSet->Aeq->data[(iEq0 +
        b_k) - 1];
    }

    iw0 += WorkingSet->ldA;
    iEq0 += WorkingSet->ldA;
  }

  for (idx = 0; idx < mIneq; idx++) {
    WorkingSet->bineq->data[idx] = -cIneq->data[idx];
  }

  if (WorkingSet->nActiveConstr > mEq) {
    iEq0 = mEq + 1;
    i = WorkingSet->nActiveConstr;
    for (idx = iEq0; idx <= i; idx++) {
      iw0 = WorkingSet->Wlocalidx->data[idx - 1];
      switch (WorkingSet->Wid->data[idx - 1]) {
       case 4:
        WorkingSet->bwset->data[idx - 1] = WorkingSet->lb->data
          [WorkingSet->Wlocalidx->data[idx - 1] - 1];
        break;

       case 5:
        WorkingSet->bwset->data[idx - 1] = 1.7976931348623157E+308;
        break;

       default:
        WorkingSet->bwset->data[idx - 1] = WorkingSet->bineq->data[iw0 - 1];
        if (iw0 >= mNonlinIneq) {
          iy0 = WorkingSet->ldA * (idx - 1);
          iw0 = WorkingSet->ldA * (iw0 - 1);
          for (k = 0; k <= nVar; k++) {
            b_k = k + 1;
            WorkingSet->ATwset->data[(iy0 + b_k) - 1] = WorkingSet->Aineq->data
              [(iw0 + b_k) - 1];
          }
        }
        break;
      }
    }
  }
}

//
// File trailer for updateWorkingSetForNewQP.cpp
//
// [EOF]
//
