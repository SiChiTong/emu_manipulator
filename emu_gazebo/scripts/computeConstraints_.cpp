//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeConstraints_.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "computeConstraints_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include <cstring>

// Function Definitions

//
// Arguments    : coder_internal_ref *c_obj_nonlcon_tunableEnvironmen
//                const emxArray_real_T *d_obj_nonlcon_tunableEnvironmen
//                const double e_obj_nonlcon_tunableEnvironmen[6]
//                const double f_obj_nonlcon_tunableEnvironmen[6]
//                double g_obj_nonlcon_tunableEnvironmen
//                int obj_mCeq
//                const emxArray_real_T *x
//                double Cineq_workspace[12]
//                emxArray_real_T *Ceq_workspace
//                int eq0
// Return Type  : int
//
int computeConstraints_(coder_internal_ref *c_obj_nonlcon_tunableEnvironmen,
  const emxArray_real_T *d_obj_nonlcon_tunableEnvironmen, const double
  e_obj_nonlcon_tunableEnvironmen[6], const double
  f_obj_nonlcon_tunableEnvironmen[6], double g_obj_nonlcon_tunableEnvironmen,
  int obj_mCeq, const emxArray_real_T *x, double Cineq_workspace[12],
  emxArray_real_T *Ceq_workspace, int eq0)
{
  int status;
  emxArray_real_T *varargout_2;
  int eqEnd_tmp;
  int eqEnd;
  double varargout_1[12];
  int i;
  int idx_current;
  bool allFinite;
  double allFinite_tmp;
  emxInit_real_T(&varargout_2, 1);
  eqEnd_tmp = eq0 + obj_mCeq;
  eqEnd = eqEnd_tmp - 2;
  b___anon_fcn(c_obj_nonlcon_tunableEnvironmen, d_obj_nonlcon_tunableEnvironmen,
               e_obj_nonlcon_tunableEnvironmen, f_obj_nonlcon_tunableEnvironmen,
               g_obj_nonlcon_tunableEnvironmen, x, varargout_1, varargout_2);
  std::memcpy(&Cineq_workspace[0], &varargout_1[0], 12U * sizeof(double));
  if (eq0 > eqEnd + 1) {
    i = -1;
    eqEnd = -1;
  } else {
    i = eq0 - 2;
  }

  eqEnd -= i;
  for (idx_current = 0; idx_current < eqEnd; idx_current++) {
    Ceq_workspace->data[(i + idx_current) + 1] = varargout_2->data[idx_current];
  }

  emxFree_real_T(&varargout_2);
  status = 1;
  allFinite = true;
  idx_current = 0;
  while (allFinite && (idx_current + 1 <= 12)) {
    allFinite = ((!rtIsInf(Cineq_workspace[idx_current])) && (!rtIsNaN
      (Cineq_workspace[idx_current])));
    idx_current++;
  }

  if (!allFinite) {
    idx_current--;
    if (rtIsNaN(Cineq_workspace[idx_current])) {
      status = -3;
    } else if (Cineq_workspace[idx_current] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  } else {
    allFinite = true;
    idx_current = eq0;
    eqEnd = eqEnd_tmp - 1;
    while (allFinite && (idx_current <= eqEnd)) {
      allFinite_tmp = Ceq_workspace->data[idx_current - 1];
      allFinite = ((!rtIsInf(allFinite_tmp)) && (!rtIsNaN(allFinite_tmp)));
      idx_current++;
    }

    if (!allFinite) {
      idx_current -= 2;
      if (rtIsNaN(Ceq_workspace->data[idx_current])) {
        status = -3;
      } else if (Ceq_workspace->data[idx_current] < 0.0) {
        status = -1;
      } else {
        status = -2;
      }
    }
  }

  return status;
}

//
// File trailer for computeConstraints_.cpp
//
// [EOF]
//
