//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ratiotest.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef RATIOTEST_H
#define RATIOTEST_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void ratiotest(const emxArray_real_T *solution_xstar, const
                      emxArray_real_T *solution_searchDir, emxArray_real_T
                      *workspace, int workingset_nVar, int workingset_ldA, const
                      emxArray_real_T *workingset_Aineq, const double
                      workingset_bineq[12], const emxArray_real_T *workingset_lb,
                      const emxArray_real_T *workingset_ub, const
                      emxArray_int32_T *workingset_indexLB, const
                      emxArray_int32_T *workingset_indexUB, const int
                      workingset_sizes[5], const int workingset_isActiveIdx[6],
                      const emxArray_boolean_T *workingset_isActiveConstr, const
                      int workingset_nWConstr[5], bool isPhaseOne, double *alpha,
                      bool *newBlocking, int *constrType, int *constrIdx);

#endif

//
// File trailer for ratiotest.h
//
// [EOF]
//
