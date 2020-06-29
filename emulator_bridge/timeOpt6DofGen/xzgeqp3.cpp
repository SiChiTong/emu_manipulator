//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzgeqp3.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "xzgeqp3.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xzlarf.h"
#include "xzlarfg.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *A
//                int m
//                int n
//                int nfxd
//                emxArray_real_T *tau
// Return Type  : void
//
void qrf(emxArray_real_T *A, int m, int n, int nfxd, emxArray_real_T *tau)
{
  emxArray_real_T *work;
  int lda;
  int i;
  int ii;
  int mmi;
  double atmp;
  emxInit_real_T(&work, 1);
  lda = A->size[0];
  i = work->size[0];
  work->size[0] = A->size[1];
  emxEnsureCapacity_real_T(work, i);
  ii = A->size[1];
  for (i = 0; i < ii; i++) {
    work->data[i] = 0.0;
  }

  for (i = 0; i < nfxd; i++) {
    ii = i * lda + i;
    mmi = m - i;
    if (i + 1 < m) {
      atmp = A->data[ii];
      tau->data[i] = xzlarfg(mmi, &atmp, A, ii + 2);
      A->data[ii] = atmp;
    } else {
      tau->data[i] = 0.0;
    }

    if (i + 1 < n) {
      atmp = A->data[ii];
      A->data[ii] = 1.0;
      xzlarf(mmi, (n - i) - 1, ii + 1, tau->data[i], A, (ii + lda) + 1, lda,
             work);
      A->data[ii] = atmp;
    }
  }

  emxFree_real_T(&work);
}

//
// File trailer for xzgeqp3.cpp
//
// [EOF]
//
