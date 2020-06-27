//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: removeConstr.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : h_struct_T *obj
//                int idx_global
// Return Type  : void
//
void removeConstr(h_struct_T *obj, int idx_global)
{
  int TYPE_tmp;
  int i;
  int idx;
  TYPE_tmp = obj->Wid->data[idx_global - 1] - 1;
  obj->isActiveConstr->data[(obj->isActiveIdx[TYPE_tmp] + obj->Wlocalidx->
    data[idx_global - 1]) - 2] = false;
  obj->Wid->data[idx_global - 1] = obj->Wid->data[obj->nActiveConstr - 1];
  obj->Wlocalidx->data[idx_global - 1] = obj->Wlocalidx->data[obj->nActiveConstr
    - 1];
  i = obj->nVar;
  for (idx = 0; idx < i; idx++) {
    obj->ATwset->data[idx + obj->ATwset->size[0] * (idx_global - 1)] =
      obj->ATwset->data[idx + obj->ATwset->size[0] * (obj->nActiveConstr - 1)];
  }

  obj->bwset->data[idx_global - 1] = obj->bwset->data[obj->nActiveConstr - 1];
  obj->nActiveConstr--;
  obj->nWConstr[TYPE_tmp]--;
}

//
// File trailer for removeConstr.cpp
//
// [EOF]
//
