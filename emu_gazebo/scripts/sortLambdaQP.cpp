//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortLambdaQP.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "sortLambdaQP.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *lambda
//                int WorkingSet_nActiveConstr
//                const int WorkingSet_sizes[5]
//                const int WorkingSet_isActiveIdx[6]
//                const emxArray_int32_T *WorkingSet_Wid
//                const emxArray_int32_T *WorkingSet_Wlocalidx
//                emxArray_real_T *workspace
// Return Type  : void
//
void sortLambdaQP(emxArray_real_T *lambda, int WorkingSet_nActiveConstr, const
                  int WorkingSet_sizes[5], const int WorkingSet_isActiveIdx[6],
                  const emxArray_int32_T *WorkingSet_Wid, const emxArray_int32_T
                  *WorkingSet_Wlocalidx, emxArray_real_T *workspace)
{
  int mAll;
  int idx;
  int idxOffset;
  if (WorkingSet_nActiveConstr != 0) {
    mAll = (((WorkingSet_sizes[0] + WorkingSet_sizes[1]) + WorkingSet_sizes[3])
            + WorkingSet_sizes[4]) + 11;
    for (idx = 0; idx <= mAll; idx++) {
      workspace->data[idx] = lambda->data[idx];
      lambda->data[idx] = 0.0;
    }

    mAll = 0;
    idx = 0;
    while ((idx + 1 <= WorkingSet_nActiveConstr) && (WorkingSet_Wid->data[idx] <=
            2)) {
      switch (WorkingSet_Wid->data[idx]) {
       case 1:
        idxOffset = 1;
        break;

       default:
        idxOffset = WorkingSet_isActiveIdx[1];
        break;
      }

      lambda->data[(idxOffset + WorkingSet_Wlocalidx->data[idx]) - 2] =
        workspace->data[mAll];
      mAll++;
      idx++;
    }

    while (idx + 1 <= WorkingSet_nActiveConstr) {
      switch (WorkingSet_Wid->data[idx]) {
       case 3:
        idxOffset = WorkingSet_isActiveIdx[2];
        break;

       case 4:
        idxOffset = WorkingSet_isActiveIdx[3];
        break;

       default:
        idxOffset = WorkingSet_isActiveIdx[4];
        break;
      }

      lambda->data[(idxOffset + WorkingSet_Wlocalidx->data[idx]) - 2] =
        workspace->data[mAll];
      mAll++;
      idx++;
    }
  }
}

//
// File trailer for sortLambdaQP.cpp
//
// [EOF]
//
