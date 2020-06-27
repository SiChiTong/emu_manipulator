//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: addAineqConstr.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "addAineqConstr.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : h_struct_T *obj
//                int idx_local
// Return Type  : void
//
void addAineqConstr(h_struct_T *obj, int idx_local)
{
  int ix0;
  int iy0;
  int n;
  int k;
  int b_k;
  obj->nWConstr[2]++;
  obj->isActiveConstr->data[(obj->isActiveIdx[2] + idx_local) - 2] = true;
  obj->nActiveConstr++;
  obj->Wid->data[obj->nActiveConstr - 1] = 3;
  obj->Wlocalidx->data[obj->nActiveConstr - 1] = idx_local;
  ix0 = obj->ldA * (idx_local - 1);
  iy0 = obj->ldA * (obj->nActiveConstr - 1);
  n = obj->nVar;
  for (k = 0; k < n; k++) {
    b_k = k + 1;
    obj->ATwset->data[(iy0 + b_k) - 1] = obj->Aineq->data[(ix0 + b_k) - 1];
  }

  obj->bwset->data[obj->nActiveConstr - 1] = obj->bineq[idx_local - 1];
}

//
// File trailer for addAineqConstr.cpp
//
// [EOF]
//
