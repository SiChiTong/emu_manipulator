//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factoryConstruct2.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef FACTORYCONSTRUCT2_H
#define FACTORYCONSTRUCT2_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void c_factoryConstruct(int mEq, const emxArray_real_T *Aeq, int mLB,
  const emxArray_int32_T *indexLB, int mUB, const emxArray_int32_T *indexUB, int
  mFixed, const emxArray_int32_T *indexFixed, int nVar, int nVarMax, int
  mConstrMax, h_struct_T *obj);

#endif

//
// File trailer for factoryConstruct2.h
//
// [EOF]
//
