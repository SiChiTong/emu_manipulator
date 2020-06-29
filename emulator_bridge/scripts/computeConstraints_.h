//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeConstraints_.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef COMPUTECONSTRAINTS__H
#define COMPUTECONSTRAINTS__H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern int computeConstraints_(coder_internal_ref
  *c_obj_nonlcon_tunableEnvironmen, const emxArray_real_T
  *d_obj_nonlcon_tunableEnvironmen, const double
  e_obj_nonlcon_tunableEnvironmen[6], const double
  f_obj_nonlcon_tunableEnvironmen[6], double g_obj_nonlcon_tunableEnvironmen,
  int obj_mCineq, int obj_mCeq, const emxArray_real_T *x, emxArray_real_T
  *Cineq_workspace, int ineq0, emxArray_real_T *Ceq_workspace, int eq0);

#endif

//
// File trailer for computeConstraints_.h
//
// [EOF]
//
