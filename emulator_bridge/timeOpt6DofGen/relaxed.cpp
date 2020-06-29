//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: relaxed.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
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
  int nArtificial;
  int idx_positive;
  int ix;
  double smax;
  int mFiniteLB;
  emxArray_real_T *xCurrent;
  double s;
  emxArray_real_T *workspace;
  int mIneq;
  int mEq;
  emxArray_int32_T *workspace_int;
  int nActiveLBArtificial;
  int workspace_int_tmp;
  double qpfvalQuadExcess;
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
    nArtificial = QPObjective->nvar;
    if (QPObjective->nvar < 1) {
      idx_positive = 0;
    } else {
      idx_positive = 1;
      if (QPObjective->nvar > 1) {
        ix = 0;
        smax = std::abs(grad->data[0]);
        for (mFiniteLB = 2; mFiniteLB <= nArtificial; mFiniteLB++) {
          ix++;
          s = std::abs(grad->data[ix]);
          if (s > smax) {
            idx_positive = mFiniteLB;
            smax = s;
          }
        }
      }
    }

    smax = std::abs(grad->data[idx_positive - 1]);
    if ((1.0 > smax) || rtIsNaN(smax)) {
      smax = 1.0;
    }

    smax *= 100.0;
  } else {
    nArtificial = WorkingSet->mConstr;
    if (WorkingSet->mConstr < 1) {
      idx_positive = 0;
    } else {
      idx_positive = 1;
      if (WorkingSet->mConstr > 1) {
        ix = 0;
        smax = std::abs(TrialState->lambdasqp->data[0]);
        for (mFiniteLB = 2; mFiniteLB <= nArtificial; mFiniteLB++) {
          ix++;
          s = std::abs(TrialState->lambdasqp->data[ix]);
          if (s > smax) {
            idx_positive = mFiniteLB;
            smax = s;
          }
        }
      }
    }

    smax = std::abs(TrialState->lambdasqp->data[idx_positive - 1]);
  }

  emxInit_real_T(&xCurrent, 1);
  QPObjective->nvar = WorkingSet->nVar;
  QPObjective->beta = beta;
  QPObjective->rho = smax;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 4;
  setProblemType(WorkingSet, 2);
  nArtificial = xCurrent->size[0];
  xCurrent->size[0] = TrialState->xstar->size[0];
  emxEnsureCapacity_real_T(xCurrent, nArtificial);
  idx_positive = TrialState->xstar->size[0];
  for (nArtificial = 0; nArtificial < idx_positive; nArtificial++) {
    xCurrent->data[nArtificial] = TrialState->xstar->data[nArtificial];
  }

  emxInit_real_T(&workspace, 2);
  nArtificial = workspace->size[0] * workspace->size[1];
  workspace->size[0] = memspace->workspace_double->size[0];
  workspace->size[1] = memspace->workspace_double->size[1];
  emxEnsureCapacity_real_T(workspace, nArtificial);
  idx_positive = memspace->workspace_double->size[0] *
    memspace->workspace_double->size[1];
  for (nArtificial = 0; nArtificial < idx_positive; nArtificial++) {
    workspace->data[nArtificial] = memspace->workspace_double->data[nArtificial];
  }

  mIneq = WorkingSet->sizes[2] - 1;
  mEq = WorkingSet->sizes[1] - 1;
  nArtificial = (WorkingSet->sizes[3] - (WorkingSet->sizes[1] << 1)) -
    WorkingSet->sizes[2];
  for (mFiniteLB = 0; mFiniteLB <= mIneq; mFiniteLB++) {
    workspace->data[mFiniteLB] = WorkingSet->bineq->data[mFiniteLB];
  }

  b_xgemv(nVarOrig, WorkingSet->sizes[2], WorkingSet->Aineq, WorkingSet->ldA,
          TrialState->xstar, workspace);
  for (idx = 0; idx <= mIneq; idx++) {
    xCurrent->data[nVarOrig + idx] = static_cast<double>((workspace->data[idx] >
      0.0)) * workspace->data[idx];
    if (workspace->data[idx] <= 0.001) {
      addBoundToActiveSetMatrix_(WorkingSet, 4, (nArtificial + idx) + 1);
    }
  }

  for (mFiniteLB = 0; mFiniteLB <= mEq; mFiniteLB++) {
    workspace->data[mFiniteLB] = WorkingSet->beq->data[mFiniteLB];
  }

  b_xgemv(nVarOrig, mEq + 1, WorkingSet->Aeq, WorkingSet->ldA, xCurrent,
          workspace);
  for (idx = 0; idx <= mEq; idx++) {
    idx_positive = (mIneq + idx) + 1;
    ix = ((mIneq + mEq) + idx) + 2;
    if (workspace->data[idx] <= 0.0) {
      xCurrent->data[nVarOrig + idx_positive] = 0.0;
      xCurrent->data[nVarOrig + ix] = -workspace->data[idx];
      addBoundToActiveSetMatrix_(WorkingSet, 4, (nArtificial + idx_positive) + 1);
      if (workspace->data[idx] >= -0.001) {
        addBoundToActiveSetMatrix_(WorkingSet, 4, (nArtificial + ix) + 1);
      }
    } else {
      xCurrent->data[nVarOrig + idx_positive] = workspace->data[idx];
      xCurrent->data[nVarOrig + ix] = 0.0;
      addBoundToActiveSetMatrix_(WorkingSet, 4, (nArtificial + ix) + 1);
      if (workspace->data[idx] <= 0.001) {
        addBoundToActiveSetMatrix_(WorkingSet, 4, (nArtificial + idx_positive) +
          1);
      }
    }
  }

  nArtificial = TrialState->xstar->size[0];
  TrialState->xstar->size[0] = xCurrent->size[0];
  emxEnsureCapacity_real_T(TrialState->xstar, nArtificial);
  idx_positive = xCurrent->size[0];
  for (nArtificial = 0; nArtificial < idx_positive; nArtificial++) {
    TrialState->xstar->data[nArtificial] = xCurrent->data[nArtificial];
  }

  nArtificial = memspace->workspace_double->size[0] * memspace->
    workspace_double->size[1];
  memspace->workspace_double->size[0] = workspace->size[0];
  memspace->workspace_double->size[1] = workspace->size[1];
  emxEnsureCapacity_real_T(memspace->workspace_double, nArtificial);
  idx_positive = workspace->size[0] * workspace->size[1];
  for (nArtificial = 0; nArtificial < idx_positive; nArtificial++) {
    memspace->workspace_double->data[nArtificial] = workspace->data[nArtificial];
  }

  emxFree_real_T(&workspace);
  emxInit_int32_T(&workspace_int, 1);
  idx_positive = qpoptions->MaxIterations;
  qpoptions->MaxIterations = (qpoptions->MaxIterations + WorkingSet->nVar) -
    nVarOrig;
  b_driver(Hessian, grad, TrialState, memspace, WorkingSet, QRManager,
           CholManager, QPObjective, *qpoptions);
  qpoptions->MaxIterations = idx_positive;
  nArtificial = workspace_int->size[0];
  workspace_int->size[0] = memspace->workspace_int->size[0];
  emxEnsureCapacity_int32_T(workspace_int, nArtificial);
  idx_positive = memspace->workspace_int->size[0];
  for (nArtificial = 0; nArtificial < idx_positive; nArtificial++) {
    workspace_int->data[nArtificial] = memspace->workspace_int->data[nArtificial];
  }

  mIneq = WorkingSet->sizes[2];
  mEq = WorkingSet->sizes[1];
  ix = WorkingSet->sizes[1] << 1;
  nArtificial = ix + WorkingSet->sizes[2];
  mFiniteLB = WorkingSet->sizes[3] - 1;
  nActiveLBArtificial = 0;
  for (idx = 0; idx < mEq; idx++) {
    idx_positive = WorkingSet->isActiveIdx[3] + mFiniteLB;
    workspace_int_tmp = WorkingSet->isActiveConstr->data[(idx_positive - (mEq <<
      1)) + idx];
    workspace_int->data[idx] = workspace_int_tmp;
    idx_positive = WorkingSet->isActiveConstr->data[(idx_positive - mEq) + idx];
    workspace_int->data[idx + mEq] = idx_positive;
    nActiveLBArtificial = (nActiveLBArtificial + workspace_int_tmp) +
      idx_positive;
  }

  for (idx = 0; idx < mIneq; idx++) {
    workspace_int_tmp = WorkingSet->isActiveConstr->data
      [((WorkingSet->isActiveIdx[3] + mFiniteLB) - nArtificial) + idx];
    workspace_int->data[idx + ix] = workspace_int_tmp;
    nActiveLBArtificial += workspace_int_tmp;
  }

  nArtificial = memspace->workspace_int->size[0];
  memspace->workspace_int->size[0] = workspace_int->size[0];
  emxEnsureCapacity_int32_T(memspace->workspace_int, nArtificial);
  idx_positive = workspace_int->size[0];
  for (nArtificial = 0; nArtificial < idx_positive; nArtificial++) {
    memspace->workspace_int->data[nArtificial] = workspace_int->data[nArtificial];
  }

  if (TrialState->state != -6) {
    nArtificial = (WorkingSet->nVarMax - nVarOrig) - 1;
    ix = nVarOrig + 1;
    s = 0.0;
    if (nArtificial >= 1) {
      idx_positive = nVarOrig + nArtificial;
      for (mFiniteLB = ix; mFiniteLB <= idx_positive; mFiniteLB++) {
        s += std::abs(TrialState->xstar->data[mFiniteLB - 1]);
      }
    }

    qpfvalQuadExcess = 0.0;
    if (nArtificial >= 1) {
      ix = nVarOrig;
      idx_positive = nVarOrig;
      for (mFiniteLB = 0; mFiniteLB < nArtificial; mFiniteLB++) {
        qpfvalQuadExcess += TrialState->xstar->data[ix] * TrialState->
          xstar->data[idx_positive];
        ix++;
        idx_positive++;
      }
    }

    beta = (TrialState->fstar - smax * s) - beta / 2.0 * qpfvalQuadExcess;
    mIneq = WorkingSet->sizes[2];
    mEq = WorkingSet->sizes[1];
    ix = nVarOrig + 1;
    nArtificial = (nVarMax - nVarOrig) - 1;
    penaltyParamTrial = MeritFunction->penaltyParam;
    smax = 0.0;
    if (WorkingSet->sizes[1] >= 1) {
      idx_positive = WorkingSet->sizes[1];
      for (mFiniteLB = 0; mFiniteLB < idx_positive; mFiniteLB++) {
        smax += std::abs(TrialState->cEq->data[mFiniteLB]);
      }
    }

    s = 0.0;
    for (idx = 0; idx < mIneq; idx++) {
      if (TrialState->cIneq->data[idx] > 0.0) {
        s += TrialState->cIneq->data[idx];
      }
    }

    qpfvalQuadExcess = smax + s;
    smax = MeritFunction->linearizedConstrViol;
    s = 0.0;
    if (nArtificial >= 1) {
      idx_positive = nVarOrig + nArtificial;
      for (mFiniteLB = ix; mFiniteLB <= idx_positive; mFiniteLB++) {
        s += std::abs(TrialState->xstar->data[mFiniteLB - 1]);
      }
    }

    MeritFunction->linearizedConstrViol = s;
    smax = (qpfvalQuadExcess + smax) - s;
    if ((smax > 2.2204460492503131E-16) && (beta > 0.0)) {
      if (TrialState->sqpFval == 0.0) {
        s = 1.0;
      } else {
        s = 1.5;
      }

      penaltyParamTrial = s * beta / smax;
    }

    if (penaltyParamTrial < MeritFunction->penaltyParam) {
      MeritFunction->phi = TrialState->sqpFval + penaltyParamTrial *
        qpfvalQuadExcess;
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
          qpfvalQuadExcess;
      }
    } else {
      if (!(penaltyParamTrial > 1.0E-10)) {
        penaltyParamTrial = 1.0E-10;
      }

      MeritFunction->penaltyParam = penaltyParamTrial;
      MeritFunction->phi = TrialState->sqpFval + MeritFunction->penaltyParam *
        qpfvalQuadExcess;
    }

    smax = beta - MeritFunction->penaltyParam * qpfvalQuadExcess;
    if (!(smax < 0.0)) {
      smax = 0.0;
    }

    MeritFunction->phiPrimePlus = smax;
    ix = WorkingSet->isActiveIdx[1] - 2;
    for (idx = 0; idx < mEq; idx++) {
      idx_positive = idx + 1;
      if ((workspace_int->data[idx_positive - 1] != 0) && (workspace_int->data
           [(idx_positive + mEq) - 1] != 0)) {
        isAeqActive = true;
      } else {
        isAeqActive = false;
      }

      nArtificial = ix + idx_positive;
      TrialState->lambda->data[nArtificial] *= static_cast<double>(isAeqActive);
    }

    idx_positive = WorkingSet->isActiveIdx[2];
    ix = WorkingSet->nActiveConstr;
    for (idx = idx_positive; idx <= ix; idx++) {
      if (WorkingSet->Wid->data[idx - 1] == 3) {
        TrialState->lambda->data[idx - 1] *= static_cast<double>
          (workspace_int->data[(WorkingSet->Wlocalidx->data[idx - 1] + (mEq << 1))
           - 1]);
      }
    }
  }

  emxFree_int32_T(&workspace_int);
  nArtificial = xCurrent->size[0];
  xCurrent->size[0] = TrialState->lambda->size[0];
  emxEnsureCapacity_real_T(xCurrent, nArtificial);
  idx_positive = TrialState->lambda->size[0];
  for (nArtificial = 0; nArtificial < idx_positive; nArtificial++) {
    xCurrent->data[nArtificial] = TrialState->lambda->data[nArtificial];
  }

  mEq = WorkingSet->sizes[1];
  nArtificial = (WorkingSet->sizes[3] - (WorkingSet->sizes[1] << 1)) -
    WorkingSet->sizes[2];
  idx = WorkingSet->nActiveConstr;
  while ((idx > mEq) && (nActiveLBArtificial > 0)) {
    if ((WorkingSet->Wid->data[idx - 1] == 4) && (WorkingSet->Wlocalidx->
         data[idx - 1] > nArtificial)) {
      idx_positive = WorkingSet->nActiveConstr - 1;
      smax = xCurrent->data[idx_positive];
      xCurrent->data[idx_positive] = 0.0;
      xCurrent->data[idx - 1] = smax;
      removeConstr(WorkingSet, idx);
      nActiveLBArtificial--;
    }

    idx--;
  }

  QPObjective->nvar = nVarOrig;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 3;
  setProblemType(WorkingSet, 3);
  nArtificial = TrialState->lambda->size[0];
  TrialState->lambda->size[0] = xCurrent->size[0];
  emxEnsureCapacity_real_T(TrialState->lambda, nArtificial);
  idx_positive = xCurrent->size[0];
  for (nArtificial = 0; nArtificial < idx_positive; nArtificial++) {
    TrialState->lambda->data[nArtificial] = xCurrent->data[nArtificial];
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
