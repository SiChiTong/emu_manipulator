//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: saveJacobian.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "saveJacobian.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : e_struct_T *obj
//                int nVar
//                const emxArray_real_T *JacCineqTrans
//                int mEq
//                const emxArray_real_T *JacCeqTrans
//                int eqCol0
//                int ldJ
// Return Type  : void
//
void saveJacobian(e_struct_T *obj, int nVar, const emxArray_real_T
                  *JacCineqTrans, int mEq, const emxArray_real_T *JacCeqTrans,
                  int eqCol0, int ldJ)
{
  int iCol;
  int iCol_old;
  int idx_col;
  int k;
  int i;
  int b_k;
  iCol = -1;
  iCol_old = -1;
  for (idx_col = 0; idx_col < 12; idx_col++) {
    for (k = 0; k < nVar; k++) {
      b_k = k + 1;
      obj->JacCineqTrans_old->data[iCol_old + b_k] = JacCineqTrans->data[iCol +
        b_k];
    }

    iCol += ldJ;
    iCol_old += ldJ;
  }

  iCol = ldJ * (eqCol0 - 1);
  iCol_old = -1;
  i = mEq - eqCol0;
  for (idx_col = 0; idx_col <= i; idx_col++) {
    for (k = 0; k < nVar; k++) {
      b_k = k + 1;
      obj->JacCeqTrans_old->data[iCol_old + b_k] = JacCeqTrans->data[(iCol + b_k)
        - 1];
    }

    iCol += ldJ;
    iCol_old += ldJ;
  }
}

//
// File trailer for saveJacobian.cpp
//
// [EOF]
//
