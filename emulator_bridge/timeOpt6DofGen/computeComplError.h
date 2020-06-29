//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeComplError.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef COMPUTECOMPLERROR_H
#define COMPUTECOMPLERROR_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern double computeComplError(const emxArray_real_T *fscales_cineq_constraint,
  int mIneq, const emxArray_real_T *cIneq, int mLB, const emxArray_real_T
  *lambda, int iL0);

#endif

//
// File trailer for computeComplError.h
//
// [EOF]
//
