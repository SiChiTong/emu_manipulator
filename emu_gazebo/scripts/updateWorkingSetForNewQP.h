//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: updateWorkingSetForNewQP.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef UPDATEWORKINGSETFORNEWQP_H
#define UPDATEWORKINGSETFORNEWQP_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void b_updateWorkingSetForNewQP(const emxArray_real_T *xk, h_struct_T
  *WorkingSet, const double cIneq[12], int mEq, int mNonlinEq, const
  emxArray_real_T *cEq, int mLB, const emxArray_real_T *lb, int mUB, int mFixed);
extern void updateWorkingSetForNewQP(const emxArray_real_T *xk, h_struct_T
  *WorkingSet, const double cIneq[12], int mEq, int mNonlinEq, const
  emxArray_real_T *cEq, int mLB, const emxArray_real_T *lb, int mUB, int mFixed);

#endif

//
// File trailer for updateWorkingSetForNewQP.h
//
// [EOF]
//
