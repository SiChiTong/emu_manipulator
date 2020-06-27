//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeGradLag.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "computeGradLag.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *workspace
//                int ldA
//                int nVar
//                const emxArray_real_T *grad
//                const emxArray_real_T *AineqTrans
//                int mEq
//                const emxArray_real_T *AeqTrans
//                const emxArray_int32_T *finiteFixed
//                int mFixed
//                const emxArray_int32_T *finiteLB
//                int mLB
//                const emxArray_int32_T *finiteUB
//                int mUB
//                const emxArray_real_T *lambda
// Return Type  : void
//
void computeGradLag(emxArray_real_T *workspace, int ldA, int nVar, const
                    emxArray_real_T *grad, const emxArray_real_T *AineqTrans,
                    int mEq, const emxArray_real_T *AeqTrans, const
                    emxArray_int32_T *finiteFixed, int mFixed, const
                    emxArray_int32_T *finiteLB, int mLB, const emxArray_int32_T *
                    finiteUB, int mUB, const emxArray_real_T *lambda)
{
  int ix;
  int iL0;
  int i;
  int iac;
  int iy;
  int i1;
  int ia;
  for (ix = 0; ix < nVar; ix++) {
    workspace->data[ix] = grad->data[ix];
  }

  for (ix = 0; ix < mFixed; ix++) {
    workspace->data[finiteFixed->data[ix] - 1] += lambda->data[ix];
  }

  if ((nVar != 0) && (mEq != 0)) {
    ix = mFixed;
    i = ldA * (mEq - 1) + 1;
    for (iac = 1; ldA < 0 ? iac >= i : iac <= i; iac += ldA) {
      iy = 0;
      i1 = (iac + nVar) - 1;
      for (ia = iac; ia <= i1; ia++) {
        workspace->data[iy] += AeqTrans->data[ia - 1] * lambda->data[ix];
        iy++;
      }

      ix++;
    }
  }

  iL0 = mFixed + mEq;
  if (nVar != 0) {
    ix = iL0;
    i = ldA * 11 + 1;
    for (iac = 1; ldA < 0 ? iac >= i : iac <= i; iac += ldA) {
      iy = 0;
      i1 = (iac + nVar) - 1;
      for (ia = iac; ia <= i1; ia++) {
        workspace->data[iy] += AineqTrans->data[ia - 1] * lambda->data[ix];
        iy++;
      }

      ix++;
    }
  }

  iL0 += 12;
  for (ix = 0; ix < mLB; ix++) {
    workspace->data[finiteLB->data[ix] - 1] -= lambda->data[iL0];
    iL0++;
  }

  for (ix = 0; ix < mUB; ix++) {
    workspace->data[finiteUB->data[ix] - 1] += lambda->data[iL0];
    iL0++;
  }
}

//
// File trailer for computeGradLag.cpp
//
// [EOF]
//
