//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ixamax.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "ixamax.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include <cmath>

// Function Definitions

//
// Arguments    : int n
//                const emxArray_real_T *x
// Return Type  : int
//
int ixamax(int n, const emxArray_real_T *x)
{
  int idxmax;
  int ix;
  double smax;
  int k;
  double s;
  if (n < 1) {
    idxmax = 0;
  } else {
    idxmax = 1;
    if (n > 1) {
      ix = 0;
      smax = std::abs(x->data[0]);
      for (k = 2; k <= n; k++) {
        ix++;
        s = std::abs(x->data[ix]);
        if (s > smax) {
          idxmax = k;
          smax = s;
        }
      }
    }
  }

  return idxmax;
}

//
// File trailer for ixamax.cpp
//
// [EOF]
//
