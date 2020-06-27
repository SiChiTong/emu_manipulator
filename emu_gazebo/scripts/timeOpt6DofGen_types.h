//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeOpt6DofGen_types.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//
#ifndef TIMEOPT6DOFGEN_TYPES_H
#define TIMEOPT6DOFGEN_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};

struct s7T39ynA5CUr3fS81Fydt3G_tag
{
  int nVarMax;
  int mNonlinIneq;
  int mNonlinEq;
  int mIneq;
  int mEq;
  int iNonIneq0;
  int iNonEq0;
  double sqpFval;
  double sqpFval_old;
  emxArray_real_T *xstarsqp;
  emxArray_real_T *xstarsqp_old;
  double cIneq[12];
  double cIneq_old[12];
  emxArray_real_T *cEq;
  emxArray_real_T *cEq_old;
  emxArray_real_T *grad;
  emxArray_real_T *grad_old;
  int FunctionEvaluations;
  int sqpIterations;
  int sqpExitFlag;
  emxArray_real_T *lambdasqp;
  emxArray_real_T *lambdasqp_old;
  double steplength;
  emxArray_real_T *delta_x;
  emxArray_real_T *socDirection;
  emxArray_real_T *lambda_old;
  emxArray_int32_T *workingset_old;
  emxArray_real_T *JacCineqTrans_old;
  emxArray_real_T *JacCeqTrans_old;
  emxArray_real_T *gradLag;
  emxArray_real_T *delta_gradLag;
  emxArray_real_T *xstar;
  double fstar;
  emxArray_real_T *lambda;
  int state;
  double maxConstr;
  int iterations;
  emxArray_real_T *searchDir;
};

typedef s7T39ynA5CUr3fS81Fydt3G_tag e_struct_T;
struct emxArray_boolean_T
{
  bool *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};

struct swx1b4PaGJygyFazeeCOkYC_tag
{
  int mConstr;
  int mConstrOrig;
  int mConstrMax;
  int nVar;
  int nVarOrig;
  int nVarMax;
  int ldA;
  emxArray_real_T *Aineq;
  double bineq[12];
  emxArray_real_T *Aeq;
  emxArray_real_T *beq;
  emxArray_real_T *lb;
  emxArray_real_T *ub;
  emxArray_int32_T *indexLB;
  emxArray_int32_T *indexUB;
  emxArray_int32_T *indexFixed;
  int mEqRemoved;
  emxArray_int32_T *indexEqRemoved;
  emxArray_real_T *ATwset;
  emxArray_real_T *bwset;
  int nActiveConstr;
  emxArray_real_T *maxConstrWorkspace;
  int sizes[5];
  int sizesNormal[5];
  int sizesPhaseOne[5];
  int sizesRegularized[5];
  int sizesRegPhaseOne[5];
  int isActiveIdx[6];
  int isActiveIdxNormal[6];
  int isActiveIdxPhaseOne[6];
  int isActiveIdxRegularized[6];
  int isActiveIdxRegPhaseOne[6];
  emxArray_boolean_T *isActiveConstr;
  emxArray_int32_T *Wid;
  emxArray_int32_T *Wlocalidx;
  int nWConstr[5];
  int probType;
  double SLACK0;
};

typedef swx1b4PaGJygyFazeeCOkYC_tag h_struct_T;
struct coder_internal_ref
{
  emxArray_real_T *contents;
};

struct cell_1
{
  coder_internal_ref *f1;
  emxArray_real_T *f2;
  double f3[6];
  double f4[6];
  double f5;
};

struct c_coder_internal_anonymous_func
{
  cell_1 tunableEnvironment;
};

struct d_struct_T
{
  c_coder_internal_anonymous_func nonlin;
  double f_1;
  double cIneq_1[12];
  emxArray_real_T *cEq_1;
  double f_2;
  double cIneq_2[12];
  emxArray_real_T *cEq_2;
  int nVar;
  int mIneq;
  int mEq;
  int numEvals;
  bool SpecifyObjectiveGradient;
  bool SpecifyConstraintGradient;
  emxArray_boolean_T *hasLB;
  emxArray_boolean_T *hasUB;
  bool hasBounds;
  int FiniteDifferenceType;
};

struct f_struct_T
{
  c_coder_internal_anonymous_func nonlcon;
  int nVar;
  int mCineq;
  int mCeq;
  bool NonFiniteSupport;
  bool SpecifyObjectiveGradient;
  bool SpecifyConstraintGradient;
  bool ScaleProblem;
};

struct g_struct_T
{
  emxArray_real_T *grad;
  emxArray_real_T *Hx;
  bool hasLinear;
  int nvar;
  int maxVar;
  double beta;
  double rho;
  int objtype;
  int prev_objtype;
  int prev_nvar;
  bool prev_hasLinear;
  double gammaScalar;
};

struct c_struct_T
{
  emxArray_real_T *workspace_double;
  emxArray_int32_T *workspace_int;
  emxArray_int32_T *workspace_sort;
};

struct i_struct_T
{
  int ldq;
  emxArray_real_T *QR;
  emxArray_real_T *Q;
  emxArray_int32_T *jpvt;
  int mrows;
  int ncols;
  emxArray_real_T *tau;
  int minRowCol;
  bool usedPivoting;
};

struct j_struct_T
{
  double penaltyParam;
  double threshold;
  int nPenaltyDecreases;
  double linearizedConstrViol;
  double initFval;
  double initConstrViolationEq;
  double initConstrViolationIneq;
  double phi;
  double phiPrimePlus;
  double phiFullStep;
  double feasRelativeFactor;
  double nlpPrimalFeasError;
  double nlpDualFeasError;
  double nlpComplError;
  double firstOrderOpt;
  bool hasObjective;
};

struct k_struct_T
{
  emxArray_real_T *UU;
  emxArray_real_T *x;
  int ldu;
  int ndims;
  int info;
};

struct struct_T
{
  bool gradOK;
  bool fevalOK;
  bool done;
  bool stepAccepted;
  bool failedLineSearch;
  int stepType;
};

struct b_struct_T
{
  int MaxIterations;
  double StepTolerance;
  double OptimalityTolerance;
  double ConstraintTolerance;
  double ObjectiveLimit;
  bool DisplayQP;
};

#endif

//
// File trailer for timeOpt6DofGen_types.h
//
// [EOF]
//
