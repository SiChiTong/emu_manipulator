//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: iterate.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "iterate.h"
#include "addAineqConstr.h"
#include "addBoundToActiveSetMatrix_.h"
#include "computeFval_ReuseHx.h"
#include "computeGrad_StoreHx.h"
#include "computeQ_.h"
#include "compute_deltax.h"
#include "factorQR.h"
#include "feasibleX0ForWorkingSet.h"
#include "maxConstraintViolation.h"
#include "ratiotest.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xgemv.h"
#include "xnrm2.h"
#include "xrotg.h"
#include <cmath>

// Function Declarations
static void c_local_checkStoppingAndUpdateF(int *activeSetChangeID, const
  emxArray_real_T *f, e_struct_T *solution, c_struct_T *memspace, const
  g_struct_T *objective, h_struct_T *workingset, i_struct_T *qrmanager, int
  options_MaxIterations, double options_ObjectiveLimit, bool updateFval);

// Function Definitions

//
// Arguments    : int *activeSetChangeID
//                const emxArray_real_T *f
//                e_struct_T *solution
//                c_struct_T *memspace
//                const g_struct_T *objective
//                h_struct_T *workingset
//                i_struct_T *qrmanager
//                int options_MaxIterations
//                double options_ObjectiveLimit
//                bool updateFval
// Return Type  : void
//
static void c_local_checkStoppingAndUpdateF(int *activeSetChangeID, const
  emxArray_real_T *f, e_struct_T *solution, c_struct_T *memspace, const
  g_struct_T *objective, h_struct_T *workingset, i_struct_T *qrmanager, int
  options_MaxIterations, double options_ObjectiveLimit, bool updateFval)
{
  int nVar;
  int k;
  bool nonDegenerateWset;
  double constrViolation_new;
  solution->iterations++;
  nVar = objective->nvar - 1;
  if (solution->iterations > options_MaxIterations) {
    solution->state = 0;
  }

  if (solution->iterations - solution->iterations / 50 * 50 == 0) {
    solution->maxConstr = maxConstraintViolation(workingset, solution->xstar);
    if (solution->maxConstr > 0.001) {
      for (k = 0; k <= nVar; k++) {
        solution->searchDir->data[k] = solution->xstar->data[k];
      }

      nonDegenerateWset = feasibleX0ForWorkingSet(memspace->workspace_double,
        solution->searchDir, workingset, qrmanager);
      if (!nonDegenerateWset) {
        solution->state = -2;
      }

      *activeSetChangeID = 0;
      constrViolation_new = maxConstraintViolation(workingset,
        solution->searchDir);
      if (constrViolation_new < solution->maxConstr) {
        for (k = 0; k <= nVar; k++) {
          solution->xstar->data[k] = solution->searchDir->data[k];
        }

        solution->maxConstr = constrViolation_new;
      }
    }
  }

  if (updateFval) {
    solution->fstar = computeFval_ReuseHx(objective, memspace->workspace_double,
      f, solution->xstar);
    if (solution->fstar <= options_ObjectiveLimit) {
      solution->state = 2;
    }
  }
}

//
// Arguments    : const emxArray_real_T *H
//                const emxArray_real_T *f
//                e_struct_T *solution
//                c_struct_T *memspace
//                h_struct_T *workingset
//                i_struct_T *qrmanager
//                k_struct_T *cholmanager
//                g_struct_T *objective
//                int options_MaxIterations
//                double options_StepTolerance
//                double options_ObjectiveLimit
// Return Type  : void
//
void iterate(const emxArray_real_T *H, const emxArray_real_T *f, e_struct_T
             *solution, c_struct_T *memspace, h_struct_T *workingset, i_struct_T
             *qrmanager, k_struct_T *cholmanager, g_struct_T *objective, int
             options_MaxIterations, double options_StepTolerance, double
             options_ObjectiveLimit)
{
  bool subProblemChanged;
  bool updateFval;
  int activeSetChangeID;
  int nVar;
  int mFixed;
  int mEq;
  int activeConstrIdx;
  int n;
  int k;
  emxArray_real_T *x;
  int exitg1;
  bool guard1 = false;
  int endIdx;
  int i;
  int idx;
  int iyend;
  int b_i;
  double temp;
  int iy;
  int QRk0;
  int ix;
  double d;
  double c;
  double s;
  bool b_guard1 = false;
  subProblemChanged = true;
  updateFval = true;
  activeSetChangeID = 0;
  nVar = workingset->nVar;
  mFixed = workingset->nWConstr[0];
  mEq = workingset->nWConstr[1];
  activeConstrIdx = 0;
  computeGrad_StoreHx(objective, H, f, solution->xstar);
  solution->fstar = computeFval_ReuseHx(objective, memspace->workspace_double, f,
    solution->xstar);
  solution->state = -5;
  solution->iterations = 0;
  n = workingset->mConstrMax;
  for (k = 0; k < n; k++) {
    solution->lambda->data[k] = 0.0;
  }

  emxInit_real_T(&x, 2);
  do {
    exitg1 = 0;
    if (solution->state == -5) {
      guard1 = false;
      if (subProblemChanged) {
        switch (activeSetChangeID) {
         case 1:
          endIdx = workingset->ldA * (workingset->nActiveConstr - 1);
          idx = qrmanager->mrows;
          iyend = qrmanager->ncols + 1;
          if (idx < iyend) {
            iyend = idx;
          }

          qrmanager->minRowCol = iyend;
          iy = qrmanager->ldq * qrmanager->ncols;
          QRk0 = qrmanager->ldq;
          if (qrmanager->mrows != 0) {
            iyend = iy + qrmanager->mrows;
            for (ix = iy + 1; ix <= iyend; ix++) {
              qrmanager->QR->data[ix - 1] = 0.0;
            }

            b_i = qrmanager->ldq * (qrmanager->mrows - 1) + 1;
            for (idx = 1; QRk0 < 0 ? idx >= b_i : idx <= b_i; idx += QRk0) {
              ix = endIdx;
              c = 0.0;
              i = (idx + qrmanager->mrows) - 1;
              for (iyend = idx; iyend <= i; iyend++) {
                c += qrmanager->Q->data[iyend - 1] * workingset->ATwset->data[ix];
                ix++;
              }

              qrmanager->QR->data[iy] += c;
              iy++;
            }
          }

          qrmanager->ncols++;
          qrmanager->jpvt->data[qrmanager->ncols - 1] = qrmanager->ncols;
          for (idx = qrmanager->mrows - 1; idx + 1 > qrmanager->ncols; idx--) {
            d = qrmanager->QR->data[idx + qrmanager->QR->size[0] *
              (qrmanager->ncols - 1)];
            xrotg(&qrmanager->QR->data[(idx + qrmanager->QR->size[0] *
                   (qrmanager->ncols - 1)) - 1], &d, &c, &s);
            qrmanager->QR->data[idx + qrmanager->QR->size[0] * (qrmanager->ncols
              - 1)] = d;
            iy = qrmanager->ldq * (idx - 1);
            n = qrmanager->mrows;
            b_i = x->size[0] * x->size[1];
            x->size[0] = qrmanager->Q->size[0];
            x->size[1] = qrmanager->Q->size[1];
            emxEnsureCapacity_real_T(x, b_i);
            iyend = qrmanager->Q->size[0] * qrmanager->Q->size[1];
            for (b_i = 0; b_i < iyend; b_i++) {
              x->data[b_i] = qrmanager->Q->data[b_i];
            }

            if (qrmanager->mrows >= 1) {
              ix = qrmanager->ldq + iy;
              for (k = 0; k < n; k++) {
                temp = c * x->data[iy] + s * x->data[ix];
                x->data[ix] = c * x->data[ix] - s * x->data[iy];
                x->data[iy] = temp;
                ix++;
                iy++;
              }
            }

            b_i = qrmanager->Q->size[0] * qrmanager->Q->size[1];
            qrmanager->Q->size[0] = x->size[0];
            qrmanager->Q->size[1] = x->size[1];
            emxEnsureCapacity_real_T(qrmanager->Q, b_i);
            iyend = x->size[0] * x->size[1];
            for (b_i = 0; b_i < iyend; b_i++) {
              qrmanager->Q->data[b_i] = x->data[b_i];
            }
          }
          break;

         case -1:
          i = activeConstrIdx;
          if (qrmanager->usedPivoting) {
            i = 1;
            while ((i <= qrmanager->ncols) && (qrmanager->jpvt->data[i - 1] !=
                    activeConstrIdx)) {
              i++;
            }
          }

          if (i >= qrmanager->ncols) {
            qrmanager->ncols--;
          } else {
            qrmanager->jpvt->data[i - 1] = qrmanager->jpvt->data
              [qrmanager->ncols - 1];
            b_i = qrmanager->minRowCol;
            for (k = 0; k < b_i; k++) {
              qrmanager->QR->data[k + qrmanager->QR->size[0] * (i - 1)] =
                qrmanager->QR->data[k + qrmanager->QR->size[0] *
                (qrmanager->ncols - 1)];
            }

            qrmanager->ncols--;
            idx = qrmanager->mrows;
            iyend = qrmanager->ncols;
            if (idx < iyend) {
              iyend = idx;
            }

            qrmanager->minRowCol = iyend;
            if (i < qrmanager->mrows) {
              idx = qrmanager->mrows - 1;
              endIdx = qrmanager->ncols;
              if (idx < endIdx) {
                endIdx = idx;
              }

              for (k = endIdx; k >= i; k--) {
                d = qrmanager->QR->data[k + qrmanager->QR->size[0] * (i - 1)];
                xrotg(&qrmanager->QR->data[(k + qrmanager->QR->size[0] * (i - 1))
                      - 1], &d, &c, &s);
                qrmanager->QR->data[k + qrmanager->QR->size[0] * (i - 1)] = d;
                qrmanager->QR->data[k + qrmanager->QR->size[0] * (k - 1)] = 0.0;
                QRk0 = k + qrmanager->ldq * i;
                n = qrmanager->ncols - i;
                b_i = x->size[0] * x->size[1];
                x->size[0] = qrmanager->QR->size[0];
                x->size[1] = qrmanager->QR->size[1];
                emxEnsureCapacity_real_T(x, b_i);
                iyend = qrmanager->QR->size[0] * qrmanager->QR->size[1];
                for (b_i = 0; b_i < iyend; b_i++) {
                  x->data[b_i] = qrmanager->QR->data[b_i];
                }

                if (n >= 1) {
                  ix = QRk0 - 1;
                  for (iyend = 0; iyend < n; iyend++) {
                    temp = c * x->data[ix] + s * x->data[QRk0];
                    x->data[QRk0] = c * x->data[QRk0] - s * x->data[ix];
                    x->data[ix] = temp;
                    QRk0 += qrmanager->ldq;
                    ix += qrmanager->ldq;
                  }
                }

                b_i = qrmanager->QR->size[0] * qrmanager->QR->size[1];
                qrmanager->QR->size[0] = x->size[0];
                qrmanager->QR->size[1] = x->size[1];
                emxEnsureCapacity_real_T(qrmanager->QR, b_i);
                iyend = x->size[0] * x->size[1];
                for (b_i = 0; b_i < iyend; b_i++) {
                  qrmanager->QR->data[b_i] = x->data[b_i];
                }

                iy = qrmanager->ldq * (k - 1);
                n = qrmanager->mrows;
                b_i = x->size[0] * x->size[1];
                x->size[0] = qrmanager->Q->size[0];
                x->size[1] = qrmanager->Q->size[1];
                emxEnsureCapacity_real_T(x, b_i);
                iyend = qrmanager->Q->size[0] * qrmanager->Q->size[1];
                for (b_i = 0; b_i < iyend; b_i++) {
                  x->data[b_i] = qrmanager->Q->data[b_i];
                }

                if (qrmanager->mrows >= 1) {
                  ix = qrmanager->ldq + iy;
                  for (iyend = 0; iyend < n; iyend++) {
                    temp = c * x->data[iy] + s * x->data[ix];
                    x->data[ix] = c * x->data[ix] - s * x->data[iy];
                    x->data[iy] = temp;
                    ix++;
                    iy++;
                  }
                }

                b_i = qrmanager->Q->size[0] * qrmanager->Q->size[1];
                qrmanager->Q->size[0] = x->size[0];
                qrmanager->Q->size[1] = x->size[1];
                emxEnsureCapacity_real_T(qrmanager->Q, b_i);
                iyend = x->size[0] * x->size[1];
                for (b_i = 0; b_i < iyend; b_i++) {
                  qrmanager->Q->data[b_i] = x->data[b_i];
                }
              }

              b_i = i + 1;
              for (k = b_i; k <= endIdx; k++) {
                d = qrmanager->QR->data[k + qrmanager->QR->size[0] * (k - 1)];
                xrotg(&qrmanager->QR->data[(k + qrmanager->QR->size[0] * (k - 1))
                      - 1], &d, &c, &s);
                qrmanager->QR->data[k + qrmanager->QR->size[0] * (k - 1)] = d;
                QRk0 = k * (qrmanager->ldq + 1);
                n = qrmanager->ncols - k;
                i = qrmanager->QR->size[0];
                idx = x->size[0] * x->size[1];
                x->size[0] = i;
                i = qrmanager->QR->size[1];
                x->size[1] = i;
                emxEnsureCapacity_real_T(x, idx);
                iyend = qrmanager->QR->size[0] * qrmanager->QR->size[1];
                for (i = 0; i < iyend; i++) {
                  x->data[i] = qrmanager->QR->data[i];
                }

                if (n >= 1) {
                  ix = QRk0 - 1;
                  for (iyend = 0; iyend < n; iyend++) {
                    temp = c * x->data[ix] + s * x->data[QRk0];
                    x->data[QRk0] = c * x->data[QRk0] - s * x->data[ix];
                    x->data[ix] = temp;
                    QRk0 += qrmanager->ldq;
                    ix += qrmanager->ldq;
                  }
                }

                i = qrmanager->QR->size[0] * qrmanager->QR->size[1];
                qrmanager->QR->size[0] = x->size[0];
                qrmanager->QR->size[1] = x->size[1];
                emxEnsureCapacity_real_T(qrmanager->QR, i);
                iyend = x->size[0] * x->size[1];
                for (i = 0; i < iyend; i++) {
                  qrmanager->QR->data[i] = x->data[i];
                }

                iy = qrmanager->ldq * (k - 1);
                n = qrmanager->mrows;
                i = qrmanager->Q->size[0];
                idx = x->size[0] * x->size[1];
                x->size[0] = i;
                i = qrmanager->Q->size[1];
                x->size[1] = i;
                emxEnsureCapacity_real_T(x, idx);
                iyend = qrmanager->Q->size[0] * qrmanager->Q->size[1];
                for (i = 0; i < iyend; i++) {
                  x->data[i] = qrmanager->Q->data[i];
                }

                if (qrmanager->mrows >= 1) {
                  ix = qrmanager->ldq + iy;
                  for (iyend = 0; iyend < n; iyend++) {
                    temp = c * x->data[iy] + s * x->data[ix];
                    x->data[ix] = c * x->data[ix] - s * x->data[iy];
                    x->data[iy] = temp;
                    ix++;
                    iy++;
                  }
                }

                i = qrmanager->Q->size[0] * qrmanager->Q->size[1];
                qrmanager->Q->size[0] = x->size[0];
                qrmanager->Q->size[1] = x->size[1];
                emxEnsureCapacity_real_T(qrmanager->Q, i);
                iyend = x->size[0] * x->size[1];
                for (i = 0; i < iyend; i++) {
                  qrmanager->Q->data[i] = x->data[i];
                }
              }
            }
          }
          break;

         default:
          factorQR(qrmanager, workingset->ATwset, nVar,
                   workingset->nActiveConstr);
          computeQ_(qrmanager, qrmanager->mrows);
          break;
        }

        compute_deltax(H, solution, memspace, qrmanager, cholmanager, objective);
        if (solution->state != -5) {
          exitg1 = 1;
        } else {
          temp = b_xnrm2(nVar, solution->searchDir);
          if (temp < options_StepTolerance) {
            guard1 = true;
          } else {
            ratiotest(solution->xstar, solution->searchDir,
                      memspace->workspace_double, workingset->nVar,
                      workingset->ldA, workingset->Aineq, workingset->bineq,
                      workingset->lb, workingset->indexLB, workingset->sizes,
                      workingset->isActiveIdx, workingset->isActiveConstr,
                      workingset->nWConstr, objective->objtype == 5, &temp,
                      &updateFval, &iyend, &activeConstrIdx);
            if (updateFval) {
              switch (iyend) {
               case 3:
                addAineqConstr(workingset, activeConstrIdx);
                break;

               case 4:
                addBoundToActiveSetMatrix_(workingset, 4, activeConstrIdx);
                break;

               default:
                addBoundToActiveSetMatrix_(workingset, 5, activeConstrIdx);
                break;
              }

              activeSetChangeID = 1;
            } else {
              if (objective->objtype == 5) {
                if (b_xnrm2(objective->nvar, solution->searchDir) > 100.0 *
                    static_cast<double>(objective->nvar) * 1.4901161193847656E-8)
                {
                  solution->state = 3;
                } else {
                  solution->state = 4;
                }
              }

              subProblemChanged = false;
              if (workingset->nActiveConstr == 0) {
                solution->state = 1;
              }
            }

            if ((nVar >= 1) && (!(temp == 0.0))) {
              iyend = nVar - 1;
              for (k = 0; k <= iyend; k++) {
                solution->xstar->data[k] += temp * solution->searchDir->data[k];
              }
            }

            computeGrad_StoreHx(objective, H, f, solution->xstar);
            updateFval = true;
            c_local_checkStoppingAndUpdateF(&activeSetChangeID, f, solution,
              memspace, objective, workingset, qrmanager, options_MaxIterations,
              options_ObjectiveLimit, updateFval);
          }
        }
      } else {
        for (k = 0; k < nVar; k++) {
          solution->searchDir->data[k] = 0.0;
        }

        guard1 = true;
      }

      if (guard1) {
        b_i = x->size[0] * x->size[1];
        x->size[0] = memspace->workspace_double->size[0];
        x->size[1] = memspace->workspace_double->size[1];
        emxEnsureCapacity_real_T(x, b_i);
        iyend = memspace->workspace_double->size[0] * memspace->
          workspace_double->size[1];
        for (b_i = 0; b_i < iyend; b_i++) {
          x->data[b_i] = memspace->workspace_double->data[b_i];
        }

        QRk0 = qrmanager->ncols;
        if (qrmanager->ncols > 0) {
          temp = 100.0 * static_cast<double>(qrmanager->mrows) *
            2.2204460492503131E-16;
          if ((qrmanager->mrows > 0) && (qrmanager->ncols > 0)) {
            updateFval = true;
          } else {
            updateFval = false;
          }

          if (updateFval) {
            idx = qrmanager->ncols;
            b_guard1 = false;
            if (qrmanager->mrows < qrmanager->ncols) {
              while ((idx > qrmanager->mrows) && (std::abs(qrmanager->QR->data
                       [(qrmanager->mrows + qrmanager->QR->size[0] * (idx - 1))
                       - 1]) >= temp)) {
                idx--;
              }

              updateFval = (idx == qrmanager->mrows);
              if (updateFval) {
                b_guard1 = true;
              }
            } else {
              b_guard1 = true;
            }

            if (b_guard1) {
              while ((idx >= 1) && (std::abs(qrmanager->QR->data[(idx +
                        qrmanager->QR->size[0] * (idx - 1)) - 1]) >= temp)) {
                idx--;
              }

              updateFval = (idx == 0);
            }
          }

          if (!updateFval) {
            solution->state = -7;
          } else {
            n = qrmanager->ncols;
            xgemv(qrmanager->mrows, qrmanager->ncols, qrmanager->Q,
                  qrmanager->ldq, objective->grad, x);
            if (qrmanager->ncols != 0) {
              for (idx = n; idx >= 1; idx--) {
                iyend = (idx + (idx - 1) * qrmanager->ldq) - 1;
                x->data[idx - 1] /= qrmanager->QR->data[iyend];
                for (i = 0; i <= idx - 2; i++) {
                  ix = (idx - i) - 2;
                  x->data[ix] -= x->data[idx - 1] * qrmanager->QR->data[(iyend -
                    i) - 1];
                }
              }
            }

            for (idx = 0; idx < QRk0; idx++) {
              solution->lambda->data[idx] = -x->data[idx];
            }
          }
        }

        b_i = memspace->workspace_double->size[0] * memspace->
          workspace_double->size[1];
        memspace->workspace_double->size[0] = x->size[0];
        memspace->workspace_double->size[1] = x->size[1];
        emxEnsureCapacity_real_T(memspace->workspace_double, b_i);
        iyend = x->size[0] * x->size[1];
        for (b_i = 0; b_i < iyend; b_i++) {
          memspace->workspace_double->data[b_i] = x->data[b_i];
        }

        if (solution->state != -7) {
          temp = 0.0;
          iyend = 0;
          b_i = (mFixed + mEq) + 1;
          i = workingset->nActiveConstr;
          for (idx = b_i; idx <= i; idx++) {
            d = solution->lambda->data[idx - 1];
            if (d < temp) {
              temp = d;
              iyend = idx;
            }
          }

          if (iyend == 0) {
            solution->state = 1;
          } else {
            activeSetChangeID = -1;
            activeConstrIdx = iyend;
            subProblemChanged = true;
            removeConstr(workingset, iyend);
            solution->lambda->data[iyend - 1] = 0.0;
          }
        }

        updateFval = false;
        c_local_checkStoppingAndUpdateF(&activeSetChangeID, f, solution,
          memspace, objective, workingset, qrmanager, options_MaxIterations,
          options_ObjectiveLimit, updateFval);
      }
    } else {
      if (!updateFval) {
        solution->fstar = computeFval_ReuseHx(objective,
          memspace->workspace_double, f, solution->xstar);
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&x);
}

//
// File trailer for iterate.cpp
//
// [EOF]
//
