//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeMeritFcn.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "computeMeritFcn.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double obj_penaltyParam
//                double fval
//                const emxArray_real_T *Cineq_workspace
//                int mIneq
//                const emxArray_real_T *Ceq_workspace
//                int mEq
//                bool evalWellDefined
// Return Type  : double
//
double computeMeritFcn(double obj_penaltyParam, double fval, const
  emxArray_real_T *Cineq_workspace, int mIneq, const emxArray_real_T
  *Ceq_workspace, int mEq, bool evalWellDefined)
{
  double val;
  double constrViolationEq;
  int k;
  double constrViolationIneq;
  if (evalWellDefined) {
    constrViolationEq = 0.0;
    if (mEq >= 1) {
      for (k = 0; k < mEq; k++) {
        constrViolationEq += std::abs(Ceq_workspace->data[k]);
      }
    }

    constrViolationIneq = 0.0;
    for (k = 0; k < mIneq; k++) {
      if (Cineq_workspace->data[k] > 0.0) {
        constrViolationIneq += Cineq_workspace->data[k];
      }
    }

    val = fval + obj_penaltyParam * (constrViolationEq + constrViolationIneq);
  } else {
    val = rtInf;
  }

  return val;
}

//
// File trailer for computeMeritFcn.cpp
//
// [EOF]
//
