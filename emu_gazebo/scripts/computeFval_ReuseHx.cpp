//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeFval_ReuseHx.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "computeFval_ReuseHx.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : const g_struct_T *obj
//                emxArray_real_T *workspace
//                const emxArray_real_T *f
//                const emxArray_real_T *x
// Return Type  : double
//
double computeFval_ReuseHx(const g_struct_T *obj, emxArray_real_T *workspace,
  const emxArray_real_T *f, const emxArray_real_T *x)
{
  double val;
  int maxRegVar_tmp;
  int ixlast;
  int k;
  val = 0.0;
  switch (obj->objtype) {
   case 5:
    val = obj->gammaScalar * x->data[obj->nvar - 1];
    break;

   case 3:
    if (obj->hasLinear) {
      ixlast = obj->nvar;
      for (k = 0; k < ixlast; k++) {
        workspace->data[k] = f->data[k];
      }

      if (obj->nvar >= 1) {
        ixlast = obj->nvar - 1;
        for (k = 0; k <= ixlast; k++) {
          workspace->data[k] += 0.5 * obj->Hx->data[k];
        }

        ixlast = obj->nvar;
        for (k = 0; k < ixlast; k++) {
          val += x->data[k] * workspace->data[k];
        }
      }
    } else {
      if (obj->nvar >= 1) {
        ixlast = obj->nvar;
        for (k = 0; k < ixlast; k++) {
          val += x->data[k] * obj->Hx->data[k];
        }
      }

      val *= 0.5;
    }
    break;

   case 4:
    maxRegVar_tmp = obj->maxVar - 1;
    if (obj->hasLinear) {
      ixlast = obj->nvar;
      for (k = 0; k < ixlast; k++) {
        workspace->data[k] = f->data[k];
      }

      ixlast = obj->maxVar - obj->nvar;
      for (k = 0; k <= ixlast - 2; k++) {
        workspace->data[obj->nvar + k] = obj->rho;
      }

      if (maxRegVar_tmp >= 1) {
        ixlast = obj->maxVar - 2;
        for (k = 0; k <= ixlast; k++) {
          workspace->data[k] += 0.5 * obj->Hx->data[k];
        }

        ixlast = obj->maxVar;
        for (k = 0; k <= ixlast - 2; k++) {
          val += x->data[k] * workspace->data[k];
        }
      }
    } else {
      if (maxRegVar_tmp >= 1) {
        ixlast = obj->maxVar;
        for (k = 0; k <= ixlast - 2; k++) {
          val += x->data[k] * obj->Hx->data[k];
        }
      }

      val *= 0.5;
      ixlast = obj->nvar + 1;
      for (k = ixlast; k <= maxRegVar_tmp; k++) {
        val += x->data[k - 1] * obj->rho;
      }
    }
    break;
  }

  return val;
}

//
// File trailer for computeFval_ReuseHx.cpp
//
// [EOF]
//
