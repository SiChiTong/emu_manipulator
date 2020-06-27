//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: solve.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "solve.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : const k_struct_T *obj
//                emxArray_real_T *rhs
// Return Type  : void
//
void solve(const k_struct_T *obj, emxArray_real_T *rhs)
{
  int n;
  int j;
  int jA;
  double temp;
  int i;
  int ix;
  n = obj->ndims;
  if (obj->ndims != 0) {
    for (j = 0; j < n; j++) {
      jA = j * obj->ldu;
      temp = rhs->data[j];
      for (i = 0; i < j; i++) {
        temp -= obj->UU->data[jA + i] * rhs->data[i];
      }

      rhs->data[j] = temp / obj->UU->data[jA + j];
    }
  }

  n = obj->ndims;
  if (obj->ndims != 0) {
    for (j = n; j >= 1; j--) {
      jA = (j + (j - 1) * obj->ldu) - 1;
      rhs->data[j - 1] /= obj->UU->data[jA];
      for (i = 0; i <= j - 2; i++) {
        ix = (j - i) - 2;
        rhs->data[ix] -= rhs->data[j - 1] * obj->UU->data[(jA - i) - 1];
      }
    }
  }
}

//
// File trailer for solve.cpp
//
// [EOF]
//
