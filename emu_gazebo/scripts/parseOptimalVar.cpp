//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: parseOptimalVar.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "parseOptimalVar.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *qr
//                const emxArray_real_T *w_star
//                emxArray_real_T *qr_new
//                emxArray_real_T *vr_new
//                emxArray_real_T *t_new
// Return Type  : void
//
void parseOptimalVar(const emxArray_real_T *qr, const emxArray_real_T *w_star,
                     emxArray_real_T *qr_new, emxArray_real_T *vr_new,
                     emxArray_real_T *t_new)
{
  int i;
  int i1;
  int i2;
  int loop_ub;
  double t_new_tmp;
  int i3;
  int input_sizes_idx_1;
  double d;
  int reshapes_f4_size_idx_1;
  int i4;
  int i5;
  int i6;
  int i7;
  emxArray_real_T *vr;
  int i8;
  double reshapes_f2[6];
  emxArray_int32_T *r;
  signed char b_input_sizes_idx_1;
  double reshapes_f4_data[6];
  if (2 > qr->size[1] - 1) {
    i = 0;
    i1 = 1;
  } else {
    i = 1;
    i1 = qr->size[1];
  }

  i2 = qr_new->size[0] * qr_new->size[1];
  qr_new->size[0] = 6;
  loop_ub = i1 - i;
  qr_new->size[1] = loop_ub + 3;
  emxEnsureCapacity_real_T(qr_new, i2);
  for (i1 = 0; i1 < 6; i1++) {
    qr_new->data[i1] = qr->data[i1];
    qr_new->data[i1 + 6] = w_star->data[(i1 + w_star->size[1]) - 24];
  }

  for (i1 = 0; i1 <= loop_ub - 2; i1++) {
    for (i2 = 0; i2 < 6; i2++) {
      qr_new->data[i2 + 6 * (i1 + 2)] = qr->data[i2 + 6 * (i + i1)];
    }
  }

  for (i = 0; i < 6; i++) {
    qr_new->data[i + 6 * (loop_ub + 1)] = w_star->data[(i + w_star->size[1]) -
      18];
    qr_new->data[i + 6 * (loop_ub + 2)] = qr->data[i + 6 * (qr->size[1] - 1)];
  }

  t_new_tmp = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 6.0
    + 1.0;
  if (t_new_tmp > static_cast<double>(w_star->size[1]) - 24.0) {
    i = -1;
    i1 = -1;
  } else {
    i = static_cast<int>(t_new_tmp) - 2;
    i1 = w_star->size[1] - 25;
  }

  loop_ub = i1 - i;
  if (loop_ub == 1) {
    i2 = t_new->size[0] * t_new->size[1];
    t_new->size[0] = 1;
    i1 = (loop_ub + i1) - i;
    t_new->size[1] = i1 + 1;
    emxEnsureCapacity_real_T(t_new, i2);
    for (i2 = 0; i2 < 1; i2++) {
      t_new->data[0] = w_star->data[i + 1] / 2.0;
    }

    for (i2 = 0; i2 < 1; i2++) {
      t_new->data[loop_ub] = w_star->data[i + 1];
    }

    for (i2 = 0; i2 < 1; i2++) {
      t_new->data[i1] = w_star->data[i + 1] / 2.0;
    }
  } else {
    if (2 > loop_ub - 1) {
      i2 = 0;
      i3 = -1;
    } else {
      i2 = 1;
      i3 = loop_ub - 2;
    }

    input_sizes_idx_1 = t_new->size[0] * t_new->size[1];
    t_new->size[0] = 1;
    loop_ub = i3 - i2;
    t_new->size[1] = loop_ub + 5;
    emxEnsureCapacity_real_T(t_new, input_sizes_idx_1);
    t_new_tmp = w_star->data[i + 1] / 2.0;
    t_new->data[0] = t_new_tmp;
    t_new->data[1] = t_new_tmp;
    for (i3 = 0; i3 <= loop_ub; i3++) {
      t_new->data[i3 + 2] = w_star->data[((i + i2) + i3) + 1];
    }

    t_new_tmp = w_star->data[i1] / 2.0;
    t_new->data[loop_ub + 3] = t_new_tmp;
    t_new->data[loop_ub + 4] = t_new_tmp;
  }

  t_new_tmp = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0;
  if (1.0 > t_new_tmp) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(t_new_tmp);
  }

  t_new_tmp = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 + 1.0;
  d = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 2.0;
  if (t_new_tmp > d) {
    i = 0;
    i1 = 0;
  } else {
    i = static_cast<int>(t_new_tmp) - 1;
    i1 = static_cast<int>(d);
  }

  t_new_tmp = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 2.0
    + 1.0;
  d = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 3.0;
  if (t_new_tmp > d) {
    i2 = 0;
    i3 = 0;
  } else {
    i2 = static_cast<int>(t_new_tmp) - 1;
    i3 = static_cast<int>(d);
  }

  t_new_tmp = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 3.0
    + 1.0;
  d = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 4.0;
  if (t_new_tmp > d) {
    input_sizes_idx_1 = 0;
    reshapes_f4_size_idx_1 = 0;
  } else {
    input_sizes_idx_1 = static_cast<int>(t_new_tmp) - 1;
    reshapes_f4_size_idx_1 = static_cast<int>(d);
  }

  t_new_tmp = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 4.0
    + 1.0;
  d = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 5.0;
  if (t_new_tmp > d) {
    i4 = 0;
    i5 = 0;
  } else {
    i4 = static_cast<int>(t_new_tmp) - 1;
    i5 = static_cast<int>(d);
  }

  t_new_tmp = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 5.0
    + 1.0;
  d = ((static_cast<double>(w_star->size[1]) - 24.0) + 1.0) / 7.0 * 6.0;
  if (t_new_tmp > d) {
    i6 = 0;
    i7 = 0;
  } else {
    i6 = static_cast<int>(t_new_tmp) - 1;
    i7 = static_cast<int>(d);
  }

  emxInit_real_T(&vr, 2);
  i8 = vr->size[0] * vr->size[1];
  vr->size[0] = 6;
  vr->size[1] = loop_ub;
  emxEnsureCapacity_real_T(vr, i8);
  for (i8 = 0; i8 < loop_ub; i8++) {
    vr->data[6 * i8] = w_star->data[i8];
  }

  loop_ub = i1 - i;
  for (i1 = 0; i1 < loop_ub; i1++) {
    vr->data[6 * i1 + 1] = w_star->data[i + i1];
  }

  loop_ub = i3 - i2;
  for (i = 0; i < loop_ub; i++) {
    vr->data[6 * i + 2] = w_star->data[i2 + i];
  }

  loop_ub = reshapes_f4_size_idx_1 - input_sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    vr->data[6 * i + 3] = w_star->data[input_sizes_idx_1 + i];
  }

  loop_ub = i5 - i4;
  for (i = 0; i < loop_ub; i++) {
    vr->data[6 * i + 4] = w_star->data[i4 + i];
  }

  loop_ub = i7 - i6;
  for (i = 0; i < loop_ub; i++) {
    vr->data[6 * i + 5] = w_star->data[i6 + i];
  }

  if (2 > vr->size[1] - 1) {
    i = -1;
    i1 = -1;
  } else {
    i = 0;
    i1 = vr->size[1] - 2;
  }

  if (w_star->size[1] - 5 > w_star->size[1]) {
    i2 = 0;
    i3 = 0;
  } else {
    i2 = w_star->size[1] - 6;
    i3 = w_star->size[1];
  }

  for (input_sizes_idx_1 = 0; input_sizes_idx_1 < 6; input_sizes_idx_1++) {
    reshapes_f2[input_sizes_idx_1] = w_star->data[(input_sizes_idx_1 +
      w_star->size[1]) - 12];
  }

  input_sizes_idx_1 = i1 - i;
  if (input_sizes_idx_1 == 0) {
    input_sizes_idx_1 = 0;
  }

  emxInit_int32_T(&r, 1);
  loop_ub = i3 - i2;
  b_input_sizes_idx_1 = static_cast<signed char>((loop_ub != 0));
  reshapes_f4_size_idx_1 = b_input_sizes_idx_1;
  i1 = r->size[0];
  r->size[0] = loop_ub;
  emxEnsureCapacity_int32_T(r, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    r->data[i1] = i2 + i1;
  }

  loop_ub = 6 * b_input_sizes_idx_1;
  for (i1 = 0; i1 < loop_ub; i1++) {
    reshapes_f4_data[i1] = w_star->data[r->data[i1]];
  }

  emxFree_int32_T(&r);
  i1 = vr_new->size[0] * vr_new->size[1];
  vr_new->size[0] = 6;
  i2 = input_sizes_idx_1 + b_input_sizes_idx_1;
  vr_new->size[1] = i2 + 3;
  emxEnsureCapacity_real_T(vr_new, i1);
  for (i1 = 0; i1 < 6; i1++) {
    vr_new->data[i1] = vr->data[i1];
    vr_new->data[i1 + 6] = reshapes_f2[i1];
  }

  for (i1 = 0; i1 < input_sizes_idx_1; i1++) {
    for (i3 = 0; i3 < 6; i3++) {
      vr_new->data[i3 + 6 * (i1 + 2)] = vr->data[i3 + 6 * ((i + i1) + 1)];
    }
  }

  if (0 <= reshapes_f4_size_idx_1 - 1) {
    for (i = 0; i < 6; i++) {
      vr_new->data[i + 6 * (input_sizes_idx_1 + 2)] = reshapes_f4_data[i];
    }
  }

  for (i = 0; i < 6; i++) {
    vr_new->data[i + 6 * (i2 + 2)] = vr->data[i + 6 * (vr->size[1] - 1)];
  }

  emxFree_real_T(&vr);
}

//
// File trailer for parseOptimalVar.cpp
//
// [EOF]
//
