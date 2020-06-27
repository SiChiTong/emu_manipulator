//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compute_deltax.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "compute_deltax.h"
#include "rt_nonfinite.h"
#include "solve.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include "xgemm.h"
#include "xpotrf.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *H
//                e_struct_T *solution
//                c_struct_T *memspace
//                const i_struct_T *qrmanager
//                k_struct_T *cholmanager
//                const g_struct_T *objective
// Return Type  : void
//
void compute_deltax(const emxArray_real_T *H, e_struct_T *solution, c_struct_T
                    *memspace, const i_struct_T *qrmanager, k_struct_T
                    *cholmanager, const g_struct_T *objective)
{
  int nVar_tmp;
  int mNull_tmp;
  int mNull;
  int ix;
  int nullStartIdx_tmp;
  int nVars;
  int ldw;
  int idx_row;
  int idx_col;
  int i;
  double c;
  emxArray_real_T *rhs;
  nVar_tmp = qrmanager->mrows - 1;
  mNull_tmp = qrmanager->mrows - qrmanager->ncols;
  mNull = mNull_tmp - 1;
  if (mNull + 1 <= 0) {
    for (ix = 0; ix <= nVar_tmp; ix++) {
      solution->searchDir->data[ix] = 0.0;
    }
  } else {
    for (ix = 0; ix <= nVar_tmp; ix++) {
      solution->searchDir->data[ix] = -objective->grad->data[ix];
    }

    if (qrmanager->ncols <= 0) {
      switch (objective->objtype) {
       case 5:
        break;

       case 3:
        cholmanager->ndims = qrmanager->mrows;
        for (ix = 0; ix <= nVar_tmp; ix++) {
          idx_row = (nVar_tmp + 1) * ix;
          ldw = cholmanager->ldu * ix;
          for (mNull_tmp = 0; mNull_tmp <= nVar_tmp; mNull_tmp++) {
            idx_col = mNull_tmp + 1;
            cholmanager->UU->data[(ldw + idx_col) - 1] = H->data[(idx_row +
              idx_col) - 1];
          }
        }

        cholmanager->info = xpotrf(qrmanager->mrows, cholmanager->UU,
          cholmanager->ldu);
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          solve(cholmanager, solution->searchDir);
        }
        break;

       case 4:
        nVars = objective->nvar;
        cholmanager->ndims = objective->nvar;
        for (ix = 0; ix < nVars; ix++) {
          idx_row = nVars * ix;
          ldw = cholmanager->ldu * ix;
          for (mNull_tmp = 0; mNull_tmp < nVars; mNull_tmp++) {
            idx_col = mNull_tmp + 1;
            cholmanager->UU->data[(ldw + idx_col) - 1] = H->data[(idx_row +
              idx_col) - 1];
          }
        }

        cholmanager->info = xpotrf(objective->nvar, cholmanager->UU,
          cholmanager->ldu);
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          solve(cholmanager, solution->searchDir);
          c = 1.0 / objective->beta;
          idx_row = objective->nvar + 1;
          i = qrmanager->mrows;
          for (mNull_tmp = idx_row; mNull_tmp <= i; mNull_tmp++) {
            solution->searchDir->data[mNull_tmp - 1] *= c;
          }
        }
        break;
      }
    } else {
      nullStartIdx_tmp = qrmanager->ldq * qrmanager->ncols + 1;
      switch (objective->objtype) {
       case 5:
        for (ix = 0; ix <= mNull; ix++) {
          memspace->workspace_double->data[ix] = -qrmanager->Q->data[nVar_tmp +
            qrmanager->Q->size[0] * (qrmanager->ncols + ix)];
        }

        nVars = qrmanager->ldq;
        if (qrmanager->mrows != 0) {
          for (ldw = 0; ldw <= nVar_tmp; ldw++) {
            solution->searchDir->data[ldw] = 0.0;
          }

          ix = 0;
          i = nullStartIdx_tmp + qrmanager->ldq * mNull;
          for (idx_col = nullStartIdx_tmp; nVars < 0 ? idx_col >= i : idx_col <=
               i; idx_col += nVars) {
            ldw = 0;
            idx_row = idx_col + nVar_tmp;
            for (mNull_tmp = idx_col; mNull_tmp <= idx_row; mNull_tmp++) {
              solution->searchDir->data[ldw] += qrmanager->Q->data[mNull_tmp - 1]
                * memspace->workspace_double->data[ix];
              ldw++;
            }

            ix++;
          }
        }
        break;

       default:
        switch (objective->objtype) {
         case 3:
          ldw = memspace->workspace_double->size[0];
          xgemm(qrmanager->mrows, mNull_tmp, qrmanager->mrows, H,
                qrmanager->mrows, qrmanager->Q, nullStartIdx_tmp, qrmanager->ldq,
                memspace->workspace_double, memspace->workspace_double->size[0]);
          b_xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q,
                  nullStartIdx_tmp, qrmanager->ldq, memspace->workspace_double,
                  ldw, cholmanager->UU, cholmanager->ldu);
          break;

         default:
          nVars = qrmanager->mrows;
          ldw = memspace->workspace_double->size[0];
          xgemm(objective->nvar, mNull_tmp, objective->nvar, H, objective->nvar,
                qrmanager->Q, nullStartIdx_tmp, qrmanager->ldq,
                memspace->workspace_double, memspace->workspace_double->size[0]);
          for (idx_col = 0; idx_col < mNull_tmp; idx_col++) {
            i = objective->nvar + 1;
            for (idx_row = i; idx_row <= nVars; idx_row++) {
              memspace->workspace_double->data[(idx_row +
                memspace->workspace_double->size[0] * idx_col) - 1] =
                objective->beta * qrmanager->Q->data[(idx_row + qrmanager->
                Q->size[0] * (idx_col + qrmanager->ncols)) - 1];
            }
          }

          b_xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q,
                  nullStartIdx_tmp, qrmanager->ldq, memspace->workspace_double,
                  ldw, cholmanager->UU, cholmanager->ldu);
          break;
        }

        cholmanager->ndims = mNull + 1;
        cholmanager->info = xpotrf(mNull + 1, cholmanager->UU, cholmanager->ldu);
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          nVars = qrmanager->ldq;
          if (qrmanager->mrows != 0) {
            for (ldw = 0; ldw <= mNull; ldw++) {
              memspace->workspace_double->data[ldw] = 0.0;
            }

            ldw = 0;
            i = nullStartIdx_tmp + qrmanager->ldq * mNull;
            for (idx_col = nullStartIdx_tmp; nVars < 0 ? idx_col >= i : idx_col <=
                 i; idx_col += nVars) {
              ix = 0;
              c = 0.0;
              idx_row = idx_col + nVar_tmp;
              for (mNull_tmp = idx_col; mNull_tmp <= idx_row; mNull_tmp++) {
                c += qrmanager->Q->data[mNull_tmp - 1] * objective->grad->
                  data[ix];
                ix++;
              }

              memspace->workspace_double->data[ldw] += -c;
              ldw++;
            }
          }

          emxInit_real_T(&rhs, 2);
          i = rhs->size[0] * rhs->size[1];
          rhs->size[0] = memspace->workspace_double->size[0];
          rhs->size[1] = memspace->workspace_double->size[1];
          emxEnsureCapacity_real_T(rhs, i);
          nVars = memspace->workspace_double->size[0] *
            memspace->workspace_double->size[1];
          for (i = 0; i < nVars; i++) {
            rhs->data[i] = memspace->workspace_double->data[i];
          }

          for (ldw = 0; ldw <= mNull; ldw++) {
            nVars = ldw * cholmanager->ldu;
            c = rhs->data[ldw];
            for (idx_col = 0; idx_col < ldw; idx_col++) {
              c -= cholmanager->UU->data[nVars + idx_col] * rhs->data[idx_col];
            }

            rhs->data[ldw] = c / cholmanager->UU->data[nVars + ldw];
          }

          i = memspace->workspace_double->size[0] * memspace->
            workspace_double->size[1];
          memspace->workspace_double->size[0] = rhs->size[0];
          memspace->workspace_double->size[1] = rhs->size[1];
          emxEnsureCapacity_real_T(memspace->workspace_double, i);
          nVars = rhs->size[0] * rhs->size[1];
          for (i = 0; i < nVars; i++) {
            memspace->workspace_double->data[i] = rhs->data[i];
          }

          emxFree_real_T(&rhs);
          for (ldw = mNull + 1; ldw >= 1; ldw--) {
            nVars = (ldw + (ldw - 1) * cholmanager->ldu) - 1;
            memspace->workspace_double->data[ldw - 1] /= cholmanager->UU->
              data[nVars];
            for (idx_col = 0; idx_col <= ldw - 2; idx_col++) {
              ix = (ldw - idx_col) - 2;
              memspace->workspace_double->data[ix] -= memspace->
                workspace_double->data[ldw - 1] * cholmanager->UU->data[(nVars -
                idx_col) - 1];
            }
          }

          nVars = qrmanager->ldq;
          if (qrmanager->mrows != 0) {
            for (ldw = 0; ldw <= nVar_tmp; ldw++) {
              solution->searchDir->data[ldw] = 0.0;
            }

            ix = 0;
            i = nullStartIdx_tmp + qrmanager->ldq * mNull;
            for (idx_col = nullStartIdx_tmp; nVars < 0 ? idx_col >= i : idx_col <=
                 i; idx_col += nVars) {
              ldw = 0;
              idx_row = idx_col + nVar_tmp;
              for (mNull_tmp = idx_col; mNull_tmp <= idx_row; mNull_tmp++) {
                solution->searchDir->data[ldw] += qrmanager->Q->data[mNull_tmp -
                  1] * memspace->workspace_double->data[ix];
                ldw++;
              }

              ix++;
            }
          }
        }
        break;
      }
    }
  }
}

//
// File trailer for compute_deltax.cpp
//
// [EOF]
//
