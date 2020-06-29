//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: countsort.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "countsort.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : emxArray_int32_T *x
//                int xLen
//                emxArray_int32_T *workspace
//                int xMin
//                int xMax
// Return Type  : void
//
void countsort(emxArray_int32_T *x, int xLen, emxArray_int32_T *workspace, int
               xMin, int xMax)
{
  int idxW;
  int idx;
  int maxOffset;
  int idxStart;
  int idxEnd;
  if ((xLen > 1) && (xMax > xMin)) {
    idxW = xMax - xMin;
    for (idx = 0; idx <= idxW; idx++) {
      workspace->data[idx] = 0;
    }

    maxOffset = idxW - 1;
    for (idx = 0; idx < xLen; idx++) {
      idxW = x->data[idx] - xMin;
      workspace->data[idxW]++;
    }

    for (idx = 2; idx <= maxOffset + 2; idx++) {
      workspace->data[idx - 1] += workspace->data[idx - 2];
    }

    idxStart = 1;
    idxEnd = workspace->data[0];
    for (idxW = 0; idxW <= maxOffset; idxW++) {
      for (idx = idxStart; idx <= idxEnd; idx++) {
        x->data[idx - 1] = idxW + xMin;
      }

      idxStart = workspace->data[idxW] + 1;
      idxEnd = workspace->data[idxW + 1];
    }

    for (idx = idxStart; idx <= idxEnd; idx++) {
      x->data[idx - 1] = xMax;
    }
  }
}

//
// File trailer for countsort.cpp
//
// [EOF]
//
