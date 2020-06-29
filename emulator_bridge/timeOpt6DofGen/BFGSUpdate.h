//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BFGSUpdate.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef BFGSUPDATE_H
#define BFGSUPDATE_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern bool BFGSUpdate(int nvar, emxArray_real_T *Bk, const emxArray_real_T *sk,
  emxArray_real_T *yk, emxArray_real_T *workspace);

#endif

//
// File trailer for BFGSUpdate.h
//
// [EOF]
//
