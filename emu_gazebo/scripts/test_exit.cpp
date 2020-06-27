//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: test_exit.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "test_exit.h"
#include "computeComplError.h"
#include "computeGradLag.h"
#include "computePrimalFeasError.h"
#include "computeQ_.h"
#include "factorQRE.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "updateWorkingSetForNewQP.h"
#include "xgemv.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : struct_T *Flags
//                c_struct_T *memspace
//                j_struct_T *MeritFunction
//                h_struct_T *WorkingSet
//                e_struct_T *TrialState
//                i_struct_T *QRManager
//                const emxArray_real_T *lb
// Return Type  : void
//
void test_exit(struct_T *Flags, c_struct_T *memspace, j_struct_T *MeritFunction,
               h_struct_T *WorkingSet, e_struct_T *TrialState, i_struct_T
               *QRManager, const emxArray_real_T *lb)
{
  int nVar;
  int mFixed;
  int mEq;
  int mLB;
  int mUB;
  int rankR;
  int mLambda;
  int iQR_diag;
  int jjA;
  int ix;
  double u1;
  double smax;
  int k;
  double optimRelativeFactor;
  double s;
  bool isFeasible;
  emxArray_real_T *gradLag;
  bool dxTooSmall;
  bool exitg1;
  emxArray_real_T *lambdaLSQ;
  double nlpDualFeasErrorTmp;
  emxArray_real_T *workspace;
  bool guard1 = false;
  int nActiveConstr;
  double b_TrialState[12];
  int fullRank_R;
  nVar = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0];
  mEq = WorkingSet->sizes[1];
  mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  rankR = WorkingSet->sizes[0] + WorkingSet->sizes[1];
  mLambda = ((rankR + WorkingSet->sizes[3]) + WorkingSet->sizes[4]) + 11;
  computeGradLag(TrialState->gradLag, WorkingSet->ldA, WorkingSet->nVar,
                 TrialState->grad, WorkingSet->Aineq, WorkingSet->sizes[1],
                 WorkingSet->Aeq, WorkingSet->indexFixed, WorkingSet->sizes[0],
                 WorkingSet->indexLB, WorkingSet->sizes[3], WorkingSet->indexUB,
                 WorkingSet->sizes[4], TrialState->lambdasqp);
  iQR_diag = WorkingSet->nVar;
  if (WorkingSet->nVar < 1) {
    jjA = 0;
  } else {
    jjA = 1;
    if (WorkingSet->nVar > 1) {
      ix = 0;
      smax = std::abs(TrialState->grad->data[0]);
      for (k = 2; k <= iQR_diag; k++) {
        ix++;
        s = std::abs(TrialState->grad->data[ix]);
        if (s > smax) {
          jjA = k;
          smax = s;
        }
      }
    }
  }

  u1 = std::abs(TrialState->grad->data[jjA - 1]);
  if ((1.0 > u1) || rtIsNaN(u1)) {
    optimRelativeFactor = 1.0;
  } else {
    optimRelativeFactor = u1;
  }

  if (rtIsInf(optimRelativeFactor) || rtIsNaN(optimRelativeFactor)) {
    optimRelativeFactor = 1.0;
  }

  MeritFunction->nlpPrimalFeasError = computePrimalFeasError
    (TrialState->xstarsqp, TrialState->cIneq, WorkingSet->sizes[1] -
     TrialState->mNonlinEq, TrialState->mNonlinEq, TrialState->cEq,
     WorkingSet->indexLB, WorkingSet->sizes[3], lb, WorkingSet->indexUB,
     WorkingSet->sizes[4]);
  if (TrialState->sqpIterations == 0) {
    if ((1.0 > MeritFunction->nlpPrimalFeasError) || rtIsNaN
        (MeritFunction->nlpPrimalFeasError)) {
      MeritFunction->feasRelativeFactor = 1.0;
    } else {
      MeritFunction->feasRelativeFactor = MeritFunction->nlpPrimalFeasError;
    }
  }

  isFeasible = (MeritFunction->nlpPrimalFeasError <= 0.002 *
                MeritFunction->feasRelativeFactor);
  iQR_diag = WorkingSet->nVar;
  gradLag = TrialState->gradLag;
  dxTooSmall = true;
  smax = 0.0;
  jjA = 0;
  exitg1 = false;
  while ((!exitg1) && (jjA <= iQR_diag - 1)) {
    dxTooSmall = ((!rtIsInf(gradLag->data[jjA])) && (!rtIsNaN(gradLag->data[jjA])));
    if (!dxTooSmall) {
      exitg1 = true;
    } else {
      u1 = std::abs(gradLag->data[jjA]);
      if ((!(smax > u1)) && (!rtIsNaN(u1))) {
        smax = u1;
      }

      jjA++;
    }
  }

  Flags->gradOK = dxTooSmall;
  MeritFunction->nlpDualFeasError = smax;
  if (!Flags->gradOK) {
    Flags->done = true;
    if (isFeasible) {
      TrialState->sqpExitFlag = 2;
    } else {
      TrialState->sqpExitFlag = -2;
    }
  } else {
    MeritFunction->nlpComplError = computeComplError(TrialState->xstarsqp,
      TrialState->cIneq, WorkingSet->indexLB, WorkingSet->sizes[3], lb,
      WorkingSet->indexUB, WorkingSet->sizes[4], TrialState->lambdasqp, rankR +
      1);
    if ((MeritFunction->nlpDualFeasError > MeritFunction->nlpComplError) ||
        rtIsNaN(MeritFunction->nlpComplError)) {
      MeritFunction->firstOrderOpt = MeritFunction->nlpDualFeasError;
    } else {
      MeritFunction->firstOrderOpt = MeritFunction->nlpComplError;
    }

    if (TrialState->sqpIterations > 1) {
      computeGradLag(memspace->workspace_double, WorkingSet->ldA,
                     WorkingSet->nVar, TrialState->grad, WorkingSet->Aineq,
                     WorkingSet->sizes[1], WorkingSet->Aeq,
                     WorkingSet->indexFixed, WorkingSet->sizes[0],
                     WorkingSet->indexLB, WorkingSet->sizes[3],
                     WorkingSet->indexUB, WorkingSet->sizes[4],
                     TrialState->lambdasqp_old);
      iQR_diag = WorkingSet->nVar;
      gradLag = memspace->workspace_double;
      nlpDualFeasErrorTmp = 0.0;
      jjA = 0;
      exitg1 = false;
      while ((!exitg1) && (jjA <= iQR_diag - 1)) {
        dxTooSmall = ((!rtIsInf(gradLag->data[jjA])) && (!rtIsNaN(gradLag->
          data[jjA])));
        if (!dxTooSmall) {
          exitg1 = true;
        } else {
          u1 = std::abs(gradLag->data[jjA]);
          if ((!(nlpDualFeasErrorTmp > u1)) && (!rtIsNaN(u1))) {
            nlpDualFeasErrorTmp = u1;
          }

          jjA++;
        }
      }

      smax = computeComplError(TrialState->xstarsqp, TrialState->cIneq,
        WorkingSet->indexLB, WorkingSet->sizes[3], lb, WorkingSet->indexUB,
        WorkingSet->sizes[4], TrialState->lambdasqp_old, WorkingSet->sizes[0] +
        1);
      if ((nlpDualFeasErrorTmp > smax) || rtIsNaN(smax)) {
        s = nlpDualFeasErrorTmp;
      } else {
        s = smax;
      }

      if ((MeritFunction->nlpDualFeasError > MeritFunction->nlpComplError) ||
          rtIsNaN(MeritFunction->nlpComplError)) {
        u1 = MeritFunction->nlpDualFeasError;
      } else {
        u1 = MeritFunction->nlpComplError;
      }

      if (s < u1) {
        MeritFunction->nlpDualFeasError = nlpDualFeasErrorTmp;
        MeritFunction->nlpComplError = smax;
        MeritFunction->firstOrderOpt = s;
      } else {
        for (k = 0; k <= mLambda; k++) {
          TrialState->lambdasqp_old->data[k] = TrialState->lambdasqp->data[k];
        }
      }
    } else {
      for (k = 0; k <= mLambda; k++) {
        TrialState->lambdasqp_old->data[k] = TrialState->lambdasqp->data[k];
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
            u1 = std::abs(TrialState->xstarsqp->data[jjA]);
            if ((1.0 > u1) || rtIsNaN(u1)) {
              u1 = 1.0;
            }

            if (1.0E-6 * u1 <= std::abs(TrialState->delta_x->data[jjA])) {
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
              nActiveConstr = WorkingSet->nActiveConstr;
              if (WorkingSet->nActiveConstr > 0) {
                std::memcpy(&b_TrialState[0], &TrialState->cIneq[0], 12U *
                            sizeof(double));
                b_updateWorkingSetForNewQP(TrialState->xstarsqp, WorkingSet,
                  b_TrialState, WorkingSet->sizes[1], TrialState->mNonlinEq,
                  TrialState->cEq, WorkingSet->sizes[3], lb, WorkingSet->sizes[4],
                  WorkingSet->sizes[0]);
                k = lambdaLSQ->size[0];
                lambdaLSQ->size[0] = TrialState->lambda->size[0];
                emxEnsureCapacity_real_T(lambdaLSQ, k);
                iQR_diag = TrialState->lambda->size[0];
                for (k = 0; k < iQR_diag; k++) {
                  lambdaLSQ->data[k] = TrialState->lambda->data[k];
                }

                for (k = 0; k < nActiveConstr; k++) {
                  lambdaLSQ->data[k] = 0.0;
                }

                factorQRE(QRManager, WorkingSet->ATwset, nVar, nActiveConstr);
                computeQ_(QRManager, QRManager->mrows);
                if (nVar > nActiveConstr) {
                  iQR_diag = nVar;
                } else {
                  iQR_diag = nActiveConstr;
                }

                smax = static_cast<double>(iQR_diag) * 2.2204460492503131E-16;
                if (1.4901161193847656E-8 < smax) {
                  smax = 1.4901161193847656E-8;
                }

                smax *= std::abs(QRManager->QR->data[0]);
                if (nVar < nActiveConstr) {
                  fullRank_R = nVar;
                } else {
                  fullRank_R = nActiveConstr;
                }

                rankR = 0;
                iQR_diag = 0;
                while ((rankR < fullRank_R) && (std::abs(QRManager->QR->
                         data[iQR_diag]) > smax)) {
                  rankR++;
                  iQR_diag = (iQR_diag + QRManager->ldq) + 1;
                }

                k = workspace->size[0] * workspace->size[1];
                workspace->size[0] = memspace->workspace_double->size[0];
                workspace->size[1] = memspace->workspace_double->size[1];
                emxEnsureCapacity_real_T(workspace, k);
                iQR_diag = memspace->workspace_double->size[0] *
                  memspace->workspace_double->size[1];
                for (k = 0; k < iQR_diag; k++) {
                  workspace->data[k] = memspace->workspace_double->data[k];
                }

                b_xgemv(nVar, nVar, QRManager->Q, QRManager->ldq,
                        TrialState->grad, workspace);
                if (rankR != 0) {
                  for (iQR_diag = rankR; iQR_diag >= 1; iQR_diag--) {
                    jjA = (iQR_diag + (iQR_diag - 1) * QRManager->ldq) - 1;
                    workspace->data[iQR_diag - 1] /= QRManager->QR->data[jjA];
                    for (k = 0; k <= iQR_diag - 2; k++) {
                      ix = (iQR_diag - k) - 2;
                      workspace->data[ix] -= workspace->data[iQR_diag - 1] *
                        QRManager->QR->data[(jjA - k) - 1];
                    }
                  }
                }

                if (nActiveConstr < fullRank_R) {
                  fullRank_R = nActiveConstr;
                }

                for (jjA = 0; jjA < fullRank_R; jjA++) {
                  lambdaLSQ->data[QRManager->jpvt->data[jjA] - 1] =
                    workspace->data[jjA];
                }

                k = TrialState->lambda->size[0];
                TrialState->lambda->size[0] = lambdaLSQ->size[0];
                emxEnsureCapacity_real_T(TrialState->lambda, k);
                iQR_diag = lambdaLSQ->size[0];
                for (k = 0; k < iQR_diag; k++) {
                  TrialState->lambda->data[k] = lambdaLSQ->data[k];
                }

                k = mFixed + 1;
                iQR_diag = mFixed + mEq;
                for (jjA = k; jjA <= iQR_diag; jjA++) {
                  TrialState->lambda->data[jjA - 1] = -TrialState->lambda->
                    data[jjA - 1];
                }

                k = memspace->workspace_double->size[0] *
                  memspace->workspace_double->size[1];
                memspace->workspace_double->size[0] = workspace->size[0];
                memspace->workspace_double->size[1] = workspace->size[1];
                emxEnsureCapacity_real_T(memspace->workspace_double, k);
                iQR_diag = workspace->size[0] * workspace->size[1];
                for (k = 0; k < iQR_diag; k++) {
                  memspace->workspace_double->data[k] = workspace->data[k];
                }

                sortLambdaQP(TrialState->lambda, WorkingSet->nActiveConstr,
                             WorkingSet->sizes, WorkingSet->isActiveIdx,
                             WorkingSet->Wid, WorkingSet->Wlocalidx,
                             memspace->workspace_double);
                computeGradLag(memspace->workspace_double, WorkingSet->ldA, nVar,
                               TrialState->grad, WorkingSet->Aineq, mEq,
                               WorkingSet->Aeq, WorkingSet->indexFixed, mFixed,
                               WorkingSet->indexLB, mLB, WorkingSet->indexUB,
                               mUB, TrialState->lambda);
                gradLag = memspace->workspace_double;
                s = 0.0;
                jjA = 0;
                exitg1 = false;
                while ((!exitg1) && (jjA <= nVar - 1)) {
                  dxTooSmall = ((!rtIsInf(gradLag->data[jjA])) && (!rtIsNaN
                    (gradLag->data[jjA])));
                  if (!dxTooSmall) {
                    exitg1 = true;
                  } else {
                    u1 = std::abs(gradLag->data[jjA]);
                    if ((!(s > u1)) && (!rtIsNaN(u1))) {
                      s = u1;
                    }

                    jjA++;
                  }
                }

                smax = computeComplError(TrialState->xstarsqp, TrialState->cIneq,
                  WorkingSet->indexLB, mLB, lb, WorkingSet->indexUB, mUB,
                  TrialState->lambda, mFixed + 1);
                if ((s <= 1.0E-6 * optimRelativeFactor) && (smax <= 1.0E-6 *
                     optimRelativeFactor)) {
                  MeritFunction->nlpDualFeasError = s;
                  MeritFunction->nlpComplError = smax;
                  if (s > smax) {
                    smax = s;
                  }

                  MeritFunction->firstOrderOpt = smax;
                  for (k = 0; k <= mLambda; k++) {
                    TrialState->lambdasqp->data[k] = TrialState->lambda->data[k];
                  }

                  Flags->done = true;
                  TrialState->sqpExitFlag = 1;
                } else {
                  if ((s <= MeritFunction->nlpDualFeasError) && (smax <=
                       MeritFunction->nlpComplError)) {
                    MeritFunction->nlpDualFeasError = s;
                    MeritFunction->nlpComplError = smax;
                    if (s > smax) {
                      smax = s;
                    }

                    MeritFunction->firstOrderOpt = smax;
                    for (k = 0; k <= mLambda; k++) {
                      TrialState->lambdasqp->data[k] = TrialState->lambda->
                        data[k];
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
// File trailer for test_exit.cpp
//
// [EOF]
//
