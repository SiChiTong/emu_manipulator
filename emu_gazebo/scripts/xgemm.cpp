//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgemm.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "xgemm.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : int m
//                int n
//                int k
//                const emxArray_real_T *A
//                int ia0
//                int lda
//                const emxArray_real_T *B
//                int ldb
//                emxArray_real_T *C
//                int ldc
// Return Type  : void
//
void b_xgemm(int m, int n, int k, const emxArray_real_T *A, int ia0, int lda,
             const emxArray_real_T *B, int ldb, emxArray_real_T *C, int ldc)
{
  int lastColC;
  int cr;
  int br;
  int i;
  int i1;
  int ic;
  int ar;
  double temp;
  int w;
  int b_w;
  if ((m != 0) && (n != 0)) {
    lastColC = ldc * (n - 1);
    for (cr = 0; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      i = cr + 1;
      i1 = cr + m;
      for (ic = i; ic <= i1; ic++) {
        C->data[ic - 1] = 0.0;
      }
    }

    br = -1;
    for (cr = 0; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      ar = ia0;
      i = cr + 1;
      i1 = cr + m;
      for (ic = i; ic <= i1; ic++) {
        temp = 0.0;
        for (w = 0; w < k; w++) {
          b_w = w + 1;
          temp += A->data[(b_w + ar) - 2] * B->data[b_w + br];
        }

        C->data[ic - 1] += temp;
        ar += lda;
      }

      br += ldb;
    }
  }
}

//
// Arguments    : int m
//                int n
//                int k
//                const emxArray_real_T *A
//                int lda
//                const emxArray_real_T *B
//                int ib0
//                int ldb
//                emxArray_real_T *C
//                int ldc
// Return Type  : void
//
void xgemm(int m, int n, int k, const emxArray_real_T *A, int lda, const
           emxArray_real_T *B, int ib0, int ldb, emxArray_real_T *C, int ldc)
{
  int br;
  int lastColC;
  int cr;
  int i;
  int i1;
  int ar;
  int ic;
  int ib;
  int ia;
  int i2;
  if ((m != 0) && (n != 0)) {
    br = ib0;
    lastColC = ldc * (n - 1);
    for (cr = 0; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      i = cr + 1;
      i1 = cr + m;
      for (ic = i; ic <= i1; ic++) {
        C->data[ic - 1] = 0.0;
      }
    }

    for (cr = 0; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      ar = -1;
      i = br + k;
      for (ib = br; ib < i; ib++) {
        ia = ar;
        i1 = cr + 1;
        i2 = cr + m;
        for (ic = i1; ic <= i2; ic++) {
          ia++;
          C->data[ic - 1] += B->data[ib - 1] * A->data[ia];
        }

        ar += lda;
      }

      br += ldb;
    }
  }
}

//
// File trailer for xgemm.cpp
//
// [EOF]
//
