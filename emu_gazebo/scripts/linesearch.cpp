//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: linesearch.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "linesearch.h"
#include "computeConstraints_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xgemv.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : bool *evalWellDefined
//                const double beq[12]
//                int WorkingSet_nVar
//                int WorkingSet_ldA
//                const emxArray_real_T *WorkingSet_Aeq
//                e_struct_T *TrialState
//                double MeritFunction_penaltyParam
//                double MeritFunction_phi
//                double MeritFunction_phiPrimePlus
//                double MeritFunction_phiFullStep
//                coder_internal_ref *c_FcnEvaluator_nonlcon_tunableE
//                const emxArray_real_T *d_FcnEvaluator_nonlcon_tunableE
//                const double e_FcnEvaluator_nonlcon_tunableE[6]
//                const double f_FcnEvaluator_nonlcon_tunableE[6]
//                double g_FcnEvaluator_nonlcon_tunableE
//                int FcnEvaluator_mCeq
//                bool socTaken
//                double *alpha
//                int *exitflag
// Return Type  : void
//
void linesearch(bool *evalWellDefined, const double beq[12], int WorkingSet_nVar,
                int WorkingSet_ldA, const emxArray_real_T *WorkingSet_Aeq,
                e_struct_T *TrialState, double MeritFunction_penaltyParam,
                double MeritFunction_phi, double MeritFunction_phiPrimePlus,
                double MeritFunction_phiFullStep, coder_internal_ref
                *c_FcnEvaluator_nonlcon_tunableE, const emxArray_real_T
                *d_FcnEvaluator_nonlcon_tunableE, const double
                e_FcnEvaluator_nonlcon_tunableE[6], const double
                f_FcnEvaluator_nonlcon_tunableE[6], double
                g_FcnEvaluator_nonlcon_tunableE, int FcnEvaluator_mCeq, bool
                socTaken, double *alpha, int *exitflag)
{
  int mLinEq;
  double phi_alpha;
  int k;
  emxArray_real_T *Ceq_workspace;
  int exitg1;
  int ixlast;
  bool tooSmallX;
  bool exitg2;
  double Cineq_workspace[12];
  int status;
  double constrViolationEq;
  double constrViolationIneq;
  mLinEq = TrialState->mEq - TrialState->mNonlinEq;
  *alpha = 1.0;
  *exitflag = 1;
  phi_alpha = MeritFunction_phiFullStep;
  for (k = 0; k < WorkingSet_nVar; k++) {
    TrialState->searchDir->data[k] = TrialState->delta_x->data[k];
  }

  emxInit_real_T(&Ceq_workspace, 1);
  do {
    exitg1 = 0;
    if (TrialState->FunctionEvaluations < 10000) {
      if ((*evalWellDefined) && (phi_alpha <= MeritFunction_phi + *alpha *
           0.0001 * MeritFunction_phiPrimePlus)) {
        exitg1 = 1;
      } else {
        *alpha *= 0.7;
        for (ixlast = 0; ixlast < WorkingSet_nVar; ixlast++) {
          TrialState->delta_x->data[ixlast] = *alpha * TrialState->
            searchDir->data[ixlast];
        }

        if (socTaken) {
          phi_alpha = *alpha * *alpha;
          if ((WorkingSet_nVar >= 1) && (!(phi_alpha == 0.0))) {
            ixlast = WorkingSet_nVar - 1;
            for (k = 0; k <= ixlast; k++) {
              TrialState->delta_x->data[k] += phi_alpha *
                TrialState->socDirection->data[k];
            }
          }
        }

        tooSmallX = true;
        ixlast = 0;
        exitg2 = false;
        while ((!exitg2) && (ixlast <= WorkingSet_nVar - 1)) {
          phi_alpha = std::abs(TrialState->xstarsqp->data[ixlast]);
          if ((1.0 > phi_alpha) || rtIsNaN(phi_alpha)) {
            phi_alpha = 1.0;
          }

          if (1.0E-6 * phi_alpha <= std::abs(TrialState->delta_x->data[ixlast]))
          {
            tooSmallX = false;
            exitg2 = true;
          } else {
            ixlast++;
          }
        }

        if (tooSmallX) {
          *exitflag = -2;
          exitg1 = 1;
        } else {
          for (ixlast = 0; ixlast < WorkingSet_nVar; ixlast++) {
            TrialState->xstarsqp->data[ixlast] = TrialState->xstarsqp_old->
              data[ixlast] + TrialState->delta_x->data[ixlast];
          }

          ixlast = Ceq_workspace->size[0];
          Ceq_workspace->size[0] = TrialState->cEq->size[0];
          emxEnsureCapacity_real_T(Ceq_workspace, ixlast);
          k = TrialState->cEq->size[0];
          for (ixlast = 0; ixlast < k; ixlast++) {
            Ceq_workspace->data[ixlast] = TrialState->cEq->data[ixlast];
          }

          std::memcpy(&Cineq_workspace[0], &TrialState->cIneq[0], 12U * sizeof
                      (double));
          phi_alpha = __anon_fcn(TrialState->xstarsqp);
          status = 1;
          if (rtIsInf(phi_alpha) || rtIsNaN(phi_alpha)) {
            if (rtIsNaN(phi_alpha)) {
              status = -6;
            } else if (phi_alpha < 0.0) {
              status = -4;
            } else {
              status = -5;
            }
          }

          if (status == 1) {
            status = computeConstraints_(c_FcnEvaluator_nonlcon_tunableE,
              d_FcnEvaluator_nonlcon_tunableE, e_FcnEvaluator_nonlcon_tunableE,
              f_FcnEvaluator_nonlcon_tunableE, g_FcnEvaluator_nonlcon_tunableE,
              FcnEvaluator_mCeq, TrialState->xstarsqp, Cineq_workspace,
              Ceq_workspace, TrialState->iNonEq0);
          }

          TrialState->sqpFval = phi_alpha;
          std::memcpy(&TrialState->cIneq[0], &Cineq_workspace[0], 12U * sizeof
                      (double));
          if (mLinEq > 0) {
            for (k = 0; k < mLinEq; k++) {
              Ceq_workspace->data[k] = beq[k];
            }

            xgemv(WorkingSet_nVar, mLinEq, WorkingSet_Aeq, WorkingSet_ldA,
                  TrialState->xstarsqp, Ceq_workspace);
          }

          ixlast = TrialState->cEq->size[0];
          TrialState->cEq->size[0] = Ceq_workspace->size[0];
          emxEnsureCapacity_real_T(TrialState->cEq, ixlast);
          k = Ceq_workspace->size[0];
          for (ixlast = 0; ixlast < k; ixlast++) {
            TrialState->cEq->data[ixlast] = Ceq_workspace->data[ixlast];
          }

          TrialState->FunctionEvaluations++;
          *evalWellDefined = (status == 1);
          ixlast = TrialState->mEq;
          if (*evalWellDefined) {
            constrViolationEq = 0.0;
            if (TrialState->mEq >= 1) {
              for (k = 0; k < ixlast; k++) {
                constrViolationEq += std::abs(Ceq_workspace->data[k]);
              }
            }

            constrViolationIneq = 0.0;
            for (ixlast = 0; ixlast < 12; ixlast++) {
              if (Cineq_workspace[ixlast] > 0.0) {
                constrViolationIneq += Cineq_workspace[ixlast];
              }
            }

            phi_alpha += MeritFunction_penaltyParam * (constrViolationEq +
              constrViolationIneq);
          } else {
            phi_alpha = rtInf;
          }
        }
      }
    } else {
      *exitflag = 0;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&Ceq_workspace);
}

//
// File trailer for linesearch.cpp
//
// [EOF]
//
