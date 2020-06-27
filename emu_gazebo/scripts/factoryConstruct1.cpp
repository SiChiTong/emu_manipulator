//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factoryConstruct1.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "factoryConstruct1.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"

// Function Definitions

//
// Arguments    : coder_internal_ref *nonlin_tunableEnvironment_f1
//                const emxArray_real_T *nonlin_tunableEnvironment_f2
//                const double nonlin_tunableEnvironment_f3[6]
//                const double nonlin_tunableEnvironment_f4[6]
//                double nonlin_tunableEnvironment_f5
//                int nVar
//                int mCeq
//                const emxArray_real_T *lb
//                d_struct_T *obj
// Return Type  : void
//
void b_factoryConstruct(coder_internal_ref *nonlin_tunableEnvironment_f1, const
  emxArray_real_T *nonlin_tunableEnvironment_f2, const double
  nonlin_tunableEnvironment_f3[6], const double nonlin_tunableEnvironment_f4[6],
  double nonlin_tunableEnvironment_f5, int nVar, int mCeq, const emxArray_real_T
  *lb, d_struct_T *obj)
{
  int idx;
  int loop_ub;
  emxArray_boolean_T *hasLB;
  emxArray_boolean_T *hasUB;
  bool b;
  obj->nonlin.tunableEnvironment.f1 = nonlin_tunableEnvironment_f1;
  idx = obj->nonlin.tunableEnvironment.f2->size[0] *
    obj->nonlin.tunableEnvironment.f2->size[1];
  obj->nonlin.tunableEnvironment.f2->size[0] = 6;
  obj->nonlin.tunableEnvironment.f2->size[1] =
    nonlin_tunableEnvironment_f2->size[1];
  emxEnsureCapacity_real_T(obj->nonlin.tunableEnvironment.f2, idx);
  loop_ub = nonlin_tunableEnvironment_f2->size[0] *
    nonlin_tunableEnvironment_f2->size[1];
  for (idx = 0; idx < loop_ub; idx++) {
    obj->nonlin.tunableEnvironment.f2->data[idx] =
      nonlin_tunableEnvironment_f2->data[idx];
  }

  for (idx = 0; idx < 6; idx++) {
    obj->nonlin.tunableEnvironment.f3[idx] = nonlin_tunableEnvironment_f3[idx];
    obj->nonlin.tunableEnvironment.f4[idx] = nonlin_tunableEnvironment_f4[idx];
  }

  emxInit_boolean_T(&hasLB, 1);
  obj->nonlin.tunableEnvironment.f5 = nonlin_tunableEnvironment_f5;
  obj->f_1 = 0.0;
  idx = obj->cEq_1->size[0];
  obj->cEq_1->size[0] = mCeq;
  emxEnsureCapacity_real_T(obj->cEq_1, idx);
  obj->f_2 = 0.0;
  idx = obj->cEq_2->size[0];
  obj->cEq_2->size[0] = mCeq;
  emxEnsureCapacity_real_T(obj->cEq_2, idx);
  obj->nVar = nVar;
  obj->mIneq = 12;
  obj->mEq = mCeq;
  obj->numEvals = 0;
  obj->SpecifyObjectiveGradient = false;
  obj->SpecifyConstraintGradient = false;
  idx = obj->hasLB->size[0];
  obj->hasLB->size[0] = nVar;
  emxEnsureCapacity_boolean_T(obj->hasLB, idx);
  idx = obj->hasUB->size[0];
  obj->hasUB->size[0] = nVar;
  emxEnsureCapacity_boolean_T(obj->hasUB, idx);
  obj->FiniteDifferenceType = 0;
  idx = hasLB->size[0];
  hasLB->size[0] = nVar;
  emxEnsureCapacity_boolean_T(hasLB, idx);
  for (idx = 0; idx < nVar; idx++) {
    hasLB->data[idx] = obj->hasLB->data[idx];
  }

  emxInit_boolean_T(&hasUB, 1);
  idx = hasUB->size[0];
  hasUB->size[0] = nVar;
  emxEnsureCapacity_boolean_T(hasUB, idx);
  for (idx = 0; idx < nVar; idx++) {
    hasUB->data[idx] = obj->hasUB->data[idx];
  }

  b = false;
  idx = 0;
  while ((!b) && (idx + 1 <= nVar)) {
    hasLB->data[idx] = ((!rtIsInf(lb->data[idx])) && (!rtIsNaN(lb->data[idx])));
    hasUB->data[idx] = false;
    b = (hasLB->data[idx] || b);
    idx++;
  }

  while (idx + 1 <= nVar) {
    hasLB->data[idx] = ((!rtIsInf(lb->data[idx])) && (!rtIsNaN(lb->data[idx])));
    hasUB->data[idx] = false;
    idx++;
  }

  idx = obj->hasLB->size[0];
  obj->hasLB->size[0] = hasLB->size[0];
  emxEnsureCapacity_boolean_T(obj->hasLB, idx);
  loop_ub = hasLB->size[0];
  for (idx = 0; idx < loop_ub; idx++) {
    obj->hasLB->data[idx] = hasLB->data[idx];
  }

  emxFree_boolean_T(&hasLB);
  idx = obj->hasUB->size[0];
  obj->hasUB->size[0] = hasUB->size[0];
  emxEnsureCapacity_boolean_T(obj->hasUB, idx);
  loop_ub = hasUB->size[0];
  for (idx = 0; idx < loop_ub; idx++) {
    obj->hasUB->data[idx] = hasUB->data[idx];
  }

  emxFree_boolean_T(&hasUB);
  obj->hasBounds = b;
}

//
// File trailer for factoryConstruct1.cpp
//
// [EOF]
//
