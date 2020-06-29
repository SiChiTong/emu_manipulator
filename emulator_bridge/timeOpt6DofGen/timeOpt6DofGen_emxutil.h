//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeOpt6DofGen_emxutil.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef TIMEOPT6DOFGEN_EMXUTIL_H
#define TIMEOPT6DOFGEN_EMXUTIL_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void c_emxFreeStruct_coder_internal_(coder_internal_ref *pStruct);
extern void c_emxInitStruct_coder_internal_(coder_internal_ref *pStruct);
extern void emxCopyStruct_struct_T(d_struct_T *dst, const d_struct_T *src);
extern void emxCopyStruct_struct_T1(e_struct_T *dst, const e_struct_T *src);
extern void emxCopyStruct_struct_T2(h_struct_T *dst, const h_struct_T *src);
extern void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int
  oldNumel);
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_int8_T(emxArray_int8_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFreeStruct_struct_T(e_struct_T *pStruct);
extern void emxFreeStruct_struct_T1(f_struct_T *pStruct);
extern void emxFreeStruct_struct_T2(d_struct_T *pStruct);
extern void emxFreeStruct_struct_T3(g_struct_T *pStruct);
extern void emxFreeStruct_struct_T4(c_struct_T *pStruct);
extern void emxFreeStruct_struct_T5(h_struct_T *pStruct);
extern void emxFreeStruct_struct_T6(i_struct_T *pStruct);
extern void emxFreeStruct_struct_T7(k_struct_T *pStruct);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_int8_T(emxArray_int8_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInitStruct_struct_T(e_struct_T *pStruct);
extern void emxInitStruct_struct_T1(f_struct_T *pStruct);
extern void emxInitStruct_struct_T2(d_struct_T *pStruct);
extern void emxInitStruct_struct_T3(g_struct_T *pStruct);
extern void emxInitStruct_struct_T4(c_struct_T *pStruct);
extern void emxInitStruct_struct_T5(h_struct_T *pStruct);
extern void emxInitStruct_struct_T6(i_struct_T *pStruct);
extern void emxInitStruct_struct_T7(k_struct_T *pStruct);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_int8_T(emxArray_int8_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for timeOpt6DofGen_emxutil.h
//
// [EOF]
//
