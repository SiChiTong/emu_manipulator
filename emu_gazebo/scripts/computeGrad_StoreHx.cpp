//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeGrad_StoreHx.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "computeGrad_StoreHx.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : g_struct_T *obj
//                const emxArray_real_T *H
//                const emxArray_real_T *f
//                const emxArray_real_T *x
// Return Type  : void
//
void computeGrad_StoreHx(g_struct_T *obj, const emxArray_real_T *H, const
  emxArray_real_T *f, const emxArray_real_T *x)
{
  int n;
  int maxRegVar;
  int k;
  int iy;
  int ix;
  int i;
  int iac;
  int i1;
  int ia;
  switch (obj->objtype) {
   case 5:
    n = obj->nvar;
    for (k = 0; k <= n - 2; k++) {
      obj->grad->data[k] = 0.0;
    }

    obj->grad->data[obj->nvar - 1] = obj->gammaScalar;
    break;

   case 3:
    n = obj->nvar - 1;
    k = obj->nvar;
    if (obj->nvar != 0) {
      for (iy = 0; iy <= n; iy++) {
        obj->Hx->data[iy] = 0.0;
      }

      ix = 0;
      i = obj->nvar * (obj->nvar - 1) + 1;
      for (iac = 1; k < 0 ? iac >= i : iac <= i; iac += k) {
        iy = 0;
        i1 = iac + n;
        for (ia = iac; ia <= i1; ia++) {
          obj->Hx->data[iy] += H->data[ia - 1] * x->data[ix];
          iy++;
        }

        ix++;
      }
    }

    n = obj->nvar;
    for (k = 0; k < n; k++) {
      obj->grad->data[k] = obj->Hx->data[k];
    }

    if (obj->hasLinear && (obj->nvar >= 1)) {
      i = obj->nvar - 1;
      for (k = 0; k <= i; k++) {
        obj->grad->data[k] += f->data[k];
      }
    }
    break;

   case 4:
    maxRegVar = obj->maxVar - 1;
    n = obj->nvar - 1;
    k = obj->nvar;
    if (obj->nvar != 0) {
      for (iy = 0; iy <= n; iy++) {
        obj->Hx->data[iy] = 0.0;
      }

      ix = 0;
      i = obj->nvar * (obj->nvar - 1) + 1;
      for (iac = 1; k < 0 ? iac >= i : iac <= i; iac += k) {
        iy = 0;
        i1 = iac + n;
        for (ia = iac; ia <= i1; ia++) {
          obj->Hx->data[iy] += H->data[ia - 1] * x->data[ix];
          iy++;
        }

        ix++;
      }
    }

    i = obj->nvar + 1;
    for (n = i; n <= maxRegVar; n++) {
      obj->Hx->data[n - 1] = obj->beta * x->data[n - 1];
    }

    for (k = 0; k < maxRegVar; k++) {
      obj->grad->data[k] = obj->Hx->data[k];
    }

    if (obj->hasLinear && (obj->nvar >= 1)) {
      i = obj->nvar - 1;
      for (k = 0; k <= i; k++) {
        obj->grad->data[k] += f->data[k];
      }
    }

    n = (obj->maxVar - obj->nvar) - 1;
    if (n >= 1) {
      iy = obj->nvar;
      i = n - 1;
      for (k = 0; k <= i; k++) {
        obj->grad->data[iy] += obj->rho;
        iy++;
      }
    }
    break;
  }
}

//
// File trailer for computeGrad_StoreHx.cpp
//
// [EOF]
//
