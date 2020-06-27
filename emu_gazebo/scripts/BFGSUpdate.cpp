//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BFGSUpdate.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "BFGSUpdate.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"

// Function Definitions

//
// Arguments    : int nvar
//                emxArray_real_T *Bk
//                const emxArray_real_T *sk
//                emxArray_real_T *yk
//                emxArray_real_T *workspace
// Return Type  : bool
//
bool BFGSUpdate(int nvar, emxArray_real_T *Bk, const emxArray_real_T *sk,
                emxArray_real_T *yk, emxArray_real_T *workspace)
{
  bool success;
  int ldBk;
  double dotSY;
  int jA;
  double curvatureS;
  int ix;
  int i;
  int ixlast;
  double theta;
  int i1;
  int ia;
  int ijA;
  ldBk = Bk->size[0];
  dotSY = 0.0;
  if (nvar >= 1) {
    for (jA = 0; jA < nvar; jA++) {
      dotSY += sk->data[jA] * yk->data[jA];
    }
  }

  if (nvar != 0) {
    for (jA = 0; jA < nvar; jA++) {
      workspace->data[jA] = 0.0;
    }

    ix = 0;
    i = Bk->size[0] * (nvar - 1) + 1;
    for (ixlast = 1; ldBk < 0 ? ixlast >= i : ixlast <= i; ixlast += ldBk) {
      jA = 0;
      i1 = (ixlast + nvar) - 1;
      for (ia = ixlast; ia <= i1; ia++) {
        workspace->data[jA] += Bk->data[ia - 1] * sk->data[ix];
        jA++;
      }

      ix++;
    }
  }

  curvatureS = 0.0;
  if (nvar >= 1) {
    for (jA = 0; jA < nvar; jA++) {
      curvatureS += sk->data[jA] * workspace->data[jA];
    }
  }

  if (dotSY < 0.2 * curvatureS) {
    theta = 0.8 * curvatureS / (curvatureS - dotSY);
    for (jA = 0; jA < nvar; jA++) {
      yk->data[jA] *= theta;
    }

    if ((nvar >= 1) && (!(1.0 - theta == 0.0))) {
      ixlast = nvar - 1;
      for (jA = 0; jA <= ixlast; jA++) {
        yk->data[jA] += (1.0 - theta) * workspace->data[jA];
      }
    }

    dotSY = 0.0;
    if (nvar >= 1) {
      for (jA = 0; jA < nvar; jA++) {
        dotSY += sk->data[jA] * yk->data[jA];
      }
    }
  }

  if ((curvatureS > 2.2204460492503131E-16) && (dotSY > 2.2204460492503131E-16))
  {
    success = true;
  } else {
    success = false;
  }

  if (success) {
    theta = -1.0 / curvatureS;
    if (!(theta == 0.0)) {
      jA = 0;
      ixlast = 0;
      for (ia = 0; ia < nvar; ia++) {
        if (workspace->data[ixlast] != 0.0) {
          curvatureS = workspace->data[ixlast] * theta;
          ix = 0;
          i = jA + 1;
          i1 = nvar + jA;
          for (ijA = i; ijA <= i1; ijA++) {
            Bk->data[ijA - 1] += workspace->data[ix] * curvatureS;
            ix++;
          }
        }

        ixlast++;
        jA += ldBk;
      }
    }

    theta = 1.0 / dotSY;
    if (!(theta == 0.0)) {
      jA = 0;
      ixlast = 0;
      for (ia = 0; ia < nvar; ia++) {
        if (yk->data[ixlast] != 0.0) {
          curvatureS = yk->data[ixlast] * theta;
          ix = 0;
          i = jA + 1;
          i1 = nvar + jA;
          for (ijA = i; ijA <= i1; ijA++) {
            Bk->data[ijA - 1] += yk->data[ix] * curvatureS;
            ix++;
          }
        }

        ixlast++;
        jA += ldBk;
      }
    }
  }

  return success;
}

//
// File trailer for BFGSUpdate.cpp
//
// [EOF]
//
