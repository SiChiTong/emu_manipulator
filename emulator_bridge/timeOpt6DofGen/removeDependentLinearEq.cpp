//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: removeDependentLinearEq.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
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
  int mLinEq;
  int idx_local;
  int idxStart;
  int k;
  int idxEnd;
  int mIneq;
  emxArray_int32_T *workspace;
  int i;
  int WorkingSet_tmp[5];
  int x[6];
  nVar = WorkingSet->nVar - 1;
  mLinEq = 12;
  for (idx_local = 0; idx_local < 12; idx_local++) {
    idxStart = WorkingSet->nVar;
    for (k = 0; k < idxStart; k++) {
      QRManager->QR->data[idx_local + k * QRManager->ldq] = Aeq->data[idx_local
        + k * 12];
    }

    WorkingSet->bwset->data[idx_local] = 0.0;
  }

  nDepInd = ComputeNumDependentEq_(QRManager, WorkingSet->bwset, 12,
    WorkingSet->nVar);
  if (nDepInd > 0) {
    for (idx_local = 0; idx_local < 12; idx_local++) {
      idxStart = WorkingSet->ldA * idx_local;
      idxEnd = QRManager->ldq * idx_local;
      for (k = 0; k <= nVar; k++) {
        mIneq = k + 1;
        QRManager->QR->data[(idxEnd + mIneq) - 1] = WorkingSet->Aeq->data
          [(idxStart + mIneq) - 1];
      }
    }

    for (idx_local = 0; idx_local < 12; idx_local++) {
      QRManager->jpvt->data[idx_local] = 0;
    }

    if (WorkingSet->nVar * 12 == 0) {
      QRManager->mrows = WorkingSet->nVar;
      QRManager->ncols = 12;
      QRManager->minRowCol = 0;
    } else {
      QRManager->usedPivoting = true;
      QRManager->mrows = WorkingSet->nVar;
      QRManager->ncols = 12;
      idxStart = WorkingSet->nVar;
      if (idxStart >= 12) {
        idxStart = 12;
      }

      QRManager->minRowCol = idxStart;
      xgeqp3(QRManager->QR, WorkingSet->nVar, 12, QRManager->jpvt,
             QRManager->tau);
    }

    for (idx_local = 0; idx_local < nDepInd; idx_local++) {
      idxArray[idx_local] = QRManager->jpvt->data[(idx_local - nDepInd) + 12];
    }

    emxInit_int32_T(&workspace, 1);
    i = workspace->size[0];
    workspace->size[0] = memspace->workspace_sort->size[0];
    emxEnsureCapacity_int32_T(workspace, i);
    idxStart = memspace->workspace_sort->size[0];
    for (i = 0; i < idxStart; i++) {
      workspace->data[i] = memspace->workspace_sort->data[i];
    }

    if (nDepInd > 1) {
      for (idx_local = 0; idx_local < 12; idx_local++) {
        workspace->data[idx_local] = 0;
      }

      for (idx_local = 0; idx_local < nDepInd; idx_local++) {
        workspace->data[idxArray[idx_local] - 1]++;
      }

      idxStart = 1;
      idxEnd = workspace->data[0];
      for (idx_local = 0; idx_local < 11; idx_local++) {
        workspace->data[idx_local + 1] += workspace->data[idx_local];
        for (mIneq = idxStart; mIneq <= idxEnd; mIneq++) {
          idxArray[mIneq - 1] = idx_local + 1;
        }

        idxStart = workspace->data[idx_local] + 1;
        idxEnd = workspace->data[idx_local + 1];
      }

      for (idx_local = idxStart; idx_local <= idxEnd; idx_local++) {
        idxArray[idx_local - 1] = 12;
      }
    }

    i = memspace->workspace_sort->size[0];
    memspace->workspace_sort->size[0] = workspace->size[0];
    emxEnsureCapacity_int32_T(memspace->workspace_sort, i);
    idxStart = workspace->size[0];
    for (i = 0; i < idxStart; i++) {
      memspace->workspace_sort->data[i] = workspace->data[i];
    }

    emxFree_int32_T(&workspace);
    for (idx_local = nDepInd; idx_local >= 1; idx_local--) {
      if (idxArray[idx_local - 1] < mLinEq) {
        for (idxStart = 0; idxStart <= nVar; idxStart++) {
          WorkingSet->Aeq->data[idxStart + WorkingSet->Aeq->size[0] *
            (idxArray[idx_local - 1] - 1)] = WorkingSet->Aeq->data[idxStart +
            WorkingSet->Aeq->size[0] * (mLinEq - 1)];
        }

        beq[idxArray[idx_local - 1] - 1] = 0.0;
      }

      mLinEq--;
    }

    idxEnd = WorkingSet->sizes[1] - nDepInd;
    mIneq = WorkingSet->sizes[2];
    WorkingSet_tmp[0] = 0;
    WorkingSet_tmp[1] = idxEnd;
    WorkingSet_tmp[2] = WorkingSet->sizes[2];
    WorkingSet_tmp[3] = 0;
    WorkingSet_tmp[4] = 0;
    WorkingSet->sizesPhaseOne[0] = 0;
    WorkingSet->sizesPhaseOne[1] = idxEnd;
    WorkingSet->sizesPhaseOne[2] = mIneq;
    WorkingSet->sizesPhaseOne[3] = 1;
    WorkingSet->sizesPhaseOne[4] = 0;
    WorkingSet->sizesRegularized[0] = 0;
    WorkingSet->sizesRegularized[1] = idxEnd;
    WorkingSet->sizesRegularized[2] = mIneq;
    i = mIneq + (idxEnd << 1);
    WorkingSet->sizesRegularized[3] = i;
    WorkingSet->sizesRegularized[4] = 0;
    WorkingSet->sizesRegPhaseOne[0] = 0;
    WorkingSet->sizesRegPhaseOne[1] = idxEnd;
    WorkingSet->sizesRegPhaseOne[2] = mIneq;
    idx_local = i + 1;
    WorkingSet->sizesRegPhaseOne[3] = idx_local;
    WorkingSet->sizesRegPhaseOne[4] = 0;
    x[0] = 1;
    x[1] = 0;
    x[2] = idxEnd;
    x[3] = mIneq;
    x[4] = 0;
    x[5] = 0;
    for (k = 0; k < 5; k++) {
      WorkingSet->sizes[k] = WorkingSet_tmp[k];
      WorkingSet->sizesNormal[k] = WorkingSet_tmp[k];
      x[k + 1] += x[k];
    }

    for (idxStart = 0; idxStart < 6; idxStart++) {
      WorkingSet->isActiveIdx[idxStart] = x[idxStart];
      WorkingSet->isActiveIdxNormal[idxStart] = x[idxStart];
    }

    x[0] = 1;
    x[1] = 0;
    x[2] = idxEnd;
    x[3] = mIneq;
    x[4] = 1;
    x[5] = 0;
    for (k = 0; k < 5; k++) {
      x[k + 1] += x[k];
    }

    for (idxStart = 0; idxStart < 6; idxStart++) {
      WorkingSet->isActiveIdxPhaseOne[idxStart] = x[idxStart];
    }

    x[0] = 1;
    x[1] = 0;
    x[2] = idxEnd;
    x[3] = mIneq;
    x[4] = i;
    x[5] = 0;
    for (k = 0; k < 5; k++) {
      x[k + 1] += x[k];
    }

    for (idxStart = 0; idxStart < 6; idxStart++) {
      WorkingSet->isActiveIdxRegularized[idxStart] = x[idxStart];
    }

    x[0] = 1;
    x[1] = 0;
    x[2] = idxEnd;
    x[3] = mIneq;
    x[4] = idx_local;
    x[5] = 0;
    for (k = 0; k < 5; k++) {
      x[k + 1] += x[k];
    }

    for (idxStart = 0; idxStart < 6; idxStart++) {
      WorkingSet->isActiveIdxRegPhaseOne[idxStart] = x[idxStart];
    }

    idxStart = nDepInd << 1;
    WorkingSet->nVarMax -= idxStart;
    WorkingSet->mConstr -= nDepInd;
    WorkingSet->mConstrMax -= 3 * nDepInd;
    WorkingSet->mConstrOrig -= nDepInd;
    QPObjective->maxVar -= idxStart;
    TrialState->nVarMax -= idxStart;
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
