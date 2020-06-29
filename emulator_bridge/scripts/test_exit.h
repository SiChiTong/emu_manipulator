//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: test_exit.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef TEST_EXIT_H
#define TEST_EXIT_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void b_test_exit(struct_T *Flags, c_struct_T *memspace, j_struct_T
  *MeritFunction, const emxArray_real_T *fscales_cineq_constraint, h_struct_T
  *WorkingSet, e_struct_T *TrialState, i_struct_T *QRManager);
extern void test_exit(j_struct_T *MeritFunction, const emxArray_real_T
                      *fscales_cineq_constraint, const h_struct_T *WorkingSet,
                      e_struct_T *TrialState, bool *Flags_gradOK, bool
                      *Flags_fevalOK, bool *Flags_done, bool *Flags_stepAccepted,
                      bool *Flags_failedLineSearch, int *Flags_stepType);

#endif

//
// File trailer for test_exit.h
//
// [EOF]
//
