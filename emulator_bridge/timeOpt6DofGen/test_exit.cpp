//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: test_exit.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "test_exit.h"
#include "computeComplError.h"
#include "computeDualFeasError.h"
#include "computePrimalFeasError.h"
#include "computeQ_.h"
#include "factorQRE.h"
#include "ixamax.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "updateWorkingSetForNewQP.h"
#include "xgemv.h"
#include <cmath>

// Function Definitions

//
// Arguments    : struct_T *Flags
//                c_struct_T *memspace
//                j_struct_T *MeritFunction
//                const emxArray_real_T *fscales_cineq_constraint
//                h_struct_T *WorkingSet
//                e_struct_T *TrialState
//                i_struct_T *QRManager
// Return Type  : void
//
void b_test_exit(struct_T *Flags, c_struct_T *memspace, j_struct_T
                 *MeritFunction, const emxArray_real_T *fscales_cineq_constraint,
                 h_struct_T *WorkingSet, e_struct_T *TrialState, i_struct_T
                 *QRManager)
{
  int nVar;
  int mEq;
  int mIneq;
  int mLB;
  int iL0;
  int mLambda;
  int b_iL0;
  int ix;
  int i;
  int jjA;
  int iy;
  int rankR;
  int fullRank_R;
  double scaleTol;
  double optimRelativeFactor;
  bool isFeasible;
  emxArray_real_T *lambdaLSQ;
  emxArray_real_T *workspace;
  bool guard1 = false;
  bool dxTooSmall;
  double nlpComplErrorTmp;
  bool exitg1;
  double d;
  double b_MeritFunction;
  nVar = WorkingSet->nVar;
  mEq = WorkingSet->sizes[1];
  mIneq = WorkingSet->sizes[2];
  mLB = WorkingSet->sizes[3] - 1;
  iL0 = WorkingSet->sizes[1] + WorkingSet->sizes[2];
  mLambda = (iL0 + WorkingSet->sizes[3]) - 1;
  for (b_iL0 = 0; b_iL0 < nVar; b_iL0++) {
    TrialState->gradLag->data[b_iL0] = TrialState->grad->data[b_iL0];
  }

  b_iL0 = WorkingSet->ldA;
  if ((WorkingSet->nVar != 0) && (WorkingSet->sizes[1] != 0)) {
    ix = 0;
    i = WorkingSet->ldA * (WorkingSet->sizes[1] - 1) + 1;
    for (jjA = 1; b_iL0 < 0 ? jjA >= i : jjA <= i; jjA += b_iL0) {
      iy = 0;
      rankR = (jjA + WorkingSet->nVar) - 1;
      for (fullRank_R = jjA; fullRank_R <= rankR; fullRank_R++) {
        TrialState->gradLag->data[iy] += WorkingSet->Aeq->data[fullRank_R - 1] *
          TrialState->lambdasqp->data[ix];
        iy++;
      }

      ix++;
    }
  }

  b_iL0 = WorkingSet->ldA;
  if ((WorkingSet->nVar != 0) && (WorkingSet->sizes[2] != 0)) {
    ix = WorkingSet->sizes[1];
    i = WorkingSet->ldA * (WorkingSet->sizes[2] - 1) + 1;
    for (jjA = 1; b_iL0 < 0 ? jjA >= i : jjA <= i; jjA += b_iL0) {
      iy = 0;
      rankR = (jjA + WorkingSet->nVar) - 1;
      for (fullRank_R = jjA; fullRank_R <= rankR; fullRank_R++) {
        TrialState->gradLag->data[iy] += WorkingSet->Aineq->data[fullRank_R - 1]
          * TrialState->lambdasqp->data[ix];
        iy++;
      }

      ix++;
    }
  }

  b_iL0 = iL0;
  for (jjA = 0; jjA <= mLB; jjA++) {
    TrialState->gradLag->data[WorkingSet->indexLB->data[jjA] - 1] -=
      TrialState->lambdasqp->data[b_iL0];
    b_iL0++;
  }

  scaleTol = std::abs(TrialState->grad->data[ixamax(WorkingSet->nVar,
    TrialState->grad) - 1]);
  if ((1.0 > scaleTol) || rtIsNaN(scaleTol)) {
    optimRelativeFactor = 1.0;
  } else {
    optimRelativeFactor = scaleTol;
  }

  if (rtIsInf(optimRelativeFactor) || rtIsNaN(optimRelativeFactor)) {
    optimRelativeFactor = 1.0;
  }

  MeritFunction->nlpPrimalFeasError = computePrimalFeasError(WorkingSet->sizes[2]
    - TrialState->mNonlinIneq, TrialState->mNonlinIneq, TrialState->cIneq,
    WorkingSet->sizes[1] - TrialState->mNonlinEq, TrialState->mNonlinEq,
    TrialState->cEq, WorkingSet->sizes[3]);
  if (TrialState->sqpIterations == 0) {
    if ((1.0 > MeritFunction->nlpPrimalFeasError) || rtIsNaN
        (MeritFunction->nlpPrimalFeasError)) {
      MeritFunction->feasRelativeFactor = 1.0;
    } else {
      MeritFunction->feasRelativeFactor = MeritFunction->nlpPrimalFeasError;
    }
  }

  isFeasible = (MeritFunction->nlpPrimalFeasError <= 0.001 *
                MeritFunction->feasRelativeFactor);
  computeDualFeasError(WorkingSet->nVar, TrialState->gradLag, &Flags->gradOK,
                       &MeritFunction->nlpDualFeasError);
  if (!Flags->gradOK) {
    Flags->done = true;
    if (isFeasible) {
      TrialState->sqpExitFlag = 2;
    } else {
      TrialState->sqpExitFlag = -2;
    }
  } else {
    MeritFunction->nlpComplError = computeComplError(fscales_cineq_constraint,
      WorkingSet->sizes[2], TrialState->cIneq, WorkingSet->sizes[3],
      TrialState->lambdasqp, WorkingSet->sizes[1] + 1);
    if ((MeritFunction->nlpDualFeasError > MeritFunction->nlpComplError) ||
        rtIsNaN(MeritFunction->nlpComplError)) {
      MeritFunction->firstOrderOpt = MeritFunction->nlpDualFeasError;
    } else {
      MeritFunction->firstOrderOpt = MeritFunction->nlpComplError;
    }

    if (TrialState->sqpIterations > 1) {
      for (b_iL0 = 0; b_iL0 < nVar; b_iL0++) {
        memspace->workspace_double->data[b_iL0] = TrialState->grad->data[b_iL0];
      }

      b_iL0 = WorkingSet->ldA;
      if ((WorkingSet->nVar != 0) && (WorkingSet->sizes[1] != 0)) {
        ix = 0;
        i = WorkingSet->ldA * (WorkingSet->sizes[1] - 1) + 1;
        for (jjA = 1; b_iL0 < 0 ? jjA >= i : jjA <= i; jjA += b_iL0) {
          iy = 0;
          rankR = (jjA + WorkingSet->nVar) - 1;
          for (fullRank_R = jjA; fullRank_R <= rankR; fullRank_R++) {
            memspace->workspace_double->data[iy] += WorkingSet->Aeq->
              data[fullRank_R - 1] * TrialState->lambdasqp_old->data[ix];
            iy++;
          }

          ix++;
        }
      }

      b_iL0 = WorkingSet->ldA;
      if ((WorkingSet->nVar != 0) && (WorkingSet->sizes[2] != 0)) {
        ix = WorkingSet->sizes[1];
        i = WorkingSet->ldA * (WorkingSet->sizes[2] - 1) + 1;
        for (jjA = 1; b_iL0 < 0 ? jjA >= i : jjA <= i; jjA += b_iL0) {
          iy = 0;
          rankR = (jjA + WorkingSet->nVar) - 1;
          for (fullRank_R = jjA; fullRank_R <= rankR; fullRank_R++) {
            memspace->workspace_double->data[iy] += WorkingSet->Aineq->
              data[fullRank_R - 1] * TrialState->lambdasqp_old->data[ix];
            iy++;
          }

          ix++;
        }
      }

      for (jjA = 0; jjA <= mLB; jjA++) {
        memspace->workspace_double->data[WorkingSet->indexLB->data[jjA] - 1] -=
          TrialState->lambdasqp_old->data[iL0];
        iL0++;
      }

      computeDualFeasError(WorkingSet->nVar, memspace->workspace_double,
                           &dxTooSmall, &scaleTol);
      nlpComplErrorTmp = computeComplError(fscales_cineq_constraint,
        WorkingSet->sizes[2], TrialState->cIneq, WorkingSet->sizes[3],
        TrialState->lambdasqp_old, 1);
      if ((scaleTol > nlpComplErrorTmp) || rtIsNaN(nlpComplErrorTmp)) {
        d = scaleTol;
      } else {
        d = nlpComplErrorTmp;
      }

      if ((MeritFunction->nlpDualFeasError > MeritFunction->nlpComplError) ||
          rtIsNaN(MeritFunction->nlpComplError)) {
        b_MeritFunction = MeritFunction->nlpDualFeasError;
      } else {
        b_MeritFunction = MeritFunction->nlpComplError;
      }

      if (d < b_MeritFunction) {
        MeritFunction->nlpDualFeasError = scaleTol;
        MeritFunction->nlpComplError = nlpComplErrorTmp;
        MeritFunction->firstOrderOpt = d;
      } else {
        for (b_iL0 = 0; b_iL0 <= mLambda; b_iL0++) {
          TrialState->lambdasqp_old->data[b_iL0] = TrialState->lambdasqp->
            data[b_iL0];
        }
      }
    } else {
      for (b_iL0 = 0; b_iL0 <= mLambda; b_iL0++) {
        TrialState->lambdasqp_old->data[b_iL0] = TrialState->lambdasqp->
          data[b_iL0];
      }
    }

    emxInit_real_T(&lambdaLSQ, 1);
    emxInit_real_T(&workspace, 2);
    if (isFeasible && (MeritFunction->nlpDualFeasError <= 1.0E-6 *
                       optimRelativeFactor) && (MeritFunction->nlpComplError <=
         1.0E-6 * optimRelativeFactor)) {
      Flags->done = true;
      TrialState->sqpExitFlag = 1;
    } else {
      Flags->done = false;
      if (isFeasible && (TrialState->sqpFval < -1.0E+20)) {
        Flags->done = true;
        TrialState->sqpExitFlag = -3;
      } else {
        guard1 = false;
        if (TrialState->sqpIterations > 0) {
          dxTooSmall = true;
          jjA = 0;
          exitg1 = false;
          while ((!exitg1) && (jjA <= nVar - 1)) {
            scaleTol = std::abs(TrialState->xstarsqp->data[jjA]);
            if ((1.0 > scaleTol) || rtIsNaN(scaleTol)) {
              scaleTol = 1.0;
            }

            if (1.0E-6 * scaleTol <= std::abs(TrialState->delta_x->data[jjA])) {
              dxTooSmall = false;
              exitg1 = true;
            } else {
              jjA++;
            }
          }

          if (dxTooSmall) {
            if (!isFeasible) {
              if (Flags->stepType != 2) {
                Flags->stepType = 2;
                Flags->failedLineSearch = false;
                Flags->stepAccepted = false;
                guard1 = true;
              } else {
                Flags->done = true;
                TrialState->sqpExitFlag = -2;
              }
            } else {
              iL0 = WorkingSet->nActiveConstr;
              if (WorkingSet->nActiveConstr > 0) {
                updateWorkingSetForNewQP(WorkingSet, WorkingSet->sizes[2],
                  TrialState->mNonlinIneq, TrialState->cIneq, WorkingSet->sizes
                  [1], TrialState->mNonlinEq, TrialState->cEq);
                i = lambdaLSQ->size[0];
                lambdaLSQ->size[0] = TrialState->lambda->size[0];
                emxEnsureCapacity_real_T(lambdaLSQ, i);
                b_iL0 = TrialState->lambda->size[0];
                for (i = 0; i < b_iL0; i++) {
                  lambdaLSQ->data[i] = TrialState->lambda->data[i];
                }

                for (b_iL0 = 0; b_iL0 < iL0; b_iL0++) {
                  lambdaLSQ->data[b_iL0] = 0.0;
                }

                factorQRE(QRManager, WorkingSet->ATwset, nVar, iL0);
                computeQ_(QRManager, QRManager->mrows);
                if (nVar > iL0) {
                  b_iL0 = nVar;
                } else {
                  b_iL0 = iL0;
                }

                scaleTol = static_cast<double>(b_iL0) * 2.2204460492503131E-16;
                if (1.4901161193847656E-8 < scaleTol) {
                  scaleTol = 1.4901161193847656E-8;
                }

                scaleTol *= std::abs(QRManager->QR->data[0]);
                if (nVar < iL0) {
                  fullRank_R = nVar;
                } else {
                  fullRank_R = iL0;
                }

                rankR = 0;
                b_iL0 = 0;
                while ((rankR < fullRank_R) && (std::abs(QRManager->QR->
                         data[b_iL0]) > scaleTol)) {
                  rankR++;
                  b_iL0 = (b_iL0 + QRManager->ldq) + 1;
                }

                i = workspace->size[0] * workspace->size[1];
                workspace->size[0] = memspace->workspace_double->size[0];
                workspace->size[1] = memspace->workspace_double->size[1];
                emxEnsureCapacity_real_T(workspace, i);
                b_iL0 = memspace->workspace_double->size[0] *
                  memspace->workspace_double->size[1];
                for (i = 0; i < b_iL0; i++) {
                  workspace->data[i] = memspace->workspace_double->data[i];
                }

                xgemv(nVar, nVar, QRManager->Q, QRManager->ldq, TrialState->grad,
                      workspace);
                if (rankR != 0) {
                  for (b_iL0 = rankR; b_iL0 >= 1; b_iL0--) {
                    jjA = (b_iL0 + (b_iL0 - 1) * QRManager->ldq) - 1;
                    workspace->data[b_iL0 - 1] /= QRManager->QR->data[jjA];
                    for (iy = 0; iy <= b_iL0 - 2; iy++) {
                      ix = (b_iL0 - iy) - 2;
                      workspace->data[ix] -= workspace->data[b_iL0 - 1] *
                        QRManager->QR->data[(jjA - iy) - 1];
                    }
                  }
                }

                if (iL0 < fullRank_R) {
                  fullRank_R = iL0;
                }

                for (jjA = 0; jjA < fullRank_R; jjA++) {
                  lambdaLSQ->data[QRManager->jpvt->data[jjA] - 1] =
                    workspace->data[jjA];
                }

                i = TrialState->lambda->size[0];
                TrialState->lambda->size[0] = lambdaLSQ->size[0];
                emxEnsureCapacity_real_T(TrialState->lambda, i);
                b_iL0 = lambdaLSQ->size[0];
                for (i = 0; i < b_iL0; i++) {
                  TrialState->lambda->data[i] = lambdaLSQ->data[i];
                }

                for (jjA = 1; jjA <= mEq; jjA++) {
                  TrialState->lambda->data[jjA - 1] = -TrialState->lambda->
                    data[jjA - 1];
                }

                i = memspace->workspace_double->size[0] *
                  memspace->workspace_double->size[1];
                memspace->workspace_double->size[0] = workspace->size[0];
                memspace->workspace_double->size[1] = workspace->size[1];
                emxEnsureCapacity_real_T(memspace->workspace_double, i);
                b_iL0 = workspace->size[0] * workspace->size[1];
                for (i = 0; i < b_iL0; i++) {
                  memspace->workspace_double->data[i] = workspace->data[i];
                }

                sortLambdaQP(TrialState->lambda, WorkingSet->nActiveConstr,
                             WorkingSet->sizes, WorkingSet->isActiveIdx,
                             WorkingSet->Wid, WorkingSet->Wlocalidx,
                             memspace->workspace_double);
                for (b_iL0 = 0; b_iL0 < nVar; b_iL0++) {
                  memspace->workspace_double->data[b_iL0] = TrialState->
                    grad->data[b_iL0];
                }

                b_iL0 = WorkingSet->ldA;
                if ((nVar != 0) && (mEq != 0)) {
                  ix = 0;
                  i = WorkingSet->ldA * (mEq - 1) + 1;
                  for (jjA = 1; b_iL0 < 0 ? jjA >= i : jjA <= i; jjA += b_iL0) {
                    iy = 0;
                    rankR = (jjA + nVar) - 1;
                    for (fullRank_R = jjA; fullRank_R <= rankR; fullRank_R++) {
                      memspace->workspace_double->data[iy] += WorkingSet->
                        Aeq->data[fullRank_R - 1] * TrialState->lambda->data[ix];
                      iy++;
                    }

                    ix++;
                  }
                }

                b_iL0 = WorkingSet->ldA;
                if ((nVar != 0) && (mIneq != 0)) {
                  ix = mEq;
                  i = WorkingSet->ldA * (mIneq - 1) + 1;
                  for (jjA = 1; b_iL0 < 0 ? jjA >= i : jjA <= i; jjA += b_iL0) {
                    iy = 0;
                    rankR = (jjA + nVar) - 1;
                    for (fullRank_R = jjA; fullRank_R <= rankR; fullRank_R++) {
                      memspace->workspace_double->data[iy] += WorkingSet->
                        Aineq->data[fullRank_R - 1] * TrialState->lambda->
                        data[ix];
                      iy++;
                    }

                    ix++;
                  }
                }

                b_iL0 = mEq + mIneq;
                for (jjA = 0; jjA <= mLB; jjA++) {
                  memspace->workspace_double->data[WorkingSet->indexLB->data[jjA]
                    - 1] -= TrialState->lambda->data[b_iL0];
                  b_iL0++;
                }

                computeDualFeasError(nVar, memspace->workspace_double,
                                     &dxTooSmall, &scaleTol);
                nlpComplErrorTmp = computeComplError(fscales_cineq_constraint,
                  mIneq, TrialState->cIneq, mLB + 1, TrialState->lambda, 1);
                if ((scaleTol <= 1.0E-6 * optimRelativeFactor) &&
                    (nlpComplErrorTmp <= 1.0E-6 * optimRelativeFactor)) {
                  MeritFunction->nlpDualFeasError = scaleTol;
                  MeritFunction->nlpComplError = nlpComplErrorTmp;
                  if (scaleTol > nlpComplErrorTmp) {
                    nlpComplErrorTmp = scaleTol;
                  }

                  MeritFunction->firstOrderOpt = nlpComplErrorTmp;
                  for (b_iL0 = 0; b_iL0 <= mLambda; b_iL0++) {
                    TrialState->lambdasqp->data[b_iL0] = TrialState->
                      lambda->data[b_iL0];
                  }

                  Flags->done = true;
                  TrialState->sqpExitFlag = 1;
                } else {
                  if ((scaleTol <= MeritFunction->nlpDualFeasError) &&
                      (nlpComplErrorTmp <= MeritFunction->nlpComplError)) {
                    MeritFunction->nlpDualFeasError = scaleTol;
                    MeritFunction->nlpComplError = nlpComplErrorTmp;
                    if (scaleTol > nlpComplErrorTmp) {
                      nlpComplErrorTmp = scaleTol;
                    }

                    MeritFunction->firstOrderOpt = nlpComplErrorTmp;
                    for (b_iL0 = 0; b_iL0 <= mLambda; b_iL0++) {
                      TrialState->lambdasqp->data[b_iL0] = TrialState->
                        lambda->data[b_iL0];
                    }
                  }

                  Flags->done = true;
                  TrialState->sqpExitFlag = 2;
                }
              } else {
                Flags->done = true;
                TrialState->sqpExitFlag = 2;
              }
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          if (TrialState->sqpIterations >= 3000) {
            Flags->done = true;
            TrialState->sqpExitFlag = 0;
          } else {
            if (TrialState->FunctionEvaluations >= 10000) {
              Flags->done = true;
              TrialState->sqpExitFlag = 0;
            }
          }
        }
      }
    }

    emxFree_real_T(&workspace);
    emxFree_real_T(&lambdaLSQ);
  }
}

//
// Arguments    : j_struct_T *MeritFunction
//                const emxArray_real_T *fscales_cineq_constraint
//                const h_struct_T *WorkingSet
//                e_struct_T *TrialState
//                bool *Flags_gradOK
//                bool *Flags_fevalOK
//                bool *Flags_done
//                bool *Flags_stepAccepted
//                bool *Flags_failedLineSearch
//                int *Flags_stepType
// Return Type  : void
//
void test_exit(j_struct_T *MeritFunction, const emxArray_real_T
               *fscales_cineq_constraint, const h_struct_T *WorkingSet,
               e_struct_T *TrialState, bool *Flags_gradOK, bool *Flags_fevalOK,
               bool *Flags_done, bool *Flags_stepAccepted, bool
               *Flags_failedLineSearch, int *Flags_stepType)
{
  int nVar;
  int mLB;
  int iL0;
  int mLambda;
  int iy;
  int mIneq;
  int ix;
  int iac;
  int i;
  int ia;
  double s;
  double smax;
  double optimRelativeFactor;
  emxArray_real_T *cIneq;
  emxArray_real_T *cEq;
  bool isFeasible;
  bool exitg1;
  *Flags_fevalOK = true;
  *Flags_done = false;
  *Flags_stepAccepted = false;
  *Flags_failedLineSearch = false;
  *Flags_stepType = 1;
  nVar = WorkingSet->nVar;
  mLB = WorkingSet->sizes[3];
  iL0 = WorkingSet->sizes[1] + WorkingSet->sizes[2];
  mLambda = iL0 + WorkingSet->sizes[3];
  for (iy = 0; iy < nVar; iy++) {
    TrialState->gradLag->data[iy] = TrialState->grad->data[iy];
  }

  mIneq = WorkingSet->ldA;
  if ((WorkingSet->nVar != 0) && (WorkingSet->sizes[1] != 0)) {
    ix = 0;
    nVar = WorkingSet->ldA * (WorkingSet->sizes[1] - 1) + 1;
    for (iac = 1; mIneq < 0 ? iac >= nVar : iac <= nVar; iac += mIneq) {
      iy = 0;
      i = (iac + WorkingSet->nVar) - 1;
      for (ia = iac; ia <= i; ia++) {
        TrialState->gradLag->data[iy] += WorkingSet->Aeq->data[ia - 1] *
          TrialState->lambdasqp->data[ix];
        iy++;
      }

      ix++;
    }
  }

  mIneq = WorkingSet->ldA;
  if ((WorkingSet->nVar != 0) && (WorkingSet->sizes[2] != 0)) {
    ix = WorkingSet->sizes[1];
    nVar = WorkingSet->ldA * (WorkingSet->sizes[2] - 1) + 1;
    for (iac = 1; mIneq < 0 ? iac >= nVar : iac <= nVar; iac += mIneq) {
      iy = 0;
      i = (iac + WorkingSet->nVar) - 1;
      for (ia = iac; ia <= i; ia++) {
        TrialState->gradLag->data[iy] += WorkingSet->Aineq->data[ia - 1] *
          TrialState->lambdasqp->data[ix];
        iy++;
      }

      ix++;
    }
  }

  for (iy = 0; iy < mLB; iy++) {
    TrialState->gradLag->data[WorkingSet->indexLB->data[iy] - 1] -=
      TrialState->lambdasqp->data[iL0];
    iL0++;
  }

  mIneq = WorkingSet->nVar;
  if (WorkingSet->nVar < 1) {
    nVar = 0;
  } else {
    nVar = 1;
    if (WorkingSet->nVar > 1) {
      ix = 0;
      smax = std::abs(TrialState->grad->data[0]);
      for (iy = 2; iy <= mIneq; iy++) {
        ix++;
        s = std::abs(TrialState->grad->data[ix]);
        if (s > smax) {
          nVar = iy;
          smax = s;
        }
      }
    }
  }

  s = std::abs(TrialState->grad->data[nVar - 1]);
  if ((1.0 > s) || rtIsNaN(s)) {
    optimRelativeFactor = 1.0;
  } else {
    optimRelativeFactor = s;
  }

  if (rtIsInf(optimRelativeFactor) || rtIsNaN(optimRelativeFactor)) {
    optimRelativeFactor = 1.0;
  }

  iy = WorkingSet->sizes[2] - TrialState->mNonlinIneq;
  iac = TrialState->mNonlinIneq;
  cIneq = TrialState->cIneq;
  mIneq = WorkingSet->sizes[1] - TrialState->mNonlinEq;
  nVar = TrialState->mNonlinEq;
  cEq = TrialState->cEq;
  mLB = WorkingSet->sizes[3];
  smax = 0.0;
  nVar += mIneq;
  mIneq = iac + iy;
  for (iy = 0; iy < nVar; iy++) {
    s = std::abs(cEq->data[iy]);
    if ((!(smax > s)) && (!rtIsNaN(s))) {
      smax = s;
    }
  }

  for (iy = 0; iy < mIneq; iy++) {
    if ((!(smax > cIneq->data[iy])) && (!rtIsNaN(cIneq->data[iy]))) {
      smax = cIneq->data[iy];
    }
  }

  for (iy = 0; iy < mLB; iy++) {
    abort();
  }

  MeritFunction->nlpPrimalFeasError = smax;
  if ((1.0 > MeritFunction->nlpPrimalFeasError) || rtIsNaN
      (MeritFunction->nlpPrimalFeasError)) {
    MeritFunction->feasRelativeFactor = 1.0;
  } else {
    MeritFunction->feasRelativeFactor = MeritFunction->nlpPrimalFeasError;
  }

  isFeasible = (MeritFunction->nlpPrimalFeasError <= 0.001 *
                MeritFunction->feasRelativeFactor);
  nVar = WorkingSet->nVar;
  cIneq = TrialState->gradLag;
  *Flags_gradOK = true;
  smax = 0.0;
  iy = 0;
  exitg1 = false;
  while ((!exitg1) && (iy <= nVar - 1)) {
    *Flags_gradOK = ((!rtIsInf(cIneq->data[iy])) && (!rtIsNaN(cIneq->data[iy])));
    if (!*Flags_gradOK) {
      exitg1 = true;
    } else {
      s = std::abs(cIneq->data[iy]);
      if ((!(smax > s)) && (!rtIsNaN(s))) {
        smax = s;
      }

      iy++;
    }
  }

  MeritFunction->nlpDualFeasError = smax;
  if (!*Flags_gradOK) {
    *Flags_done = true;
    if (isFeasible) {
      TrialState->sqpExitFlag = 2;
    } else {
      TrialState->sqpExitFlag = -2;
    }
  } else {
    computeComplError(fscales_cineq_constraint, WorkingSet->sizes[2],
                      TrialState->cIneq, WorkingSet->sizes[3],
                      TrialState->lambdasqp, WorkingSet->sizes[1] + 1);
    MeritFunction->nlpComplError = 0.0;
    smax = MeritFunction->nlpDualFeasError;
    if (!(smax > 0.0)) {
      smax = 0.0;
    }

    MeritFunction->firstOrderOpt = smax;
    for (iy = 0; iy < mLambda; iy++) {
      TrialState->lambdasqp_old->data[iy] = TrialState->lambdasqp->data[iy];
    }

    if (isFeasible && (MeritFunction->nlpDualFeasError <= 1.0E-6 *
                       optimRelativeFactor)) {
      *Flags_done = true;
      TrialState->sqpExitFlag = 1;
    } else if (isFeasible && (TrialState->sqpFval < -1.0E+20)) {
      *Flags_done = true;
      TrialState->sqpExitFlag = -3;
    } else {
      if (TrialState->FunctionEvaluations >= 10000) {
        *Flags_done = true;
        TrialState->sqpExitFlag = 0;
      }
    }
  }
}

//
// File trailer for test_exit.cpp
//
// [EOF]
//
