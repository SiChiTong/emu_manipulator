//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeConstraints_.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "computeConstraints_.h"
#include "checkVectorNonFinite.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"

// Function Definitions

//
// Arguments    : coder_internal_ref *c_obj_nonlcon_tunableEnvironmen
//                const emxArray_real_T *d_obj_nonlcon_tunableEnvironmen
//                const double e_obj_nonlcon_tunableEnvironmen[6]
//                const double f_obj_nonlcon_tunableEnvironmen[6]
//                double g_obj_nonlcon_tunableEnvironmen
//                int obj_mCineq
//                int obj_mCeq
//                const emxArray_real_T *x
//                emxArray_real_T *Cineq_workspace
//                int ineq0
//                emxArray_real_T *Ceq_workspace
//                int eq0
// Return Type  : int
//
int computeConstraints_(coder_internal_ref *c_obj_nonlcon_tunableEnvironmen,
  const emxArray_real_T *d_obj_nonlcon_tunableEnvironmen, const double
  e_obj_nonlcon_tunableEnvironmen[6], const double
  f_obj_nonlcon_tunableEnvironmen[6], double g_obj_nonlcon_tunableEnvironmen,
  int obj_mCineq, int obj_mCeq, const emxArray_real_T *x, emxArray_real_T
  *Cineq_workspace, int ineq0, emxArray_real_T *Ceq_workspace, int eq0)
{
  int status;
  emxArray_real_T *varargout_2;
  emxArray_real_T *varargout_1;
  int ineqEnd;
  int eqEnd;
  int i;
  int i1;
  emxInit_real_T(&varargout_2, 1);
  emxInit_real_T(&varargout_1, 1);
  ineqEnd = (ineq0 + obj_mCineq) - 2;
  eqEnd = (eq0 + obj_mCeq) - 2;
  __anon_fcn(c_obj_nonlcon_tunableEnvironmen, d_obj_nonlcon_tunableEnvironmen,
             e_obj_nonlcon_tunableEnvironmen, f_obj_nonlcon_tunableEnvironmen,
             g_obj_nonlcon_tunableEnvironmen, x, varargout_1, varargout_2);
  if (ineq0 > ineqEnd + 1) {
    i = -1;
    ineqEnd = -1;
  } else {
    i = ineq0 - 2;
  }

  ineqEnd -= i;
  for (i1 = 0; i1 < ineqEnd; i1++) {
    Cineq_workspace->data[(i + i1) + 1] = varargout_1->data[i1];
  }

  emxFree_real_T(&varargout_1);
  if (eq0 > eqEnd + 1) {
    i = -1;
    eqEnd = -1;
  } else {
    i = eq0 - 2;
  }

  ineqEnd = eqEnd - i;
  for (i1 = 0; i1 < ineqEnd; i1++) {
    Ceq_workspace->data[(i + i1) + 1] = varargout_2->data[i1];
  }

  emxFree_real_T(&varargout_2);
  status = checkVectorNonFinite(obj_mCineq, Cineq_workspace, ineq0);
  if (status == 1) {
    status = checkVectorNonFinite(obj_mCeq, Ceq_workspace, eq0);
  }

  return status;
}

//
// File trailer for computeConstraints_.cpp
//
// [EOF]
//
