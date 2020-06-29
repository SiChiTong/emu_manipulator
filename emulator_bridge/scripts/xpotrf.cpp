//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xpotrf.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "xpotrf.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include <cmath>

// Function Definitions

//
// Arguments    : int n
//                emxArray_real_T *A
//                int lda
// Return Type  : int
//
int xpotrf(int n, emxArray_real_T *A, int lda)
{
  int info;
  int j;
  bool exitg1;
  int idxA1j;
  int idxAjj;
  double ssq;
  int ix;
  int iy;
  int k;
  int nmj;
  int ia0;
  int idxAjjp1;
  int i;
  double c;
  int ia;
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j <= n - 1)) {
    idxA1j = j * lda;
    idxAjj = idxA1j + j;
    ssq = 0.0;
    if (j >= 1) {
      ix = idxA1j;
      iy = idxA1j;
      for (k = 0; k < j; k++) {
        ssq += A->data[ix] * A->data[iy];
        ix++;
        iy++;
      }
    }

    ssq = A->data[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = std::sqrt(ssq);
      A->data[idxAjj] = ssq;
      if (j + 1 < n) {
        nmj = (n - j) - 2;
        ia0 = (idxA1j + lda) + 1;
        idxAjjp1 = idxAjj + lda;
        if ((j != 0) && (nmj + 1 != 0)) {
          iy = idxAjjp1;
          i = ia0 + lda * nmj;
          for (idxAjj = ia0; lda < 0 ? idxAjj >= i : idxAjj <= i; idxAjj += lda)
          {
            ix = idxA1j;
            c = 0.0;
            k = (idxAjj + j) - 1;
            for (ia = idxAjj; ia <= k; ia++) {
              c += A->data[ia - 1] * A->data[ix];
              ix++;
            }

            A->data[iy] += -c;
            iy += lda;
          }
        }

        ssq = 1.0 / ssq;
        i = (idxAjjp1 + lda * nmj) + 1;
        for (k = idxAjjp1 + 1; lda < 0 ? k >= i : k <= i; k += lda) {
          A->data[k - 1] *= ssq;
        }
      }

      j++;
    } else {
      A->data[idxAjj] = ssq;
      info = j + 1;
      exitg1 = true;
    }
  }

  return info;
}

//
// File trailer for xpotrf.cpp
//
// [EOF]
//
