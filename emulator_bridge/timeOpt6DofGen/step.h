//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: step.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef STEP_H
#define STEP_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern bool step(int *STEP_TYPE, emxArray_real_T *Hessian, e_struct_T
                 *TrialState, j_struct_T *MeritFunction, c_struct_T *memspace,
                 h_struct_T *WorkingSet, i_struct_T *QRManager, k_struct_T
                 *CholManager, g_struct_T *QPObjective, b_struct_T qpoptions);

#endif

//
// File trailer for step.h
//
// [EOF]
//
