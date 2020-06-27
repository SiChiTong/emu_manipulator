//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evalObjAndConstr.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "evalObjAndConstr.h"
#include "computeConstraints_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

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
//                double *fval
//                int *status
// Return Type  : void
//
void evalObjAndConstr(coder_internal_ref *c_obj_nonlcon_tunableEnvironmen, const
                      emxArray_real_T *d_obj_nonlcon_tunableEnvironmen, const
                      double e_obj_nonlcon_tunableEnvironmen[6], const double
                      f_obj_nonlcon_tunableEnvironmen[6], double
                      g_obj_nonlcon_tunableEnvironmen, int obj_mCeq, const
                      emxArray_real_T *x, double Cineq_workspace[12],
                      emxArray_real_T *Ceq_workspace, int eq0, double *fval, int
                      *status)
{
  *fval = __anon_fcn(x);
  *status = 1;
  if (rtIsInf(*fval) || rtIsNaN(*fval)) {
    if (rtIsNaN(*fval)) {
      *status = -6;
    } else if (*fval < 0.0) {
      *status = -4;
    } else {
      *status = -5;
    }
  }

  if (*status == 1) {
    *status = computeConstraints_(c_obj_nonlcon_tunableEnvironmen,
      d_obj_nonlcon_tunableEnvironmen, e_obj_nonlcon_tunableEnvironmen,
      f_obj_nonlcon_tunableEnvironmen, g_obj_nonlcon_tunableEnvironmen, obj_mCeq,
      x, Cineq_workspace, Ceq_workspace, eq0);
  }
}

//
// File trailer for evalObjAndConstr.cpp
//
// [EOF]
//
