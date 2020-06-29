//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factoryConstruct2.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "factoryConstruct2.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"

// Function Definitions

//
// Arguments    : int MaxVars
//                g_struct_T *obj
// Return Type  : void
//
void c_factoryConstruct(int MaxVars, g_struct_T *obj)
{
  int i;
  i = obj->grad->size[0];
  obj->grad->size[0] = MaxVars;
  emxEnsureCapacity_real_T(obj->grad, i);
  i = obj->Hx->size[0];
  obj->Hx->size[0] = MaxVars - 1;
  emxEnsureCapacity_real_T(obj->Hx, i);
  obj->hasLinear = false;
  obj->nvar = 0;
  obj->maxVar = MaxVars;
  obj->beta = 0.0;
  obj->rho = 0.0;
  obj->objtype = 3;
  obj->prev_objtype = 3;
  obj->prev_nvar = 0;
  obj->prev_hasLinear = false;
  obj->gammaScalar = 0.0;
}

//
// File trailer for factoryConstruct2.cpp
//
// [EOF]
//
