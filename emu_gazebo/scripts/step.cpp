//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: step.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "step.h"
#include "addAeqConstr.h"
#include "addBoundToActiveSetMatrix_.h"
#include "driver1.h"
#include "relaxed.h"
#include "rt_nonfinite.h"
#include "soc.h"
#include "sortLambdaQP.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include <cmath>

// Function Definitions

//
// Arguments    : int *STEP_TYPE
//                emxArray_real_T *Hessian
//                const emxArray_real_T *lb
//                e_struct_T *TrialState
//                j_struct_T *MeritFunction
//                c_struct_T *memspace
//                h_struct_T *WorkingSet
//                i_struct_T *QRManager
//                k_struct_T *CholManager
//                g_struct_T *QPObjective
//                b_struct_T qpoptions
// Return Type  : bool
//
bool step(int *STEP_TYPE, emxArray_real_T *Hessian, const emxArray_real_T *lb,
          e_struct_T *TrialState, j_struct_T *MeritFunction, c_struct_T
          *memspace, h_struct_T *WorkingSet, i_struct_T *QRManager, k_struct_T
          *CholManager, g_struct_T *QPObjective, b_struct_T qpoptions)
{
  bool stepSuccess;
  bool checkBoundViolation;
  int nVar;
  int k;
  emxArray_real_T *xk;
  int n;
  int mUB;
  int mLB;
  double constrViolationEq;
  e_struct_T b_TrialState;
  int exitg1;
  bool guard1 = false;
  double penaltyParamTrial;
  bool nonlinEqRemoved;
  double constrViolationIneq;
  int b_nVar;
  emxArray_real_T *xstarqp;
  stepSuccess = true;
  checkBoundViolation = true;
  nVar = WorkingSet->nVar - 1;
  if (*STEP_TYPE != 3) {
    for (k = 0; k <= nVar; k++) {
      TrialState->xstar->data[k] = TrialState->xstarsqp->data[k];
    }
  } else {
    for (k = 0; k <= nVar; k++) {
      TrialState->searchDir->data[k] = TrialState->xstar->data[k];
    }
  }

  emxInit_real_T(&xk, 1);
  n = xk->size[0];
  xk->size[0] = TrialState->xstar->size[0];
  emxEnsureCapacity_real_T(xk, n);
  mUB = TrialState->xstar->size[0];
  for (n = 0; n < mUB; n++) {
    xk->data[n] = TrialState->xstar->data[n];
  }

  mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  for (k = 0; k < mLB; k++) {
    constrViolationEq = WorkingSet->lb->data[WorkingSet->indexLB->data[k] - 1];
    if (-xk->data[WorkingSet->indexLB->data[k] - 1] >= constrViolationEq) {
      xk->data[WorkingSet->indexLB->data[k] - 1] = -constrViolationEq;
      if (!WorkingSet->isActiveConstr->data[(WorkingSet->isActiveIdx[3] + k) - 1])
      {
        addBoundToActiveSetMatrix_(WorkingSet, 4, k + 1);
      }
    }
  }

  for (k = 0; k < mUB; k++) {
    constrViolationEq = WorkingSet->ub->data[WorkingSet->indexUB->data[k] - 1];
    if (xk->data[WorkingSet->indexUB->data[k] - 1] >= constrViolationEq) {
      xk->data[WorkingSet->indexUB->data[k] - 1] = constrViolationEq;
      if (!WorkingSet->isActiveConstr->data[(WorkingSet->isActiveIdx[4] + k) - 1])
      {
        addBoundToActiveSetMatrix_(WorkingSet, 5, k + 1);
      }
    }
  }

  n = TrialState->xstar->size[0];
  TrialState->xstar->size[0] = xk->size[0];
  emxEnsureCapacity_real_T(TrialState->xstar, n);
  mUB = xk->size[0];
  for (n = 0; n < mUB; n++) {
    TrialState->xstar->data[n] = xk->data[n];
  }

  emxInitStruct_struct_T(&b_TrialState);
  do {
    exitg1 = 0;
    guard1 = false;
    switch (*STEP_TYPE) {
     case 1:
      emxCopyStruct_struct_T1(&b_TrialState, TrialState);
      b_driver(Hessian, TrialState->grad, &b_TrialState, memspace, WorkingSet,
               QRManager, CholManager, QPObjective, qpoptions);
      if (b_TrialState.state > 0) {
        penaltyParamTrial = MeritFunction->penaltyParam;
        constrViolationEq = 0.0;
        if (WorkingSet->sizes[1] >= 1) {
          mUB = WorkingSet->sizes[1];
          for (k = 0; k < mUB; k++) {
            constrViolationEq += std::abs(b_TrialState.cEq->data[k]);
          }
        }

        constrViolationIneq = 0.0;
        for (k = 0; k < 12; k++) {
          if (b_TrialState.cIneq[k] > 0.0) {
            constrViolationIneq += b_TrialState.cIneq[k];
          }
        }

        constrViolationIneq += constrViolationEq;
        constrViolationEq = MeritFunction->linearizedConstrViol;
        MeritFunction->linearizedConstrViol = 0.0;
        constrViolationEq += constrViolationIneq;
        if ((constrViolationEq > 2.2204460492503131E-16) && (b_TrialState.fstar >
             0.0)) {
          if (b_TrialState.sqpFval == 0.0) {
            penaltyParamTrial = 1.0;
          } else {
            penaltyParamTrial = 1.5;
          }

          penaltyParamTrial = penaltyParamTrial * b_TrialState.fstar /
            constrViolationEq;
        }

        if (penaltyParamTrial < MeritFunction->penaltyParam) {
          MeritFunction->phi = b_TrialState.sqpFval + penaltyParamTrial *
            constrViolationIneq;
          if ((MeritFunction->initFval + penaltyParamTrial *
               (MeritFunction->initConstrViolationEq +
                MeritFunction->initConstrViolationIneq)) - MeritFunction->phi >
              static_cast<double>(MeritFunction->nPenaltyDecreases) *
              MeritFunction->threshold) {
            MeritFunction->nPenaltyDecreases++;
            if ((MeritFunction->nPenaltyDecreases << 1) >
                b_TrialState.sqpIterations) {
              MeritFunction->threshold *= 10.0;
            }

            if (!(penaltyParamTrial > 1.0E-10)) {
              penaltyParamTrial = 1.0E-10;
            }

            MeritFunction->penaltyParam = penaltyParamTrial;
          } else {
            MeritFunction->phi = b_TrialState.sqpFval +
              MeritFunction->penaltyParam * constrViolationIneq;
          }
        } else {
          if (!(penaltyParamTrial > 1.0E-10)) {
            penaltyParamTrial = 1.0E-10;
          }

          MeritFunction->penaltyParam = penaltyParamTrial;
          MeritFunction->phi = b_TrialState.sqpFval +
            MeritFunction->penaltyParam * constrViolationIneq;
        }

        constrViolationEq = b_TrialState.fstar - MeritFunction->penaltyParam *
          constrViolationIneq;
        if (!(constrViolationEq < 0.0)) {
          constrViolationEq = 0.0;
        }

        MeritFunction->phiPrimePlus = constrViolationEq;
      }

      sortLambdaQP(b_TrialState.lambda, WorkingSet->nActiveConstr,
                   WorkingSet->sizes, WorkingSet->isActiveIdx, WorkingSet->Wid,
                   WorkingSet->Wlocalidx, memspace->workspace_double);
      nonlinEqRemoved = (WorkingSet->mEqRemoved > 0);
      while ((WorkingSet->mEqRemoved > 0) && (WorkingSet->indexEqRemoved->
              data[WorkingSet->mEqRemoved - 1] >= b_TrialState.iNonEq0)) {
        addAeqConstr(WorkingSet, WorkingSet->indexEqRemoved->data
                     [WorkingSet->mEqRemoved - 1]);
        WorkingSet->mEqRemoved--;
      }

      if (nonlinEqRemoved) {
        mUB = (WorkingSet->sizes[0] + b_TrialState.iNonEq0) - 1;
        n = b_TrialState.mNonlinEq;
        for (k = 0; k < n; k++) {
          WorkingSet->Wlocalidx->data[mUB + k] = b_TrialState.iNonEq0 + k;
        }
      }

      emxCopyStruct_struct_T1(TrialState, &b_TrialState);
      if ((b_TrialState.state <= 0) && (b_TrialState.state != -6)) {
        *STEP_TYPE = 2;
      } else {
        n = TrialState->delta_x->size[0];
        TrialState->delta_x->size[0] = b_TrialState.delta_x->size[0];
        emxEnsureCapacity_real_T(TrialState->delta_x, n);
        mUB = b_TrialState.delta_x->size[0];
        for (n = 0; n < mUB; n++) {
          TrialState->delta_x->data[n] = b_TrialState.delta_x->data[n];
        }

        for (k = 0; k <= nVar; k++) {
          TrialState->delta_x->data[k] = b_TrialState.xstar->data[k];
        }

        guard1 = true;
      }
      break;

     case 2:
      emxCopyStruct_struct_T1(&b_TrialState, TrialState);
      relaxed(Hessian, TrialState->grad, &b_TrialState, MeritFunction, memspace,
              WorkingSet, QRManager, CholManager, QPObjective, &qpoptions);
      emxCopyStruct_struct_T1(TrialState, &b_TrialState);
      n = TrialState->delta_x->size[0];
      TrialState->delta_x->size[0] = b_TrialState.delta_x->size[0];
      emxEnsureCapacity_real_T(TrialState->delta_x, n);
      mUB = b_TrialState.delta_x->size[0];
      for (n = 0; n < mUB; n++) {
        TrialState->delta_x->data[n] = b_TrialState.delta_x->data[n];
      }

      for (k = 0; k <= nVar; k++) {
        TrialState->delta_x->data[k] = b_TrialState.xstar->data[k];
      }

      guard1 = true;
      break;

     default:
      n = xk->size[0];
      xk->size[0] = TrialState->grad->size[0];
      emxEnsureCapacity_real_T(xk, n);
      mUB = TrialState->grad->size[0];
      for (n = 0; n < mUB; n++) {
        xk->data[n] = TrialState->grad->data[n];
      }

      stepSuccess = soc(Hessian, xk, TrialState, memspace, WorkingSet, QRManager,
                        CholManager, QPObjective, qpoptions);
      checkBoundViolation = stepSuccess;
      if (stepSuccess && (TrialState->state != -6)) {
        for (k = 0; k <= nVar; k++) {
          TrialState->delta_x->data[k] = TrialState->xstar->data[k] +
            TrialState->socDirection->data[k];
        }
      }

      guard1 = true;
      break;
    }

    if (guard1) {
      if (TrialState->state != -6) {
        exitg1 = 1;
      } else {
        b_nVar = Hessian->size[0] - 1;
        constrViolationEq = 0.0;
        constrViolationIneq = 1.0;
        for (k = 0; k <= b_nVar; k++) {
          penaltyParamTrial = std::abs(TrialState->grad->data[k]);
          if ((!(constrViolationEq > penaltyParamTrial)) && (!rtIsNaN
               (penaltyParamTrial))) {
            constrViolationEq = penaltyParamTrial;
          }

          penaltyParamTrial = std::abs(TrialState->xstar->data[k]);
          if ((!(constrViolationIneq > penaltyParamTrial)) && (!rtIsNaN
               (penaltyParamTrial))) {
            constrViolationIneq = penaltyParamTrial;
          }
        }

        penaltyParamTrial = constrViolationEq / constrViolationIneq;
        if ((2.2204460492503131E-16 > penaltyParamTrial) || rtIsNaN
            (penaltyParamTrial)) {
          constrViolationEq = 2.2204460492503131E-16;
        } else {
          constrViolationEq = penaltyParamTrial;
        }

        for (mLB = 0; mLB <= b_nVar; mLB++) {
          mUB = (b_nVar + 1) * mLB;
          for (k = 0; k < mLB; k++) {
            Hessian->data[mUB + k] = 0.0;
          }

          Hessian->data[mLB + Hessian->size[0] * mLB] = constrViolationEq;
          mUB += mLB;
          n = b_nVar - mLB;
          for (k = 0; k < n; k++) {
            Hessian->data[(mUB + k) + 1] = 0.0;
          }
        }
      }
    }
  } while (exitg1 == 0);

  emxFreeStruct_struct_T(&b_TrialState);
  if (checkBoundViolation) {
    mLB = WorkingSet->sizes[3];
    n = xk->size[0];
    xk->size[0] = TrialState->delta_x->size[0];
    emxEnsureCapacity_real_T(xk, n);
    mUB = TrialState->delta_x->size[0];
    for (n = 0; n < mUB; n++) {
      xk->data[n] = TrialState->delta_x->data[n];
    }

    emxInit_real_T(&xstarqp, 1);
    n = xstarqp->size[0];
    xstarqp->size[0] = TrialState->xstar->size[0];
    emxEnsureCapacity_real_T(xstarqp, n);
    mUB = TrialState->xstar->size[0];
    for (n = 0; n < mUB; n++) {
      xstarqp->data[n] = TrialState->xstar->data[n];
    }

    for (k = 0; k < mLB; k++) {
      constrViolationEq = xk->data[WorkingSet->indexLB->data[k] - 1];
      constrViolationIneq = (TrialState->xstarsqp->data[WorkingSet->
        indexLB->data[k] - 1] + constrViolationEq) - lb->data
        [WorkingSet->indexLB->data[k] - 1];
      if (constrViolationIneq < 0.0) {
        xk->data[WorkingSet->indexLB->data[k] - 1] = constrViolationEq -
          constrViolationIneq;
        xstarqp->data[WorkingSet->indexLB->data[k] - 1] -= constrViolationIneq;
      }
    }

    n = TrialState->delta_x->size[0];
    TrialState->delta_x->size[0] = xk->size[0];
    emxEnsureCapacity_real_T(TrialState->delta_x, n);
    mUB = xk->size[0];
    for (n = 0; n < mUB; n++) {
      TrialState->delta_x->data[n] = xk->data[n];
    }

    n = TrialState->xstar->size[0];
    TrialState->xstar->size[0] = xstarqp->size[0];
    emxEnsureCapacity_real_T(TrialState->xstar, n);
    mUB = xstarqp->size[0];
    for (n = 0; n < mUB; n++) {
      TrialState->xstar->data[n] = xstarqp->data[n];
    }

    emxFree_real_T(&xstarqp);
  }

  emxFree_real_T(&xk);
  return stepSuccess;
}

//
// File trailer for step.cpp
//
// [EOF]
//
