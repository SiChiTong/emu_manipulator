//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: driver.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "driver.h"
#include "BFGSUpdate.h"
#include "computeDualFeasError.h"
#include "computeFiniteDifferences.h"
#include "computeGradLag.h"
#include "computePrimalFeasError.h"
#include "evalObjAndConstr.h"
#include "ixamax.h"
#include "linesearch.h"
#include "rt_nonfinite.h"
#include "saveJacobian.h"
#include "step.h"
#include "test_exit.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "updateWorkingSetForNewQP.h"
#include "xgemv.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : emxArray_real_T *Hessian
//                const double beq[12]
//                const emxArray_real_T *lb
//                e_struct_T *TrialState
//                j_struct_T *MeritFunction
//                f_struct_T *FcnEvaluator
//                d_struct_T *FiniteDifferences
//                c_struct_T *memspace
//                h_struct_T *WorkingSet
//                i_struct_T *QRManager
//                k_struct_T *CholManager
//                g_struct_T *QPObjective
//                const emxArray_real_T *c_runTimeOptions_FiniteDifferen
// Return Type  : void
//
void driver(emxArray_real_T *Hessian, const double beq[12], const
            emxArray_real_T *lb, e_struct_T *TrialState, j_struct_T
            *MeritFunction, f_struct_T *FcnEvaluator, d_struct_T
            *FiniteDifferences, c_struct_T *memspace, h_struct_T *WorkingSet,
            i_struct_T *QRManager, k_struct_T *CholManager, g_struct_T
            *QPObjective, const emxArray_real_T *c_runTimeOptions_FiniteDifferen)
{
  e_struct_T b_TrialState;
  int nVar;
  int mFixed;
  int mEq;
  int mLB;
  int mUB;
  int mConstr_tmp;
  int mLinEq;
  int b_nVar;
  int ixlast;
  int qpoptions_MaxIterations;
  struct_T Flags;
  double optimRelativeFactor;
  bool isFeasible;
  double constrViolationIneq;
  int k;
  emxArray_real_T *y;
  int i;
  emxArray_real_T *workspaceEq;
  b_struct_T expl_temp;
  int ix;
  int b_ix;
  int ldJ;
  int iy;
  int i1;
  int ia;
  emxInitStruct_struct_T(&b_TrialState);
  nVar = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0];
  mEq = WorkingSet->sizes[1];
  mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  mConstr_tmp = (((WorkingSet->sizes[0] + WorkingSet->sizes[1]) +
                  WorkingSet->sizes[3]) + WorkingSet->sizes[4]) + 11;
  mLinEq = WorkingSet->sizes[1] - TrialState->mNonlinEq;
  b_nVar = WorkingSet->nVar;
  ixlast = ((WorkingSet->sizes[3] + WorkingSet->sizes[4]) + (WorkingSet->sizes[0]
             << 1)) + 12;
  if (b_nVar > ixlast) {
    ixlast = b_nVar;
  }

  qpoptions_MaxIterations = 10 * ixlast;
  TrialState->steplength = 1.0;
  emxCopyStruct_struct_T1(&b_TrialState, TrialState);
  Flags.fevalOK = true;
  Flags.stepAccepted = false;
  Flags.failedLineSearch = false;
  Flags.stepType = 1;
  computeGradLag(b_TrialState.gradLag, WorkingSet->ldA, WorkingSet->nVar,
                 b_TrialState.grad, WorkingSet->Aineq, WorkingSet->sizes[1],
                 WorkingSet->Aeq, WorkingSet->indexFixed, WorkingSet->sizes[0],
                 WorkingSet->indexLB, WorkingSet->sizes[3], WorkingSet->indexUB,
                 WorkingSet->sizes[4], b_TrialState.lambdasqp);
  optimRelativeFactor = std::abs(b_TrialState.grad->data[ixamax(WorkingSet->nVar,
    b_TrialState.grad) - 1]);
  if ((1.0 > optimRelativeFactor) || rtIsNaN(optimRelativeFactor)) {
    optimRelativeFactor = 1.0;
  }

  if (rtIsInf(optimRelativeFactor) || rtIsNaN(optimRelativeFactor)) {
    optimRelativeFactor = 1.0;
  }

  MeritFunction->nlpPrimalFeasError = computePrimalFeasError
    (b_TrialState.xstarsqp, b_TrialState.cIneq, WorkingSet->sizes[1] -
     b_TrialState.mNonlinEq, b_TrialState.mNonlinEq, b_TrialState.cEq,
     WorkingSet->indexLB, WorkingSet->sizes[3], lb, WorkingSet->indexUB,
     WorkingSet->sizes[4]);
  if ((1.0 > MeritFunction->nlpPrimalFeasError) || rtIsNaN
      (MeritFunction->nlpPrimalFeasError)) {
    MeritFunction->feasRelativeFactor = 1.0;
  } else {
    MeritFunction->feasRelativeFactor = MeritFunction->nlpPrimalFeasError;
  }

  isFeasible = (MeritFunction->nlpPrimalFeasError <= 0.002 *
                MeritFunction->feasRelativeFactor);
  computeDualFeasError(WorkingSet->nVar, b_TrialState.gradLag, &Flags.gradOK,
                       &MeritFunction->nlpDualFeasError);
  if (!Flags.gradOK) {
    Flags.done = true;
    if (isFeasible) {
      b_TrialState.sqpExitFlag = 2;
    } else {
      b_TrialState.sqpExitFlag = -2;
    }
  } else {
    MeritFunction->nlpComplError = 0.0;
    constrViolationIneq = MeritFunction->nlpDualFeasError;
    if (!(constrViolationIneq > 0.0)) {
      constrViolationIneq = 0.0;
    }

    MeritFunction->firstOrderOpt = constrViolationIneq;
    for (k = 0; k <= mConstr_tmp; k++) {
      b_TrialState.lambdasqp_old->data[k] = b_TrialState.lambdasqp->data[k];
    }

    if (isFeasible && (MeritFunction->nlpDualFeasError <= 1.0E-6 *
                       optimRelativeFactor)) {
      Flags.done = true;
      b_TrialState.sqpExitFlag = 1;
    } else {
      Flags.done = false;
      if (isFeasible && (b_TrialState.sqpFval < -1.0E+20)) {
        Flags.done = true;
        b_TrialState.sqpExitFlag = -3;
      } else {
        if (b_TrialState.FunctionEvaluations >= 10000) {
          Flags.done = true;
          b_TrialState.sqpExitFlag = 0;
        }
      }
    }
  }

  emxInit_real_T(&y, 2);
  emxCopyStruct_struct_T1(TrialState, &b_TrialState);
  saveJacobian(TrialState, WorkingSet->nVar, WorkingSet->Aineq,
               WorkingSet->sizes[1], WorkingSet->Aeq, b_TrialState.iNonEq0,
               WorkingSet->ldA);
  TrialState->sqpFval_old = TrialState->sqpFval;
  b_nVar = TrialState->xstarsqp->size[1] - 1;
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = TrialState->xstarsqp_old->size[1];
  emxEnsureCapacity_real_T(y, i);
  ixlast = TrialState->xstarsqp_old->size[0] * TrialState->xstarsqp_old->size[1];
  emxFreeStruct_struct_T(&b_TrialState);
  for (i = 0; i < ixlast; i++) {
    y->data[i] = TrialState->xstarsqp_old->data[i];
  }

  for (k = 0; k <= b_nVar; k++) {
    y->data[k] = TrialState->xstarsqp->data[k];
  }

  i = TrialState->xstarsqp_old->size[0] * TrialState->xstarsqp_old->size[1];
  TrialState->xstarsqp_old->size[0] = y->size[0];
  TrialState->xstarsqp_old->size[1] = y->size[1];
  emxEnsureCapacity_real_T(TrialState->xstarsqp_old, i);
  ixlast = y->size[0] * y->size[1];
  for (i = 0; i < ixlast; i++) {
    TrialState->xstarsqp_old->data[i] = y->data[i];
  }

  for (k = 0; k <= b_nVar; k++) {
    TrialState->grad_old->data[k] = TrialState->grad->data[k];
  }

  std::memcpy(&TrialState->cIneq_old[0], &TrialState->cIneq[0], 12U * sizeof
              (double));
  b_nVar = TrialState->mEq;
  for (k = 0; k < b_nVar; k++) {
    TrialState->cEq_old->data[k] = TrialState->cEq->data[k];
  }

  if (!Flags.done) {
    TrialState->sqpIterations = 1;
  }

  emxInit_real_T(&workspaceEq, 1);
  while (!Flags.done) {
    while (!(Flags.stepAccepted || Flags.failedLineSearch)) {
      b_updateWorkingSetForNewQP(TrialState->xstarsqp, WorkingSet,
        TrialState->cIneq, mEq, TrialState->mNonlinEq, TrialState->cEq, mLB, lb,
        mUB, mFixed);
      expl_temp.DisplayQP = false;
      expl_temp.ObjectiveLimit = -1.0E+20;
      expl_temp.ConstraintTolerance = 0.002;
      expl_temp.OptimalityTolerance = 2.2204460492503131E-14;
      expl_temp.StepTolerance = 1.0E-6;
      expl_temp.MaxIterations = qpoptions_MaxIterations;
      Flags.stepAccepted = step(&Flags.stepType, Hessian, lb, TrialState,
        MeritFunction, memspace, WorkingSet, QRManager, CholManager, QPObjective,
        expl_temp);
      if (Flags.stepAccepted) {
        i = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = TrialState->xstarsqp->size[1];
        emxEnsureCapacity_real_T(y, i);
        ixlast = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
        for (i = 0; i < ixlast; i++) {
          y->data[i] = TrialState->xstarsqp->data[i];
        }

        if (nVar >= 1) {
          ixlast = nVar - 1;
          for (k = 0; k <= ixlast; k++) {
            y->data[k] += TrialState->delta_x->data[k];
          }
        }

        i = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
        TrialState->xstarsqp->size[0] = y->size[0];
        TrialState->xstarsqp->size[1] = y->size[1];
        emxEnsureCapacity_real_T(TrialState->xstarsqp, i);
        ixlast = y->size[0] * y->size[1];
        for (i = 0; i < ixlast; i++) {
          TrialState->xstarsqp->data[i] = y->data[i];
        }

        evalObjAndConstr(FcnEvaluator->nonlcon.tunableEnvironment.f1,
                         FcnEvaluator->nonlcon.tunableEnvironment.f2,
                         FcnEvaluator->nonlcon.tunableEnvironment.f3,
                         FcnEvaluator->nonlcon.tunableEnvironment.f4,
                         FcnEvaluator->nonlcon.tunableEnvironment.f5,
                         FcnEvaluator->mCeq, y, TrialState->cIneq,
                         TrialState->cEq, TrialState->iNonEq0,
                         &TrialState->sqpFval, &b_nVar);
        Flags.fevalOK = (b_nVar == 1);
        TrialState->FunctionEvaluations++;
        i = workspaceEq->size[0];
        workspaceEq->size[0] = TrialState->cEq->size[0];
        emxEnsureCapacity_real_T(workspaceEq, i);
        ixlast = TrialState->cEq->size[0];
        for (i = 0; i < ixlast; i++) {
          workspaceEq->data[i] = TrialState->cEq->data[i];
        }

        if (mLinEq > 0) {
          for (k = 0; k < mLinEq; k++) {
            workspaceEq->data[k] = beq[k];
          }

          xgemv(nVar, mLinEq, WorkingSet->Aeq, WorkingSet->ldA, y, workspaceEq);
        }

        i = TrialState->cEq->size[0];
        TrialState->cEq->size[0] = workspaceEq->size[0];
        emxEnsureCapacity_real_T(TrialState->cEq, i);
        ixlast = workspaceEq->size[0];
        for (i = 0; i < ixlast; i++) {
          TrialState->cEq->data[i] = workspaceEq->data[i];
        }

        if (Flags.fevalOK) {
          optimRelativeFactor = 0.0;
          if (mEq >= 1) {
            for (k = 0; k < mEq; k++) {
              optimRelativeFactor += std::abs(workspaceEq->data[k]);
            }
          }

          constrViolationIneq = 0.0;
          for (b_nVar = 0; b_nVar < 12; b_nVar++) {
            if (TrialState->cIneq[b_nVar] > 0.0) {
              constrViolationIneq += TrialState->cIneq[b_nVar];
            }
          }

          MeritFunction->phiFullStep = TrialState->sqpFval +
            MeritFunction->penaltyParam * (optimRelativeFactor +
            constrViolationIneq);
        } else {
          MeritFunction->phiFullStep = rtInf;
        }
      }

      if ((Flags.stepType == 1) && Flags.stepAccepted && Flags.fevalOK &&
          (MeritFunction->phi < MeritFunction->phiFullStep) &&
          (TrialState->sqpFval < TrialState->sqpFval_old)) {
        Flags.stepType = 3;
        Flags.stepAccepted = false;
      } else {
        if ((Flags.stepType == 3) && Flags.stepAccepted) {
          isFeasible = true;
        } else {
          isFeasible = false;
        }

        linesearch(&Flags.fevalOK, beq, WorkingSet->nVar, WorkingSet->ldA,
                   WorkingSet->Aeq, TrialState, MeritFunction->penaltyParam,
                   MeritFunction->phi, MeritFunction->phiPrimePlus,
                   MeritFunction->phiFullStep,
                   FcnEvaluator->nonlcon.tunableEnvironment.f1,
                   FcnEvaluator->nonlcon.tunableEnvironment.f2,
                   FcnEvaluator->nonlcon.tunableEnvironment.f3,
                   FcnEvaluator->nonlcon.tunableEnvironment.f4,
                   FcnEvaluator->nonlcon.tunableEnvironment.f5,
                   FcnEvaluator->mCeq, isFeasible, &optimRelativeFactor, &b_nVar);
        TrialState->steplength = optimRelativeFactor;
        if (b_nVar > 0) {
          Flags.stepAccepted = true;
        } else {
          Flags.failedLineSearch = true;
        }
      }
    }

    if (Flags.stepAccepted && (!Flags.failedLineSearch)) {
      for (b_nVar = 0; b_nVar < nVar; b_nVar++) {
        TrialState->xstarsqp->data[b_nVar] = TrialState->xstarsqp_old->
          data[b_nVar] + TrialState->delta_x->data[b_nVar];
      }

      for (b_nVar = 0; b_nVar <= mConstr_tmp; b_nVar++) {
        TrialState->lambdasqp->data[b_nVar] += TrialState->steplength *
          (TrialState->lambda->data[b_nVar] - TrialState->lambdasqp->data[b_nVar]);
      }

      TrialState->sqpFval_old = TrialState->sqpFval;
      b_nVar = TrialState->xstarsqp->size[1] - 1;
      i = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = TrialState->xstarsqp_old->size[1];
      emxEnsureCapacity_real_T(y, i);
      ixlast = TrialState->xstarsqp_old->size[0] * TrialState->
        xstarsqp_old->size[1];
      for (i = 0; i < ixlast; i++) {
        y->data[i] = TrialState->xstarsqp_old->data[i];
      }

      for (k = 0; k <= b_nVar; k++) {
        y->data[k] = TrialState->xstarsqp->data[k];
      }

      i = TrialState->xstarsqp_old->size[0] * TrialState->xstarsqp_old->size[1];
      TrialState->xstarsqp_old->size[0] = y->size[0];
      TrialState->xstarsqp_old->size[1] = y->size[1];
      emxEnsureCapacity_real_T(TrialState->xstarsqp_old, i);
      ixlast = y->size[0] * y->size[1];
      for (i = 0; i < ixlast; i++) {
        TrialState->xstarsqp_old->data[i] = y->data[i];
      }

      for (k = 0; k <= b_nVar; k++) {
        TrialState->grad_old->data[k] = TrialState->grad->data[k];
      }

      std::memcpy(&TrialState->cIneq_old[0], &TrialState->cIneq[0], 12U * sizeof
                  (double));
      b_nVar = TrialState->mEq;
      for (k = 0; k < b_nVar; k++) {
        TrialState->cEq_old->data[k] = TrialState->cEq->data[k];
      }

      Flags.gradOK = computeFiniteDifferences(FiniteDifferences,
        TrialState->sqpFval, TrialState->cIneq, TrialState->cEq,
        TrialState->iNonEq0, TrialState->xstarsqp, TrialState->grad,
        WorkingSet->Aineq, WorkingSet->Aeq, TrialState->iNonEq0, lb,
        c_runTimeOptions_FiniteDifferen);
      TrialState->FunctionEvaluations += FiniteDifferences->numEvals;
    } else {
      TrialState->sqpFval = TrialState->sqpFval_old;
      b_nVar = TrialState->xstarsqp->size[1];
      i = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = TrialState->xstarsqp->size[1];
      emxEnsureCapacity_real_T(y, i);
      ixlast = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
      for (i = 0; i < ixlast; i++) {
        y->data[i] = TrialState->xstarsqp->data[i];
      }

      for (k = 0; k < b_nVar; k++) {
        y->data[k] = TrialState->xstarsqp_old->data[k];
      }

      i = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
      TrialState->xstarsqp->size[0] = y->size[0];
      TrialState->xstarsqp->size[1] = y->size[1];
      emxEnsureCapacity_real_T(TrialState->xstarsqp, i);
      ixlast = y->size[0] * y->size[1];
      for (i = 0; i < ixlast; i++) {
        TrialState->xstarsqp->data[i] = y->data[i];
      }

      std::memcpy(&TrialState->cIneq[0], &TrialState->cIneq_old[0], 12U * sizeof
                  (double));
      b_nVar = TrialState->mEq;
      for (k = 0; k < b_nVar; k++) {
        TrialState->cEq->data[k] = TrialState->cEq_old->data[k];
      }
    }

    test_exit(&Flags, memspace, MeritFunction, WorkingSet, TrialState, QRManager,
              lb);
    if ((!Flags.done) && Flags.stepAccepted) {
      Flags.stepAccepted = false;
      Flags.stepType = 1;
      Flags.failedLineSearch = false;
      ix = (mFixed + TrialState->iNonEq0) - 1;
      b_ix = mFixed + mEq;
      ldJ = WorkingSet->ldA;
      for (k = 0; k < nVar; k++) {
        TrialState->delta_gradLag->data[k] = TrialState->grad->data[k];
      }

      if (nVar >= 1) {
        ixlast = nVar - 1;
        for (k = 0; k <= ixlast; k++) {
          TrialState->delta_gradLag->data[k] += -TrialState->grad_old->data[k];
        }
      }

      b_nVar = WorkingSet->ldA * (TrialState->iNonEq0 - 1) + 1;
      if (nVar != 0) {
        ixlast = ix;
        i = b_nVar + WorkingSet->ldA * (TrialState->mNonlinEq - 1);
        for (k = b_nVar; ldJ < 0 ? k >= i : k <= i; k += ldJ) {
          iy = 0;
          i1 = (k + nVar) - 1;
          for (ia = k; ia <= i1; ia++) {
            TrialState->delta_gradLag->data[iy] += WorkingSet->Aeq->data[ia - 1]
              * TrialState->lambdasqp->data[ixlast];
            iy++;
          }

          ixlast++;
        }

        i = WorkingSet->ldA * (TrialState->mNonlinEq - 1) + 1;
        for (k = 1; ldJ < 0 ? k >= i : k <= i; k += ldJ) {
          iy = 0;
          i1 = (k + nVar) - 1;
          for (ia = k; ia <= i1; ia++) {
            TrialState->delta_gradLag->data[iy] += TrialState->
              JacCeqTrans_old->data[ia - 1] * -TrialState->lambdasqp->data[ix];
            iy++;
          }

          ix++;
        }

        ixlast = b_ix;
        i = WorkingSet->ldA * 11 + 1;
        for (k = 1; ldJ < 0 ? k >= i : k <= i; k += ldJ) {
          iy = 0;
          i1 = (k + nVar) - 1;
          for (ia = k; ia <= i1; ia++) {
            TrialState->delta_gradLag->data[iy] += WorkingSet->Aineq->data[ia -
              1] * TrialState->lambdasqp->data[ixlast];
            iy++;
          }

          ixlast++;
        }

        for (k = 1; ldJ < 0 ? k >= i : k <= i; k += ldJ) {
          iy = 0;
          i1 = (k + nVar) - 1;
          for (ia = k; ia <= i1; ia++) {
            TrialState->delta_gradLag->data[iy] += TrialState->
              JacCineqTrans_old->data[ia - 1] * -TrialState->lambdasqp->
              data[b_ix];
            iy++;
          }

          b_ix++;
        }
      }

      saveJacobian(TrialState, nVar, WorkingSet->Aineq, mEq, WorkingSet->Aeq,
                   TrialState->iNonEq0, WorkingSet->ldA);
      BFGSUpdate(nVar, Hessian, TrialState->delta_x, TrialState->delta_gradLag,
                 memspace->workspace_double);
      TrialState->sqpIterations++;
    }
  }

  emxFree_real_T(&y);
  emxFree_real_T(&workspaceEq);
}

//
// File trailer for driver.cpp
//
// [EOF]
//
