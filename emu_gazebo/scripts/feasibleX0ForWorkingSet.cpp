//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feasibleX0ForWorkingSet.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "feasibleX0ForWorkingSet.h"
#include "computeQ_.h"
#include "factorQR.h"
#include "maxConstraintViolation.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xgemv.h"
#include "xzgeqp3.h"
#include <cmath>

// Function Definitions

//
// Arguments    : emxArray_real_T *workspace
//                emxArray_real_T *xCurrent
//                h_struct_T *workingset
//                i_struct_T *qrmanager
// Return Type  : bool
//
bool feasibleX0ForWorkingSet(emxArray_real_T *workspace, emxArray_real_T
  *xCurrent, h_struct_T *workingset, i_struct_T *qrmanager)
{
  bool nonDegenerateWset;
  int mWConstr_tmp;
  int nVar;
  int ldw;
  int ar;
  int iy;
  emxArray_real_T *B;
  int i;
  int iAcol;
  int ix;
  int ldq;
  double c;
  int i1;
  int mEq;
  int ia;
  int br;
  int exitg1;
  emxArray_real_T *tau;
  double v;
  mWConstr_tmp = workingset->nActiveConstr - 1;
  nVar = workingset->nVar;
  ldw = workingset->ATwset->size[0];
  nonDegenerateWset = true;
  if (workingset->nActiveConstr != 0) {
    for (ar = 0; ar <= mWConstr_tmp; ar++) {
      workspace->data[ar] = workingset->bwset->data[ar];
      workspace->data[ar + workspace->size[0]] = workingset->bwset->data[ar];
    }

    if ((workingset->nVar != 0) && (workingset->nActiveConstr != 0)) {
      iy = 0;
      i = workingset->ATwset->size[0] * mWConstr_tmp + 1;
      for (iAcol = 1; ldw < 0 ? iAcol >= i : iAcol <= i; iAcol += ldw) {
        ix = 0;
        c = 0.0;
        i1 = (iAcol + nVar) - 1;
        for (ia = iAcol; ia <= i1; ia++) {
          c += workingset->ATwset->data[ia - 1] * xCurrent->data[ix];
          ix++;
        }

        workspace->data[iy] += -c;
        iy++;
      }
    }

    emxInit_real_T(&B, 2);
    if (workingset->nActiveConstr >= workingset->nVar) {
      for (iAcol = 0; iAcol < nVar; iAcol++) {
        for (iy = 0; iy <= mWConstr_tmp; iy++) {
          qrmanager->QR->data[iy + qrmanager->QR->size[0] * iAcol] =
            workingset->ATwset->data[iAcol + workingset->ATwset->size[0] * iy];
        }
      }

      if (workingset->nActiveConstr * workingset->nVar == 0) {
        qrmanager->mrows = workingset->nActiveConstr;
        qrmanager->ncols = workingset->nVar;
        qrmanager->minRowCol = 0;
      } else {
        qrmanager->usedPivoting = false;
        qrmanager->mrows = workingset->nActiveConstr;
        qrmanager->ncols = workingset->nVar;
        i = workingset->nVar;
        for (ar = 0; ar < i; ar++) {
          qrmanager->jpvt->data[ar] = ar + 1;
        }

        iAcol = workingset->nActiveConstr;
        ix = workingset->nVar;
        if (iAcol < ix) {
          ix = iAcol;
        }

        qrmanager->minRowCol = ix;
        i = B->size[0] * B->size[1];
        B->size[0] = qrmanager->QR->size[0];
        B->size[1] = qrmanager->QR->size[1];
        emxEnsureCapacity_real_T(B, i);
        iAcol = qrmanager->QR->size[0] * qrmanager->QR->size[1];
        for (i = 0; i < iAcol; i++) {
          B->data[i] = qrmanager->QR->data[i];
        }

        emxInit_real_T(&tau, 1);
        iAcol = qrmanager->QR->size[0];
        iy = qrmanager->QR->size[1];
        if (iAcol < iy) {
          iy = iAcol;
        }

        i = tau->size[0];
        tau->size[0] = iy;
        emxEnsureCapacity_real_T(tau, i);
        for (i = 0; i < iy; i++) {
          tau->data[i] = 0.0;
        }

        if (ix >= 1) {
          qrf(B, workingset->nActiveConstr, workingset->nVar, ix, tau);
        }

        i = qrmanager->QR->size[0] * qrmanager->QR->size[1];
        qrmanager->QR->size[0] = B->size[0];
        qrmanager->QR->size[1] = B->size[1];
        emxEnsureCapacity_real_T(qrmanager->QR, i);
        iAcol = B->size[0] * B->size[1];
        for (i = 0; i < iAcol; i++) {
          qrmanager->QR->data[i] = B->data[i];
        }

        i = qrmanager->tau->size[0];
        qrmanager->tau->size[0] = tau->size[0];
        emxEnsureCapacity_real_T(qrmanager->tau, i);
        iAcol = tau->size[0];
        for (i = 0; i < iAcol; i++) {
          qrmanager->tau->data[i] = tau->data[i];
        }

        emxFree_real_T(&tau);
      }

      computeQ_(qrmanager, qrmanager->mrows);
      ldq = qrmanager->ldq;
      ldw = workspace->size[0];
      i = B->size[0] * B->size[1];
      B->size[0] = workspace->size[0];
      B->size[1] = workspace->size[1];
      emxEnsureCapacity_real_T(B, i);
      iAcol = workspace->size[0] * workspace->size[1];
      for (i = 0; i < iAcol; i++) {
        B->data[i] = workspace->data[i];
      }

      if (workingset->nVar != 0) {
        for (iy = 0; ldw < 0 ? iy >= ldw : iy <= ldw; iy += ldw) {
          i = iy + 1;
          i1 = iy + nVar;
          for (ix = i; ix <= i1; ix++) {
            workspace->data[ix - 1] = 0.0;
          }
        }

        br = -1;
        for (iy = 0; ldw < 0 ? iy >= ldw : iy <= ldw; iy += ldw) {
          ar = -1;
          i = iy + 1;
          i1 = iy + nVar;
          for (ix = i; ix <= i1; ix++) {
            c = 0.0;
            for (iAcol = 0; iAcol <= mWConstr_tmp; iAcol++) {
              mEq = iAcol + 1;
              c += qrmanager->Q->data[mEq + ar] * B->data[mEq + br];
            }

            workspace->data[ix - 1] += c;
            ar += ldq;
          }

          br += ldw;
        }
      }

      for (ar = nVar; ar >= 1; ar--) {
        iAcol = ldq * (ar - 1) - 1;
        i = ar + -1;
        if (workspace->data[i] != 0.0) {
          workspace->data[i] /= qrmanager->QR->data[ar + iAcol];
          for (mEq = 0; mEq <= ar - 2; mEq++) {
            workspace->data[mEq] -= workspace->data[i] * qrmanager->QR->data
              [(mEq + iAcol) + 1];
          }
        }
      }

      iy = ldw - 1;
      for (ar = nVar; ar >= 1; ar--) {
        iAcol = ldq * (ar - 1) - 1;
        i = ar + iy;
        if (workspace->data[i] != 0.0) {
          workspace->data[i] /= qrmanager->QR->data[ar + iAcol];
          for (mEq = 0; mEq <= ar - 2; mEq++) {
            i1 = (mEq + iy) + 1;
            workspace->data[i1] -= workspace->data[i] * qrmanager->QR->data[(mEq
              + iAcol) + 1];
          }
        }
      }
    } else {
      factorQR(qrmanager, workingset->ATwset, workingset->nVar,
               workingset->nActiveConstr);
      computeQ_(qrmanager, qrmanager->minRowCol);
      ldq = qrmanager->ldq;
      ldw = workspace->size[0];
      for (mEq = 0; mEq <= mWConstr_tmp; mEq++) {
        iAcol = ldq * mEq;
        c = workspace->data[mEq];
        for (ar = 0; ar < mEq; ar++) {
          c -= qrmanager->QR->data[ar + iAcol] * workspace->data[ar];
        }

        workspace->data[mEq] = c / qrmanager->QR->data[mEq + iAcol];
      }

      for (mEq = 0; mEq <= mWConstr_tmp; mEq++) {
        iAcol = ldq * mEq;
        iy = mEq + ldw;
        c = workspace->data[iy];
        for (ar = 0; ar < mEq; ar++) {
          c -= qrmanager->QR->data[ar + iAcol] * workspace->data[ar + ldw];
        }

        workspace->data[iy] = c / qrmanager->QR->data[mEq + iAcol];
      }

      i = B->size[0] * B->size[1];
      B->size[0] = workspace->size[0];
      B->size[1] = workspace->size[1];
      emxEnsureCapacity_real_T(B, i);
      iAcol = workspace->size[0] * workspace->size[1];
      for (i = 0; i < iAcol; i++) {
        B->data[i] = workspace->data[i];
      }

      if (workingset->nVar != 0) {
        for (iy = 0; ldw < 0 ? iy >= ldw : iy <= ldw; iy += ldw) {
          i = iy + 1;
          i1 = iy + nVar;
          for (ix = i; ix <= i1; ix++) {
            workspace->data[ix - 1] = 0.0;
          }
        }

        br = 1;
        for (iy = 0; ldw < 0 ? iy >= ldw : iy <= ldw; iy += ldw) {
          ar = -1;
          i = br + mWConstr_tmp;
          for (iAcol = br; iAcol <= i; iAcol++) {
            ia = ar;
            i1 = iy + 1;
            mEq = iy + nVar;
            for (ix = i1; ix <= mEq; ix++) {
              ia++;
              workspace->data[ix - 1] += B->data[iAcol - 1] * qrmanager->Q->
                data[ia];
            }

            ar += ldq;
          }

          br += ldw;
        }
      }
    }

    emxFree_real_T(&B);
    ar = 0;
    do {
      exitg1 = 0;
      if (ar <= nVar - 1) {
        c = workspace->data[ar];
        if (rtIsInf(c) || rtIsNaN(c)) {
          nonDegenerateWset = false;
          exitg1 = 1;
        } else {
          c = workspace->data[ar + workspace->size[0]];
          if (rtIsInf(c) || rtIsNaN(c)) {
            nonDegenerateWset = false;
            exitg1 = 1;
          } else {
            ar++;
          }
        }
      } else {
        if (nVar >= 1) {
          iAcol = nVar - 1;
          for (ar = 0; ar <= iAcol; ar++) {
            workspace->data[ar] += xCurrent->data[ar];
          }
        }

        iy = workingset->sizes[3];
        ix = workingset->sizes[4];
        br = workingset->sizes[0];
        switch (workingset->probType) {
         case 2:
          v = 0.0;
          mEq = workingset->sizes[1] - 1;
          for (ar = 0; ar < 12; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->bineq[ar];
          }

          c_xgemv(workingset->nVarOrig, workingset->Aineq, workingset->ldA,
                  workspace, workingset->maxConstrWorkspace);
          for (ar = 0; ar < 12; ar++) {
            workingset->maxConstrWorkspace->data[ar] -= workspace->
              data[workingset->nVarOrig + ar];
            if ((!(v > workingset->maxConstrWorkspace->data[ar])) && (!rtIsNaN
                 (workingset->maxConstrWorkspace->data[ar]))) {
              v = workingset->maxConstrWorkspace->data[ar];
            }
          }

          for (ar = 0; ar <= mEq; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->beq->data[ar];
          }

          xgemv(workingset->nVarOrig, workingset->sizes[1], workingset->Aeq,
                workingset->ldA, workspace, workingset->maxConstrWorkspace);
          iAcol = (workingset->nVarOrig + workingset->sizes[1]) + 12;
          for (ar = 0; ar <= mEq; ar++) {
            workingset->maxConstrWorkspace->data[ar] =
              (workingset->maxConstrWorkspace->data[ar] - workspace->data
               [(workingset->nVarOrig + ar) + 12]) + workspace->data[iAcol + ar];
            c = std::abs(workingset->maxConstrWorkspace->data[ar]);
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
          break;

         default:
          v = 0.0;
          mEq = workingset->sizes[1] - 1;
          for (ar = 0; ar < 12; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->bineq[ar];
          }

          c_xgemv(workingset->nVar, workingset->Aineq, workingset->ldA,
                  workspace, workingset->maxConstrWorkspace);
          for (ar = 0; ar < 12; ar++) {
            if ((!(v > workingset->maxConstrWorkspace->data[ar])) && (!rtIsNaN
                 (workingset->maxConstrWorkspace->data[ar]))) {
              v = workingset->maxConstrWorkspace->data[ar];
            }
          }

          for (ar = 0; ar <= mEq; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->beq->data[ar];
          }

          xgemv(workingset->nVar, workingset->sizes[1], workingset->Aeq,
                workingset->ldA, workspace, workingset->maxConstrWorkspace);
          for (ar = 0; ar <= mEq; ar++) {
            c = std::abs(workingset->maxConstrWorkspace->data[ar]);
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
          break;
        }

        if (workingset->sizes[3] > 0) {
          for (ar = 0; ar < iy; ar++) {
            c = -workspace->data[workingset->indexLB->data[ar] - 1] -
              workingset->lb->data[workingset->indexLB->data[ar] - 1];
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
        }

        if (workingset->sizes[4] > 0) {
          for (ar = 0; ar < ix; ar++) {
            c = workspace->data[workingset->indexUB->data[ar] - 1] -
              workingset->ub->data[workingset->indexUB->data[ar] - 1];
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
        }

        if (workingset->sizes[0] > 0) {
          for (ar = 0; ar < br; ar++) {
            iAcol = workingset->indexFixed->data[ar] - 1;
            c = std::abs(workspace->data[iAcol] - workingset->ub->data[iAcol]);
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
        }

        c = maxConstraintViolation(workingset, workspace, workspace->size[0] + 1);
        if ((v <= 2.2204460492503131E-16) || (v < c)) {
          for (ar = 0; ar < nVar; ar++) {
            xCurrent->data[ar] = workspace->data[ar];
          }
        } else {
          for (ar = 0; ar < nVar; ar++) {
            xCurrent->data[ar] = workspace->data[workspace->size[0] + ar];
          }
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return nonDegenerateWset;
}

//
// File trailer for feasibleX0ForWorkingSet.cpp
//
// [EOF]
//
