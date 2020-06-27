//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: addAeqConstr.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "addAeqConstr.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : h_struct_T *obj
//                int idx_local
// Return Type  : void
//
void addAeqConstr(h_struct_T *obj, int idx_local)
{
  int totalEq;
  int ix0;
  int idx;
  int n;
  int k;
  int b_k;
  totalEq = obj->nWConstr[0] + obj->nWConstr[1];
  if ((obj->nActiveConstr == totalEq) && (idx_local > obj->nWConstr[1])) {
    obj->nWConstr[1]++;
    obj->isActiveConstr->data[(obj->isActiveIdx[1] + idx_local) - 2] = true;
    obj->nActiveConstr++;
    obj->Wid->data[obj->nActiveConstr - 1] = 2;
    obj->Wlocalidx->data[obj->nActiveConstr - 1] = idx_local;
    ix0 = obj->ldA * (idx_local - 1);
    idx = obj->ldA * (obj->nActiveConstr - 1);
    n = obj->nVar;
    for (k = 0; k < n; k++) {
      b_k = k + 1;
      obj->ATwset->data[(idx + b_k) - 1] = obj->Aeq->data[(ix0 + b_k) - 1];
    }

    obj->bwset->data[obj->nActiveConstr - 1] = obj->beq->data[idx_local - 1];
  } else {
    obj->nActiveConstr++;
    obj->Wid->data[obj->nActiveConstr - 1] = obj->Wid->data[totalEq];
    obj->Wlocalidx->data[obj->nActiveConstr - 1] = obj->Wlocalidx->data[totalEq];
    ix0 = obj->nVar;
    for (idx = 0; idx < ix0; idx++) {
      obj->ATwset->data[idx + obj->ATwset->size[0] * (obj->nActiveConstr - 1)] =
        obj->ATwset->data[idx + obj->ATwset->size[0] * totalEq];
    }

    obj->bwset->data[obj->nActiveConstr - 1] = obj->bwset->data[totalEq];
    obj->nWConstr[1]++;
    obj->isActiveConstr->data[(obj->isActiveIdx[1] + idx_local) - 2] = true;
    obj->Wid->data[totalEq] = 2;
    obj->Wlocalidx->data[totalEq] = idx_local;
    ix0 = obj->ldA * (idx_local - 1);
    idx = obj->ldA * totalEq;
    n = obj->nVar;
    for (k = 0; k < n; k++) {
      b_k = k + 1;
      obj->ATwset->data[(idx + b_k) - 1] = obj->Aeq->data[(ix0 + b_k) - 1];
    }

    obj->bwset->data[totalEq] = obj->beq->data[idx_local - 1];
  }
}

//
// File trailer for addAeqConstr.cpp
//
// [EOF]
//
