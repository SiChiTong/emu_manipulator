//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeOpt6DofGen.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef TIMEOPT6DOFGEN_H
#define TIMEOPT6DOFGEN_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void __anon_fcn(coder_internal_ref *qr, const emxArray_real_T *b_qr,
  const double v_max[6], const double a_max[6], double precision, const
  emxArray_real_T *w, emxArray_real_T *varargout_1, emxArray_real_T *varargout_2);
extern void timeOpt6DofGen(const emxArray_real_T *qr, const double v_max[6],
  const double a_max[6], double precision, emxArray_real_T *w, double *cost_out,
  double *flag);

#endif

//
// File trailer for timeOpt6DofGen.h
//
// [EOF]
//
