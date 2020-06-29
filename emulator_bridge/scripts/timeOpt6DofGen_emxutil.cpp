//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeOpt6DofGen_emxutil.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "timeOpt6DofGen_emxutil.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include <cstdlib>
#include <cstring>

// Function Declarations
static void c_emxCopyStruct_coder_internal_(c_coder_internal_anonymous_func *dst,
  const c_coder_internal_anonymous_func *src);
static void d_emxFreeStruct_coder_internal_(c_coder_internal_anonymous_func
  *pStruct);
static void d_emxInitStruct_coder_internal_(c_coder_internal_anonymous_func
  *pStruct);
static void emxCopyMatrix_int32_T(int dst[5], const int src[5]);
static void emxCopyMatrix_int32_T1(int dst[6], const int src[6]);
static void emxCopyMatrix_real_T(double dst[6], const double src[6]);
static void emxCopyStruct_cell_2(cell_2 *dst, const cell_2 *src);
static void emxCopy_boolean_T(emxArray_boolean_T **dst, emxArray_boolean_T *
  const *src);
static void emxCopy_int32_T(emxArray_int32_T **dst, emxArray_int32_T * const
  *src);
static void emxCopy_real_T(emxArray_real_T **dst, emxArray_real_T * const *src);
static void emxFreeStruct_cell_2(cell_2 *pStruct);
static void emxInitStruct_cell_2(cell_2 *pStruct);

// Function Definitions

//
// Arguments    : c_coder_internal_anonymous_func *dst
//                const c_coder_internal_anonymous_func *src
// Return Type  : void
//
static void c_emxCopyStruct_coder_internal_(c_coder_internal_anonymous_func *dst,
  const c_coder_internal_anonymous_func *src)
{
  emxCopyStruct_cell_2(&dst->tunableEnvironment, &src->tunableEnvironment);
}

//
// Arguments    : c_coder_internal_anonymous_func *pStruct
// Return Type  : void
//
static void d_emxFreeStruct_coder_internal_(c_coder_internal_anonymous_func
  *pStruct)
{
  emxFreeStruct_cell_2(&pStruct->tunableEnvironment);
}

//
// Arguments    : c_coder_internal_anonymous_func *pStruct
// Return Type  : void
//
static void d_emxInitStruct_coder_internal_(c_coder_internal_anonymous_func
  *pStruct)
{
  emxInitStruct_cell_2(&pStruct->tunableEnvironment);
}

//
// Arguments    : int dst[5]
//                const int src[5]
// Return Type  : void
//
static void emxCopyMatrix_int32_T(int dst[5], const int src[5])
{
  int i;
  for (i = 0; i < 5; i++) {
    dst[i] = src[i];
  }
}

//
// Arguments    : int dst[6]
//                const int src[6]
// Return Type  : void
//
static void emxCopyMatrix_int32_T1(int dst[6], const int src[6])
{
  int i;
  for (i = 0; i < 6; i++) {
    dst[i] = src[i];
  }
}

//
// Arguments    : double dst[6]
//                const double src[6]
// Return Type  : void
//
static void emxCopyMatrix_real_T(double dst[6], const double src[6])
{
  int i;
  for (i = 0; i < 6; i++) {
    dst[i] = src[i];
  }
}

//
// Arguments    : cell_2 *dst
//                const cell_2 *src
// Return Type  : void
//
static void emxCopyStruct_cell_2(cell_2 *dst, const cell_2 *src)
{
  dst->f1 = src->f1;
  emxCopy_real_T(&dst->f2, &src->f2);
  emxCopyMatrix_real_T(dst->f3, src->f3);
  emxCopyMatrix_real_T(dst->f4, src->f4);
  dst->f5 = src->f5;
}

//
// Arguments    : emxArray_boolean_T **dst
//                emxArray_boolean_T * const *src
// Return Type  : void
//
static void emxCopy_boolean_T(emxArray_boolean_T **dst, emxArray_boolean_T *
  const *src)
{
  int numElDst;
  int numElSrc;
  int i;
  numElDst = 1;
  numElSrc = 1;
  for (i = 0; i < (*dst)->numDimensions; i++) {
    numElDst *= (*dst)->size[i];
    numElSrc *= (*src)->size[i];
  }

  for (i = 0; i < (*dst)->numDimensions; i++) {
    (*dst)->size[i] = (*src)->size[i];
  }

  emxEnsureCapacity_boolean_T(*dst, numElDst);
  for (i = 0; i < numElSrc; i++) {
    (*dst)->data[i] = (*src)->data[i];
  }
}

//
// Arguments    : emxArray_int32_T **dst
//                emxArray_int32_T * const *src
// Return Type  : void
//
static void emxCopy_int32_T(emxArray_int32_T **dst, emxArray_int32_T * const
  *src)
{
  int numElDst;
  int numElSrc;
  int i;
  numElDst = 1;
  numElSrc = 1;
  for (i = 0; i < (*dst)->numDimensions; i++) {
    numElDst *= (*dst)->size[i];
    numElSrc *= (*src)->size[i];
  }

  for (i = 0; i < (*dst)->numDimensions; i++) {
    (*dst)->size[i] = (*src)->size[i];
  }

  emxEnsureCapacity_int32_T(*dst, numElDst);
  for (i = 0; i < numElSrc; i++) {
    (*dst)->data[i] = (*src)->data[i];
  }
}

//
// Arguments    : emxArray_real_T **dst
//                emxArray_real_T * const *src
// Return Type  : void
//
static void emxCopy_real_T(emxArray_real_T **dst, emxArray_real_T * const *src)
{
  int numElDst;
  int numElSrc;
  int i;
  numElDst = 1;
  numElSrc = 1;
  for (i = 0; i < (*dst)->numDimensions; i++) {
    numElDst *= (*dst)->size[i];
    numElSrc *= (*src)->size[i];
  }

  for (i = 0; i < (*dst)->numDimensions; i++) {
    (*dst)->size[i] = (*src)->size[i];
  }

  emxEnsureCapacity_real_T(*dst, numElDst);
  for (i = 0; i < numElSrc; i++) {
    (*dst)->data[i] = (*src)->data[i];
  }
}

//
// Arguments    : cell_2 *pStruct
// Return Type  : void
//
static void emxFreeStruct_cell_2(cell_2 *pStruct)
{
  emxFree_real_T(&pStruct->f2);
}

//
// Arguments    : cell_2 *pStruct
// Return Type  : void
//
static void emxInitStruct_cell_2(cell_2 *pStruct)
{
  emxInit_real_T(&pStruct->f2, 2);
}

//
// Arguments    : coder_internal_ref *pStruct
// Return Type  : void
//
void c_emxFreeStruct_coder_internal_(coder_internal_ref *pStruct)
{
  emxFree_real_T(&pStruct->contents);
}

//
// Arguments    : coder_internal_ref *pStruct
// Return Type  : void
//
void c_emxInitStruct_coder_internal_(coder_internal_ref *pStruct)
{
  emxInit_real_T(&pStruct->contents, 2);
}

//
// Arguments    : d_struct_T *dst
//                const d_struct_T *src
// Return Type  : void
//
void emxCopyStruct_struct_T(d_struct_T *dst, const d_struct_T *src)
{
  c_emxCopyStruct_coder_internal_(&dst->nonlin, &src->nonlin);
  dst->f_1 = src->f_1;
  emxCopy_real_T(&dst->cIneq_1, &src->cIneq_1);
  emxCopy_real_T(&dst->cEq_1, &src->cEq_1);
  dst->f_2 = src->f_2;
  emxCopy_real_T(&dst->cIneq_2, &src->cIneq_2);
  emxCopy_real_T(&dst->cEq_2, &src->cEq_2);
  dst->nVar = src->nVar;
  dst->mIneq = src->mIneq;
  dst->mEq = src->mEq;
  dst->numEvals = src->numEvals;
  dst->SpecifyObjectiveGradient = src->SpecifyObjectiveGradient;
  dst->SpecifyConstraintGradient = src->SpecifyConstraintGradient;
  emxCopy_boolean_T(&dst->hasLB, &src->hasLB);
  emxCopy_boolean_T(&dst->hasUB, &src->hasUB);
  dst->hasBounds = src->hasBounds;
  dst->FiniteDifferenceType = src->FiniteDifferenceType;
}

//
// Arguments    : e_struct_T *dst
//                const e_struct_T *src
// Return Type  : void
//
void emxCopyStruct_struct_T1(e_struct_T *dst, const e_struct_T *src)
{
  dst->nVarMax = src->nVarMax;
  dst->mNonlinIneq = src->mNonlinIneq;
  dst->mNonlinEq = src->mNonlinEq;
  dst->mIneq = src->mIneq;
  dst->mEq = src->mEq;
  dst->iNonIneq0 = src->iNonIneq0;
  dst->iNonEq0 = src->iNonEq0;
  dst->sqpFval = src->sqpFval;
  dst->sqpFval_old = src->sqpFval_old;
  emxCopy_real_T(&dst->xstarsqp, &src->xstarsqp);
  emxCopy_real_T(&dst->xstarsqp_old, &src->xstarsqp_old);
  emxCopy_real_T(&dst->cIneq, &src->cIneq);
  emxCopy_real_T(&dst->cIneq_old, &src->cIneq_old);
  emxCopy_real_T(&dst->cEq, &src->cEq);
  emxCopy_real_T(&dst->cEq_old, &src->cEq_old);
  emxCopy_real_T(&dst->grad, &src->grad);
  emxCopy_real_T(&dst->grad_old, &src->grad_old);
  dst->FunctionEvaluations = src->FunctionEvaluations;
  dst->sqpIterations = src->sqpIterations;
  dst->sqpExitFlag = src->sqpExitFlag;
  emxCopy_real_T(&dst->lambdasqp, &src->lambdasqp);
  emxCopy_real_T(&dst->lambdasqp_old, &src->lambdasqp_old);
  dst->steplength = src->steplength;
  emxCopy_real_T(&dst->delta_x, &src->delta_x);
  emxCopy_real_T(&dst->socDirection, &src->socDirection);
  emxCopy_real_T(&dst->lambda_old, &src->lambda_old);
  emxCopy_int32_T(&dst->workingset_old, &src->workingset_old);
  emxCopy_real_T(&dst->JacCineqTrans_old, &src->JacCineqTrans_old);
  emxCopy_real_T(&dst->JacCeqTrans_old, &src->JacCeqTrans_old);
  emxCopy_real_T(&dst->gradLag, &src->gradLag);
  emxCopy_real_T(&dst->delta_gradLag, &src->delta_gradLag);
  emxCopy_real_T(&dst->xstar, &src->xstar);
  dst->fstar = src->fstar;
  emxCopy_real_T(&dst->lambda, &src->lambda);
  dst->state = src->state;
  dst->maxConstr = src->maxConstr;
  dst->iterations = src->iterations;
  emxCopy_real_T(&dst->searchDir, &src->searchDir);
}

//
// Arguments    : h_struct_T *dst
//                const h_struct_T *src
// Return Type  : void
//
void emxCopyStruct_struct_T2(h_struct_T *dst, const h_struct_T *src)
{
  dst->mConstr = src->mConstr;
  dst->mConstrOrig = src->mConstrOrig;
  dst->mConstrMax = src->mConstrMax;
  dst->nVar = src->nVar;
  dst->nVarOrig = src->nVarOrig;
  dst->nVarMax = src->nVarMax;
  dst->ldA = src->ldA;
  emxCopy_real_T(&dst->Aineq, &src->Aineq);
  emxCopy_real_T(&dst->bineq, &src->bineq);
  emxCopy_real_T(&dst->Aeq, &src->Aeq);
  emxCopy_real_T(&dst->beq, &src->beq);
  emxCopy_real_T(&dst->lb, &src->lb);
  emxCopy_real_T(&dst->ub, &src->ub);
  emxCopy_int32_T(&dst->indexLB, &src->indexLB);
  emxCopy_int32_T(&dst->indexUB, &src->indexUB);
  emxCopy_int32_T(&dst->indexFixed, &src->indexFixed);
  dst->mEqRemoved = src->mEqRemoved;
  emxCopy_int32_T(&dst->indexEqRemoved, &src->indexEqRemoved);
  emxCopy_real_T(&dst->ATwset, &src->ATwset);
  emxCopy_real_T(&dst->bwset, &src->bwset);
  dst->nActiveConstr = src->nActiveConstr;
  emxCopy_real_T(&dst->maxConstrWorkspace, &src->maxConstrWorkspace);
  emxCopyMatrix_int32_T(dst->sizes, src->sizes);
  emxCopyMatrix_int32_T(dst->sizesNormal, src->sizesNormal);
  emxCopyMatrix_int32_T(dst->sizesPhaseOne, src->sizesPhaseOne);
  emxCopyMatrix_int32_T(dst->sizesRegularized, src->sizesRegularized);
  emxCopyMatrix_int32_T(dst->sizesRegPhaseOne, src->sizesRegPhaseOne);
  emxCopyMatrix_int32_T1(dst->isActiveIdx, src->isActiveIdx);
  emxCopyMatrix_int32_T1(dst->isActiveIdxNormal, src->isActiveIdxNormal);
  emxCopyMatrix_int32_T1(dst->isActiveIdxPhaseOne, src->isActiveIdxPhaseOne);
  emxCopyMatrix_int32_T1(dst->isActiveIdxRegularized,
    src->isActiveIdxRegularized);
  emxCopyMatrix_int32_T1(dst->isActiveIdxRegPhaseOne,
    src->isActiveIdxRegPhaseOne);
  emxCopy_boolean_T(&dst->isActiveConstr, &src->isActiveConstr);
  emxCopy_int32_T(&dst->Wid, &src->Wid);
  emxCopy_int32_T(&dst->Wlocalidx, &src->Wlocalidx);
  emxCopyMatrix_int32_T(dst->nWConstr, src->nWConstr);
  dst->probType = src->probType;
  dst->SLACK0 = src->SLACK0;
}

//
// Arguments    : emxArray_boolean_T *emxArray
//                int oldNumel
// Return Type  : void
//
void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int oldNumel)
{
  int newNumel;
  int i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }

    newData = std::calloc(static_cast<unsigned int>(i), sizeof(bool));
    if (emxArray->data != NULL) {
      std::memcpy(newData, emxArray->data, sizeof(bool) * oldNumel);
      if (emxArray->canFreeData) {
        std::free(emxArray->data);
      }
    }

    emxArray->data = (bool *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

//
// Arguments    : emxArray_int32_T *emxArray
//                int oldNumel
// Return Type  : void
//
void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel)
{
  int newNumel;
  int i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }

    newData = std::calloc(static_cast<unsigned int>(i), sizeof(int));
    if (emxArray->data != NULL) {
      std::memcpy(newData, emxArray->data, sizeof(int) * oldNumel);
      if (emxArray->canFreeData) {
        std::free(emxArray->data);
      }
    }

    emxArray->data = (int *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

//
// Arguments    : emxArray_int8_T *emxArray
//                int oldNumel
// Return Type  : void
//
void emxEnsureCapacity_int8_T(emxArray_int8_T *emxArray, int oldNumel)
{
  int newNumel;
  int i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }

    newData = std::calloc(static_cast<unsigned int>(i), sizeof(signed char));
    if (emxArray->data != NULL) {
      std::memcpy(newData, emxArray->data, sizeof(signed char) * oldNumel);
      if (emxArray->canFreeData) {
        std::free(emxArray->data);
      }
    }

    emxArray->data = (signed char *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

//
// Arguments    : emxArray_real_T *emxArray
//                int oldNumel
// Return Type  : void
//
void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel)
{
  int newNumel;
  int i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }

    newData = std::calloc(static_cast<unsigned int>(i), sizeof(double));
    if (emxArray->data != NULL) {
      std::memcpy(newData, emxArray->data, sizeof(double) * oldNumel);
      if (emxArray->canFreeData) {
        std::free(emxArray->data);
      }
    }

    emxArray->data = (double *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

//
// Arguments    : e_struct_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct_T(e_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->xstarsqp);
  emxFree_real_T(&pStruct->xstarsqp_old);
  emxFree_real_T(&pStruct->cIneq);
  emxFree_real_T(&pStruct->cIneq_old);
  emxFree_real_T(&pStruct->cEq);
  emxFree_real_T(&pStruct->cEq_old);
  emxFree_real_T(&pStruct->grad);
  emxFree_real_T(&pStruct->grad_old);
  emxFree_real_T(&pStruct->lambdasqp);
  emxFree_real_T(&pStruct->lambdasqp_old);
  emxFree_real_T(&pStruct->delta_x);
  emxFree_real_T(&pStruct->socDirection);
  emxFree_real_T(&pStruct->lambda_old);
  emxFree_int32_T(&pStruct->workingset_old);
  emxFree_real_T(&pStruct->JacCineqTrans_old);
  emxFree_real_T(&pStruct->JacCeqTrans_old);
  emxFree_real_T(&pStruct->gradLag);
  emxFree_real_T(&pStruct->delta_gradLag);
  emxFree_real_T(&pStruct->xstar);
  emxFree_real_T(&pStruct->lambda);
  emxFree_real_T(&pStruct->searchDir);
}

//
// Arguments    : f_struct_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct_T1(f_struct_T *pStruct)
{
  d_emxFreeStruct_coder_internal_(&pStruct->nonlcon);
}

//
// Arguments    : d_struct_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct_T2(d_struct_T *pStruct)
{
  d_emxFreeStruct_coder_internal_(&pStruct->nonlin);
  emxFree_real_T(&pStruct->cIneq_1);
  emxFree_real_T(&pStruct->cEq_1);
  emxFree_real_T(&pStruct->cIneq_2);
  emxFree_real_T(&pStruct->cEq_2);
  emxFree_boolean_T(&pStruct->hasLB);
  emxFree_boolean_T(&pStruct->hasUB);
}

//
// Arguments    : g_struct_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct_T3(g_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->grad);
  emxFree_real_T(&pStruct->Hx);
}

//
// Arguments    : c_struct_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct_T4(c_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->workspace_double);
  emxFree_int32_T(&pStruct->workspace_int);
  emxFree_int32_T(&pStruct->workspace_sort);
}

//
// Arguments    : h_struct_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct_T5(h_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->Aineq);
  emxFree_real_T(&pStruct->bineq);
  emxFree_real_T(&pStruct->Aeq);
  emxFree_real_T(&pStruct->beq);
  emxFree_real_T(&pStruct->lb);
  emxFree_real_T(&pStruct->ub);
  emxFree_int32_T(&pStruct->indexLB);
  emxFree_int32_T(&pStruct->indexUB);
  emxFree_int32_T(&pStruct->indexFixed);
  emxFree_int32_T(&pStruct->indexEqRemoved);
  emxFree_real_T(&pStruct->ATwset);
  emxFree_real_T(&pStruct->bwset);
  emxFree_real_T(&pStruct->maxConstrWorkspace);
  emxFree_boolean_T(&pStruct->isActiveConstr);
  emxFree_int32_T(&pStruct->Wid);
  emxFree_int32_T(&pStruct->Wlocalidx);
}

//
// Arguments    : i_struct_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct_T6(i_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->QR);
  emxFree_real_T(&pStruct->Q);
  emxFree_int32_T(&pStruct->jpvt);
  emxFree_real_T(&pStruct->tau);
}

//
// Arguments    : k_struct_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct_T7(k_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->UU);
  emxFree_real_T(&pStruct->x);
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
// Return Type  : void
//
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_boolean_T *)NULL) {
    if (((*pEmxArray)->data != (bool *)NULL) && (*pEmxArray)->canFreeData) {
      std::free((*pEmxArray)->data);
    }

    std::free((*pEmxArray)->size);
    std::free(*pEmxArray);
    *pEmxArray = (emxArray_boolean_T *)NULL;
  }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
// Return Type  : void
//
void emxFree_int32_T(emxArray_int32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int32_T *)NULL) {
    if (((*pEmxArray)->data != (int *)NULL) && (*pEmxArray)->canFreeData) {
      std::free((*pEmxArray)->data);
    }

    std::free((*pEmxArray)->size);
    std::free(*pEmxArray);
    *pEmxArray = (emxArray_int32_T *)NULL;
  }
}

//
// Arguments    : emxArray_int8_T **pEmxArray
// Return Type  : void
//
void emxFree_int8_T(emxArray_int8_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int8_T *)NULL) {
    if (((*pEmxArray)->data != (signed char *)NULL) && (*pEmxArray)->canFreeData)
    {
      std::free((*pEmxArray)->data);
    }

    std::free((*pEmxArray)->size);
    std::free(*pEmxArray);
    *pEmxArray = (emxArray_int8_T *)NULL;
  }
}

//
// Arguments    : emxArray_real_T **pEmxArray
// Return Type  : void
//
void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (double *)NULL) && (*pEmxArray)->canFreeData) {
      std::free((*pEmxArray)->data);
    }

    std::free((*pEmxArray)->size);
    std::free(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

//
// Arguments    : e_struct_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct_T(e_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->xstarsqp, 2);
  emxInit_real_T(&pStruct->xstarsqp_old, 2);
  emxInit_real_T(&pStruct->cIneq, 1);
  emxInit_real_T(&pStruct->cIneq_old, 1);
  emxInit_real_T(&pStruct->cEq, 1);
  emxInit_real_T(&pStruct->cEq_old, 1);
  emxInit_real_T(&pStruct->grad, 1);
  emxInit_real_T(&pStruct->grad_old, 1);
  emxInit_real_T(&pStruct->lambdasqp, 1);
  emxInit_real_T(&pStruct->lambdasqp_old, 1);
  emxInit_real_T(&pStruct->delta_x, 1);
  emxInit_real_T(&pStruct->socDirection, 1);
  emxInit_real_T(&pStruct->lambda_old, 1);
  emxInit_int32_T(&pStruct->workingset_old, 1);
  emxInit_real_T(&pStruct->JacCineqTrans_old, 2);
  emxInit_real_T(&pStruct->JacCeqTrans_old, 2);
  emxInit_real_T(&pStruct->gradLag, 1);
  emxInit_real_T(&pStruct->delta_gradLag, 1);
  emxInit_real_T(&pStruct->xstar, 1);
  emxInit_real_T(&pStruct->lambda, 1);
  emxInit_real_T(&pStruct->searchDir, 1);
}

//
// Arguments    : f_struct_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct_T1(f_struct_T *pStruct)
{
  d_emxInitStruct_coder_internal_(&pStruct->nonlcon);
}

//
// Arguments    : d_struct_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct_T2(d_struct_T *pStruct)
{
  d_emxInitStruct_coder_internal_(&pStruct->nonlin);
  emxInit_real_T(&pStruct->cIneq_1, 1);
  emxInit_real_T(&pStruct->cEq_1, 1);
  emxInit_real_T(&pStruct->cIneq_2, 1);
  emxInit_real_T(&pStruct->cEq_2, 1);
  emxInit_boolean_T(&pStruct->hasLB, 1);
  emxInit_boolean_T(&pStruct->hasUB, 1);
}

//
// Arguments    : g_struct_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct_T3(g_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->grad, 1);
  emxInit_real_T(&pStruct->Hx, 1);
}

//
// Arguments    : c_struct_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct_T4(c_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->workspace_double, 2);
  emxInit_int32_T(&pStruct->workspace_int, 1);
  emxInit_int32_T(&pStruct->workspace_sort, 1);
}

//
// Arguments    : h_struct_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct_T5(h_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->Aineq, 2);
  emxInit_real_T(&pStruct->bineq, 2);
  emxInit_real_T(&pStruct->Aeq, 2);
  emxInit_real_T(&pStruct->beq, 2);
  emxInit_real_T(&pStruct->lb, 1);
  emxInit_real_T(&pStruct->ub, 1);
  emxInit_int32_T(&pStruct->indexLB, 1);
  emxInit_int32_T(&pStruct->indexUB, 1);
  emxInit_int32_T(&pStruct->indexFixed, 1);
  emxInit_int32_T(&pStruct->indexEqRemoved, 1);
  emxInit_real_T(&pStruct->ATwset, 2);
  emxInit_real_T(&pStruct->bwset, 1);
  emxInit_real_T(&pStruct->maxConstrWorkspace, 1);
  emxInit_boolean_T(&pStruct->isActiveConstr, 1);
  emxInit_int32_T(&pStruct->Wid, 1);
  emxInit_int32_T(&pStruct->Wlocalidx, 1);
}

//
// Arguments    : i_struct_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct_T6(i_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->QR, 2);
  emxInit_real_T(&pStruct->Q, 2);
  emxInit_int32_T(&pStruct->jpvt, 1);
  emxInit_real_T(&pStruct->tau, 1);
}

//
// Arguments    : k_struct_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct_T7(k_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->UU, 2);
  emxInit_real_T(&pStruct->x, 1);
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions)
{
  emxArray_boolean_T *emxArray;
  int i;
  *pEmxArray = (emxArray_boolean_T *)std::malloc(sizeof(emxArray_boolean_T));
  emxArray = *pEmxArray;
  emxArray->data = (bool *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)std::malloc(sizeof(int) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions)
{
  emxArray_int32_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int32_T *)std::malloc(sizeof(emxArray_int32_T));
  emxArray = *pEmxArray;
  emxArray->data = (int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)std::malloc(sizeof(int) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_int8_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_int8_T(emxArray_int8_T **pEmxArray, int numDimensions)
{
  emxArray_int8_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int8_T *)std::malloc(sizeof(emxArray_int8_T));
  emxArray = *pEmxArray;
  emxArray->data = (signed char *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)std::malloc(sizeof(int) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_real_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)std::malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)std::malloc(sizeof(int) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// File trailer for timeOpt6DofGen_emxutil.cpp
//
// [EOF]
//
