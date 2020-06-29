//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: removeDependentLinearEq.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef REMOVEDEPENDENTLINEAREQ_H
#define REMOVEDEPENDENTLINEAREQ_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern int removeDependentLinearEq(const emxArray_real_T *Aeq, double beq[12],
  int idxArray[12], c_struct_T *memspace, e_struct_T *TrialState, h_struct_T
  *WorkingSet, i_struct_T *QRManager, g_struct_T *QPObjective);

#endif

//
// File trailer for removeDependentLinearEq.h
//
// [EOF]
//
