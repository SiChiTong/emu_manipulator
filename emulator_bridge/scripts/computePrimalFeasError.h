//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computePrimalFeasError.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef COMPUTEPRIMALFEASERROR_H
#define COMPUTEPRIMALFEASERROR_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern double computePrimalFeasError(int mLinIneq, int mNonlinIneq, const
  emxArray_real_T *cIneq, int mLinEq, int mNonlinEq, const emxArray_real_T *cEq,
  int mLB);

#endif

//
// File trailer for computePrimalFeasError.h
//
// [EOF]
//
