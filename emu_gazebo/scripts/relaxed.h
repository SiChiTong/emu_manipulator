//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: relaxed.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef RELAXED_H
#define RELAXED_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void relaxed(const emxArray_real_T *Hessian, const emxArray_real_T *grad,
                    e_struct_T *TrialState, j_struct_T *MeritFunction,
                    c_struct_T *memspace, h_struct_T *WorkingSet, i_struct_T
                    *QRManager, k_struct_T *CholManager, g_struct_T *QPObjective,
                    b_struct_T *qpoptions);

#endif

//
// File trailer for relaxed.h
//
// [EOF]
//
