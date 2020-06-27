//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkNonlinearInputs.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "checkNonlinearInputs.h"
#include "cubicGenCodeGen.h"
#include "parseOptimalVar.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *x0
//                coder_internal_ref *nonlcon_tunableEnvironment_f1
//                const emxArray_real_T *nonlcon_tunableEnvironment_f2
//                double nonlcon_tunableEnvironment_f5
// Return Type  : int
//
int checkNonlinearInputs(const emxArray_real_T *x0, coder_internal_ref
  *nonlcon_tunableEnvironment_f1, const emxArray_real_T
  *nonlcon_tunableEnvironment_f2, double nonlcon_tunableEnvironment_f5)
{
  int mNonlinEq;
  emxArray_real_T *r;
  emxArray_real_T *vr_int;
  emxArray_real_T *tim;
  int i;
  int loop_ub;
  emxArray_real_T *b_nonlcon_tunableEnvironment_f1;
  emxArray_real_T *b_vr_int;
  emxArray_real_T *b_tim;
  emxArray_real_T *q1;
  emxArray_real_T *a_con1;
  emxArray_real_T *a_con2;
  emxArray_real_T *a_con3;
  emxArray_real_T *a_con4;
  emxArray_real_T *a_con5;
  emxArray_real_T *a_con6;
  emxInit_real_T(&r, 2);
  emxInit_real_T(&vr_int, 2);
  emxInit_real_T(&tim, 2);
  parseOptimalVar(nonlcon_tunableEnvironment_f2, x0, r, vr_int, tim);
  i = nonlcon_tunableEnvironment_f1->contents->size[0] *
    nonlcon_tunableEnvironment_f1->contents->size[1];
  nonlcon_tunableEnvironment_f1->contents->size[0] = 6;
  nonlcon_tunableEnvironment_f1->contents->size[1] = r->size[1];
  emxEnsureCapacity_real_T(nonlcon_tunableEnvironment_f1->contents, i);
  loop_ub = r->size[0] * r->size[1];
  for (i = 0; i < loop_ub; i++) {
    nonlcon_tunableEnvironment_f1->contents->data[i] = r->data[i];
  }

  emxFree_real_T(&r);
  emxInit_real_T(&b_nonlcon_tunableEnvironment_f1, 2);
  loop_ub = nonlcon_tunableEnvironment_f1->contents->size[1];
  i = b_nonlcon_tunableEnvironment_f1->size[0] *
    b_nonlcon_tunableEnvironment_f1->size[1];
  b_nonlcon_tunableEnvironment_f1->size[0] = 1;
  b_nonlcon_tunableEnvironment_f1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_nonlcon_tunableEnvironment_f1, i);
  for (i = 0; i < loop_ub; i++) {
    b_nonlcon_tunableEnvironment_f1->data[i] =
      nonlcon_tunableEnvironment_f1->contents->data[6 * i];
  }

  emxInit_real_T(&b_vr_int, 2);
  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i];
  }

  emxInit_real_T(&b_tim, 2);
  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q1, 2);
  emxInit_real_T(&a_con1, 1);
  cubicGenCodeGen(b_nonlcon_tunableEnvironment_f1, b_vr_int, b_tim,
                  nonlcon_tunableEnvironment_f5, q1, a_con1);
  loop_ub = nonlcon_tunableEnvironment_f1->contents->size[1];
  i = b_nonlcon_tunableEnvironment_f1->size[0] *
    b_nonlcon_tunableEnvironment_f1->size[1];
  b_nonlcon_tunableEnvironment_f1->size[0] = 1;
  b_nonlcon_tunableEnvironment_f1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_nonlcon_tunableEnvironment_f1, i);
  for (i = 0; i < loop_ub; i++) {
    b_nonlcon_tunableEnvironment_f1->data[i] =
      nonlcon_tunableEnvironment_f1->contents->data[6 * i + 1];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 1];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&a_con2, 1);
  cubicGenCodeGen(b_nonlcon_tunableEnvironment_f1, b_vr_int, b_tim,
                  nonlcon_tunableEnvironment_f5, q1, a_con2);
  loop_ub = nonlcon_tunableEnvironment_f1->contents->size[1];
  i = b_nonlcon_tunableEnvironment_f1->size[0] *
    b_nonlcon_tunableEnvironment_f1->size[1];
  b_nonlcon_tunableEnvironment_f1->size[0] = 1;
  b_nonlcon_tunableEnvironment_f1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_nonlcon_tunableEnvironment_f1, i);
  for (i = 0; i < loop_ub; i++) {
    b_nonlcon_tunableEnvironment_f1->data[i] =
      nonlcon_tunableEnvironment_f1->contents->data[6 * i + 2];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 2];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&a_con3, 1);
  cubicGenCodeGen(b_nonlcon_tunableEnvironment_f1, b_vr_int, b_tim,
                  nonlcon_tunableEnvironment_f5, q1, a_con3);
  loop_ub = nonlcon_tunableEnvironment_f1->contents->size[1];
  i = b_nonlcon_tunableEnvironment_f1->size[0] *
    b_nonlcon_tunableEnvironment_f1->size[1];
  b_nonlcon_tunableEnvironment_f1->size[0] = 1;
  b_nonlcon_tunableEnvironment_f1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_nonlcon_tunableEnvironment_f1, i);
  for (i = 0; i < loop_ub; i++) {
    b_nonlcon_tunableEnvironment_f1->data[i] =
      nonlcon_tunableEnvironment_f1->contents->data[6 * i + 3];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 3];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&a_con4, 1);
  cubicGenCodeGen(b_nonlcon_tunableEnvironment_f1, b_vr_int, b_tim,
                  nonlcon_tunableEnvironment_f5, q1, a_con4);
  loop_ub = nonlcon_tunableEnvironment_f1->contents->size[1];
  i = b_nonlcon_tunableEnvironment_f1->size[0] *
    b_nonlcon_tunableEnvironment_f1->size[1];
  b_nonlcon_tunableEnvironment_f1->size[0] = 1;
  b_nonlcon_tunableEnvironment_f1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_nonlcon_tunableEnvironment_f1, i);
  for (i = 0; i < loop_ub; i++) {
    b_nonlcon_tunableEnvironment_f1->data[i] =
      nonlcon_tunableEnvironment_f1->contents->data[6 * i + 4];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 4];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&a_con5, 1);
  cubicGenCodeGen(b_nonlcon_tunableEnvironment_f1, b_vr_int, b_tim,
                  nonlcon_tunableEnvironment_f5, q1, a_con5);
  loop_ub = nonlcon_tunableEnvironment_f1->contents->size[1];
  i = b_nonlcon_tunableEnvironment_f1->size[0] *
    b_nonlcon_tunableEnvironment_f1->size[1];
  b_nonlcon_tunableEnvironment_f1->size[0] = 1;
  b_nonlcon_tunableEnvironment_f1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_nonlcon_tunableEnvironment_f1, i);
  emxFree_real_T(&b_tim);
  for (i = 0; i < loop_ub; i++) {
    b_nonlcon_tunableEnvironment_f1->data[i] =
      nonlcon_tunableEnvironment_f1->contents->data[6 * i + 5];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 5];
  }

  emxFree_real_T(&vr_int);
  emxInit_real_T(&a_con6, 1);
  cubicGenCodeGen(b_nonlcon_tunableEnvironment_f1, b_vr_int, tim,
                  nonlcon_tunableEnvironment_f5, q1, a_con6);
  mNonlinEq = (((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                 a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) + 12;
  emxFree_real_T(&b_vr_int);
  emxFree_real_T(&b_nonlcon_tunableEnvironment_f1);
  emxFree_real_T(&a_con6);
  emxFree_real_T(&a_con5);
  emxFree_real_T(&a_con4);
  emxFree_real_T(&a_con3);
  emxFree_real_T(&a_con2);
  emxFree_real_T(&a_con1);
  emxFree_real_T(&q1);
  emxFree_real_T(&tim);
  return mNonlinEq;
}

//
// File trailer for checkNonlinearInputs.cpp
//
// [EOF]
//
