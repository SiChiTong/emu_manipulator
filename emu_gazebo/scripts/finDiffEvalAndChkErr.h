//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: finDiffEvalAndChkErr.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef FINDIFFEVALANDCHKERR_H
#define FINDIFFEVALANDCHKERR_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern bool finDiffEvalAndChkErr(coder_internal_ref
  *c_obj_nonlin_tunableEnvironment, const emxArray_real_T
  *d_obj_nonlin_tunableEnvironment, const double
  e_obj_nonlin_tunableEnvironment[6], const double
  f_obj_nonlin_tunableEnvironment[6], double g_obj_nonlin_tunableEnvironment,
  int obj_mEq, double *fplus, double cIneqPlus[12], emxArray_real_T *cEqPlus,
  int dim, double delta, emxArray_real_T *xk);

#endif

//
// File trailer for finDiffEvalAndChkErr.h
//
// [EOF]
//
