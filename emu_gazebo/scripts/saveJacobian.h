//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: saveJacobian.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef SAVEJACOBIAN_H
#define SAVEJACOBIAN_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void saveJacobian(e_struct_T *obj, int nVar, const emxArray_real_T
  *JacCineqTrans, int mEq, const emxArray_real_T *JacCeqTrans, int eqCol0, int
  ldJ);

#endif

//
// File trailer for saveJacobian.h
//
// [EOF]
//
