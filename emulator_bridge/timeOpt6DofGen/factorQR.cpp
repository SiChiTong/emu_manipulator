//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factorQR.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "factorQR.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xzgeqp3.h"

// Function Definitions

//
// Arguments    : i_struct_T *obj
//                const emxArray_real_T *A
//                int mrows
//                int ncols
// Return Type  : void
//
void factorQR(i_struct_T *obj, const emxArray_real_T *A, int mrows, int ncols)
{
  int k;
  emxArray_real_T *b_A;
  emxArray_real_T *tau;
  bool guard1 = false;
  int idx;
  int ix0;
  int minmana;
  int b_k;
  k = mrows * ncols;
  emxInit_real_T(&b_A, 2);
  emxInit_real_T(&tau, 1);
  guard1 = false;
  if (k > 0) {
    for (idx = 0; idx < ncols; idx++) {
      ix0 = A->size[0] * idx;
      minmana = obj->ldq * idx;
      for (k = 0; k < mrows; k++) {
        b_k = k + 1;
        obj->QR->data[(minmana + b_k) - 1] = A->data[(ix0 + b_k) - 1];
      }
    }

    guard1 = true;
  } else if (k == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    guard1 = true;
  }

  if (guard1) {
    obj->usedPivoting = false;
    obj->mrows = mrows;
    obj->ncols = ncols;
    for (idx = 0; idx < ncols; idx++) {
      obj->jpvt->data[idx] = idx + 1;
    }

    if (mrows < ncols) {
      k = mrows;
    } else {
      k = ncols;
    }

    obj->minRowCol = k;
    ix0 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = obj->QR->size[0];
    b_A->size[1] = obj->QR->size[1];
    emxEnsureCapacity_real_T(b_A, ix0);
    idx = obj->QR->size[0] * obj->QR->size[1];
    for (ix0 = 0; ix0 < idx; ix0++) {
      b_A->data[ix0] = obj->QR->data[ix0];
    }

    idx = obj->QR->size[0];
    minmana = obj->QR->size[1];
    if (idx < minmana) {
      minmana = idx;
    }

    ix0 = tau->size[0];
    tau->size[0] = minmana;
    emxEnsureCapacity_real_T(tau, ix0);
    for (ix0 = 0; ix0 < minmana; ix0++) {
      tau->data[ix0] = 0.0;
    }

    if (k >= 1) {
      qrf(b_A, mrows, ncols, k, tau);
    }

    k = obj->QR->size[0] * obj->QR->size[1];
    obj->QR->size[0] = b_A->size[0];
    obj->QR->size[1] = b_A->size[1];
    emxEnsureCapacity_real_T(obj->QR, k);
    idx = b_A->size[0] * b_A->size[1];
    for (k = 0; k < idx; k++) {
      obj->QR->data[k] = b_A->data[k];
    }

    k = obj->tau->size[0];
    obj->tau->size[0] = tau->size[0];
    emxEnsureCapacity_real_T(obj->tau, k);
    idx = tau->size[0];
    for (k = 0; k < idx; k++) {
      obj->tau->data[k] = tau->data[k];
    }
  }

  emxFree_real_T(&tau);
  emxFree_real_T(&b_A);
}

//
// File trailer for factorQR.cpp
//
// [EOF]
//
