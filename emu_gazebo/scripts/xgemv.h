//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgemv.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef XGEMV_H
#define XGEMV_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void b_xgemv(int m, int n, const emxArray_real_T *A, int lda, const
                    emxArray_real_T *x, emxArray_real_T *y);
extern void c_xgemv(int m, const emxArray_real_T *A, int lda, const
                    emxArray_real_T *x, emxArray_real_T *y);
extern void d_xgemv(int m, const emxArray_real_T *A, int lda, const
                    emxArray_real_T *x, int ix0, emxArray_real_T *y);
extern void e_xgemv(int m, int n, const emxArray_real_T *A, int lda, const
                    emxArray_real_T *x, int ix0, emxArray_real_T *y);
extern void xgemv(int m, int n, const emxArray_real_T *A, int lda, const
                  emxArray_real_T *x, emxArray_real_T *y);

#endif

//
// File trailer for xgemv.h
//
// [EOF]
//
