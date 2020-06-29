//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ComputeNumDependentEq_.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "ComputeNumDependentEq_.h"
#include "computeQ_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "xgeqp3.h"
#include <cmath>

// Function Definitions

//
// Arguments    : i_struct_T *qrmanager
//                const emxArray_real_T *beqf
//                int mConstr
//                int nVar
// Return Type  : int
//
int ComputeNumDependentEq_(i_struct_T *qrmanager, const emxArray_real_T *beqf,
  int mConstr, int nVar)
{
  int numDependent;
  int idx;
  double tol;
  bool exitg1;
  int ix;
  double qtb;
  int iy;
  int k;
  numDependent = mConstr - nVar;
  if (0 > numDependent) {
    numDependent = 0;
  }

  for (idx = 0; idx < nVar; idx++) {
    qrmanager->jpvt->data[idx] = 0;
  }

  if (mConstr * nVar == 0) {
    qrmanager->mrows = mConstr;
    qrmanager->ncols = nVar;
    qrmanager->minRowCol = 0;
  } else {
    qrmanager->usedPivoting = true;
    qrmanager->mrows = mConstr;
    qrmanager->ncols = nVar;
    if (mConstr < nVar) {
      idx = mConstr;
    } else {
      idx = nVar;
    }

    qrmanager->minRowCol = idx;
    xgeqp3(qrmanager->QR, mConstr, nVar, qrmanager->jpvt, qrmanager->tau);
  }

  tol = 100.0 * static_cast<double>(nVar) * 2.2204460492503131E-16;
  if (nVar < mConstr) {
    idx = nVar;
  } else {
    idx = mConstr;
  }

  while ((idx > 0) && (std::abs(qrmanager->QR->data[(idx + qrmanager->QR->size[0]
            * (idx - 1)) - 1]) < tol)) {
    idx--;
    numDependent++;
  }

  if (numDependent > 0) {
    computeQ_(qrmanager, qrmanager->mrows);
    idx = 0;
    exitg1 = false;
    while ((!exitg1) && (idx <= numDependent - 1)) {
      ix = qrmanager->ldq * ((mConstr - idx) - 1);
      qtb = 0.0;
      iy = 0;
      for (k = 0; k < mConstr; k++) {
        qtb += qrmanager->Q->data[ix] * beqf->data[iy];
        ix++;
        iy++;
      }

      if (std::abs(qtb) >= tol) {
        numDependent = -1;
        exitg1 = true;
      } else {
        idx++;
      }
    }
  }

  return numDependent;
}

//
// File trailer for ComputeNumDependentEq_.cpp
//
// [EOF]
//
