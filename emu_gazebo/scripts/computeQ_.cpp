//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeQ_.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "computeQ_.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xgerc.h"

// Function Definitions

//
// Arguments    : i_struct_T *obj
//                int nrows
// Return Type  : void
//
void computeQ_(i_struct_T *obj, int nrows)
{
  int i;
  int b_i;
  int m;
  int iQR0;
  int lastc;
  int n;
  int lda;
  int i1;
  emxArray_real_T *work;
  int ia;
  int itau;
  int c_i;
  emxArray_real_T *C;
  int iaii;
  int ic0;
  int lastv;
  bool exitg2;
  int exitg1;
  double c;
  i = obj->minRowCol;
  for (b_i = 0; b_i < i; b_i++) {
    iQR0 = obj->ldq * b_i + b_i;
    n = obj->mrows - b_i;
    for (lastc = 0; lastc <= n - 2; lastc++) {
      i1 = (iQR0 + lastc) + 1;
      obj->Q->data[i1] = obj->QR->data[i1];
    }
  }

  m = obj->mrows;
  lastc = obj->minRowCol;
  lda = obj->ldq;
  if (nrows >= 1) {
    i = nrows - 1;
    for (iQR0 = lastc; iQR0 <= i; iQR0++) {
      ia = iQR0 * lda;
      i1 = m - 1;
      for (c_i = 0; c_i <= i1; c_i++) {
        obj->Q->data[ia + c_i] = 0.0;
      }

      obj->Q->data[ia + iQR0] = 1.0;
    }

    emxInit_real_T(&work, 1);
    itau = obj->minRowCol - 1;
    b_i = obj->Q->size[1];
    i = work->size[0];
    work->size[0] = b_i;
    emxEnsureCapacity_real_T(work, i);
    for (i = 0; i < b_i; i++) {
      work->data[i] = 0.0;
    }

    c_i = obj->minRowCol;
    emxInit_real_T(&C, 2);
    while (c_i >= 1) {
      iaii = c_i + (c_i - 1) * lda;
      if (c_i < nrows) {
        obj->Q->data[iaii - 1] = 1.0;
        ic0 = iaii + lda;
        i = C->size[0] * C->size[1];
        C->size[0] = obj->Q->size[0];
        C->size[1] = obj->Q->size[1];
        emxEnsureCapacity_real_T(C, i);
        b_i = obj->Q->size[0] * obj->Q->size[1];
        for (i = 0; i < b_i; i++) {
          C->data[i] = obj->Q->data[i];
        }

        if (obj->tau->data[itau] != 0.0) {
          lastv = (m - c_i) + 1;
          b_i = (iaii + m) - c_i;
          while ((lastv > 0) && (obj->Q->data[b_i - 1] == 0.0)) {
            lastv--;
            b_i--;
          }

          lastc = nrows - c_i;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            iQR0 = ic0 + (lastc - 1) * lda;
            ia = iQR0;
            do {
              exitg1 = 0;
              if (ia <= (iQR0 + lastv) - 1) {
                if (obj->Q->data[ia - 1] != 0.0) {
                  exitg1 = 1;
                } else {
                  ia++;
                }
              } else {
                lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = 0;
          lastc = 0;
        }

        if (lastv > 0) {
          if (lastc != 0) {
            for (iQR0 = 0; iQR0 < lastc; iQR0++) {
              work->data[iQR0] = 0.0;
            }

            iQR0 = 0;
            i = ic0 + lda * (lastc - 1);
            for (n = ic0; lda < 0 ? n >= i : n <= i; n += lda) {
              b_i = iaii;
              c = 0.0;
              i1 = (n + lastv) - 1;
              for (ia = n; ia <= i1; ia++) {
                c += obj->Q->data[ia - 1] * obj->Q->data[b_i - 1];
                b_i++;
              }

              work->data[iQR0] += c;
              iQR0++;
            }
          }

          xgerc(lastv, lastc, -obj->tau->data[itau], iaii, work, C, ic0, lda);
        }

        i = obj->Q->size[0] * obj->Q->size[1];
        obj->Q->size[0] = C->size[0];
        obj->Q->size[1] = C->size[1];
        emxEnsureCapacity_real_T(obj->Q, i);
        b_i = C->size[0] * C->size[1];
        for (i = 0; i < b_i; i++) {
          obj->Q->data[i] = C->data[i];
        }
      }

      if (c_i < m) {
        iQR0 = iaii + 1;
        i = (iaii + m) - c_i;
        for (lastc = iQR0; lastc <= i; lastc++) {
          obj->Q->data[lastc - 1] *= -obj->tau->data[itau];
        }
      }

      obj->Q->data[iaii - 1] = 1.0 - obj->tau->data[itau];
      for (iQR0 = 0; iQR0 <= c_i - 2; iQR0++) {
        obj->Q->data[(iaii - iQR0) - 2] = 0.0;
      }

      itau--;
      c_i--;
    }

    emxFree_real_T(&C);
    emxFree_real_T(&work);
  }
}

//
// File trailer for computeQ_.cpp
//
// [EOF]
//
