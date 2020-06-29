//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fmincon.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "fmincon.h"
#include "computeConstraints_.h"
#include "computeFiniteDifferences.h"
#include "computeObjective_.h"
#include "driver.h"
#include "factoryConstruct.h"
#include "factoryConstruct1.h"
#include "factoryConstruct2.h"
#include "factoryConstruct3.h"
#include "removeDependentLinearEq.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : const emxArray_real_T *x0
//                const emxArray_real_T *Aeq
//                coder_internal_ref *nonlcon_tunableEnvironment_f1
//                const emxArray_real_T *nonlcon_tunableEnvironment_f2
//                const double nonlcon_tunableEnvironment_f3[6]
//                const double nonlcon_tunableEnvironment_f4[6]
//                double nonlcon_tunableEnvironment_f5
//                emxArray_real_T *x
//                double *fval
//                double *exitflag
// Return Type  : void
//
void fmincon(const emxArray_real_T *x0, const emxArray_real_T *Aeq,
             coder_internal_ref *nonlcon_tunableEnvironment_f1, const
             emxArray_real_T *nonlcon_tunableEnvironment_f2, const double
             nonlcon_tunableEnvironment_f3[6], const double
             nonlcon_tunableEnvironment_f4[6], double
             nonlcon_tunableEnvironment_f5, emxArray_real_T *x, double *fval,
             double *exitflag)
{
  emxArray_real_T *c_runTimeOptions_FiniteDifferen;
  d_struct_T FiniteDifferences;
  d_struct_T r;
  int nVar;
  int i;
  int idx;
  emxArray_real_T *Hessian;
  emxArray_real_T *varargout_2;
  emxArray_real_T *varargout_1;
  int mNonlinIneq;
  int nVarMax;
  int mConstrMax;
  int maxDims;
  int loop_ub;
  e_struct_T TrialState;
  int k;
  f_struct_T FcnEvaluator;
  g_struct_T QPObjective;
  c_struct_T memspace;
  emxArray_real_T *fscales_cineq_constraint;
  h_struct_T WorkingSet;
  double beqFiltered[12];
  i_struct_T obj;
  int nDepEq;
  int idxDepEq[12];
  int mEq;
  emxArray_real_T *b_TrialState;
  int ldAe;
  double c;
  j_struct_T MeritFunction;
  k_struct_T b_obj;
  emxInit_real_T(&c_runTimeOptions_FiniteDifferen, 1);
  emxInitStruct_struct_T2(&FiniteDifferences);
  emxInitStruct_struct_T2(&r);
  nVar = x0->size[1];
  i = c_runTimeOptions_FiniteDifferen->size[0];
  c_runTimeOptions_FiniteDifferen->size[0] = x0->size[1];
  emxEnsureCapacity_real_T(c_runTimeOptions_FiniteDifferen, i);
  for (idx = 0; idx < nVar; idx++) {
    c_runTimeOptions_FiniteDifferen->data[idx] = 1.4901161193847656E-8;
  }

  emxInit_real_T(&Hessian, 2);
  emxInit_real_T(&varargout_2, 1);
  emxInit_real_T(&varargout_1, 1);
  __anon_fcn(nonlcon_tunableEnvironment_f1, nonlcon_tunableEnvironment_f2,
             nonlcon_tunableEnvironment_f3, nonlcon_tunableEnvironment_f4,
             nonlcon_tunableEnvironment_f5, x0, varargout_1, varargout_2);
  mNonlinIneq = varargout_1->size[0] - 1;
  nVar = x0->size[1] - 1;
  nVarMax = (varargout_2->size[0] + 12) << 1;
  mConstrMax = (((varargout_1->size[0] + varargout_2->size[0]) + nVarMax) +
                varargout_1->size[0]) + 13;
  nVarMax = ((x0->size[1] + nVarMax) + varargout_1->size[0]) + 1;
  if (nVarMax > mConstrMax) {
    maxDims = nVarMax;
  } else {
    maxDims = mConstrMax;
  }

  i = Hessian->size[0] * Hessian->size[1];
  Hessian->size[0] = x0->size[1];
  Hessian->size[1] = x0->size[1];
  emxEnsureCapacity_real_T(Hessian, i);
  loop_ub = x0->size[1] * x0->size[1];
  for (i = 0; i < loop_ub; i++) {
    Hessian->data[i] = 0.0;
  }

  emxInitStruct_struct_T(&TrialState);
  factoryConstruct(nVarMax, mConstrMax, varargout_1->size[0], varargout_2->size
                   [0] + 12, x0->size, varargout_1->size[0], varargout_2->size[0],
                   &TrialState);
  for (k = 0; k <= nVar; k++) {
    Hessian->data[k + Hessian->size[0] * k] = 1.0;
    TrialState.xstarsqp->data[k] = x0->data[k];
  }

  emxInitStruct_struct_T1(&FcnEvaluator);
  FcnEvaluator.nVar = x0->size[1];
  FcnEvaluator.mCineq = varargout_1->size[0];
  FcnEvaluator.mCeq = varargout_2->size[0];
  FcnEvaluator.nonlcon.tunableEnvironment.f1 = nonlcon_tunableEnvironment_f1;
  i = FcnEvaluator.nonlcon.tunableEnvironment.f2->size[0] *
    FcnEvaluator.nonlcon.tunableEnvironment.f2->size[1];
  FcnEvaluator.nonlcon.tunableEnvironment.f2->size[0] = 6;
  FcnEvaluator.nonlcon.tunableEnvironment.f2->size[1] =
    nonlcon_tunableEnvironment_f2->size[1];
  emxEnsureCapacity_real_T(FcnEvaluator.nonlcon.tunableEnvironment.f2, i);
  loop_ub = nonlcon_tunableEnvironment_f2->size[0] *
    nonlcon_tunableEnvironment_f2->size[1];
  for (i = 0; i < loop_ub; i++) {
    FcnEvaluator.nonlcon.tunableEnvironment.f2->data[i] =
      nonlcon_tunableEnvironment_f2->data[i];
  }

  for (i = 0; i < 6; i++) {
    FcnEvaluator.nonlcon.tunableEnvironment.f3[i] =
      nonlcon_tunableEnvironment_f3[i];
    FcnEvaluator.nonlcon.tunableEnvironment.f4[i] =
      nonlcon_tunableEnvironment_f4[i];
  }

  emxInitStruct_struct_T3(&QPObjective);
  emxInitStruct_struct_T4(&memspace);
  emxInit_real_T(&fscales_cineq_constraint, 1);
  FcnEvaluator.nonlcon.tunableEnvironment.f5 = nonlcon_tunableEnvironment_f5;
  FcnEvaluator.NonFiniteSupport = true;
  FcnEvaluator.SpecifyObjectiveGradient = false;
  FcnEvaluator.SpecifyConstraintGradient = false;
  FcnEvaluator.ScaleProblem = false;
  b_factoryConstruct(nonlcon_tunableEnvironment_f1,
                     nonlcon_tunableEnvironment_f2,
                     nonlcon_tunableEnvironment_f3,
                     nonlcon_tunableEnvironment_f4,
                     nonlcon_tunableEnvironment_f5, x0->size[1],
                     varargout_1->size[0], varargout_2->size[0], &r);
  emxCopyStruct_struct_T(&FiniteDifferences, &r);
  c_factoryConstruct(nVarMax, &QPObjective);
  QPObjective.nvar = x0->size[1];
  QPObjective.hasLinear = true;
  QPObjective.objtype = 3;
  i = memspace.workspace_double->size[0] * memspace.workspace_double->size[1];
  memspace.workspace_double->size[0] = maxDims;
  memspace.workspace_double->size[1] = nVarMax;
  emxEnsureCapacity_real_T(memspace.workspace_double, i);
  i = memspace.workspace_int->size[0];
  memspace.workspace_int->size[0] = maxDims;
  emxEnsureCapacity_int32_T(memspace.workspace_int, i);
  i = memspace.workspace_sort->size[0];
  memspace.workspace_sort->size[0] = maxDims;
  emxEnsureCapacity_int32_T(memspace.workspace_sort, i);
  i = fscales_cineq_constraint->size[0];
  fscales_cineq_constraint->size[0] = varargout_1->size[0];
  emxEnsureCapacity_real_T(fscales_cineq_constraint, i);
  loop_ub = varargout_1->size[0];
  for (i = 0; i < loop_ub; i++) {
    fscales_cineq_constraint->data[i] = 1.0;
  }

  emxInitStruct_struct_T5(&WorkingSet);
  d_factoryConstruct(varargout_1->size[0], varargout_2->size[0] + 12, Aeq,
                     x0->size[1], nVarMax, mConstrMax, &WorkingSet);
  std::memset(&beqFiltered[0], 0, 12U * sizeof(double));
  emxInitStruct_struct_T6(&obj);
  obj.ldq = maxDims;
  i = obj.QR->size[0] * obj.QR->size[1];
  obj.QR->size[0] = maxDims;
  obj.QR->size[1] = maxDims;
  emxEnsureCapacity_real_T(obj.QR, i);
  i = obj.Q->size[0] * obj.Q->size[1];
  obj.Q->size[0] = maxDims;
  obj.Q->size[1] = maxDims;
  emxEnsureCapacity_real_T(obj.Q, i);
  loop_ub = maxDims * maxDims;
  for (i = 0; i < loop_ub; i++) {
    obj.Q->data[i] = 0.0;
  }

  i = obj.jpvt->size[0];
  obj.jpvt->size[0] = maxDims;
  emxEnsureCapacity_int32_T(obj.jpvt, i);
  for (i = 0; i < maxDims; i++) {
    obj.jpvt->data[i] = 0;
  }

  obj.mrows = 0;
  obj.ncols = 0;
  i = obj.tau->size[0];
  obj.tau->size[0] = maxDims;
  emxEnsureCapacity_real_T(obj.tau, i);
  obj.minRowCol = 0;
  obj.usedPivoting = false;
  nDepEq = removeDependentLinearEq(Aeq, beqFiltered, idxDepEq, &memspace,
    &TrialState, &WorkingSet, &obj, &QPObjective);
  if (nDepEq < 0) {
    nDepEq = 0;
  }

  mEq = (varargout_2->size[0] - nDepEq) + 12;
  mConstrMax = 11 - nDepEq;
  i = varargout_1->size[0];
  varargout_1->size[0] = TrialState.cIneq->size[0];
  emxEnsureCapacity_real_T(varargout_1, i);
  loop_ub = TrialState.cIneq->size[0];
  for (i = 0; i < loop_ub; i++) {
    varargout_1->data[i] = TrialState.cIneq->data[i];
  }

  i = varargout_2->size[0];
  varargout_2->size[0] = TrialState.cEq->size[0];
  emxEnsureCapacity_real_T(varargout_2, i);
  loop_ub = TrialState.cEq->size[0];
  for (i = 0; i < loop_ub; i++) {
    varargout_2->data[i] = TrialState.cEq->data[i];
  }

  emxInit_real_T(&b_TrialState, 2);
  i = b_TrialState->size[0] * b_TrialState->size[1];
  b_TrialState->size[0] = 1;
  b_TrialState->size[1] = TrialState.xstarsqp->size[1];
  emxEnsureCapacity_real_T(b_TrialState, i);
  loop_ub = TrialState.xstarsqp->size[0] * TrialState.xstarsqp->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_TrialState->data[i] = TrialState.xstarsqp->data[i];
  }

  computeObjective_(b_TrialState, &TrialState.sqpFval, &nVarMax);
  emxFree_real_T(&b_TrialState);
  if (nVarMax == 1) {
    computeConstraints_(FcnEvaluator.nonlcon.tunableEnvironment.f1,
                        FcnEvaluator.nonlcon.tunableEnvironment.f2,
                        FcnEvaluator.nonlcon.tunableEnvironment.f3,
                        FcnEvaluator.nonlcon.tunableEnvironment.f4,
                        nonlcon_tunableEnvironment_f5, FcnEvaluator.mCineq,
                        FcnEvaluator.mCeq, TrialState.xstarsqp, varargout_1,
                        TrialState.iNonIneq0, varargout_2, TrialState.iNonEq0);
  }

  computeFiniteDifferences(&FiniteDifferences, TrialState.sqpFval, varargout_1,
    TrialState.iNonIneq0, varargout_2, TrialState.iNonEq0, TrialState.xstarsqp,
    TrialState.grad, WorkingSet.Aineq, TrialState.iNonIneq0, WorkingSet.Aeq,
    TrialState.iNonEq0, c_runTimeOptions_FiniteDifferen);
  TrialState.FunctionEvaluations = FiniteDifferences.numEvals + 1;
  ldAe = WorkingSet.ldA;
  if (12 - nDepEq > 0) {
    for (k = 0; k <= mConstrMax; k++) {
      varargout_2->data[k] = 0.0;
    }

    if ((x0->size[1] != 0) && (12 - nDepEq != 0)) {
      nVarMax = 11 - nDepEq;
      for (idx = 0; idx <= nVarMax; idx++) {
        varargout_2->data[idx] = -varargout_2->data[idx];
      }

      idx = 0;
      i = WorkingSet.ldA * (11 - nDepEq) + 1;
      for (nVarMax = 1; ldAe < 0 ? nVarMax >= i : nVarMax <= i; nVarMax += ldAe)
      {
        mConstrMax = 0;
        c = 0.0;
        loop_ub = nVarMax + nVar;
        for (nDepEq = nVarMax; nDepEq <= loop_ub; nDepEq++) {
          c += WorkingSet.Aeq->data[nDepEq - 1] * TrialState.xstarsqp->
            data[mConstrMax];
          mConstrMax++;
        }

        varargout_2->data[idx] += c;
        idx++;
      }
    }
  }

  i = TrialState.cIneq->size[0];
  TrialState.cIneq->size[0] = varargout_1->size[0];
  emxEnsureCapacity_real_T(TrialState.cIneq, i);
  loop_ub = varargout_1->size[0];
  for (i = 0; i < loop_ub; i++) {
    TrialState.cIneq->data[i] = varargout_1->data[i];
  }

  i = TrialState.cEq->size[0];
  TrialState.cEq->size[0] = varargout_2->size[0];
  emxEnsureCapacity_real_T(TrialState.cEq, i);
  loop_ub = varargout_2->size[0];
  for (i = 0; i < loop_ub; i++) {
    TrialState.cEq->data[i] = varargout_2->data[i];
  }

  nVarMax = TrialState.mNonlinEq;
  nVar = WorkingSet.nVar;
  for (idx = 0; idx < mEq; idx++) {
    WorkingSet.beq->data[idx] = -varargout_2->data[idx];
    WorkingSet.bwset->data[idx] = WorkingSet.beq->data[idx];
  }

  mConstrMax = WorkingSet.ldA * (mEq - TrialState.mNonlinEq);
  nDepEq = mConstrMax;
  for (idx = 0; idx < nVarMax; idx++) {
    for (k = 0; k < nVar; k++) {
      loop_ub = k + 1;
      WorkingSet.ATwset->data[(mConstrMax + loop_ub) - 1] = WorkingSet.Aeq->
        data[(nDepEq + loop_ub) - 1];
    }

    mConstrMax += WorkingSet.ldA;
    nDepEq += WorkingSet.ldA;
  }

  for (idx = 0; idx <= mNonlinIneq; idx++) {
    WorkingSet.bineq->data[idx] = -varargout_1->data[idx];
  }

  if (0 > mEq) {
    nVarMax = mEq + 1;
    for (idx = nVarMax; idx < 1; idx++) {
      abort();
    }
  }

  setProblemType(&WorkingSet, 3);
  nVarMax = WorkingSet.isActiveIdx[2];
  i = WorkingSet.mConstrMax;
  for (idx = nVarMax; idx <= i; idx++) {
    WorkingSet.isActiveConstr->data[idx - 1] = false;
  }

  WorkingSet.nWConstr[0] = 0;
  WorkingSet.nWConstr[1] = WorkingSet.sizes[1];
  WorkingSet.nWConstr[2] = 0;
  WorkingSet.nWConstr[3] = 0;
  WorkingSet.nWConstr[4] = 0;
  WorkingSet.nActiveConstr = WorkingSet.nWConstr[1];
  nVarMax = WorkingSet.sizes[1];
  for (mConstrMax = 0; mConstrMax < nVarMax; mConstrMax++) {
    WorkingSet.Wid->data[mConstrMax] = 2;
    WorkingSet.Wlocalidx->data[mConstrMax] = mConstrMax + 1;
    WorkingSet.isActiveConstr->data[mConstrMax] = true;
    loop_ub = WorkingSet.ldA * mConstrMax;
    nDepEq = WorkingSet.nVar;
    for (k = 0; k < nDepEq; k++) {
      i = loop_ub + k;
      WorkingSet.ATwset->data[i] = WorkingSet.Aeq->data[i];
    }

    WorkingSet.bwset->data[mConstrMax] = WorkingSet.beq->data[mConstrMax];
  }

  MeritFunction.initFval = TrialState.sqpFval;
  MeritFunction.penaltyParam = 1.0;
  MeritFunction.threshold = 0.0001;
  MeritFunction.nPenaltyDecreases = 0;
  MeritFunction.linearizedConstrViol = 0.0;
  c = 0.0;
  if (mEq >= 1) {
    for (k = 0; k < mEq; k++) {
      c += std::abs(varargout_2->data[k]);
    }
  }

  emxFree_real_T(&varargout_2);
  MeritFunction.initConstrViolationEq = c;
  c = 0.0;
  for (idx = 0; idx <= mNonlinIneq; idx++) {
    if (varargout_1->data[idx] > 0.0) {
      c += varargout_1->data[idx];
    }
  }

  emxFree_real_T(&varargout_1);
  emxInitStruct_struct_T7(&b_obj);
  MeritFunction.initConstrViolationIneq = c;
  MeritFunction.phi = 0.0;
  MeritFunction.phiPrimePlus = 0.0;
  MeritFunction.phiFullStep = 0.0;
  MeritFunction.feasRelativeFactor = 0.0;
  MeritFunction.nlpPrimalFeasError = 0.0;
  MeritFunction.nlpDualFeasError = 0.0;
  MeritFunction.nlpComplError = 0.0;
  MeritFunction.firstOrderOpt = 0.0;
  MeritFunction.hasObjective = true;
  i = b_obj.UU->size[0] * b_obj.UU->size[1];
  b_obj.UU->size[0] = maxDims;
  b_obj.UU->size[1] = maxDims;
  emxEnsureCapacity_real_T(b_obj.UU, i);
  i = b_obj.x->size[0];
  b_obj.x->size[0] = maxDims;
  emxEnsureCapacity_real_T(b_obj.x, i);
  b_obj.ldu = maxDims;
  b_obj.ndims = 0;
  b_obj.info = 0;
  driver(Hessian, &TrialState, &MeritFunction, &FcnEvaluator, &FiniteDifferences,
         &memspace, &WorkingSet, &obj, &b_obj, &QPObjective,
         fscales_cineq_constraint, c_runTimeOptions_FiniteDifferen);
  i = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = TrialState.xstarsqp->size[1];
  emxEnsureCapacity_real_T(x, i);
  loop_ub = TrialState.xstarsqp->size[0] * TrialState.xstarsqp->size[1];
  emxFreeStruct_struct_T7(&b_obj);
  emxFreeStruct_struct_T6(&obj);
  emxFree_real_T(&Hessian);
  emxFreeStruct_struct_T5(&WorkingSet);
  emxFree_real_T(&fscales_cineq_constraint);
  emxFreeStruct_struct_T4(&memspace);
  emxFreeStruct_struct_T3(&QPObjective);
  emxFreeStruct_struct_T1(&FcnEvaluator);
  emxFree_real_T(&c_runTimeOptions_FiniteDifferen);
  for (i = 0; i < loop_ub; i++) {
    x->data[i] = TrialState.xstarsqp->data[i];
  }

  *fval = TrialState.sqpFval;
  *exitflag = TrialState.sqpExitFlag;
  emxFreeStruct_struct_T(&TrialState);
  emxFreeStruct_struct_T2(&r);
  emxFreeStruct_struct_T2(&FiniteDifferences);
}

//
// File trailer for fmincon.cpp
//
// [EOF]
//
