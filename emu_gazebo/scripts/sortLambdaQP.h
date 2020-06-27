//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortLambdaQP.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef SORTLAMBDAQP_H
#define SORTLAMBDAQP_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void sortLambdaQP(emxArray_real_T *lambda, int WorkingSet_nActiveConstr,
  const int WorkingSet_sizes[5], const int WorkingSet_isActiveIdx[6], const
  emxArray_int32_T *WorkingSet_Wid, const emxArray_int32_T *WorkingSet_Wlocalidx,
  emxArray_real_T *workspace);

#endif

//
// File trailer for sortLambdaQP.h
//
// [EOF]
//
