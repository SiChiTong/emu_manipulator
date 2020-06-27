//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: removeDependentLinearEq.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "removeDependentLinearEq.h"
#include "ComputeNumDependentEq_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xgeqp3.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *Aeq
//                double beq[12]
//                int idxArray[12]
//                c_struct_T *memspace
//                e_struct_T *TrialState
//                h_struct_T *WorkingSet
//                i_struct_T *QRManager
//                g_struct_T *QPObjective
// Return Type  : int
//
int removeDependentLinearEq(const emxArray_real_T *Aeq, double beq[12], int
  idxArray[12], c_struct_T *memspace, e_struct_T *TrialState, h_struct_T
  *WorkingSet, i_struct_T *QRManager, g_struct_T *QPObjective)
{
  int nDepInd;
  int nVar;
  int mFixed;
  int mLinEq;
  int mTotalLinEq;
  int idx_local;
  int idx;
  int idx_global;
  int k;
  int i;
  int idxStart;
  emxArray_int32_T *workspace;
  int WorkingSet_tmp[5];
  int x[6];
  nVar = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0];
  mLinEq = 12;
  mTotalLinEq = WorkingSet->sizes[0] + 12;
  for (idx_local = 0; idx_local < mFixed; idx_local++) {
    for (idx = 1; idx < WorkingSet->indexFixed->data[idx_local]; idx++) {
      QRManager->QR->data[idx_local + QRManager->QR->size[0] * (idx - 1)] = 0.0;
    }

    QRManager->QR->data[idx_local + QRManager->QR->size[0] * (idx - 1)] = 1.0;
    while (idx + 1 <= nVar) {
      QRManager->QR->data[idx_local + QRManager->QR->size[0] * idx] = 0.0;
      idx++;
    }

    WorkingSet->bwset->data[idx_local] = rtInf;
  }

  for (idx_local = 0; idx_local < 12; idx_local++) {
    idx_global = mFixed + idx_local;
    idx = WorkingSet->nVar;
    for (k = 0; k < idx; k++) {
      QRManager->QR->data[idx_global + k * QRManager->ldq] = Aeq->data[idx_local
        + k * 12];
    }

    WorkingSet->bwset->data[idx_global] = 0.0;
  }

  nDepInd = ComputeNumDependentEq_(QRManager, WorkingSet->bwset,
    WorkingSet->sizes[0] + 12, WorkingSet->nVar);
  if (nDepInd > 0) {
    for (idx_local = 0; idx_local < mFixed; idx_local++) {
      for (idx = 1; idx < WorkingSet->indexFixed->data[idx_local]; idx++) {
        QRManager->QR->data[(idx + QRManager->QR->size[0] * idx_local) - 1] =
          0.0;
      }

      QRManager->QR->data[(idx + QRManager->QR->size[0] * idx_local) - 1] = 1.0;
      while (idx + 1 <= nVar) {
        QRManager->QR->data[idx + QRManager->QR->size[0] * idx_local] = 0.0;
      }
    }

    for (idx_local = 0; idx_local < 12; idx_local++) {
      idx_global = WorkingSet->ldA * idx_local;
      idx = QRManager->ldq * (mFixed + idx_local);
      for (k = 0; k < nVar; k++) {
        idxStart = k + 1;
        QRManager->QR->data[(idx + idxStart) - 1] = WorkingSet->Aeq->data
          [(idx_global + idxStart) - 1];
      }
    }

    for (idx = 0; idx < mFixed; idx++) {
      QRManager->jpvt->data[idx] = 1;
    }

    i = WorkingSet->sizes[0] + 1;
    for (idx = i; idx <= mTotalLinEq; idx++) {
      QRManager->jpvt->data[idx - 1] = 0;
    }

    if (WorkingSet->nVar * (WorkingSet->sizes[0] + 12) == 0) {
      QRManager->mrows = WorkingSet->nVar;
      QRManager->ncols = WorkingSet->sizes[0] + 12;
      QRManager->minRowCol = 0;
    } else {
      QRManager->usedPivoting = true;
      QRManager->mrows = WorkingSet->nVar;
      QRManager->ncols = WorkingSet->sizes[0] + 12;
      idx_global = WorkingSet->nVar;
      idx = WorkingSet->sizes[0] + 12;
      if (idx_global < idx) {
        idx = idx_global;
      }

      QRManager->minRowCol = idx;
      xgeqp3(QRManager->QR, WorkingSet->nVar, WorkingSet->sizes[0] + 12,
             QRManager->jpvt, QRManager->tau);
    }

    for (idx = 0; idx < nDepInd; idx++) {
      idxArray[idx] = QRManager->jpvt->data[((mFixed - nDepInd) + idx) + 12];
    }

    emxInit_int32_T(&workspace, 1);
    i = workspace->size[0];
    workspace->size[0] = memspace->workspace_sort->size[0];
    emxEnsureCapacity_int32_T(workspace, i);
    idx_global = memspace->workspace_sort->size[0];
    for (i = 0; i < idx_global; i++) {
      workspace->data[i] = memspace->workspace_sort->data[i];
    }

    if (nDepInd > 1) {
      for (idx = 0; idx < mTotalLinEq; idx++) {
        workspace->data[idx] = 0;
      }

      for (idx = 0; idx < nDepInd; idx++) {
        workspace->data[idxArray[idx] - 1]++;
      }

      for (idx = 2; idx <= mTotalLinEq; idx++) {
        workspace->data[idx - 1] += workspace->data[idx - 2];
      }

      idxStart = 1;
      mTotalLinEq = workspace->data[0];
      i = WorkingSet->sizes[0] + 10;
      for (idx_global = 0; idx_global <= i; idx_global++) {
        for (idx = idxStart; idx <= mTotalLinEq; idx++) {
          idxArray[idx - 1] = idx_global + 1;
        }

        idxStart = workspace->data[idx_global] + 1;
        mTotalLinEq = workspace->data[idx_global + 1];
      }

      for (idx = idxStart; idx <= mTotalLinEq; idx++) {
        idxArray[idx - 1] = mFixed + 12;
      }
    }

    i = memspace->workspace_sort->size[0];
    memspace->workspace_sort->size[0] = workspace->size[0];
    emxEnsureCapacity_int32_T(memspace->workspace_sort, i);
    idx_global = workspace->size[0];
    for (i = 0; i < idx_global; i++) {
      memspace->workspace_sort->data[i] = workspace->data[i];
    }

    emxFree_int32_T(&workspace);
    for (idx = nDepInd; idx >= 1; idx--) {
      if (idxArray[idx - 1] < mLinEq) {
        for (idx_global = 0; idx_global < nVar; idx_global++) {
          WorkingSet->Aeq->data[idx_global + WorkingSet->Aeq->size[0] *
            (idxArray[idx - 1] - 1)] = WorkingSet->Aeq->data[idx_global +
            WorkingSet->Aeq->size[0] * (mLinEq - 1)];
        }

        beq[idxArray[idx - 1] - 1] = 0.0;
      }

      mLinEq--;
    }

    idx = WorkingSet->sizes[1] - nDepInd;
    idxStart = WorkingSet->sizes[3];
    mTotalLinEq = WorkingSet->sizes[4];
    WorkingSet_tmp[0] = WorkingSet->sizes[0];
    WorkingSet_tmp[1] = idx;
    WorkingSet_tmp[2] = 12;
    WorkingSet_tmp[3] = WorkingSet->sizes[3];
    WorkingSet_tmp[4] = WorkingSet->sizes[4];
    WorkingSet->sizesPhaseOne[0] = mFixed;
    WorkingSet->sizesPhaseOne[1] = idx;
    WorkingSet->sizesPhaseOne[2] = 12;
    WorkingSet->sizesPhaseOne[3] = idxStart + 1;
    WorkingSet->sizesPhaseOne[4] = mTotalLinEq;
    WorkingSet->sizesRegularized[0] = mFixed;
    WorkingSet->sizesRegularized[1] = idx;
    WorkingSet->sizesRegularized[2] = 12;
    i = idxStart + (idx << 1);
    idx_local = i + 12;
    WorkingSet->sizesRegularized[3] = idx_local;
    WorkingSet->sizesRegularized[4] = mTotalLinEq;
    WorkingSet->sizesRegPhaseOne[0] = mFixed;
    WorkingSet->sizesRegPhaseOne[1] = idx;
    WorkingSet->sizesRegPhaseOne[2] = 12;
    i += 13;
    WorkingSet->sizesRegPhaseOne[3] = i;
    WorkingSet->sizesRegPhaseOne[4] = mTotalLinEq;
    x[0] = 1;
    x[1] = mFixed;
    x[2] = idx;
    x[3] = 12;
    x[4] = idxStart;
    x[5] = mTotalLinEq;
    for (k = 0; k < 5; k++) {
      WorkingSet->sizes[k] = WorkingSet_tmp[k];
      WorkingSet->sizesNormal[k] = WorkingSet_tmp[k];
      x[k + 1] += x[k];
    }

    for (idx_global = 0; idx_global < 6; idx_global++) {
      WorkingSet->isActiveIdx[idx_global] = x[idx_global];
      WorkingSet->isActiveIdxNormal[idx_global] = x[idx_global];
    }

    x[0] = 1;
    x[1] = mFixed;
    x[2] = idx;
    x[3] = 12;
    x[4] = idxStart + 1;
    x[5] = mTotalLinEq;
    for (k = 0; k < 5; k++) {
      x[k + 1] += x[k];
    }

    for (idx_global = 0; idx_global < 6; idx_global++) {
      WorkingSet->isActiveIdxPhaseOne[idx_global] = x[idx_global];
    }

    x[0] = 1;
    x[1] = mFixed;
    x[2] = idx;
    x[3] = 12;
    x[4] = idx_local;
    x[5] = mTotalLinEq;
    for (k = 0; k < 5; k++) {
      x[k + 1] += x[k];
    }

    for (idx_global = 0; idx_global < 6; idx_global++) {
      WorkingSet->isActiveIdxRegularized[idx_global] = x[idx_global];
    }

    x[0] = 1;
    x[1] = mFixed;
    x[2] = idx;
    x[3] = 12;
    x[4] = i;
    x[5] = mTotalLinEq;
    for (k = 0; k < 5; k++) {
      x[k + 1] += x[k];
    }

    for (idx_global = 0; idx_global < 6; idx_global++) {
      WorkingSet->isActiveIdxRegPhaseOne[idx_global] = x[idx_global];
    }

    idx_global = nDepInd << 1;
    WorkingSet->nVarMax -= idx_global;
    WorkingSet->mConstr -= nDepInd;
    WorkingSet->mConstrMax -= 3 * nDepInd;
    WorkingSet->mConstrOrig -= nDepInd;
    QPObjective->maxVar -= idx_global;
    TrialState->nVarMax -= idx_global;
    TrialState->mEq -= nDepInd;
    TrialState->iNonEq0 -= nDepInd;
  }

  return nDepInd;
}

//
// File trailer for removeDependentLinearEq.cpp
//
// [EOF]
//
