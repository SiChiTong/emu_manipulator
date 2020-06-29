//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkVectorNonFinite.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "checkVectorNonFinite.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : int N
//                const emxArray_real_T *vec
//                int iv0
// Return Type  : int
//
int checkVectorNonFinite(int N, const emxArray_real_T *vec, int iv0)
{
  int status;
  bool allFinite;
  int idx_current;
  int idx_end;
  double allFinite_tmp;
  status = 1;
  allFinite = true;
  idx_current = iv0;
  idx_end = (iv0 + N) - 1;
  while (allFinite && (idx_current <= idx_end)) {
    allFinite_tmp = vec->data[idx_current - 1];
    allFinite = ((!rtIsInf(allFinite_tmp)) && (!rtIsNaN(allFinite_tmp)));
    idx_current++;
  }

  if (!allFinite) {
    idx_current -= 2;
    if (rtIsNaN(vec->data[idx_current])) {
      status = -3;
    } else if (vec->data[idx_current] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  }

  return status;
}

//
// File trailer for checkVectorNonFinite.cpp
//
// [EOF]
//
