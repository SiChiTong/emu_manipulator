//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: finDiffEvalAndChkErr.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
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
//                int obj_mIneq
//                int obj_mEq
//                double *fplus
//                emxArray_real_T *cIneqPlus
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
  int obj_mIneq, int obj_mEq, double *fplus, emxArray_real_T *cIneqPlus,
  emxArray_real_T *cEqPlus, int dim, double delta, emxArray_real_T *xk)
{
  bool evalOK;
  double temp_tmp;
  double d;
  int i;
  int idx;
  int k;
  temp_tmp = xk->data[dim - 1];
  xk->data[dim - 1] = temp_tmp + delta;
  d = ((static_cast<double>(xk->size[1]) - 24.0) + 1.0) / 7.0 * 6.0 + 1.0;
  if (d > static_cast<double>(xk->size[1]) - 24.0) {
    i = -1;
    idx = -1;
  } else {
    i = static_cast<int>(d) - 2;
    idx = xk->size[1] - 25;
  }

  idx -= i;
  if (idx == 0) {
    *fplus = 0.0;
  } else {
    *fplus = xk->data[i + 1];
    for (k = 2; k <= idx; k++) {
      *fplus += xk->data[i + k];
    }
  }

  evalOK = ((!rtIsInf(*fplus)) && (!rtIsNaN(*fplus)));
  if (evalOK) {
    __anon_fcn(c_obj_nonlin_tunableEnvironment, d_obj_nonlin_tunableEnvironment,
               e_obj_nonlin_tunableEnvironment, f_obj_nonlin_tunableEnvironment,
               g_obj_nonlin_tunableEnvironment, xk, cIneqPlus, cEqPlus);
    idx = 0;
    while (evalOK && (idx + 1 <= obj_mIneq)) {
      evalOK = ((!rtIsInf(cIneqPlus->data[idx])) && (!rtIsNaN(cIneqPlus->
                  data[idx])));
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
