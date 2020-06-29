//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeDualFeasError.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "computeDualFeasError.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include <cmath>

// Function Definitions

//
// Arguments    : int nVar
//                const emxArray_real_T *gradLag
//                bool *gradOK
//                double *val
// Return Type  : void
//
void computeDualFeasError(int nVar, const emxArray_real_T *gradLag, bool *gradOK,
  double *val)
{
  int idx;
  bool exitg1;
  double u1;
  *gradOK = true;
  *val = 0.0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx <= nVar - 1)) {
    *gradOK = ((!rtIsInf(gradLag->data[idx])) && (!rtIsNaN(gradLag->data[idx])));
    if (!*gradOK) {
      exitg1 = true;
    } else {
      u1 = std::abs(gradLag->data[idx]);
      if ((!(*val > u1)) && (!rtIsNaN(u1))) {
        *val = u1;
      }

      idx++;
    }
  }
}

//
// File trailer for computeDualFeasError.cpp
//
// [EOF]
//
