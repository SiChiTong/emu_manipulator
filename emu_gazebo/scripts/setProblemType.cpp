//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: setProblemType.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "setProblemType.h"
#include "modifyOverheadPhaseOne_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : h_struct_T *obj
//                int PROBLEM_TYPE
// Return Type  : void
//
void setProblemType(h_struct_T *obj, int PROBLEM_TYPE)
{
  int i;
  int mEq;
  int offsetIneq_tmp_tmp;
  int offsetEq1;
  int offsetEq2;
  int idx_col;
  int i1;
  int i2;
  int idxGlobalColStart;
  int idx_row;
  int b_idx_col;
  switch (PROBLEM_TYPE) {
   case 3:
    obj->nVar = obj->nVarOrig;
    obj->mConstr = obj->mConstrOrig;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesNormal[i];
    }

    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxNormal[i];
    }
    break;

   case 1:
    obj->nVar = obj->nVarOrig + 1;
    obj->mConstr = obj->mConstrOrig + 1;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesPhaseOne[i];
    }

    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxPhaseOne[i];
    }

    modifyOverheadPhaseOne_(obj);
    break;

   case 2:
    obj->nVar = obj->nVarMax - 1;
    obj->mConstr = obj->mConstrMax - 1;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesRegularized[i];
    }

    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxRegularized[i];
    }

    if (obj->probType != 4) {
      mEq = obj->sizes[1];
      offsetIneq_tmp_tmp = obj->nVarOrig + 1;
      offsetEq1 = obj->nVarOrig + 11;
      offsetEq2 = (obj->nVarOrig + obj->sizes[1]) + 11;
      i = obj->sizes[0];
      for (idx_col = 0; idx_col < i; idx_col++) {
        i1 = obj->nVarOrig + 1;
        i2 = obj->nVar;
        for (idx_row = i1; idx_row <= i2; idx_row++) {
          obj->ATwset->data[(idx_row + obj->ATwset->size[0] * idx_col) - 1] =
            0.0;
        }
      }

      for (idx_col = 0; idx_col < 12; idx_col++) {
        i = offsetIneq_tmp_tmp + idx_col;
        i1 = i - 1;
        for (idx_row = offsetIneq_tmp_tmp; idx_row <= i1; idx_row++) {
          obj->Aineq->data[(idx_row + obj->Aineq->size[0] * idx_col) - 1] = 0.0;
        }

        obj->Aineq->data[i1 + obj->Aineq->size[0] * idx_col] = -1.0;
        i++;
        i1 = obj->nVar;
        for (idx_row = i; idx_row <= i1; idx_row++) {
          obj->Aineq->data[(idx_row + obj->Aineq->size[0] * idx_col) - 1] = 0.0;
        }
      }

      idxGlobalColStart = obj->isActiveIdx[1] - 2;
      for (idx_col = 0; idx_col < mEq; idx_col++) {
        b_idx_col = idx_col + 1;
        for (idx_row = offsetIneq_tmp_tmp; idx_row <= offsetEq1 + 1; idx_row++)
        {
          obj->Aeq->data[(idx_row + obj->Aeq->size[0] * (b_idx_col - 1)) - 1] =
            0.0;
          obj->ATwset->data[(idx_row + obj->ATwset->size[0] * (idxGlobalColStart
            + b_idx_col)) - 1] = 0.0;
        }

        i = offsetEq1 + 2;
        i1 = offsetEq1 + b_idx_col;
        for (idx_row = i; idx_row <= i1; idx_row++) {
          obj->Aeq->data[(idx_row + obj->Aeq->size[0] * (b_idx_col - 1)) - 1] =
            0.0;
          obj->ATwset->data[(idx_row + obj->ATwset->size[0] * (idxGlobalColStart
            + b_idx_col)) - 1] = 0.0;
        }

        obj->Aeq->data[i1 + obj->Aeq->size[0] * (b_idx_col - 1)] = -1.0;
        i = idxGlobalColStart + b_idx_col;
        obj->ATwset->data[i1 + obj->ATwset->size[0] * i] = -1.0;
        i1 += 2;
        for (idx_row = i1; idx_row <= offsetEq2 + 1; idx_row++) {
          obj->Aeq->data[(idx_row + obj->Aeq->size[0] * (b_idx_col - 1)) - 1] =
            0.0;
          obj->ATwset->data[(idx_row + obj->ATwset->size[0] * i) - 1] = 0.0;
        }

        i1 = offsetEq2 + 2;
        i2 = offsetEq2 + b_idx_col;
        for (idx_row = i1; idx_row <= i2; idx_row++) {
          obj->Aeq->data[(idx_row + obj->Aeq->size[0] * (b_idx_col - 1)) - 1] =
            0.0;
          obj->ATwset->data[(idx_row + obj->ATwset->size[0] * i) - 1] = 0.0;
        }

        obj->Aeq->data[i2 + obj->Aeq->size[0] * (b_idx_col - 1)] = 1.0;
        obj->ATwset->data[i2 + obj->ATwset->size[0] * i] = 1.0;
        i1 = i2 + 2;
        i2 = obj->nVar;
        for (idx_row = i1; idx_row <= i2; idx_row++) {
          obj->Aeq->data[(idx_row + obj->Aeq->size[0] * (b_idx_col - 1)) - 1] =
            0.0;
          obj->ATwset->data[(idx_row + obj->ATwset->size[0] * i) - 1] = 0.0;
        }
      }

      mEq = obj->nVarOrig;
      i = obj->sizesNormal[3] + 1;
      i1 = obj->sizesRegularized[3];
      for (offsetEq1 = i; offsetEq1 <= i1; offsetEq1++) {
        mEq++;
        obj->indexLB->data[offsetEq1 - 1] = mEq;
      }

      i = obj->nVarOrig + 1;
      i1 = (obj->nVarOrig + (obj->sizes[1] << 1)) + 12;
      for (offsetEq1 = i; offsetEq1 <= i1; offsetEq1++) {
        obj->lb->data[offsetEq1 - 1] = 0.0;
      }

      offsetEq1 = obj->isActiveIdx[2];
      i = obj->nActiveConstr;
      for (idx_col = offsetEq1; idx_col <= i; idx_col++) {
        switch (obj->Wid->data[idx_col - 1]) {
         case 3:
          mEq = obj->Wlocalidx->data[idx_col - 1];
          i1 = offsetIneq_tmp_tmp + mEq;
          i2 = i1 - 2;
          for (idx_row = offsetIneq_tmp_tmp; idx_row <= i2; idx_row++) {
            obj->ATwset->data[(idx_row + obj->ATwset->size[0] * (idx_col - 1)) -
              1] = 0.0;
          }

          obj->ATwset->data[(i1 + obj->ATwset->size[0] * (idx_col - 1)) - 2] =
            -1.0;
          i2 = obj->nVar;
          for (idx_row = i1; idx_row <= i2; idx_row++) {
            obj->ATwset->data[(idx_row + obj->ATwset->size[0] * (idx_col - 1)) -
              1] = 0.0;
          }
          break;

         default:
          i1 = obj->nVar;
          for (idx_row = offsetIneq_tmp_tmp; idx_row <= i1; idx_row++) {
            obj->ATwset->data[(idx_row + obj->ATwset->size[0] * (idx_col - 1)) -
              1] = 0.0;
          }
          break;
        }
      }
    }
    break;

   default:
    obj->nVar = obj->nVarMax;
    obj->mConstr = obj->mConstrMax;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesRegPhaseOne[i];
    }

    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxRegPhaseOne[i];
    }

    modifyOverheadPhaseOne_(obj);
    break;
  }

  obj->probType = PROBLEM_TYPE;
}

//
// File trailer for setProblemType.cpp
//
// [EOF]
//
