//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: modifyOverheadPhaseOne_.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "modifyOverheadPhaseOne_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : h_struct_T *obj
// Return Type  : void
//
void modifyOverheadPhaseOne_(h_struct_T *obj)
{
  int i;
  int idx;
  int idxStartIneq;
  i = obj->sizes[0];
  for (idx = 0; idx < i; idx++) {
    obj->ATwset->data[(obj->nVar + obj->ATwset->size[0] * idx) - 1] = 0.0;
  }

  i = obj->sizes[1];
  for (idx = 0; idx < i; idx++) {
    obj->Aeq->data[(obj->nVar + obj->Aeq->size[0] * idx) - 1] = 0.0;
    obj->ATwset->data[(obj->nVar + obj->ATwset->size[0] * ((obj->isActiveIdx[1]
      + idx) - 1)) - 1] = 0.0;
  }

  for (idx = 0; idx < 12; idx++) {
    obj->Aineq->data[(obj->nVar + obj->Aineq->size[0] * idx) - 1] = -1.0;
  }

  obj->indexLB->data[obj->sizes[3] - 1] = obj->nVar;
  obj->lb->data[obj->nVar - 1] = 1.0E-5;
  idxStartIneq = obj->isActiveIdx[2];
  i = obj->nActiveConstr;
  for (idx = idxStartIneq; idx <= i; idx++) {
    obj->ATwset->data[(obj->nVar + obj->ATwset->size[0] * (idx - 1)) - 1] = -1.0;
  }
}

//
// File trailer for modifyOverheadPhaseOne_.cpp
//
// [EOF]
//
