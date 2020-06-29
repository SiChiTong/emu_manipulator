//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: driver1.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef DRIVER1_H
#define DRIVER1_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void b_driver(const emxArray_real_T *H, const emxArray_real_T *f,
                     e_struct_T *solution, c_struct_T *memspace, h_struct_T
                     *workingset, i_struct_T *qrmanager, k_struct_T *cholmanager,
                     g_struct_T *objective, b_struct_T options);

#endif

//
// File trailer for driver1.h
//
// [EOF]
//
