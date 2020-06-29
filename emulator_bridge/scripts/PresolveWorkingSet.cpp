//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PresolveWorkingSet.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "PresolveWorkingSet.h"
#include "ComputeNumDependentEq_.h"
#include "countsort.h"
#include "factorQRE.h"
#include "feasibleX0ForWorkingSet.h"
#include "maxConstraintViolation.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include <cmath>

// Function Definitions

//
// Arguments    : e_struct_T *solution
//                c_struct_T *memspace
//                h_struct_T *workingset
//                i_struct_T *qrmanager
// Return Type  : void
//
void PresolveWorkingSet(e_struct_T *solution, c_struct_T *memspace, h_struct_T
  *workingset, i_struct_T *qrmanager)
{
  int nVar;
  int mWorkingFixed;
  int TYPE;
  int nDepInd;
  int idx_local;
  int idxEndIneq;
  int i;
  emxArray_int32_T *depIdx;
  double tol;
  bool okWorkingSet;
  int idx;
  bool guard1 = false;
  solution->state = 82;
  nVar = workingset->nVar;
  mWorkingFixed = workingset->nWConstr[0];
  TYPE = workingset->nWConstr[1] + workingset->nWConstr[0];
  nDepInd = 0;
  if (TYPE > 0) {
    for (idx_local = 0; idx_local < TYPE; idx_local++) {
      for (idxEndIneq = 0; idxEndIneq < nVar; idxEndIneq++) {
        qrmanager->QR->data[idx_local + qrmanager->QR->size[0] * idxEndIneq] =
          workingset->ATwset->data[idxEndIneq + workingset->ATwset->size[0] *
          idx_local];
      }
    }

    nDepInd = ComputeNumDependentEq_(qrmanager, workingset->bwset, TYPE,
      workingset->nVar);
    if (nDepInd > 0) {
      emxInit_int32_T(&depIdx, 1);
      i = depIdx->size[0];
      depIdx->size[0] = memspace->workspace_int->size[0];
      emxEnsureCapacity_int32_T(depIdx, i);
      idx_local = memspace->workspace_int->size[0];
      for (i = 0; i < idx_local; i++) {
        depIdx->data[i] = memspace->workspace_int->data[i];
      }

      for (idx = 0; idx < mWorkingFixed; idx++) {
        qrmanager->jpvt->data[idx] = 1;
      }

      i = workingset->nWConstr[0] + 1;
      for (idx = i; idx <= TYPE; idx++) {
        qrmanager->jpvt->data[idx - 1] = 0;
      }

      factorQRE(qrmanager, workingset->ATwset, workingset->nVar, TYPE);
      for (idx = 0; idx < nDepInd; idx++) {
        depIdx->data[idx] = qrmanager->jpvt->data[(TYPE - nDepInd) + idx];
      }

      i = memspace->workspace_int->size[0];
      memspace->workspace_int->size[0] = depIdx->size[0];
      emxEnsureCapacity_int32_T(memspace->workspace_int, i);
      idx_local = depIdx->size[0];
      for (i = 0; i < idx_local; i++) {
        memspace->workspace_int->data[i] = depIdx->data[i];
      }

      emxFree_int32_T(&depIdx);
      countsort(memspace->workspace_int, nDepInd, memspace->workspace_sort, 1,
                TYPE);
      for (idx = nDepInd; idx >= 1; idx--) {
        nVar = (workingset->nWConstr[0] + workingset->nWConstr[1]) - 1;
        if (nVar + 1 != 0) {
          i = memspace->workspace_int->data[idx - 1];
          if (i <= nVar + 1) {
            if ((workingset->nActiveConstr == nVar + 1) || (i == nVar + 1)) {
              workingset->mEqRemoved++;
              workingset->indexEqRemoved->data[workingset->mEqRemoved - 1] =
                workingset->Wlocalidx->data[memspace->workspace_int->data[idx -
                1] - 1];
              removeConstr(workingset, memspace->workspace_int->data[idx - 1]);
            } else {
              workingset->mEqRemoved++;
              mWorkingFixed = i - 1;
              TYPE = workingset->Wid->data[mWorkingFixed] - 1;
              idx_local = workingset->Wlocalidx->data[mWorkingFixed];
              workingset->indexEqRemoved->data[workingset->mEqRemoved - 1] =
                workingset->Wlocalidx->data[mWorkingFixed];
              workingset->isActiveConstr->data[(workingset->isActiveIdx[TYPE] +
                idx_local) - 2] = false;
              workingset->Wid->data[mWorkingFixed] = workingset->Wid->data[nVar];
              workingset->Wlocalidx->data[mWorkingFixed] = workingset->
                Wlocalidx->data[nVar];
              i = workingset->nVar;
              for (idxEndIneq = 0; idxEndIneq < i; idxEndIneq++) {
                workingset->ATwset->data[idxEndIneq + workingset->ATwset->size[0]
                  * mWorkingFixed] = workingset->ATwset->data[idxEndIneq +
                  workingset->ATwset->size[0] * nVar];
              }

              workingset->bwset->data[mWorkingFixed] = workingset->bwset->
                data[nVar];
              workingset->Wid->data[nVar] = workingset->Wid->data
                [workingset->nActiveConstr - 1];
              workingset->Wlocalidx->data[nVar] = workingset->Wlocalidx->
                data[workingset->nActiveConstr - 1];
              i = workingset->nVar;
              for (idxEndIneq = 0; idxEndIneq < i; idxEndIneq++) {
                workingset->ATwset->data[idxEndIneq + workingset->ATwset->size[0]
                  * nVar] = workingset->ATwset->data[idxEndIneq +
                  workingset->ATwset->size[0] * (workingset->nActiveConstr - 1)];
              }

              workingset->bwset->data[nVar] = workingset->bwset->data
                [workingset->nActiveConstr - 1];
              workingset->nActiveConstr--;
              workingset->nWConstr[TYPE]--;
            }
          }
        }
      }
    }
  }

  if (nDepInd != -1) {
    idx_local = workingset->nActiveConstr;
    i = workingset->nWConstr[1] + workingset->nWConstr[0];
    if ((workingset->nWConstr[2] + workingset->nWConstr[3]) +
        workingset->nWConstr[4] > 0) {
      tol = 100.0 * static_cast<double>(workingset->nVar) *
        2.2204460492503131E-16;
      for (idx = 0; idx < i; idx++) {
        qrmanager->jpvt->data[idx] = 1;
      }

      idxEndIneq = i + 1;
      for (idx = idxEndIneq; idx <= idx_local; idx++) {
        qrmanager->jpvt->data[idx - 1] = 0;
      }

      factorQRE(qrmanager, workingset->ATwset, workingset->nVar,
                workingset->nActiveConstr);
      idx_local = 0;
      for (idx = workingset->nActiveConstr; idx > workingset->nVar; idx--) {
        idx_local++;
        memspace->workspace_int->data[idx_local - 1] = qrmanager->jpvt->data[idx
          - 1];
      }

      if (idx <= workingset->nVar) {
        while ((idx > i) && (std::abs(qrmanager->QR->data[(idx + qrmanager->
                  QR->size[0] * (idx - 1)) - 1]) < tol)) {
          idx_local++;
          memspace->workspace_int->data[idx_local - 1] = qrmanager->jpvt->
            data[idx - 1];
          idx--;
        }
      }

      countsort(memspace->workspace_int, idx_local, memspace->workspace_sort, i
                + 1, workingset->nActiveConstr);
      for (idx = idx_local; idx >= 1; idx--) {
        removeConstr(workingset, memspace->workspace_int->data[idx - 1]);
      }
    }

    okWorkingSet = feasibleX0ForWorkingSet(memspace->workspace_double,
      solution->xstar, workingset, qrmanager);
    guard1 = false;
    if (!okWorkingSet) {
      idx_local = workingset->nActiveConstr;
      i = workingset->nWConstr[1] + workingset->nWConstr[0];
      if ((workingset->nWConstr[2] + workingset->nWConstr[3]) +
          workingset->nWConstr[4] > 0) {
        tol = 1000.0 * static_cast<double>(workingset->nVar) *
          2.2204460492503131E-16;
        for (idx = 0; idx < i; idx++) {
          qrmanager->jpvt->data[idx] = 1;
        }

        idxEndIneq = i + 1;
        for (idx = idxEndIneq; idx <= idx_local; idx++) {
          qrmanager->jpvt->data[idx - 1] = 0;
        }

        factorQRE(qrmanager, workingset->ATwset, workingset->nVar,
                  workingset->nActiveConstr);
        idx_local = 0;
        for (idx = workingset->nActiveConstr; idx > workingset->nVar; idx--) {
          idx_local++;
          memspace->workspace_int->data[idx_local - 1] = qrmanager->jpvt->
            data[idx - 1];
        }

        if (idx <= workingset->nVar) {
          while ((idx > i) && (std::abs(qrmanager->QR->data[(idx + qrmanager->
                    QR->size[0] * (idx - 1)) - 1]) < tol)) {
            idx_local++;
            memspace->workspace_int->data[idx_local - 1] = qrmanager->jpvt->
              data[idx - 1];
            idx--;
          }
        }

        countsort(memspace->workspace_int, idx_local, memspace->workspace_sort,
                  i + 1, workingset->nActiveConstr);
        for (idx = idx_local; idx >= 1; idx--) {
          removeConstr(workingset, memspace->workspace_int->data[idx - 1]);
        }
      }

      okWorkingSet = feasibleX0ForWorkingSet(memspace->workspace_double,
        solution->xstar, workingset, qrmanager);
      if (!okWorkingSet) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1 && (workingset->nWConstr[0] + workingset->nWConstr[1] ==
                   workingset->nVar)) {
      tol = maxConstraintViolation(workingset, solution->xstar);
      if (tol > 0.001) {
        solution->state = -2;
      }
    }
  } else {
    solution->state = -3;
    idx_local = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
    idxEndIneq = workingset->nActiveConstr;
    for (nVar = idx_local; nVar <= idxEndIneq; nVar++) {
      workingset->isActiveConstr->data[(workingset->isActiveIdx[workingset->
        Wid->data[nVar - 1] - 1] + workingset->Wlocalidx->data[nVar - 1]) - 2] =
        false;
    }

    workingset->nWConstr[2] = 0;
    workingset->nWConstr[3] = 0;
    workingset->nWConstr[4] = 0;
    workingset->nActiveConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  }
}

//
// File trailer for PresolveWorkingSet.cpp
//
// [EOF]
//
