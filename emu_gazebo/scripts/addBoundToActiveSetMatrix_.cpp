//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: addBoundToActiveSetMatrix_.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "addBoundToActiveSetMatrix_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : h_struct_T *obj
//                int TYPE
//                int idx_local
// Return Type  : void
//
void addBoundToActiveSetMatrix_(h_struct_T *obj, int TYPE, int idx_local)
{
  int i;
  int idx_bnd_local;
  int idx;
  int i1;
  obj->nWConstr[TYPE - 1]++;
  obj->isActiveConstr->data[(obj->isActiveIdx[TYPE - 1] + idx_local) - 2] = true;
  obj->nActiveConstr++;
  obj->Wid->data[obj->nActiveConstr - 1] = TYPE;
  obj->Wlocalidx->data[obj->nActiveConstr - 1] = idx_local;
  i = obj->nActiveConstr - 1;
  switch (TYPE) {
   case 5:
    idx_bnd_local = obj->indexUB->data[idx_local - 1];
    obj->bwset->data[obj->nActiveConstr - 1] = obj->ub->data[idx_bnd_local - 1];
    break;

   default:
    idx_bnd_local = obj->indexLB->data[idx_local - 1];
    obj->bwset->data[obj->nActiveConstr - 1] = obj->lb->data[idx_bnd_local - 1];
    break;
  }

  for (idx = 0; idx <= idx_bnd_local - 2; idx++) {
    obj->ATwset->data[idx + obj->ATwset->size[0] * i] = 0.0;
  }

  obj->ATwset->data[(idx_bnd_local + obj->ATwset->size[0] * (obj->nActiveConstr
    - 1)) - 1] = 2.0 * static_cast<double>((TYPE == 5)) - 1.0;
  idx_bnd_local++;
  i1 = obj->nVar;
  for (idx = idx_bnd_local; idx <= i1; idx++) {
    obj->ATwset->data[(idx + obj->ATwset->size[0] * i) - 1] = 0.0;
  }

  switch (obj->probType) {
   case 3:
   case 2:
    break;

   default:
    obj->ATwset->data[(obj->nVar + obj->ATwset->size[0] * (obj->nActiveConstr -
      1)) - 1] = -1.0;
    break;
  }
}

//
// File trailer for addBoundToActiveSetMatrix_.cpp
//
// [EOF]
//
