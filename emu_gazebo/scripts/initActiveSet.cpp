//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: initActiveSet.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "initActiveSet.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : h_struct_T *obj
// Return Type  : void
//
void initActiveSet(h_struct_T *obj)
{
  int idxFillStart;
  int iy0;
  int idx_global;
  int nWFixed;
  int idx_local;
  int ix0;
  int n;
  int k;
  int b_k;
  setProblemType(obj, 3);
  idxFillStart = obj->isActiveIdx[2];
  iy0 = obj->mConstrMax;
  for (idx_global = idxFillStart; idx_global <= iy0; idx_global++) {
    obj->isActiveConstr->data[idx_global - 1] = false;
  }

  obj->nWConstr[0] = obj->sizes[0];
  obj->nWConstr[1] = obj->sizes[1];
  obj->nWConstr[2] = 0;
  obj->nWConstr[3] = 0;
  obj->nWConstr[4] = 0;
  obj->nActiveConstr = obj->nWConstr[0] + obj->nWConstr[1];
  nWFixed = obj->sizes[0];
  for (idx_local = 0; idx_local < nWFixed; idx_local++) {
    obj->Wid->data[idx_local] = 1;
    obj->Wlocalidx->data[idx_local] = idx_local + 1;
    obj->isActiveConstr->data[idx_local] = true;
    idxFillStart = obj->indexFixed->data[idx_local] - 1;
    iy0 = obj->indexFixed->data[idx_local];
    for (idx_global = 0; idx_global <= iy0 - 2; idx_global++) {
      obj->ATwset->data[idx_global + obj->ATwset->size[0] * idx_local] = 0.0;
    }

    obj->ATwset->data[idxFillStart + obj->ATwset->size[0] * idx_local] = 1.0;
    iy0 = idxFillStart + 2;
    ix0 = obj->nVar;
    for (idx_global = iy0; idx_global <= ix0; idx_global++) {
      obj->ATwset->data[(idx_global + obj->ATwset->size[0] * idx_local) - 1] =
        0.0;
    }

    obj->bwset->data[idx_local] = obj->ub->data[idxFillStart];
  }

  idxFillStart = obj->sizes[1];
  for (idx_local = 0; idx_local < idxFillStart; idx_local++) {
    idx_global = nWFixed + idx_local;
    obj->Wid->data[idx_global] = 2;
    obj->Wlocalidx->data[idx_global] = idx_local + 1;
    obj->isActiveConstr->data[idx_global] = true;
    ix0 = obj->ldA * idx_local;
    iy0 = obj->ldA * idx_global;
    n = obj->nVar;
    for (k = 0; k < n; k++) {
      b_k = k + 1;
      obj->ATwset->data[(iy0 + b_k) - 1] = obj->Aeq->data[(ix0 + b_k) - 1];
    }

    obj->bwset->data[idx_global] = obj->beq->data[idx_local];
  }
}

//
// File trailer for initActiveSet.cpp
//
// [EOF]
//
