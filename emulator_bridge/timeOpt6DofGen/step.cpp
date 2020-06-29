//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: step.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "step.h"
#include "addAeqConstr.h"
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
bool step(int *STEP_TYPE, emxArray_real_T *Hessian, e_struct_T *TrialState,
          j_struct_T *MeritFunction, c_struct_T *memspace, h_struct_T
          *WorkingSet, i_struct_T *QRManager, k_struct_T *CholManager,
          g_struct_T *QPObjective, b_struct_T qpoptions)
{
  bool stepSuccess;
  int nVar;
  int k;
  e_struct_T b_TrialState;
  emxArray_real_T *r;
  int exitg1;
  bool guard1 = false;
  int mIneq;
  int kend;
  double penaltyParamTrial;
  bool nonlinEqRemoved;
  double constrViolationEq;
  int idx;
  double constrViolationIneq;
  int b_nVar;
  stepSuccess = true;
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

  emxInitStruct_struct_T(&b_TrialState);
  emxInit_real_T(&r, 1);
  do {
    exitg1 = 0;
    guard1 = false;
    switch (*STEP_TYPE) {
     case 1:
      emxCopyStruct_struct_T1(&b_TrialState, TrialState);
      b_driver(Hessian, TrialState->grad, &b_TrialState, memspace, WorkingSet,
               QRManager, CholManager, QPObjective, qpoptions);
      if (b_TrialState.state > 0) {
        mIneq = WorkingSet->sizes[2];
        penaltyParamTrial = MeritFunction->penaltyParam;
        constrViolationEq = 0.0;
        if (WorkingSet->sizes[1] >= 1) {
          kend = WorkingSet->sizes[1];
          for (k = 0; k < kend; k++) {
            constrViolationEq += std::abs(b_TrialState.cEq->data[k]);
          }
        }

        constrViolationIneq = 0.0;
        for (idx = 0; idx < mIneq; idx++) {
          if (b_TrialState.cIneq->data[idx] > 0.0) {
            constrViolationIneq += b_TrialState.cIneq->data[idx];
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
        mIneq = b_TrialState.mNonlinEq;
        for (idx = 0; idx < mIneq; idx++) {
          kend = b_TrialState.iNonEq0 + idx;
          WorkingSet->Wlocalidx->data[kend - 1] = kend;
        }
      }

      emxCopyStruct_struct_T1(TrialState, &b_TrialState);
      if ((b_TrialState.state <= 0) && (b_TrialState.state != -6)) {
        *STEP_TYPE = 2;
      } else {
        mIneq = TrialState->delta_x->size[0];
        TrialState->delta_x->size[0] = b_TrialState.delta_x->size[0];
        emxEnsureCapacity_real_T(TrialState->delta_x, mIneq);
        kend = b_TrialState.delta_x->size[0];
        for (mIneq = 0; mIneq < kend; mIneq++) {
          TrialState->delta_x->data[mIneq] = b_TrialState.delta_x->data[mIneq];
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
      mIneq = TrialState->delta_x->size[0];
      TrialState->delta_x->size[0] = b_TrialState.delta_x->size[0];
      emxEnsureCapacity_real_T(TrialState->delta_x, mIneq);
      kend = b_TrialState.delta_x->size[0];
      for (mIneq = 0; mIneq < kend; mIneq++) {
        TrialState->delta_x->data[mIneq] = b_TrialState.delta_x->data[mIneq];
      }

      for (k = 0; k <= nVar; k++) {
        TrialState->delta_x->data[k] = b_TrialState.xstar->data[k];
      }

      guard1 = true;
      break;

     default:
      mIneq = r->size[0];
      r->size[0] = TrialState->grad->size[0];
      emxEnsureCapacity_real_T(r, mIneq);
      kend = TrialState->grad->size[0];
      for (mIneq = 0; mIneq < kend; mIneq++) {
        r->data[mIneq] = TrialState->grad->data[mIneq];
      }

      stepSuccess = soc(Hessian, r, TrialState, memspace, WorkingSet, QRManager,
                        CholManager, QPObjective, qpoptions);
      if (stepSuccess && (TrialState->state != -6)) {
        for (idx = 0; idx <= nVar; idx++) {
          TrialState->delta_x->data[idx] = TrialState->xstar->data[idx] +
            TrialState->socDirection->data[idx];
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
        for (idx = 0; idx <= b_nVar; idx++) {
          penaltyParamTrial = std::abs(TrialState->grad->data[idx]);
          if ((!(constrViolationEq > penaltyParamTrial)) && (!rtIsNaN
               (penaltyParamTrial))) {
            constrViolationEq = penaltyParamTrial;
          }

          penaltyParamTrial = std::abs(TrialState->xstar->data[idx]);
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

        for (idx = 0; idx <= b_nVar; idx++) {
          kend = (b_nVar + 1) * idx;
          for (k = 0; k < idx; k++) {
            Hessian->data[kend + k] = 0.0;
          }

          Hessian->data[idx + Hessian->size[0] * idx] = constrViolationEq;
          kend += idx;
          mIneq = b_nVar - idx;
          for (k = 0; k < mIneq; k++) {
            Hessian->data[(kend + k) + 1] = 0.0;
          }
        }
      }
    }
  } while (exitg1 == 0);

  emxFree_real_T(&r);
  emxFreeStruct_struct_T(&b_TrialState);
  return stepSuccess;
}

//
// File trailer for step.cpp
//
// [EOF]
//
