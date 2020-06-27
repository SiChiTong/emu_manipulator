//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: linesearch.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef LINESEARCH_H
#define LINESEARCH_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void linesearch(bool *evalWellDefined, const double beq[12], int
  WorkingSet_nVar, int WorkingSet_ldA, const emxArray_real_T *WorkingSet_Aeq,
  e_struct_T *TrialState, double MeritFunction_penaltyParam, double
  MeritFunction_phi, double MeritFunction_phiPrimePlus, double
  MeritFunction_phiFullStep, coder_internal_ref *c_FcnEvaluator_nonlcon_tunableE,
  const emxArray_real_T *d_FcnEvaluator_nonlcon_tunableE, const double
  e_FcnEvaluator_nonlcon_tunableE[6], const double
  f_FcnEvaluator_nonlcon_tunableE[6], double g_FcnEvaluator_nonlcon_tunableE,
  int FcnEvaluator_mCeq, bool socTaken, double *alpha, int *exitflag);

#endif

//
// File trailer for linesearch.h
//
// [EOF]
//
