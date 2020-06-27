//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeFval.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "computeFval.h"
#include "linearForm_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : const g_struct_T *obj
//                emxArray_real_T *workspace
//                const emxArray_real_T *H
//                const emxArray_real_T *f
//                const emxArray_real_T *x
// Return Type  : double
//
double computeFval(const g_struct_T *obj, emxArray_real_T *workspace, const
                   emxArray_real_T *H, const emxArray_real_T *f, const
                   emxArray_real_T *x)
{
  double val;
  int ixlast;
  int k;
  int idx;
  val = 0.0;
  switch (obj->objtype) {
   case 5:
    val = obj->gammaScalar * x->data[obj->nvar - 1];
    break;

   case 3:
    linearForm_(obj->hasLinear, obj->nvar, workspace, H, f, x);
    if (obj->nvar >= 1) {
      ixlast = obj->nvar;
      for (k = 0; k < ixlast; k++) {
        val += x->data[k] * workspace->data[k];
      }
    }
    break;

   case 4:
    linearForm_(obj->hasLinear, obj->nvar, workspace, H, f, x);
    ixlast = obj->nvar + 1;
    k = obj->maxVar - 1;
    for (idx = ixlast; idx <= k; idx++) {
      workspace->data[idx - 1] = 0.5 * obj->beta * x->data[idx - 1] + obj->rho;
    }

    if (k >= 1) {
      ixlast = obj->maxVar;
      for (k = 0; k <= ixlast - 2; k++) {
        val += x->data[k] * workspace->data[k];
      }
    }
    break;
  }

  return val;
}

//
// File trailer for computeFval.cpp
//
// [EOF]
//
