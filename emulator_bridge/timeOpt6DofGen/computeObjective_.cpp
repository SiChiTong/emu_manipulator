//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeObjective_.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "computeObjective_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *x
//                double *fval
//                int *status
// Return Type  : void
//
void computeObjective_(const emxArray_real_T *x, double *fval, int *status)
{
  double d;
  int i;
  int vlen_tmp;
  int k;
  d = ((static_cast<double>(x->size[1]) - 24.0) + 1.0) / 7.0 * 6.0 + 1.0;
  if (d > static_cast<double>(x->size[1]) - 24.0) {
    i = -1;
    vlen_tmp = -1;
  } else {
    i = static_cast<int>(d) - 2;
    vlen_tmp = x->size[1] - 25;
  }

  vlen_tmp -= i;
  if (vlen_tmp == 0) {
    *fval = 0.0;
  } else {
    *fval = x->data[i + 1];
    for (k = 2; k <= vlen_tmp; k++) {
      *fval += x->data[i + k];
    }
  }

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
}

//
// File trailer for computeObjective_.cpp
//
// [EOF]
//
