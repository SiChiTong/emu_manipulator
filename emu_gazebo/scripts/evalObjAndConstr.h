//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evalObjAndConstr.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef EVALOBJANDCONSTR_H
#define EVALOBJANDCONSTR_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void evalObjAndConstr(coder_internal_ref *c_obj_nonlcon_tunableEnvironmen,
  const emxArray_real_T *d_obj_nonlcon_tunableEnvironmen, const double
  e_obj_nonlcon_tunableEnvironmen[6], const double
  f_obj_nonlcon_tunableEnvironmen[6], double g_obj_nonlcon_tunableEnvironmen,
  int obj_mCeq, const emxArray_real_T *x, double Cineq_workspace[12],
  emxArray_real_T *Ceq_workspace, int eq0, double *fval, int *status);

#endif

//
// File trailer for evalObjAndConstr.h
//
// [EOF]
//
