//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: finDiffEvalAndChkErr.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "finDiffEvalAndChkErr.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : coder_internal_ref *c_obj_nonlin_tunableEnvironment
//                const emxArray_real_T *d_obj_nonlin_tunableEnvironment
//                const double e_obj_nonlin_tunableEnvironment[6]
//                const double f_obj_nonlin_tunableEnvironment[6]
//                double g_obj_nonlin_tunableEnvironment
//                int obj_mEq
//                double *fplus
//                double cIneqPlus[12]
//                emxArray_real_T *cEqPlus
//                int dim
//                double delta
//                emxArray_real_T *xk
// Return Type  : bool
//
bool finDiffEvalAndChkErr(coder_internal_ref *c_obj_nonlin_tunableEnvironment,
  const emxArray_real_T *d_obj_nonlin_tunableEnvironment, const double
  e_obj_nonlin_tunableEnvironment[6], const double
  f_obj_nonlin_tunableEnvironment[6], double g_obj_nonlin_tunableEnvironment,
  int obj_mEq, double *fplus, double cIneqPlus[12], emxArray_real_T *cEqPlus,
  int dim, double delta, emxArray_real_T *xk)
{
  bool evalOK;
  double temp_tmp;
  int idx;
  temp_tmp = xk->data[dim - 1];
  xk->data[dim - 1] = temp_tmp + delta;
  *fplus = __anon_fcn(xk);
  evalOK = ((!rtIsInf(*fplus)) && (!rtIsNaN(*fplus)));
  if (evalOK) {
    b___anon_fcn(c_obj_nonlin_tunableEnvironment,
                 d_obj_nonlin_tunableEnvironment,
                 e_obj_nonlin_tunableEnvironment,
                 f_obj_nonlin_tunableEnvironment,
                 g_obj_nonlin_tunableEnvironment, xk, cIneqPlus, cEqPlus);
    idx = 0;
    while (evalOK && (idx + 1 <= 12)) {
      evalOK = ((!rtIsInf(cIneqPlus[idx])) && (!rtIsNaN(cIneqPlus[idx])));
      idx++;
    }

    if (evalOK) {
      idx = 0;
      while (evalOK && (idx + 1 <= obj_mEq)) {
        evalOK = ((!rtIsInf(cEqPlus->data[idx])) && (!rtIsNaN(cEqPlus->data[idx])));
        idx++;
      }

      xk->data[dim - 1] = temp_tmp;
    }
  }

  return evalOK;
}

//
// File trailer for finDiffEvalAndChkErr.cpp
//
// [EOF]
//
