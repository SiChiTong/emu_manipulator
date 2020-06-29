//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeMeritFcn.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef COMPUTEMERITFCN_H
#define COMPUTEMERITFCN_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern double computeMeritFcn(double obj_penaltyParam, double fval, const
  emxArray_real_T *Cineq_workspace, int mIneq, const emxArray_real_T
  *Ceq_workspace, int mEq, bool evalWellDefined);

#endif

//
// File trailer for computeMeritFcn.h
//
// [EOF]
//
