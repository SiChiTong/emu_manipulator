//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: driver.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef DRIVER_H
#define DRIVER_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void driver(emxArray_real_T *Hessian, e_struct_T *TrialState, j_struct_T *
                   MeritFunction, f_struct_T *FcnEvaluator, d_struct_T
                   *FiniteDifferences, c_struct_T *memspace, h_struct_T
                   *WorkingSet, i_struct_T *QRManager, k_struct_T *CholManager,
                   g_struct_T *QPObjective, const emxArray_real_T
                   *fscales_cineq_constraint, const emxArray_real_T
                   *c_runTimeOptions_FiniteDifferen);

#endif

//
// File trailer for driver.h
//
// [EOF]
//
