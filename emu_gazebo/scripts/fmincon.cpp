//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fmincon.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "fmincon.h"
#include "checkNonlinearInputs.h"
#include "computeConstraints_.h"
#include "computeFiniteDifferences.h"
#include "driver.h"
#include "factoryConstruct.h"
#include "factoryConstruct1.h"
#include "factoryConstruct2.h"
#include "initActiveSet.h"
#include "removeDependentLinearEq.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "updateWorkingSetForNewQP.h"
#include "xgemv.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : const emxArray_real_T *x0
//                const emxArray_real_T *Aeq
//                const emxArray_real_T *lb
//                const emxArray_real_T *ub
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
void fmincon(const emxArray_real_T *x0, const emxArray_real_T *Aeq, const
             emxArray_real_T *lb, const emxArray_real_T *ub, coder_internal_ref *
             nonlcon_tunableEnvironment_f1, const emxArray_real_T
             *nonlcon_tunableEnvironment_f2, const double
             nonlcon_tunableEnvironment_f3[6], const double
             nonlcon_tunableEnvironment_f4[6], double
             nonlcon_tunableEnvironment_f5, emxArray_real_T *x, double *fval,
             double *exitflag)
{
  emxArray_real_T *c_runTimeOptions_FiniteDifferen;
  d_struct_T FiniteDifferences;
  d_struct_T r;
  int mEq;
  int i;
  int idx;
  emxArray_real_T *Hessian;
  int mNonlinEq;
  int mConstrMax;
  int nVarMax;
  int maxDims;
  e_struct_T TrialState;
  int k;
  f_struct_T FcnEvaluator;
  g_struct_T QPObjective;
  c_struct_T memspace;
  emxArray_int32_T *indexLB;
  emxArray_int32_T *indexUB;
  emxArray_int32_T *indexFixed;
  int mLB;
  h_struct_T WorkingSet;
  double normResid;
  double beqFiltered[12];
  i_struct_T obj;
  int idxDepEq[12];
  emxArray_real_T *Ceq_workspace;
  double Cineq_workspace[12];
  j_struct_T MeritFunction;
  k_struct_T b_obj;
  emxInit_real_T(&c_runTimeOptions_FiniteDifferen, 1);
  emxInitStruct_struct_T2(&FiniteDifferences);
  emxInitStruct_struct_T2(&r);
  mEq = x0->size[1];
  i = c_runTimeOptions_FiniteDifferen->size[0];
  c_runTimeOptions_FiniteDifferen->size[0] = x0->size[1];
  emxEnsureCapacity_real_T(c_runTimeOptions_FiniteDifferen, i);
  for (idx = 0; idx < mEq; idx++) {
    c_runTimeOptions_FiniteDifferen->data[idx] = 1.4901161193847656E-8;
  }

  emxInit_real_T(&Hessian, 2);
  mNonlinEq = checkNonlinearInputs(x0, nonlcon_tunableEnvironment_f1,
    nonlcon_tunableEnvironment_f2, nonlcon_tunableEnvironment_f5);
  mEq = x0->size[1] - 1;
  idx = (mNonlinEq + 12) << 1;
  mConstrMax = (((mNonlinEq + lb->size[1]) + ub->size[1]) + idx) + 37;
  nVarMax = (x0->size[1] + idx) + 13;
  if (nVarMax > mConstrMax) {
    maxDims = nVarMax;
  } else {
    maxDims = mConstrMax;
  }

  i = Hessian->size[0] * Hessian->size[1];
  Hessian->size[0] = x0->size[1];
  Hessian->size[1] = x0->size[1];
  emxEnsureCapacity_real_T(Hessian, i);
  idx = x0->size[1] * x0->size[1];
  for (i = 0; i < idx; i++) {
    Hessian->data[i] = 0.0;
  }

  emxInitStruct_struct_T(&TrialState);
  factoryConstruct(nVarMax, mConstrMax, mNonlinEq + 12, x0->size, mNonlinEq,
                   &TrialState);
  for (k = 0; k <= mEq; k++) {
    Hessian->data[k + Hessian->size[0] * k] = 1.0;
    TrialState.xstarsqp->data[k] = x0->data[k];
  }

  emxInitStruct_struct_T1(&FcnEvaluator);
  FcnEvaluator.nVar = x0->size[1];
  FcnEvaluator.mCeq = mNonlinEq;
  FcnEvaluator.nonlcon.tunableEnvironment.f1 = nonlcon_tunableEnvironment_f1;
  i = FcnEvaluator.nonlcon.tunableEnvironment.f2->size[0] *
    FcnEvaluator.nonlcon.tunableEnvironment.f2->size[1];
  FcnEvaluator.nonlcon.tunableEnvironment.f2->size[0] = 6;
  FcnEvaluator.nonlcon.tunableEnvironment.f2->size[1] =
    nonlcon_tunableEnvironment_f2->size[1];
  emxEnsureCapacity_real_T(FcnEvaluator.nonlcon.tunableEnvironment.f2, i);
  idx = nonlcon_tunableEnvironment_f2->size[0] *
    nonlcon_tunableEnvironment_f2->size[1];
  for (i = 0; i < idx; i++) {
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
  emxInit_int32_T(&indexLB, 1);
  emxInit_int32_T(&indexUB, 1);
  emxInit_int32_T(&indexFixed, 1);
  FcnEvaluator.nonlcon.tunableEnvironment.f5 = nonlcon_tunableEnvironment_f5;
  FcnEvaluator.mCineq = 12;
  FcnEvaluator.NonFiniteSupport = true;
  FcnEvaluator.SpecifyObjectiveGradient = false;
  FcnEvaluator.SpecifyConstraintGradient = false;
  FcnEvaluator.ScaleProblem = false;
  b_factoryConstruct(nonlcon_tunableEnvironment_f1,
                     nonlcon_tunableEnvironment_f2,
                     nonlcon_tunableEnvironment_f3,
                     nonlcon_tunableEnvironment_f4,
                     nonlcon_tunableEnvironment_f5, x0->size[1], mNonlinEq, lb,
                     &r);
  emxCopyStruct_struct_T(&FiniteDifferences, &r);
  i = QPObjective.grad->size[0];
  QPObjective.grad->size[0] = nVarMax;
  emxEnsureCapacity_real_T(QPObjective.grad, i);
  i = QPObjective.Hx->size[0];
  QPObjective.Hx->size[0] = nVarMax - 1;
  emxEnsureCapacity_real_T(QPObjective.Hx, i);
  QPObjective.maxVar = nVarMax;
  QPObjective.beta = 0.0;
  QPObjective.rho = 0.0;
  QPObjective.prev_objtype = 3;
  QPObjective.prev_nvar = 0;
  QPObjective.prev_hasLinear = false;
  QPObjective.gammaScalar = 0.0;
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
  i = indexLB->size[0];
  indexLB->size[0] = lb->size[1];
  emxEnsureCapacity_int32_T(indexLB, i);
  i = indexUB->size[0];
  indexUB->size[0] = ub->size[1];
  emxEnsureCapacity_int32_T(indexUB, i);
  i = indexFixed->size[0];
  idx = lb->size[1];
  k = ub->size[1];
  if (idx < k) {
    k = idx;
  }

  indexFixed->size[0] = k;
  emxEnsureCapacity_int32_T(indexFixed, i);
  mLB = 0;
  for (idx = 0; idx <= mEq; idx++) {
    normResid = lb->data[idx];
    if ((!rtIsInf(normResid)) && (!rtIsNaN(normResid))) {
      mLB++;
      indexLB->data[mLB - 1] = idx + 1;
    }
  }

  emxInitStruct_struct_T5(&WorkingSet);
  c_factoryConstruct(mNonlinEq + 12, Aeq, mLB, indexLB, 0, indexUB, 0,
                     indexFixed, x0->size[1], nVarMax, mConstrMax, &WorkingSet);
  emxFree_int32_T(&indexFixed);
  emxFree_int32_T(&indexUB);
  emxFree_int32_T(&indexLB);
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
  idx = maxDims * maxDims;
  for (i = 0; i < idx; i++) {
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
  nVarMax = removeDependentLinearEq(Aeq, beqFiltered, idxDepEq, &memspace,
    &TrialState, &WorkingSet, &obj, &QPObjective);
  if (nVarMax < 0) {
    nVarMax = 0;
  }

  mEq = (mNonlinEq - nVarMax) + 12;
  mConstrMax = 11 - nVarMax;
  for (idx = 0; idx < mLB; idx++) {
    normResid = lb->data[WorkingSet.indexLB->data[idx] - 1];
    if ((!(TrialState.xstarsqp->data[WorkingSet.indexLB->data[idx] - 1] >
           normResid)) && (!rtIsNaN(normResid))) {
      TrialState.xstarsqp->data[WorkingSet.indexLB->data[idx] - 1] = normResid;
    }
  }

  emxInit_real_T(&Ceq_workspace, 1);
  i = Ceq_workspace->size[0];
  Ceq_workspace->size[0] = TrialState.cEq->size[0];
  emxEnsureCapacity_real_T(Ceq_workspace, i);
  idx = TrialState.cEq->size[0];
  for (i = 0; i < idx; i++) {
    Ceq_workspace->data[i] = TrialState.cEq->data[i];
  }

  std::memcpy(&Cineq_workspace[0], &TrialState.cIneq[0], 12U * sizeof(double));
  *fval = __anon_fcn(TrialState.xstarsqp);
  if ((!rtIsInf(*fval)) && (!rtIsNaN(*fval))) {
    computeConstraints_(FcnEvaluator.nonlcon.tunableEnvironment.f1,
                        FcnEvaluator.nonlcon.tunableEnvironment.f2,
                        FcnEvaluator.nonlcon.tunableEnvironment.f3,
                        FcnEvaluator.nonlcon.tunableEnvironment.f4,
                        nonlcon_tunableEnvironment_f5, mNonlinEq,
                        TrialState.xstarsqp, Cineq_workspace, Ceq_workspace,
                        TrialState.iNonEq0);
  }

  TrialState.sqpFval = *fval;
  std::memcpy(&TrialState.cIneq[0], &Cineq_workspace[0], 12U * sizeof(double));
  computeFiniteDifferences(&FiniteDifferences, *fval, Cineq_workspace,
    Ceq_workspace, TrialState.iNonEq0, TrialState.xstarsqp, TrialState.grad,
    WorkingSet.Aineq, WorkingSet.Aeq, TrialState.iNonEq0, lb,
    c_runTimeOptions_FiniteDifferen);
  TrialState.FunctionEvaluations = FiniteDifferences.numEvals + 1;
  if (12 - nVarMax > 0) {
    for (k = 0; k <= mConstrMax; k++) {
      Ceq_workspace->data[k] = beqFiltered[k];
    }

    xgemv(x0->size[1], 12 - nVarMax, WorkingSet.Aeq, WorkingSet.ldA,
          TrialState.xstarsqp, Ceq_workspace);
  }

  i = TrialState.cEq->size[0];
  TrialState.cEq->size[0] = Ceq_workspace->size[0];
  emxEnsureCapacity_real_T(TrialState.cEq, i);
  idx = Ceq_workspace->size[0];
  for (i = 0; i < idx; i++) {
    TrialState.cEq->data[i] = Ceq_workspace->data[i];
  }

  updateWorkingSetForNewQP(x0, &WorkingSet, Cineq_workspace, mEq,
    TrialState.mNonlinEq, Ceq_workspace, mLB, lb, 0, 0);
  initActiveSet(&WorkingSet);
  MeritFunction.initFval = *fval;
  MeritFunction.penaltyParam = 1.0;
  MeritFunction.threshold = 0.0001;
  MeritFunction.nPenaltyDecreases = 0;
  MeritFunction.linearizedConstrViol = 0.0;
  normResid = 0.0;
  if (mEq >= 1) {
    for (k = 0; k < mEq; k++) {
      normResid += std::abs(Ceq_workspace->data[k]);
    }
  }

  emxFree_real_T(&Ceq_workspace);
  MeritFunction.initConstrViolationEq = normResid;
  normResid = 0.0;
  for (idx = 0; idx < 12; idx++) {
    if (Cineq_workspace[idx] > 0.0) {
      normResid += Cineq_workspace[idx];
    }
  }

  emxInitStruct_struct_T7(&b_obj);
  MeritFunction.initConstrViolationIneq = normResid;
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
  driver(Hessian, beqFiltered, lb, &TrialState, &MeritFunction, &FcnEvaluator,
         &FiniteDifferences, &memspace, &WorkingSet, &obj, &b_obj, &QPObjective,
         c_runTimeOptions_FiniteDifferen);
  i = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = TrialState.xstarsqp->size[1];
  emxEnsureCapacity_real_T(x, i);
  idx = TrialState.xstarsqp->size[0] * TrialState.xstarsqp->size[1];
  emxFreeStruct_struct_T7(&b_obj);
  emxFreeStruct_struct_T6(&obj);
  emxFree_real_T(&Hessian);
  emxFreeStruct_struct_T5(&WorkingSet);
  emxFreeStruct_struct_T4(&memspace);
  emxFreeStruct_struct_T3(&QPObjective);
  emxFreeStruct_struct_T1(&FcnEvaluator);
  emxFree_real_T(&c_runTimeOptions_FiniteDifferen);
  for (i = 0; i < idx; i++) {
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
