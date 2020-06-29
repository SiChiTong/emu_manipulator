//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: driver.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "driver.h"
#include "BFGSUpdate.h"
#include "computeConstraints_.h"
#include "computeFiniteDifferences.h"
#include "computeMeritFcn.h"
#include "computeObjective_.h"
#include "rt_nonfinite.h"
#include "saveJacobian.h"
#include "step.h"
#include "test_exit.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "updateWorkingSetForNewQP.h"
#include "xgemv.h"
#include <cmath>

// Function Definitions

//
// Arguments    : emxArray_real_T *Hessian
//                e_struct_T *TrialState
//                j_struct_T *MeritFunction
//                f_struct_T *FcnEvaluator
//                d_struct_T *FiniteDifferences
//                c_struct_T *memspace
//                h_struct_T *WorkingSet
//                i_struct_T *QRManager
//                k_struct_T *CholManager
//                g_struct_T *QPObjective
//                const emxArray_real_T *fscales_cineq_constraint
//                const emxArray_real_T *c_runTimeOptions_FiniteDifferen
// Return Type  : void
//
void driver(emxArray_real_T *Hessian, e_struct_T *TrialState, j_struct_T
            *MeritFunction, f_struct_T *FcnEvaluator, d_struct_T
            *FiniteDifferences, c_struct_T *memspace, h_struct_T *WorkingSet,
            i_struct_T *QRManager, k_struct_T *CholManager, g_struct_T
            *QPObjective, const emxArray_real_T *fscales_cineq_constraint, const
            emxArray_real_T *c_runTimeOptions_FiniteDifferen)
{
  e_struct_T b_TrialState;
  emxArray_real_T *y;
  int nVar;
  int mEq;
  int mIneq;
  int mConstr;
  int mLinIneq;
  int mLinEq;
  int ixlast;
  int u1;
  int qpoptions_MaxIterations;
  struct_T Flags;
  int b_nVar;
  int i;
  emxArray_real_T *Cineq_workspace;
  emxArray_real_T *Ceq_workspace;
  emxArray_real_T *c_TrialState;
  b_struct_T expl_temp;
  bool socTaken;
  bool b;
  int b_mLinIneq;
  int b_mLinEq;
  double alpha;
  int exitflagLnSrch;
  double phi_alpha;
  int exitg1;
  int ix;
  int ldJ;
  bool tooSmallX;
  bool exitg2;
  emxInitStruct_struct_T(&b_TrialState);
  emxInit_real_T(&y, 2);
  nVar = WorkingSet->nVar;
  mEq = WorkingSet->sizes[1];
  mIneq = WorkingSet->sizes[2];
  mConstr = (WorkingSet->sizes[1] + WorkingSet->sizes[2]) + WorkingSet->sizes[3];
  mLinIneq = WorkingSet->sizes[2] - TrialState->mNonlinIneq;
  mLinEq = WorkingSet->sizes[1] - TrialState->mNonlinEq;
  ixlast = WorkingSet->nVar;
  u1 = WorkingSet->sizes[2] + WorkingSet->sizes[3];
  if (ixlast > u1) {
    u1 = ixlast;
  }

  qpoptions_MaxIterations = 10 * u1;
  TrialState->steplength = 1.0;
  emxCopyStruct_struct_T1(&b_TrialState, TrialState);
  test_exit(MeritFunction, fscales_cineq_constraint, WorkingSet, &b_TrialState,
            &Flags.gradOK, &Flags.fevalOK, &Flags.done, &Flags.stepAccepted,
            &Flags.failedLineSearch, &Flags.stepType);
  emxCopyStruct_struct_T1(TrialState, &b_TrialState);
  saveJacobian(TrialState, nVar, mIneq, WorkingSet->Aineq,
               b_TrialState.iNonIneq0, mEq, WorkingSet->Aeq,
               b_TrialState.iNonEq0, WorkingSet->ldA);
  TrialState->sqpFval_old = TrialState->sqpFval;
  b_nVar = TrialState->xstarsqp->size[1] - 1;
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = TrialState->xstarsqp_old->size[1];
  emxEnsureCapacity_real_T(y, i);
  u1 = TrialState->xstarsqp_old->size[0] * TrialState->xstarsqp_old->size[1];
  emxFreeStruct_struct_T(&b_TrialState);
  for (i = 0; i < u1; i++) {
    y->data[i] = TrialState->xstarsqp_old->data[i];
  }

  for (u1 = 0; u1 <= b_nVar; u1++) {
    y->data[u1] = TrialState->xstarsqp->data[u1];
  }

  i = TrialState->xstarsqp_old->size[0] * TrialState->xstarsqp_old->size[1];
  TrialState->xstarsqp_old->size[0] = y->size[0];
  TrialState->xstarsqp_old->size[1] = y->size[1];
  emxEnsureCapacity_real_T(TrialState->xstarsqp_old, i);
  u1 = y->size[0] * y->size[1];
  for (i = 0; i < u1; i++) {
    TrialState->xstarsqp_old->data[i] = y->data[i];
  }

  for (u1 = 0; u1 <= b_nVar; u1++) {
    TrialState->grad_old->data[u1] = TrialState->grad->data[u1];
  }

  ixlast = TrialState->mIneq;
  for (u1 = 0; u1 < ixlast; u1++) {
    TrialState->cIneq_old->data[u1] = TrialState->cIneq->data[u1];
  }

  ixlast = TrialState->mEq;
  for (u1 = 0; u1 < ixlast; u1++) {
    TrialState->cEq_old->data[u1] = TrialState->cEq->data[u1];
  }

  if (!Flags.done) {
    TrialState->sqpIterations = 1;
  }

  emxInit_real_T(&Cineq_workspace, 1);
  emxInit_real_T(&Ceq_workspace, 1);
  emxInit_real_T(&c_TrialState, 2);
  while (!Flags.done) {
    while (!(Flags.stepAccepted || Flags.failedLineSearch)) {
      updateWorkingSetForNewQP(WorkingSet, mIneq, TrialState->mNonlinIneq,
        TrialState->cIneq, mEq, TrialState->mNonlinEq, TrialState->cEq);
      expl_temp.DisplayQP = false;
      expl_temp.ObjectiveLimit = -1.0E+20;
      expl_temp.ConstraintTolerance = 0.001;
      expl_temp.OptimalityTolerance = 2.2204460492503131E-14;
      expl_temp.StepTolerance = 1.0E-6;
      expl_temp.MaxIterations = qpoptions_MaxIterations;
      Flags.stepAccepted = step(&Flags.stepType, Hessian, TrialState,
        MeritFunction, memspace, WorkingSet, QRManager, CholManager, QPObjective,
        expl_temp);
      if (Flags.stepAccepted) {
        i = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = TrialState->xstarsqp->size[1];
        emxEnsureCapacity_real_T(y, i);
        u1 = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
        for (i = 0; i < u1; i++) {
          y->data[i] = TrialState->xstarsqp->data[i];
        }

        if (nVar >= 1) {
          ixlast = nVar - 1;
          for (u1 = 0; u1 <= ixlast; u1++) {
            y->data[u1] += TrialState->delta_x->data[u1];
          }
        }

        i = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
        TrialState->xstarsqp->size[0] = y->size[0];
        TrialState->xstarsqp->size[1] = y->size[1];
        emxEnsureCapacity_real_T(TrialState->xstarsqp, i);
        u1 = y->size[0] * y->size[1];
        for (i = 0; i < u1; i++) {
          TrialState->xstarsqp->data[i] = y->data[i];
        }

        i = Cineq_workspace->size[0];
        Cineq_workspace->size[0] = TrialState->cIneq->size[0];
        emxEnsureCapacity_real_T(Cineq_workspace, i);
        u1 = TrialState->cIneq->size[0];
        for (i = 0; i < u1; i++) {
          Cineq_workspace->data[i] = TrialState->cIneq->data[i];
        }

        i = Ceq_workspace->size[0];
        Ceq_workspace->size[0] = TrialState->cEq->size[0];
        emxEnsureCapacity_real_T(Ceq_workspace, i);
        u1 = TrialState->cEq->size[0];
        for (i = 0; i < u1; i++) {
          Ceq_workspace->data[i] = TrialState->cEq->data[i];
        }

        computeObjective_(y, &TrialState->sqpFval, &ixlast);
        if (ixlast == 1) {
          ixlast = computeConstraints_
            (FcnEvaluator->nonlcon.tunableEnvironment.f1,
             FcnEvaluator->nonlcon.tunableEnvironment.f2,
             FcnEvaluator->nonlcon.tunableEnvironment.f3,
             FcnEvaluator->nonlcon.tunableEnvironment.f4,
             FcnEvaluator->nonlcon.tunableEnvironment.f5, FcnEvaluator->mCineq,
             FcnEvaluator->mCeq, y, Cineq_workspace, TrialState->iNonIneq0,
             Ceq_workspace, TrialState->iNonEq0);
        }

        Flags.fevalOK = (ixlast == 1);
        TrialState->FunctionEvaluations++;
        if (mLinIneq > 0) {
          b_xgemv(nVar, mLinIneq, WorkingSet->Aineq, WorkingSet->ldA, y,
                  Cineq_workspace);
        }

        if (mLinEq > 0) {
          for (u1 = 0; u1 < mLinEq; u1++) {
            Ceq_workspace->data[u1] = 0.0;
          }

          b_xgemv(nVar, mLinEq, WorkingSet->Aeq, WorkingSet->ldA, y,
                  Ceq_workspace);
        }

        i = TrialState->cIneq->size[0];
        TrialState->cIneq->size[0] = Cineq_workspace->size[0];
        emxEnsureCapacity_real_T(TrialState->cIneq, i);
        u1 = Cineq_workspace->size[0];
        for (i = 0; i < u1; i++) {
          TrialState->cIneq->data[i] = Cineq_workspace->data[i];
        }

        i = TrialState->cEq->size[0];
        TrialState->cEq->size[0] = Ceq_workspace->size[0];
        emxEnsureCapacity_real_T(TrialState->cEq, i);
        u1 = Ceq_workspace->size[0];
        for (i = 0; i < u1; i++) {
          TrialState->cEq->data[i] = Ceq_workspace->data[i];
        }

        MeritFunction->phiFullStep = computeMeritFcn(MeritFunction->penaltyParam,
          TrialState->sqpFval, Cineq_workspace, mIneq, Ceq_workspace, mEq,
          Flags.fevalOK);
      }

      if ((Flags.stepType == 1) && Flags.stepAccepted && Flags.fevalOK &&
          (MeritFunction->phi < MeritFunction->phiFullStep) &&
          (TrialState->sqpFval < TrialState->sqpFval_old)) {
        Flags.stepType = 3;
        Flags.stepAccepted = false;
      } else {
        if ((Flags.stepType == 3) && Flags.stepAccepted) {
          socTaken = true;
        } else {
          socTaken = false;
        }

        b = Flags.fevalOK;
        b_nVar = WorkingSet->nVar - 1;
        b_mLinIneq = TrialState->mIneq - TrialState->mNonlinIneq;
        b_mLinEq = TrialState->mEq - TrialState->mNonlinEq;
        alpha = 1.0;
        exitflagLnSrch = 1;
        phi_alpha = MeritFunction->phiFullStep;
        for (u1 = 0; u1 <= b_nVar; u1++) {
          TrialState->searchDir->data[u1] = TrialState->delta_x->data[u1];
        }

        do {
          exitg1 = 0;
          if (TrialState->FunctionEvaluations < 10000) {
            if (b && (phi_alpha <= MeritFunction->phi + alpha * 0.0001 *
                      MeritFunction->phiPrimePlus)) {
              exitg1 = 1;
            } else {
              alpha *= 0.7;
              for (u1 = 0; u1 <= b_nVar; u1++) {
                TrialState->delta_x->data[u1] = alpha * TrialState->
                  searchDir->data[u1];
              }

              if (socTaken) {
                phi_alpha = alpha * alpha;
                if ((b_nVar + 1 >= 1) && (!(phi_alpha == 0.0))) {
                  for (u1 = 0; u1 <= b_nVar; u1++) {
                    TrialState->delta_x->data[u1] += phi_alpha *
                      TrialState->socDirection->data[u1];
                  }
                }
              }

              tooSmallX = true;
              u1 = 0;
              exitg2 = false;
              while ((!exitg2) && (u1 <= b_nVar)) {
                phi_alpha = std::abs(TrialState->xstarsqp->data[u1]);
                if ((1.0 > phi_alpha) || rtIsNaN(phi_alpha)) {
                  phi_alpha = 1.0;
                }

                if (1.0E-6 * phi_alpha <= std::abs(TrialState->delta_x->data[u1]))
                {
                  tooSmallX = false;
                  exitg2 = true;
                } else {
                  u1++;
                }
              }

              if (tooSmallX) {
                exitflagLnSrch = -2;
                exitg1 = 1;
              } else {
                for (u1 = 0; u1 <= b_nVar; u1++) {
                  TrialState->xstarsqp->data[u1] = TrialState->
                    xstarsqp_old->data[u1] + TrialState->delta_x->data[u1];
                }

                i = Cineq_workspace->size[0];
                Cineq_workspace->size[0] = TrialState->cIneq->size[0];
                emxEnsureCapacity_real_T(Cineq_workspace, i);
                u1 = TrialState->cIneq->size[0];
                for (i = 0; i < u1; i++) {
                  Cineq_workspace->data[i] = TrialState->cIneq->data[i];
                }

                i = Ceq_workspace->size[0];
                Ceq_workspace->size[0] = TrialState->cEq->size[0];
                emxEnsureCapacity_real_T(Ceq_workspace, i);
                u1 = TrialState->cEq->size[0];
                for (i = 0; i < u1; i++) {
                  Ceq_workspace->data[i] = TrialState->cEq->data[i];
                }

                i = c_TrialState->size[0] * c_TrialState->size[1];
                c_TrialState->size[0] = 1;
                c_TrialState->size[1] = TrialState->xstarsqp->size[1];
                emxEnsureCapacity_real_T(c_TrialState, i);
                u1 = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size
                  [1] - 1;
                for (i = 0; i <= u1; i++) {
                  c_TrialState->data[i] = TrialState->xstarsqp->data[i];
                }

                computeObjective_(c_TrialState, &TrialState->sqpFval, &ixlast);
                if (ixlast == 1) {
                  ixlast = computeConstraints_
                    (FcnEvaluator->nonlcon.tunableEnvironment.f1,
                     FcnEvaluator->nonlcon.tunableEnvironment.f2,
                     FcnEvaluator->nonlcon.tunableEnvironment.f3,
                     FcnEvaluator->nonlcon.tunableEnvironment.f4,
                     FcnEvaluator->nonlcon.tunableEnvironment.f5,
                     FcnEvaluator->mCineq, FcnEvaluator->mCeq,
                     TrialState->xstarsqp, Cineq_workspace,
                     TrialState->iNonIneq0, Ceq_workspace, TrialState->iNonEq0);
                }

                if (b_mLinIneq > 0) {
                  b_xgemv(b_nVar + 1, b_mLinIneq, WorkingSet->Aineq,
                          WorkingSet->ldA, TrialState->xstarsqp, Cineq_workspace);
                }

                if (b_mLinEq > 0) {
                  for (u1 = 0; u1 < b_mLinEq; u1++) {
                    Ceq_workspace->data[u1] = 0.0;
                  }

                  b_xgemv(b_nVar + 1, b_mLinEq, WorkingSet->Aeq, WorkingSet->ldA,
                          TrialState->xstarsqp, Ceq_workspace);
                }

                i = TrialState->cIneq->size[0];
                TrialState->cIneq->size[0] = Cineq_workspace->size[0];
                emxEnsureCapacity_real_T(TrialState->cIneq, i);
                u1 = Cineq_workspace->size[0];
                for (i = 0; i < u1; i++) {
                  TrialState->cIneq->data[i] = Cineq_workspace->data[i];
                }

                i = TrialState->cEq->size[0];
                TrialState->cEq->size[0] = Ceq_workspace->size[0];
                emxEnsureCapacity_real_T(TrialState->cEq, i);
                u1 = Ceq_workspace->size[0];
                for (i = 0; i < u1; i++) {
                  TrialState->cEq->data[i] = Ceq_workspace->data[i];
                }

                TrialState->FunctionEvaluations++;
                b = (ixlast == 1);
                phi_alpha = computeMeritFcn(MeritFunction->penaltyParam,
                  TrialState->sqpFval, Cineq_workspace, TrialState->mIneq,
                  Ceq_workspace, TrialState->mEq, b);
              }
            }
          } else {
            exitflagLnSrch = 0;
            exitg1 = 1;
          }
        } while (exitg1 == 0);

        Flags.fevalOK = b;
        TrialState->steplength = alpha;
        if (exitflagLnSrch > 0) {
          Flags.stepAccepted = true;
        } else {
          Flags.failedLineSearch = true;
        }
      }
    }

    if (Flags.stepAccepted && (!Flags.failedLineSearch)) {
      for (u1 = 0; u1 < nVar; u1++) {
        TrialState->xstarsqp->data[u1] = TrialState->xstarsqp_old->data[u1] +
          TrialState->delta_x->data[u1];
      }

      for (u1 = 0; u1 < mConstr; u1++) {
        TrialState->lambdasqp->data[u1] += TrialState->steplength *
          (TrialState->lambda->data[u1] - TrialState->lambdasqp->data[u1]);
      }

      TrialState->sqpFval_old = TrialState->sqpFval;
      b_nVar = TrialState->xstarsqp->size[1] - 1;
      i = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = TrialState->xstarsqp_old->size[1];
      emxEnsureCapacity_real_T(y, i);
      u1 = TrialState->xstarsqp_old->size[0] * TrialState->xstarsqp_old->size[1];
      for (i = 0; i < u1; i++) {
        y->data[i] = TrialState->xstarsqp_old->data[i];
      }

      for (u1 = 0; u1 <= b_nVar; u1++) {
        y->data[u1] = TrialState->xstarsqp->data[u1];
      }

      i = TrialState->xstarsqp_old->size[0] * TrialState->xstarsqp_old->size[1];
      TrialState->xstarsqp_old->size[0] = y->size[0];
      TrialState->xstarsqp_old->size[1] = y->size[1];
      emxEnsureCapacity_real_T(TrialState->xstarsqp_old, i);
      u1 = y->size[0] * y->size[1];
      for (i = 0; i < u1; i++) {
        TrialState->xstarsqp_old->data[i] = y->data[i];
      }

      for (u1 = 0; u1 <= b_nVar; u1++) {
        TrialState->grad_old->data[u1] = TrialState->grad->data[u1];
      }

      ixlast = TrialState->mIneq;
      for (u1 = 0; u1 < ixlast; u1++) {
        TrialState->cIneq_old->data[u1] = TrialState->cIneq->data[u1];
      }

      ixlast = TrialState->mEq;
      for (u1 = 0; u1 < ixlast; u1++) {
        TrialState->cEq_old->data[u1] = TrialState->cEq->data[u1];
      }

      Flags.gradOK = computeFiniteDifferences(FiniteDifferences,
        TrialState->sqpFval, TrialState->cIneq, TrialState->iNonIneq0,
        TrialState->cEq, TrialState->iNonEq0, TrialState->xstarsqp,
        TrialState->grad, WorkingSet->Aineq, TrialState->iNonIneq0,
        WorkingSet->Aeq, TrialState->iNonEq0, c_runTimeOptions_FiniteDifferen);
      TrialState->FunctionEvaluations += FiniteDifferences->numEvals;
    } else {
      TrialState->sqpFval = TrialState->sqpFval_old;
      ixlast = TrialState->xstarsqp->size[1];
      i = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = TrialState->xstarsqp->size[1];
      emxEnsureCapacity_real_T(y, i);
      u1 = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
      for (i = 0; i < u1; i++) {
        y->data[i] = TrialState->xstarsqp->data[i];
      }

      for (u1 = 0; u1 < ixlast; u1++) {
        y->data[u1] = TrialState->xstarsqp_old->data[u1];
      }

      i = TrialState->xstarsqp->size[0] * TrialState->xstarsqp->size[1];
      TrialState->xstarsqp->size[0] = y->size[0];
      TrialState->xstarsqp->size[1] = y->size[1];
      emxEnsureCapacity_real_T(TrialState->xstarsqp, i);
      u1 = y->size[0] * y->size[1];
      for (i = 0; i < u1; i++) {
        TrialState->xstarsqp->data[i] = y->data[i];
      }

      ixlast = TrialState->mIneq;
      for (u1 = 0; u1 < ixlast; u1++) {
        TrialState->cIneq->data[u1] = TrialState->cIneq_old->data[u1];
      }

      ixlast = TrialState->mEq;
      for (u1 = 0; u1 < ixlast; u1++) {
        TrialState->cEq->data[u1] = TrialState->cEq_old->data[u1];
      }
    }

    b_test_exit(&Flags, memspace, MeritFunction, fscales_cineq_constraint,
                WorkingSet, TrialState, QRManager);
    if ((!Flags.done) && Flags.stepAccepted) {
      Flags.stepAccepted = false;
      Flags.stepType = 1;
      Flags.failedLineSearch = false;
      ix = (mEq + TrialState->iNonIneq0) - 1;
      ldJ = WorkingSet->ldA;
      for (u1 = 0; u1 < nVar; u1++) {
        TrialState->delta_gradLag->data[u1] = TrialState->grad->data[u1];
      }

      if (nVar >= 1) {
        ixlast = nVar - 1;
        for (u1 = 0; u1 <= ixlast; u1++) {
          TrialState->delta_gradLag->data[u1] += -TrialState->grad_old->data[u1];
        }
      }

      u1 = WorkingSet->ldA * (TrialState->iNonEq0 - 1) + 1;
      if (nVar != 0) {
        ixlast = TrialState->iNonEq0;
        i = u1 + WorkingSet->ldA * (TrialState->mNonlinEq - 1);
        for (b_nVar = u1; ldJ < 0 ? b_nVar >= i : b_nVar <= i; b_nVar += ldJ) {
          b_mLinIneq = 0;
          b_mLinEq = (b_nVar + nVar) - 1;
          for (exitflagLnSrch = b_nVar; exitflagLnSrch <= b_mLinEq;
               exitflagLnSrch++) {
            TrialState->delta_gradLag->data[b_mLinIneq] += WorkingSet->Aeq->
              data[exitflagLnSrch - 1] * TrialState->lambdasqp->data[ixlast - 1];
            b_mLinIneq++;
          }

          ixlast++;
        }

        ixlast = TrialState->iNonEq0;
        i = WorkingSet->ldA * (TrialState->mNonlinEq - 1) + 1;
        for (b_nVar = 1; ldJ < 0 ? b_nVar >= i : b_nVar <= i; b_nVar += ldJ) {
          b_mLinIneq = 0;
          b_mLinEq = (b_nVar + nVar) - 1;
          for (exitflagLnSrch = b_nVar; exitflagLnSrch <= b_mLinEq;
               exitflagLnSrch++) {
            TrialState->delta_gradLag->data[b_mLinIneq] +=
              TrialState->JacCeqTrans_old->data[exitflagLnSrch - 1] *
              -TrialState->lambdasqp->data[ixlast - 1];
            b_mLinIneq++;
          }

          ixlast++;
        }
      }

      u1 = WorkingSet->ldA * (TrialState->iNonIneq0 - 1) + 1;
      if (nVar != 0) {
        ixlast = ix;
        i = u1 + WorkingSet->ldA * (TrialState->mNonlinIneq - 1);
        for (b_nVar = u1; ldJ < 0 ? b_nVar >= i : b_nVar <= i; b_nVar += ldJ) {
          b_mLinIneq = 0;
          b_mLinEq = (b_nVar + nVar) - 1;
          for (exitflagLnSrch = b_nVar; exitflagLnSrch <= b_mLinEq;
               exitflagLnSrch++) {
            TrialState->delta_gradLag->data[b_mLinIneq] += WorkingSet->
              Aineq->data[exitflagLnSrch - 1] * TrialState->lambdasqp->
              data[ixlast];
            b_mLinIneq++;
          }

          ixlast++;
        }

        i = WorkingSet->ldA * (TrialState->mNonlinIneq - 1) + 1;
        for (b_nVar = 1; ldJ < 0 ? b_nVar >= i : b_nVar <= i; b_nVar += ldJ) {
          b_mLinIneq = 0;
          b_mLinEq = (b_nVar + nVar) - 1;
          for (exitflagLnSrch = b_nVar; exitflagLnSrch <= b_mLinEq;
               exitflagLnSrch++) {
            TrialState->delta_gradLag->data[b_mLinIneq] +=
              TrialState->JacCineqTrans_old->data[exitflagLnSrch - 1] *
              -TrialState->lambdasqp->data[ix];
            b_mLinIneq++;
          }

          ix++;
        }
      }

      saveJacobian(TrialState, nVar, mIneq, WorkingSet->Aineq,
                   TrialState->iNonIneq0, mEq, WorkingSet->Aeq,
                   TrialState->iNonEq0, WorkingSet->ldA);
      BFGSUpdate(nVar, Hessian, TrialState->delta_x, TrialState->delta_gradLag,
                 memspace->workspace_double);
      TrialState->sqpIterations++;
    }
  }

  emxFree_real_T(&c_TrialState);
  emxFree_real_T(&y);
  emxFree_real_T(&Ceq_workspace);
  emxFree_real_T(&Cineq_workspace);
}

//
// File trailer for driver.cpp
//
// [EOF]
//
