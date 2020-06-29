//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ratiotest.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "ratiotest.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "xgemv.h"
#include "xnrm2.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const emxArray_real_T *solution_xstar
//                const emxArray_real_T *solution_searchDir
//                emxArray_real_T *workspace
//                int workingset_nVar
//                int workingset_ldA
//                const emxArray_real_T *workingset_Aineq
//                const emxArray_real_T *workingset_bineq
//                const emxArray_real_T *workingset_lb
//                const emxArray_int32_T *workingset_indexLB
//                const int workingset_sizes[5]
//                const int workingset_isActiveIdx[6]
//                const emxArray_boolean_T *workingset_isActiveConstr
//                const int workingset_nWConstr[5]
//                bool isPhaseOne
//                double *alpha
//                bool *newBlocking
//                int *constrType
//                int *constrIdx
// Return Type  : void
//
void ratiotest(const emxArray_real_T *solution_xstar, const emxArray_real_T
               *solution_searchDir, emxArray_real_T *workspace, int
               workingset_nVar, int workingset_ldA, const emxArray_real_T
               *workingset_Aineq, const emxArray_real_T *workingset_bineq, const
               emxArray_real_T *workingset_lb, const emxArray_int32_T
               *workingset_indexLB, const int workingset_sizes[5], const int
               workingset_isActiveIdx[6], const emxArray_boolean_T
               *workingset_isActiveConstr, const int workingset_nWConstr[5],
               bool isPhaseOne, double *alpha, bool *newBlocking, int
               *constrType, int *constrIdx)
{
  int totalIneq;
  double denomTol;
  int k;
  double phaseOneCorrectionX;
  double phaseOneCorrectionP;
  int ldw;
  int i;
  int iyend;
  double pk_corrected;
  int iy;
  double ratio;
  double c;
  int i1;
  int ia;
  totalIneq = workingset_sizes[2] - 1;
  *alpha = 1.0E+30;
  *newBlocking = false;
  *constrType = 0;
  *constrIdx = 0;
  denomTol = 2.2204460492503131E-13 * b_xnrm2(workingset_nVar,
    solution_searchDir);
  if (workingset_nWConstr[2] < workingset_sizes[2]) {
    for (k = 0; k <= totalIneq; k++) {
      workspace->data[k] = workingset_bineq->data[k];
    }

    b_xgemv(workingset_nVar, workingset_sizes[2], workingset_Aineq,
            workingset_ldA, solution_xstar, workspace);
    ldw = workspace->size[0];
    k = workspace->size[0] + 1;
    if (workingset_nVar != 0) {
      iyend = workspace->size[0] + workingset_sizes[2];
      for (iy = k; iy <= iyend; iy++) {
        workspace->data[iy - 1] = 0.0;
      }

      iy = ldw;
      i = workingset_ldA * (workingset_sizes[2] - 1) + 1;
      for (k = 1; workingset_ldA < 0 ? k >= i : k <= i; k += workingset_ldA) {
        iyend = 0;
        c = 0.0;
        i1 = (k + workingset_nVar) - 1;
        for (ia = k; ia <= i1; ia++) {
          c += workingset_Aineq->data[ia - 1] * solution_searchDir->data[iyend];
          iyend++;
        }

        workspace->data[iy] += c;
        iy++;
      }
    }

    for (k = 0; k <= totalIneq; k++) {
      i = ldw + k;
      if ((workspace->data[i] > denomTol) && (!workingset_isActiveConstr->data
           [(workingset_isActiveIdx[2] + k) - 1])) {
        c = std::abs(workspace->data[k]);
        if ((!(c < 0.001 - workspace->data[k])) && (!rtIsNaN(0.001 -
              workspace->data[k]))) {
          c = 0.001 - workspace->data[k];
        }

        c /= workspace->data[i];
        if (c < *alpha) {
          *alpha = c;
          *constrType = 3;
          *constrIdx = k + 1;
          *newBlocking = true;
        }
      }
    }
  }

  if (workingset_nWConstr[3] < workingset_sizes[3]) {
    phaseOneCorrectionX = static_cast<double>(isPhaseOne) * solution_xstar->
      data[workingset_nVar - 1];
    phaseOneCorrectionP = static_cast<double>(isPhaseOne) *
      solution_searchDir->data[workingset_nVar - 1];
    i = workingset_sizes[3];
    for (k = 0; k <= i - 2; k++) {
      pk_corrected = -solution_searchDir->data[workingset_indexLB->data[k] - 1]
        - phaseOneCorrectionP;
      if ((pk_corrected > denomTol) && (!workingset_isActiveConstr->data
           [(workingset_isActiveIdx[3] + k) - 1])) {
        ratio = (-solution_xstar->data[workingset_indexLB->data[k] - 1] -
                 workingset_lb->data[workingset_indexLB->data[k] - 1]) -
          phaseOneCorrectionX;
        c = std::abs(ratio);
        if ((!(c < 0.001 - ratio)) && (!rtIsNaN(0.001 - ratio))) {
          c = 0.001 - ratio;
        }

        c /= pk_corrected;
        if (c < *alpha) {
          *alpha = c;
          *constrType = 4;
          *constrIdx = k + 1;
          *newBlocking = true;
        }
      }
    }

    i = workingset_indexLB->data[workingset_sizes[3] - 1] - 1;
    if ((-solution_searchDir->data[i] > denomTol) &&
        (!workingset_isActiveConstr->data[(workingset_isActiveIdx[3] +
          workingset_sizes[3]) - 2])) {
      ratio = -solution_xstar->data[i] - workingset_lb->data[i];
      c = std::abs(ratio);
      if ((!(c < 0.001 - ratio)) && (!rtIsNaN(0.001 - ratio))) {
        c = 0.001 - ratio;
      }

      c /= -solution_searchDir->data[i];
      if (c < *alpha) {
        *alpha = c;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
      }
    }
  }

  if (!isPhaseOne) {
    if ((*newBlocking) && (*alpha > 1.0)) {
      *newBlocking = false;
    }

    if (!(*alpha < 1.0)) {
      *alpha = 1.0;
    }
  }
}

//
// File trailer for ratiotest.cpp
//
// [EOF]
//
