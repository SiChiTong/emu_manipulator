//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: relaxed.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "relaxed.h"
#include "addBoundToActiveSetMatrix_.h"
#include "driver1.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include "sortLambdaQP.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xgemv.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const emxArray_real_T *Hessian
//                const emxArray_real_T *grad
//                e_struct_T *TrialState
//                j_struct_T *MeritFunction
//                c_struct_T *memspace
//                h_struct_T *WorkingSet
//                i_struct_T *QRManager
//                k_struct_T *CholManager
//                g_struct_T *QPObjective
//                b_struct_T *qpoptions
// Return Type  : void
//
void relaxed(const emxArray_real_T *Hessian, const emxArray_real_T *grad,
             e_struct_T *TrialState, j_struct_T *MeritFunction, c_struct_T
             *memspace, h_struct_T *WorkingSet, i_struct_T *QRManager,
             k_struct_T *CholManager, g_struct_T *QPObjective, b_struct_T
             *qpoptions)
{
  int nVarOrig;
  int nVarMax;
  double beta;
  int idx;
  int n;
  int idx_negative;
  int ix;
  double rho;
  double smax;
  int k;
  emxArray_real_T *xCurrent;
  double s;
  emxArray_real_T *workspace;
  int mEq;
  int mLBOrig;
  int iac;
  int mFiniteLB;
  emxArray_int32_T *workspace_int;
  double penaltyParamTrial;
  bool isAeqActive;
  nVarOrig = WorkingSet->nVar;
  nVarMax = WorkingSet->nVarMax;
  beta = 0.0;
  for (idx = 0; idx < nVarOrig; idx++) {
    beta += Hessian->data[idx + Hessian->size[0] * idx];
  }

  beta /= static_cast<double>(WorkingSet->nVar);
  if (TrialState->sqpIterations <= 1) {
    n = QPObjective->nvar;
    if (QPObjective->nvar < 1) {
      idx_negative = 0;
    } else {
      idx_negative = 1;
      if (QPObjective->nvar > 1) {
        ix = 0;
        smax = std::abs(grad->data[0]);
        for (k = 2; k <= n; k++) {
          ix++;
          s = std::abs(grad->data[ix]);
          if (s > smax) {
            idx_negative = k;
            smax = s;
          }
        }
      }
    }

    smax = std::abs(grad->data[idx_negative - 1]);
    if ((1.0 > smax) || rtIsNaN(smax)) {
      smax = 1.0;
    }

    rho = 100.0 * smax;
  } else {
    n = WorkingSet->mConstr;
    if (WorkingSet->mConstr < 1) {
      idx_negative = 0;
    } else {
      idx_negative = 1;
      if (WorkingSet->mConstr > 1) {
        ix = 0;
        smax = std::abs(TrialState->lambdasqp->data[0]);
        for (k = 2; k <= n; k++) {
          ix++;
          s = std::abs(TrialState->lambdasqp->data[ix]);
          if (s > smax) {
            idx_negative = k;
            smax = s;
          }
        }
      }
    }

    rho = std::abs(TrialState->lambdasqp->data[idx_negative - 1]);
  }

  emxInit_real_T(&xCurrent, 1);
  QPObjective->nvar = WorkingSet->nVar;
  QPObjective->beta = beta;
  QPObjective->rho = rho;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 4;
  setProblemType(WorkingSet, 2);
  k = xCurrent->size[0];
  xCurrent->size[0] = TrialState->xstar->size[0];
  emxEnsureCapacity_real_T(xCurrent, k);
  idx_negative = TrialState->xstar->size[0];
  for (k = 0; k < idx_negative; k++) {
    xCurrent->data[k] = TrialState->xstar->data[k];
  }

  emxInit_real_T(&workspace, 2);
  k = workspace->size[0] * workspace->size[1];
  workspace->size[0] = memspace->workspace_double->size[0];
  workspace->size[1] = memspace->workspace_double->size[1];
  emxEnsureCapacity_real_T(workspace, k);
  idx_negative = memspace->workspace_double->size[0] *
    memspace->workspace_double->size[1];
  for (k = 0; k < idx_negative; k++) {
    workspace->data[k] = memspace->workspace_double->data[k];
  }

  mEq = WorkingSet->sizes[1] - 1;
  mLBOrig = (WorkingSet->sizes[3] - (WorkingSet->sizes[1] << 1)) - 11;
  for (k = 0; k < 12; k++) {
    workspace->data[k] = WorkingSet->bineq[k];
  }

  c_xgemv(nVarOrig, WorkingSet->Aineq, WorkingSet->ldA, TrialState->xstar,
          workspace);
  for (idx = 0; idx < 12; idx++) {
    xCurrent->data[nVarOrig + idx] = static_cast<double>((workspace->data[idx] >
      0.0)) * workspace->data[idx];
    if (workspace->data[idx] <= 0.002) {
      addBoundToActiveSetMatrix_(WorkingSet, 4, mLBOrig + idx);
    }
  }

  for (k = 0; k <= mEq; k++) {
    workspace->data[k] = WorkingSet->beq->data[k];
  }

  idx_negative = WorkingSet->ldA;
  if ((nVarOrig != 0) && (mEq + 1 != 0)) {
    for (idx = 0; idx <= mEq; idx++) {
      workspace->data[idx] = -workspace->data[idx];
    }

    idx = 0;
    k = WorkingSet->ldA * mEq + 1;
    for (iac = 1; idx_negative < 0 ? iac >= k : iac <= k; iac += idx_negative) {
      ix = 0;
      smax = 0.0;
      mFiniteLB = (iac + nVarOrig) - 1;
      for (n = iac; n <= mFiniteLB; n++) {
        smax += WorkingSet->Aeq->data[n - 1] * xCurrent->data[ix];
        ix++;
      }

      workspace->data[idx] += smax;
      idx++;
    }
  }

  for (idx = 0; idx <= mEq; idx++) {
    idx_negative = (mEq + idx) + 13;
    if (workspace->data[idx] <= 0.0) {
      xCurrent->data[(nVarOrig + idx) + 12] = 0.0;
      xCurrent->data[nVarOrig + idx_negative] = -workspace->data[idx];
      addBoundToActiveSetMatrix_(WorkingSet, 4, (mLBOrig + idx) + 12);
      if (workspace->data[idx] >= -0.002) {
        addBoundToActiveSetMatrix_(WorkingSet, 4, mLBOrig + idx_negative);
      }
    } else {
      xCurrent->data[(nVarOrig + idx) + 12] = workspace->data[idx];
      xCurrent->data[nVarOrig + idx_negative] = 0.0;
      addBoundToActiveSetMatrix_(WorkingSet, 4, mLBOrig + idx_negative);
      if (workspace->data[idx] <= 0.002) {
        addBoundToActiveSetMatrix_(WorkingSet, 4, (mLBOrig + idx) + 12);
      }
    }
  }

  k = TrialState->xstar->size[0];
  TrialState->xstar->size[0] = xCurrent->size[0];
  emxEnsureCapacity_real_T(TrialState->xstar, k);
  idx_negative = xCurrent->size[0];
  for (k = 0; k < idx_negative; k++) {
    TrialState->xstar->data[k] = xCurrent->data[k];
  }

  k = memspace->workspace_double->size[0] * memspace->workspace_double->size[1];
  memspace->workspace_double->size[0] = workspace->size[0];
  memspace->workspace_double->size[1] = workspace->size[1];
  emxEnsureCapacity_real_T(memspace->workspace_double, k);
  idx_negative = workspace->size[0] * workspace->size[1];
  for (k = 0; k < idx_negative; k++) {
    memspace->workspace_double->data[k] = workspace->data[k];
  }

  emxFree_real_T(&workspace);
  emxInit_int32_T(&workspace_int, 1);
  idx_negative = qpoptions->MaxIterations;
  qpoptions->MaxIterations = (qpoptions->MaxIterations + WorkingSet->nVar) -
    nVarOrig;
  b_driver(Hessian, grad, TrialState, memspace, WorkingSet, QRManager,
           CholManager, QPObjective, *qpoptions);
  qpoptions->MaxIterations = idx_negative;
  k = workspace_int->size[0];
  workspace_int->size[0] = memspace->workspace_int->size[0];
  emxEnsureCapacity_int32_T(workspace_int, k);
  idx_negative = memspace->workspace_int->size[0];
  for (k = 0; k < idx_negative; k++) {
    workspace_int->data[k] = memspace->workspace_int->data[k];
  }

  mEq = WorkingSet->sizes[1];
  iac = (WorkingSet->sizes[1] << 1) - 1;
  mFiniteLB = WorkingSet->sizes[3] - 1;
  mLBOrig = 0;
  for (idx = 0; idx < mEq; idx++) {
    idx_negative = WorkingSet->isActiveIdx[3] + mFiniteLB;
    n = WorkingSet->isActiveConstr->data[(idx_negative - (mEq << 1)) + idx];
    workspace_int->data[idx] = n;
    idx_negative = WorkingSet->isActiveConstr->data[(idx_negative - mEq) + idx];
    workspace_int->data[idx + mEq] = idx_negative;
    mLBOrig = (mLBOrig + n) + idx_negative;
  }

  for (idx = 0; idx < 12; idx++) {
    n = WorkingSet->isActiveConstr->data[(((WorkingSet->isActiveIdx[3] +
      mFiniteLB) - iac) + idx) - 13];
    workspace_int->data[(idx + iac) + 1] = n;
    mLBOrig += n;
  }

  k = memspace->workspace_int->size[0];
  memspace->workspace_int->size[0] = workspace_int->size[0];
  emxEnsureCapacity_int32_T(memspace->workspace_int, k);
  idx_negative = workspace_int->size[0];
  for (k = 0; k < idx_negative; k++) {
    memspace->workspace_int->data[k] = workspace_int->data[k];
  }

  if (TrialState->state != -6) {
    idx_negative = (WorkingSet->nVarMax - nVarOrig) - 1;
    iac = nVarOrig + 1;
    smax = 0.0;
    if (idx_negative >= 1) {
      mFiniteLB = nVarOrig + idx_negative;
      for (k = iac; k <= mFiniteLB; k++) {
        smax += std::abs(TrialState->xstar->data[k - 1]);
      }
    }

    s = 0.0;
    if (idx_negative >= 1) {
      ix = nVarOrig;
      idx = nVarOrig;
      for (k = 0; k < idx_negative; k++) {
        s += TrialState->xstar->data[ix] * TrialState->xstar->data[idx];
        ix++;
        idx++;
      }
    }

    beta = (TrialState->fstar - rho * smax) - beta / 2.0 * s;
    mEq = WorkingSet->sizes[1];
    iac = nVarOrig + 1;
    n = (nVarMax - nVarOrig) - 1;
    penaltyParamTrial = MeritFunction->penaltyParam;
    smax = 0.0;
    if (WorkingSet->sizes[1] >= 1) {
      mFiniteLB = WorkingSet->sizes[1];
      for (k = 0; k < mFiniteLB; k++) {
        smax += std::abs(TrialState->cEq->data[k]);
      }
    }

    s = 0.0;
    for (idx = 0; idx < 12; idx++) {
      if (TrialState->cIneq[idx] > 0.0) {
        s += TrialState->cIneq[idx];
      }
    }

    rho = smax + s;
    smax = MeritFunction->linearizedConstrViol;
    s = 0.0;
    if (n >= 1) {
      mFiniteLB = nVarOrig + n;
      for (k = iac; k <= mFiniteLB; k++) {
        s += std::abs(TrialState->xstar->data[k - 1]);
      }
    }

    MeritFunction->linearizedConstrViol = s;
    smax = (rho + smax) - s;
    if ((smax > 2.2204460492503131E-16) && (beta > 0.0)) {
      if (TrialState->sqpFval == 0.0) {
        s = 1.0;
      } else {
        s = 1.5;
      }

      penaltyParamTrial = s * beta / smax;
    }

    if (penaltyParamTrial < MeritFunction->penaltyParam) {
      MeritFunction->phi = TrialState->sqpFval + penaltyParamTrial * rho;
      if ((MeritFunction->initFval + penaltyParamTrial *
           (MeritFunction->initConstrViolationEq +
            MeritFunction->initConstrViolationIneq)) - MeritFunction->phi >
          static_cast<double>(MeritFunction->nPenaltyDecreases) *
          MeritFunction->threshold) {
        MeritFunction->nPenaltyDecreases++;
        if ((MeritFunction->nPenaltyDecreases << 1) > TrialState->sqpIterations)
        {
          MeritFunction->threshold *= 10.0;
        }

        if (!(penaltyParamTrial > 1.0E-10)) {
          penaltyParamTrial = 1.0E-10;
        }

        MeritFunction->penaltyParam = penaltyParamTrial;
      } else {
        MeritFunction->phi = TrialState->sqpFval + MeritFunction->penaltyParam *
          rho;
      }
    } else {
      if (!(penaltyParamTrial > 1.0E-10)) {
        penaltyParamTrial = 1.0E-10;
      }

      MeritFunction->penaltyParam = penaltyParamTrial;
      MeritFunction->phi = TrialState->sqpFval + MeritFunction->penaltyParam *
        rho;
    }

    smax = beta - MeritFunction->penaltyParam * rho;
    if (!(smax < 0.0)) {
      smax = 0.0;
    }

    MeritFunction->phiPrimePlus = smax;
    mFiniteLB = WorkingSet->isActiveIdx[1] - 2;
    for (idx = 0; idx < mEq; idx++) {
      idx_negative = idx + 1;
      if ((workspace_int->data[idx_negative - 1] != 0) && (workspace_int->data
           [(idx_negative + mEq) - 1] != 0)) {
        isAeqActive = true;
      } else {
        isAeqActive = false;
      }

      k = mFiniteLB + idx_negative;
      TrialState->lambda->data[k] *= static_cast<double>(isAeqActive);
    }

    idx_negative = WorkingSet->isActiveIdx[2];
    mFiniteLB = WorkingSet->nActiveConstr;
    for (idx = idx_negative; idx <= mFiniteLB; idx++) {
      if (WorkingSet->Wid->data[idx - 1] == 3) {
        TrialState->lambda->data[idx - 1] *= static_cast<double>
          (workspace_int->data[(WorkingSet->Wlocalidx->data[idx - 1] + (mEq << 1))
           - 1]);
      }
    }
  }

  emxFree_int32_T(&workspace_int);
  k = xCurrent->size[0];
  xCurrent->size[0] = TrialState->lambda->size[0];
  emxEnsureCapacity_real_T(xCurrent, k);
  idx_negative = TrialState->lambda->size[0];
  for (k = 0; k < idx_negative; k++) {
    xCurrent->data[k] = TrialState->lambda->data[k];
  }

  idx_negative = WorkingSet->sizes[0];
  mEq = WorkingSet->sizes[1];
  mFiniteLB = (WorkingSet->sizes[3] - (WorkingSet->sizes[1] << 1)) - 12;
  idx = WorkingSet->nActiveConstr;
  while ((idx > idx_negative + mEq) && (mLBOrig > 0)) {
    if ((WorkingSet->Wid->data[idx - 1] == 4) && (WorkingSet->Wlocalidx->
         data[idx - 1] > mFiniteLB)) {
      iac = WorkingSet->nActiveConstr - 1;
      smax = xCurrent->data[iac];
      xCurrent->data[iac] = 0.0;
      xCurrent->data[idx - 1] = smax;
      removeConstr(WorkingSet, idx);
      mLBOrig--;
    }

    idx--;
  }

  QPObjective->nvar = nVarOrig;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 3;
  setProblemType(WorkingSet, 3);
  k = TrialState->lambda->size[0];
  TrialState->lambda->size[0] = xCurrent->size[0];
  emxEnsureCapacity_real_T(TrialState->lambda, k);
  idx_negative = xCurrent->size[0];
  for (k = 0; k < idx_negative; k++) {
    TrialState->lambda->data[k] = xCurrent->data[k];
  }

  emxFree_real_T(&xCurrent);
  sortLambdaQP(TrialState->lambda, WorkingSet->nActiveConstr, WorkingSet->sizes,
               WorkingSet->isActiveIdx, WorkingSet->Wid, WorkingSet->Wlocalidx,
               memspace->workspace_double);
}

//
// File trailer for relaxed.cpp
//
// [EOF]
//
