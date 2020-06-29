//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feasibleX0ForWorkingSet.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "feasibleX0ForWorkingSet.h"
#include "computeQ_.h"
#include "factorQR.h"
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
  int kAcol;
  int ix;
  int ldq;
  double c;
  int i1;
  int mLB;
  int ia;
  int br;
  int exitg1;
  emxArray_real_T *tau;
  double v;
  double b_v;
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
      for (kAcol = 1; ldw < 0 ? kAcol >= i : kAcol <= i; kAcol += ldw) {
        ix = 0;
        c = 0.0;
        i1 = (kAcol + nVar) - 1;
        for (ia = kAcol; ia <= i1; ia++) {
          c += workingset->ATwset->data[ia - 1] * xCurrent->data[ix];
          ix++;
        }

        workspace->data[iy] += -c;
        iy++;
      }
    }

    emxInit_real_T(&B, 2);
    if (workingset->nActiveConstr >= workingset->nVar) {
      for (ix = 0; ix < nVar; ix++) {
        for (iy = 0; iy <= mWConstr_tmp; iy++) {
          qrmanager->QR->data[iy + qrmanager->QR->size[0] * ix] =
            workingset->ATwset->data[ix + workingset->ATwset->size[0] * iy];
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

        ix = workingset->nActiveConstr;
        kAcol = workingset->nVar;
        if (ix < kAcol) {
          kAcol = ix;
        }

        qrmanager->minRowCol = kAcol;
        i = B->size[0] * B->size[1];
        B->size[0] = qrmanager->QR->size[0];
        B->size[1] = qrmanager->QR->size[1];
        emxEnsureCapacity_real_T(B, i);
        ix = qrmanager->QR->size[0] * qrmanager->QR->size[1];
        for (i = 0; i < ix; i++) {
          B->data[i] = qrmanager->QR->data[i];
        }

        emxInit_real_T(&tau, 1);
        ix = qrmanager->QR->size[0];
        iy = qrmanager->QR->size[1];
        if (ix < iy) {
          iy = ix;
        }

        i = tau->size[0];
        tau->size[0] = iy;
        emxEnsureCapacity_real_T(tau, i);
        for (i = 0; i < iy; i++) {
          tau->data[i] = 0.0;
        }

        if (kAcol >= 1) {
          qrf(B, workingset->nActiveConstr, workingset->nVar, kAcol, tau);
        }

        i = qrmanager->QR->size[0] * qrmanager->QR->size[1];
        qrmanager->QR->size[0] = B->size[0];
        qrmanager->QR->size[1] = B->size[1];
        emxEnsureCapacity_real_T(qrmanager->QR, i);
        ix = B->size[0] * B->size[1];
        for (i = 0; i < ix; i++) {
          qrmanager->QR->data[i] = B->data[i];
        }

        i = qrmanager->tau->size[0];
        qrmanager->tau->size[0] = tau->size[0];
        emxEnsureCapacity_real_T(qrmanager->tau, i);
        ix = tau->size[0];
        for (i = 0; i < ix; i++) {
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
      ix = workspace->size[0] * workspace->size[1];
      for (i = 0; i < ix; i++) {
        B->data[i] = workspace->data[i];
      }

      if (workingset->nVar != 0) {
        for (kAcol = 0; ldw < 0 ? kAcol >= ldw : kAcol <= ldw; kAcol += ldw) {
          i = kAcol + 1;
          i1 = kAcol + nVar;
          for (mLB = i; mLB <= i1; mLB++) {
            workspace->data[mLB - 1] = 0.0;
          }
        }

        br = -1;
        for (kAcol = 0; ldw < 0 ? kAcol >= ldw : kAcol <= ldw; kAcol += ldw) {
          ar = -1;
          i = kAcol + 1;
          i1 = kAcol + nVar;
          for (mLB = i; mLB <= i1; mLB++) {
            c = 0.0;
            for (iy = 0; iy <= mWConstr_tmp; iy++) {
              ix = iy + 1;
              c += qrmanager->Q->data[ix + ar] * B->data[ix + br];
            }

            workspace->data[mLB - 1] += c;
            ar += ldq;
          }

          br += ldw;
        }
      }

      for (ar = nVar; ar >= 1; ar--) {
        kAcol = ldq * (ar - 1) - 1;
        i = ar + -1;
        if (workspace->data[i] != 0.0) {
          workspace->data[i] /= qrmanager->QR->data[ar + kAcol];
          for (mLB = 0; mLB <= ar - 2; mLB++) {
            workspace->data[mLB] -= workspace->data[i] * qrmanager->QR->data
              [(mLB + kAcol) + 1];
          }
        }
      }

      iy = ldw - 1;
      for (ar = nVar; ar >= 1; ar--) {
        kAcol = ldq * (ar - 1) - 1;
        i = ar + iy;
        if (workspace->data[i] != 0.0) {
          workspace->data[i] /= qrmanager->QR->data[ar + kAcol];
          for (mLB = 0; mLB <= ar - 2; mLB++) {
            i1 = (mLB + iy) + 1;
            workspace->data[i1] -= workspace->data[i] * qrmanager->QR->data[(mLB
              + kAcol) + 1];
          }
        }
      }
    } else {
      factorQR(qrmanager, workingset->ATwset, workingset->nVar,
               workingset->nActiveConstr);
      computeQ_(qrmanager, qrmanager->minRowCol);
      ldq = qrmanager->ldq;
      ldw = workspace->size[0];
      for (mLB = 0; mLB <= mWConstr_tmp; mLB++) {
        ix = ldq * mLB;
        c = workspace->data[mLB];
        for (ar = 0; ar < mLB; ar++) {
          c -= qrmanager->QR->data[ar + ix] * workspace->data[ar];
        }

        workspace->data[mLB] = c / qrmanager->QR->data[mLB + ix];
      }

      for (mLB = 0; mLB <= mWConstr_tmp; mLB++) {
        ix = ldq * mLB;
        iy = mLB + ldw;
        c = workspace->data[iy];
        for (ar = 0; ar < mLB; ar++) {
          c -= qrmanager->QR->data[ar + ix] * workspace->data[ar + ldw];
        }

        workspace->data[iy] = c / qrmanager->QR->data[mLB + ix];
      }

      i = B->size[0] * B->size[1];
      B->size[0] = workspace->size[0];
      B->size[1] = workspace->size[1];
      emxEnsureCapacity_real_T(B, i);
      ix = workspace->size[0] * workspace->size[1];
      for (i = 0; i < ix; i++) {
        B->data[i] = workspace->data[i];
      }

      if (workingset->nVar != 0) {
        for (kAcol = 0; ldw < 0 ? kAcol >= ldw : kAcol <= ldw; kAcol += ldw) {
          i = kAcol + 1;
          i1 = kAcol + nVar;
          for (mLB = i; mLB <= i1; mLB++) {
            workspace->data[mLB - 1] = 0.0;
          }
        }

        br = 1;
        for (kAcol = 0; ldw < 0 ? kAcol >= ldw : kAcol <= ldw; kAcol += ldw) {
          ar = -1;
          i = br + mWConstr_tmp;
          for (iy = br; iy <= i; iy++) {
            ia = ar;
            i1 = kAcol + 1;
            ix = kAcol + nVar;
            for (mLB = i1; mLB <= ix; mLB++) {
              ia++;
              workspace->data[mLB - 1] += B->data[iy - 1] * qrmanager->Q->
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
          ix = nVar - 1;
          for (ar = 0; ar <= ix; ar++) {
            workspace->data[ar] += xCurrent->data[ar];
          }
        }

        kAcol = workspace->size[0];
        mLB = workingset->sizes[3];
        switch (workingset->probType) {
         case 2:
          v = 0.0;
          ix = workingset->sizes[2] - 1;
          br = workingset->sizes[1] - 1;
          for (ar = 0; ar <= ix; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->bineq->
              data[ar];
          }

          b_xgemv(workingset->nVarOrig, workingset->sizes[2], workingset->Aineq,
                  workingset->ldA, workspace, workingset->maxConstrWorkspace);
          for (ar = 0; ar <= ix; ar++) {
            workingset->maxConstrWorkspace->data[ar] -= workspace->
              data[workingset->nVarOrig + ar];
            if ((!(v > workingset->maxConstrWorkspace->data[ar])) && (!rtIsNaN
                 (workingset->maxConstrWorkspace->data[ar]))) {
              v = workingset->maxConstrWorkspace->data[ar];
            }
          }

          for (ar = 0; ar <= br; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->beq->data[ar];
          }

          b_xgemv(workingset->nVarOrig, workingset->sizes[1], workingset->Aeq,
                  workingset->ldA, workspace, workingset->maxConstrWorkspace);
          ix = workingset->nVarOrig + workingset->sizes[2];
          iy = ix + workingset->sizes[1];
          for (ar = 0; ar <= br; ar++) {
            workingset->maxConstrWorkspace->data[ar] =
              (workingset->maxConstrWorkspace->data[ar] - workspace->data[ix +
               ar]) + workspace->data[iy + ar];
            c = std::abs(workingset->maxConstrWorkspace->data[ar]);
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
          break;

         default:
          v = 0.0;
          ix = workingset->sizes[2] - 1;
          br = workingset->sizes[1] - 1;
          for (ar = 0; ar <= ix; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->bineq->
              data[ar];
          }

          b_xgemv(workingset->nVar, workingset->sizes[2], workingset->Aineq,
                  workingset->ldA, workspace, workingset->maxConstrWorkspace);
          for (ar = 0; ar <= ix; ar++) {
            if ((!(v > workingset->maxConstrWorkspace->data[ar])) && (!rtIsNaN
                 (workingset->maxConstrWorkspace->data[ar]))) {
              v = workingset->maxConstrWorkspace->data[ar];
            }
          }

          for (ar = 0; ar <= br; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->beq->data[ar];
          }

          b_xgemv(workingset->nVar, workingset->sizes[1], workingset->Aeq,
                  workingset->ldA, workspace, workingset->maxConstrWorkspace);
          for (ar = 0; ar <= br; ar++) {
            c = std::abs(workingset->maxConstrWorkspace->data[ar]);
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
          break;
        }

        if (workingset->sizes[3] > 0) {
          for (ar = 0; ar < mLB; ar++) {
            c = -workspace->data[workingset->indexLB->data[ar] - 1] -
              workingset->lb->data[workingset->indexLB->data[ar] - 1];
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
        }

        mLB = workingset->sizes[3];
        switch (workingset->probType) {
         case 2:
          b_v = 0.0;
          ix = workingset->sizes[2] - 1;
          br = workingset->sizes[1] - 1;
          for (ar = 0; ar <= ix; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->bineq->
              data[ar];
          }

          c_xgemv(workingset->nVarOrig, workingset->sizes[2], workingset->Aineq,
                  workingset->ldA, workspace, workspace->size[0] + 1,
                  workingset->maxConstrWorkspace);
          for (ar = 0; ar <= ix; ar++) {
            workingset->maxConstrWorkspace->data[ar] -= workspace->data[(kAcol +
              workingset->nVarOrig) + ar];
            if ((!(b_v > workingset->maxConstrWorkspace->data[ar])) && (!rtIsNaN
                 (workingset->maxConstrWorkspace->data[ar]))) {
              b_v = workingset->maxConstrWorkspace->data[ar];
            }
          }

          for (ar = 0; ar <= br; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->beq->data[ar];
          }

          c_xgemv(workingset->nVarOrig, workingset->sizes[1], workingset->Aeq,
                  workingset->ldA, workspace, workspace->size[0] + 1,
                  workingset->maxConstrWorkspace);
          ix = workingset->nVarOrig + workingset->sizes[2];
          iy = ix + workingset->sizes[1];
          for (ar = 0; ar <= br; ar++) {
            workingset->maxConstrWorkspace->data[ar] =
              (workingset->maxConstrWorkspace->data[ar] - workspace->data[(kAcol
                + ix) + ar]) + workspace->data[(kAcol + iy) + ar];
            c = std::abs(workingset->maxConstrWorkspace->data[ar]);
            if ((!(b_v > c)) && (!rtIsNaN(c))) {
              b_v = c;
            }
          }
          break;

         default:
          b_v = 0.0;
          ix = workingset->sizes[2] - 1;
          br = workingset->sizes[1] - 1;
          for (ar = 0; ar <= ix; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->bineq->
              data[ar];
          }

          c_xgemv(workingset->nVar, workingset->sizes[2], workingset->Aineq,
                  workingset->ldA, workspace, workspace->size[0] + 1,
                  workingset->maxConstrWorkspace);
          for (ar = 0; ar <= ix; ar++) {
            if ((!(b_v > workingset->maxConstrWorkspace->data[ar])) && (!rtIsNaN
                 (workingset->maxConstrWorkspace->data[ar]))) {
              b_v = workingset->maxConstrWorkspace->data[ar];
            }
          }

          for (ar = 0; ar <= br; ar++) {
            workingset->maxConstrWorkspace->data[ar] = workingset->beq->data[ar];
          }

          c_xgemv(workingset->nVar, workingset->sizes[1], workingset->Aeq,
                  workingset->ldA, workspace, workspace->size[0] + 1,
                  workingset->maxConstrWorkspace);
          for (ar = 0; ar <= br; ar++) {
            c = std::abs(workingset->maxConstrWorkspace->data[ar]);
            if ((!(b_v > c)) && (!rtIsNaN(c))) {
              b_v = c;
            }
          }
          break;
        }

        if (workingset->sizes[3] > 0) {
          for (ar = 0; ar < mLB; ar++) {
            c = -workspace->data[(kAcol + workingset->indexLB->data[ar]) - 1] -
              workingset->lb->data[workingset->indexLB->data[ar] - 1];
            if ((!(b_v > c)) && (!rtIsNaN(c))) {
              b_v = c;
            }
          }
        }

        if ((v <= 2.2204460492503131E-16) || (v < b_v)) {
          for (ar = 0; ar < nVar; ar++) {
            xCurrent->data[ar] = workspace->data[ar];
          }
        } else {
          for (ar = 0; ar < nVar; ar++) {
            xCurrent->data[ar] = workspace->data[kAcol + ar];
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
