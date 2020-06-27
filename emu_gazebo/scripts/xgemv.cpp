//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgemv.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "xgemv.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : int m
//                int n
//                const emxArray_real_T *A
//                int lda
//                const emxArray_real_T *x
//                emxArray_real_T *y
// Return Type  : void
//
void b_xgemv(int m, int n, const emxArray_real_T *A, int lda, const
             emxArray_real_T *x, emxArray_real_T *y)
{
  int iy;
  int i;
  int iac;
  int ix;
  double c;
  int i1;
  int ia;
  if ((m != 0) && (n != 0)) {
    for (iy = 0; iy < n; iy++) {
      y->data[iy] = 0.0;
    }

    iy = 0;
    i = lda * (n - 1) + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      ix = 0;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        c += A->data[ia - 1] * x->data[ix];
        ix++;
      }

      y->data[iy] += c;
      iy++;
    }
  }
}

//
// Arguments    : int m
//                const emxArray_real_T *A
//                int lda
//                const emxArray_real_T *x
//                emxArray_real_T *y
// Return Type  : void
//
void c_xgemv(int m, const emxArray_real_T *A, int lda, const emxArray_real_T *x,
             emxArray_real_T *y)
{
  int iy;
  int i;
  int iac;
  int ix;
  double c;
  int i1;
  int ia;
  if (m != 0) {
    for (iy = 0; iy < 12; iy++) {
      y->data[iy] = -y->data[iy];
    }

    iy = 0;
    i = lda * 11 + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      ix = 0;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        c += A->data[ia - 1] * x->data[ix];
        ix++;
      }

      y->data[iy] += c;
      iy++;
    }
  }
}

//
// Arguments    : int m
//                const emxArray_real_T *A
//                int lda
//                const emxArray_real_T *x
//                int ix0
//                emxArray_real_T *y
// Return Type  : void
//
void d_xgemv(int m, const emxArray_real_T *A, int lda, const emxArray_real_T *x,
             int ix0, emxArray_real_T *y)
{
  int iy;
  int i;
  int iac;
  int ix;
  double c;
  int i1;
  int ia;
  if (m != 0) {
    for (iy = 0; iy < 12; iy++) {
      y->data[iy] = -y->data[iy];
    }

    iy = 0;
    i = lda * 11 + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      ix = ix0;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        c += A->data[ia - 1] * x->data[ix - 1];
        ix++;
      }

      y->data[iy] += c;
      iy++;
    }
  }
}

//
// Arguments    : int m
//                int n
//                const emxArray_real_T *A
//                int lda
//                const emxArray_real_T *x
//                int ix0
//                emxArray_real_T *y
// Return Type  : void
//
void e_xgemv(int m, int n, const emxArray_real_T *A, int lda, const
             emxArray_real_T *x, int ix0, emxArray_real_T *y)
{
  int iy;
  int i;
  int iac;
  int ix;
  double c;
  int i1;
  int ia;
  if ((m != 0) && (n != 0)) {
    for (iy = 0; iy < n; iy++) {
      y->data[iy] = -y->data[iy];
    }

    iy = 0;
    i = lda * (n - 1) + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      ix = ix0;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        c += A->data[ia - 1] * x->data[ix - 1];
        ix++;
      }

      y->data[iy] += c;
      iy++;
    }
  }
}

//
// Arguments    : int m
//                int n
//                const emxArray_real_T *A
//                int lda
//                const emxArray_real_T *x
//                emxArray_real_T *y
// Return Type  : void
//
void xgemv(int m, int n, const emxArray_real_T *A, int lda, const
           emxArray_real_T *x, emxArray_real_T *y)
{
  int iy;
  int i;
  int iac;
  int ix;
  double c;
  int i1;
  int ia;
  if ((m != 0) && (n != 0)) {
    for (iy = 0; iy < n; iy++) {
      y->data[iy] = -y->data[iy];
    }

    iy = 0;
    i = lda * (n - 1) + 1;
    for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      ix = 0;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        c += A->data[ia - 1] * x->data[ix];
        ix++;
      }

      y->data[iy] += c;
      iy++;
    }
  }
}

//
// File trailer for xgemv.cpp
//
// [EOF]
//
