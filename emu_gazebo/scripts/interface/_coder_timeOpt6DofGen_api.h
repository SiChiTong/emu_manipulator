/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_timeOpt6DofGen_api.h
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 25-Jun-2020 20:47:06
 */

#ifndef _CODER_TIMEOPT6DOFGEN_API_H
#define _CODER_TIMEOPT6DOFGEN_API_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void timeOpt6DofGen(emxArray_real_T *qr, real_T v_max[6], real_T a_max[6],
  real_T precision, emxArray_real_T *w, real_T *cost_out, real_T *flag);
extern void timeOpt6DofGen_api(const mxArray * const prhs[4], int32_T nlhs,
  const mxArray *plhs[3]);
extern void timeOpt6DofGen_atexit(void);
extern void timeOpt6DofGen_initialize(void);
extern void timeOpt6DofGen_terminate(void);
extern void timeOpt6DofGen_xil_shutdown(void);
extern void timeOpt6DofGen_xil_terminate(void);

#endif

/*
 * File trailer for _coder_timeOpt6DofGen_api.h
 *
 * [EOF]
 */
