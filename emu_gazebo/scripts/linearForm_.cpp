//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: linearForm_.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "linearForm_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : bool obj_hasLinear
//                int obj_nvar
//                emxArray_real_T *workspace
//                const emxArray_real_T *H
//                const emxArray_real_T *f
//                const emxArray_real_T *x
// Return Type  : void
//
void linearForm_(bool obj_hasLinear, int obj_nvar, emxArray_real_T *workspace,
                 const emxArray_real_T *H, const emxArray_real_T *f, const
                 emxArray_real_T *x)
{
  int beta1;
  int ix;
  int i;
  int iac;
  double c;
  int i1;
  int ia;
  beta1 = 0;
  if (obj_hasLinear) {
    for (beta1 = 0; beta1 < obj_nvar; beta1++) {
      workspace->data[beta1] = f->data[beta1];
    }

    beta1 = 1;
  }

  if (obj_nvar != 0) {
    if (beta1 != 1) {
      for (beta1 = 0; beta1 < obj_nvar; beta1++) {
        workspace->data[beta1] = 0.0;
      }
    }

    ix = 0;
    i = obj_nvar * (obj_nvar - 1) + 1;
    for (iac = 1; obj_nvar < 0 ? iac >= i : iac <= i; iac += obj_nvar) {
      c = 0.5 * x->data[ix];
      beta1 = 0;
      i1 = (iac + obj_nvar) - 1;
      for (ia = iac; ia <= i1; ia++) {
        workspace->data[beta1] += H->data[ia - 1] * c;
        beta1++;
      }

      ix++;
    }
  }
}

//
// File trailer for linearForm_.cpp
//
// [EOF]
//
