//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeFiniteDifferences.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef COMPUTEFINITEDIFFERENCES_H
#define COMPUTEFINITEDIFFERENCES_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern bool computeFiniteDifferences(d_struct_T *obj, double fCurrent, const
  emxArray_real_T *cIneqCurrent, int ineq0, const emxArray_real_T *cEqCurrent,
  int eq0, emxArray_real_T *xk, emxArray_real_T *gradf, emxArray_real_T
  *JacCineqTrans, int CineqColStart, emxArray_real_T *JacCeqTrans, int
  CeqColStart, const emxArray_real_T *c_runTimeOptions_FiniteDifferen);

#endif

//
// File trailer for computeFiniteDifferences.h
//
// [EOF]
//
