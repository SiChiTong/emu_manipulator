//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: iterate.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef ITERATE_H
#define ITERATE_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void iterate(const emxArray_real_T *H, const emxArray_real_T *f,
                    e_struct_T *solution, c_struct_T *memspace, h_struct_T
                    *workingset, i_struct_T *qrmanager, k_struct_T *cholmanager,
                    g_struct_T *objective, int options_MaxIterations, double
                    options_StepTolerance, double options_ObjectiveLimit);

#endif

//
// File trailer for iterate.h
//
// [EOF]
//
