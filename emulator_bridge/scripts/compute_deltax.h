//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compute_deltax.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef COMPUTE_DELTAX_H
#define COMPUTE_DELTAX_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void compute_deltax(const emxArray_real_T *H, e_struct_T *solution,
  c_struct_T *memspace, const i_struct_T *qrmanager, k_struct_T *cholmanager,
  const g_struct_T *objective);

#endif

//
// File trailer for compute_deltax.h
//
// [EOF]
//
