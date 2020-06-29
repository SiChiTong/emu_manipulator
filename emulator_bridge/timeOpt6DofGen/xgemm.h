//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgemm.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef XGEMM_H
#define XGEMM_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void b_xgemm(int m, int n, int k, const emxArray_real_T *A, int ia0, int
                    lda, const emxArray_real_T *B, int ldb, emxArray_real_T *C,
                    int ldc);
extern void xgemm(int m, int n, int k, const emxArray_real_T *A, int lda, const
                  emxArray_real_T *B, int ib0, int ldb, emxArray_real_T *C, int
                  ldc);

#endif

//
// File trailer for xgemm.h
//
// [EOF]
//
