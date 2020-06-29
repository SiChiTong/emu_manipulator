//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeOpt6DofGen.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "timeOpt6DofGen.h"
#include "cubicGenCodeGen.h"
#include "fmincon.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen_data.h"
#include "timeOpt6DofGen_emxutil.h"
#include "timeOpt6DofGen_initialize.h"
#include <cmath>

// Function Definitions

//
// Arguments    : coder_internal_ref *qr
//                const emxArray_real_T *b_qr
//                const double v_max[6]
//                const double a_max[6]
//                double precision
//                const emxArray_real_T *w
//                emxArray_real_T *varargout_1
//                emxArray_real_T *varargout_2
// Return Type  : void
//
void __anon_fcn(coder_internal_ref *qr, const emxArray_real_T *b_qr, const
                double v_max[6], const double a_max[6], double precision, const
                emxArray_real_T *w, emxArray_real_T *varargout_1,
                emxArray_real_T *varargout_2)
{
  int i;
  int i1;
  int i2;
  int loop_ub;
  double d;
  int nx;
  emxArray_real_T *tim;
  int i3;
  double tim_tmp;
  int input_sizes_idx_1;
  int reshapes_f4_size_idx_1;
  int i4;
  int i5;
  int i6;
  emxArray_real_T *vr;
  int i7;
  double reshapes_f2[6];
  emxArray_int32_T *r;
  signed char b_input_sizes_idx_1;
  double reshapes_f4_data[6];
  emxArray_real_T *vr_int;
  emxArray_real_T *c_qr;
  emxArray_real_T *b_vr_int;
  emxArray_real_T *b_tim;
  emxArray_real_T *q1;
  emxArray_real_T *a_con1;
  emxArray_real_T *q2;
  emxArray_real_T *a_con2;
  emxArray_real_T *q3;
  emxArray_real_T *a_con3;
  emxArray_real_T *q4;
  emxArray_real_T *a_con4;
  emxArray_real_T *q5;
  emxArray_real_T *a_con5;
  emxArray_real_T *q6;
  emxArray_real_T *a_con6;
  bool exitg1;
  double ex;
  double b_ex;
  double c_ex;
  double d_ex;
  double e_ex;
  double f_ex;
  double g_ex;
  double h_ex;
  double i_ex;
  double j_ex;
  double k_ex;
  if (2 > b_qr->size[1] - 1) {
    i = 0;
    i1 = 1;
  } else {
    i = 1;
    i1 = b_qr->size[1];
  }

  i2 = qr->contents->size[0] * qr->contents->size[1];
  qr->contents->size[0] = 6;
  emxEnsureCapacity_real_T(qr->contents, i2);
  loop_ub = i1 - i;
  i1 = qr->contents->size[0] * qr->contents->size[1];
  qr->contents->size[1] = loop_ub + 3;
  emxEnsureCapacity_real_T(qr->contents, i1);
  for (i1 = 0; i1 < 6; i1++) {
    qr->contents->data[i1] = b_qr->data[i1];
    qr->contents->data[i1 + 6] = w->data[(i1 + w->size[1]) - 24];
  }

  for (i1 = 0; i1 <= loop_ub - 2; i1++) {
    for (i2 = 0; i2 < 6; i2++) {
      qr->contents->data[i2 + 6 * (i1 + 2)] = b_qr->data[i2 + 6 * (i + i1)];
    }
  }

  for (i = 0; i < 6; i++) {
    qr->contents->data[i + 6 * (loop_ub + 1)] = w->data[(i + w->size[1]) - 18];
    qr->contents->data[i + 6 * (loop_ub + 2)] = b_qr->data[i + 6 * (b_qr->size[1]
      - 1)];
  }

  d = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 6.0 + 1.0;
  if (d > static_cast<double>(w->size[1]) - 24.0) {
    i = -1;
    i1 = -1;
  } else {
    i = static_cast<int>(d) - 2;
    i1 = w->size[1] - 25;
  }

  nx = i1 - i;
  emxInit_real_T(&tim, 2);
  if (nx == 1) {
    i2 = tim->size[0] * tim->size[1];
    tim->size[0] = 1;
    i1 = (nx + i1) - i;
    tim->size[1] = i1 + 1;
    emxEnsureCapacity_real_T(tim, i2);
    for (i2 = 0; i2 < 1; i2++) {
      tim->data[0] = w->data[i + 1] / 2.0;
    }

    for (i2 = 0; i2 < 1; i2++) {
      tim->data[nx] = w->data[i + 1];
    }

    for (i2 = 0; i2 < 1; i2++) {
      tim->data[i1] = w->data[i + 1] / 2.0;
    }
  } else {
    if (2 > nx - 1) {
      i2 = 0;
      i3 = -1;
    } else {
      i2 = 1;
      i3 = nx - 2;
    }

    nx = tim->size[0] * tim->size[1];
    tim->size[0] = 1;
    loop_ub = i3 - i2;
    tim->size[1] = loop_ub + 5;
    emxEnsureCapacity_real_T(tim, nx);
    tim_tmp = w->data[i + 1] / 2.0;
    tim->data[0] = tim_tmp;
    tim->data[1] = tim_tmp;
    for (i3 = 0; i3 <= loop_ub; i3++) {
      tim->data[i3 + 2] = w->data[((i + i2) + i3) + 1];
    }

    tim_tmp = w->data[i1] / 2.0;
    tim->data[loop_ub + 3] = tim_tmp;
    tim->data[loop_ub + 4] = tim_tmp;
  }

  d = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0;
  if (1.0 > d) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(d);
  }

  d = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 + 1.0;
  tim_tmp = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 2.0;
  if (d > tim_tmp) {
    i = 0;
    i1 = 0;
  } else {
    i = static_cast<int>(d) - 1;
    i1 = static_cast<int>(tim_tmp);
  }

  d = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 2.0 + 1.0;
  tim_tmp = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 3.0;
  if (d > tim_tmp) {
    i2 = 0;
    i3 = 0;
  } else {
    i2 = static_cast<int>(d) - 1;
    i3 = static_cast<int>(tim_tmp);
  }

  d = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 3.0 + 1.0;
  tim_tmp = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 4.0;
  if (d > tim_tmp) {
    nx = 0;
    input_sizes_idx_1 = 0;
  } else {
    nx = static_cast<int>(d) - 1;
    input_sizes_idx_1 = static_cast<int>(tim_tmp);
  }

  d = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 4.0 + 1.0;
  tim_tmp = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 5.0;
  if (d > tim_tmp) {
    reshapes_f4_size_idx_1 = 0;
    i4 = 0;
  } else {
    reshapes_f4_size_idx_1 = static_cast<int>(d) - 1;
    i4 = static_cast<int>(tim_tmp);
  }

  d = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 5.0 + 1.0;
  tim_tmp = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 6.0;
  if (d > tim_tmp) {
    i5 = 0;
    i6 = 0;
  } else {
    i5 = static_cast<int>(d) - 1;
    i6 = static_cast<int>(tim_tmp);
  }

  emxInit_real_T(&vr, 2);
  i7 = vr->size[0] * vr->size[1];
  vr->size[0] = 6;
  vr->size[1] = loop_ub;
  emxEnsureCapacity_real_T(vr, i7);
  for (i7 = 0; i7 < loop_ub; i7++) {
    vr->data[6 * i7] = w->data[i7];
  }

  loop_ub = i1 - i;
  for (i1 = 0; i1 < loop_ub; i1++) {
    vr->data[6 * i1 + 1] = w->data[i + i1];
  }

  loop_ub = i3 - i2;
  for (i = 0; i < loop_ub; i++) {
    vr->data[6 * i + 2] = w->data[i2 + i];
  }

  loop_ub = input_sizes_idx_1 - nx;
  for (i = 0; i < loop_ub; i++) {
    vr->data[6 * i + 3] = w->data[nx + i];
  }

  loop_ub = i4 - reshapes_f4_size_idx_1;
  for (i = 0; i < loop_ub; i++) {
    vr->data[6 * i + 4] = w->data[reshapes_f4_size_idx_1 + i];
  }

  loop_ub = i6 - i5;
  for (i = 0; i < loop_ub; i++) {
    vr->data[6 * i + 5] = w->data[i5 + i];
  }

  if (2 > vr->size[1] - 1) {
    i = -1;
    i1 = -1;
  } else {
    i = 0;
    i1 = vr->size[1] - 2;
  }

  if (w->size[1] - 5 > w->size[1]) {
    i2 = 0;
    i3 = 0;
  } else {
    i2 = w->size[1] - 6;
    i3 = w->size[1];
  }

  for (nx = 0; nx < 6; nx++) {
    reshapes_f2[nx] = w->data[(nx + w->size[1]) - 12];
  }

  input_sizes_idx_1 = i1 - i;
  if (input_sizes_idx_1 == 0) {
    input_sizes_idx_1 = 0;
  }

  emxInit_int32_T(&r, 1);
  nx = i3 - i2;
  b_input_sizes_idx_1 = static_cast<signed char>((nx != 0));
  reshapes_f4_size_idx_1 = b_input_sizes_idx_1;
  i1 = r->size[0];
  r->size[0] = nx;
  emxEnsureCapacity_int32_T(r, i1);
  for (i1 = 0; i1 < nx; i1++) {
    r->data[i1] = i2 + i1;
  }

  nx = 6 * b_input_sizes_idx_1;
  for (i1 = 0; i1 < nx; i1++) {
    reshapes_f4_data[i1] = w->data[r->data[i1]];
  }

  emxFree_int32_T(&r);
  emxInit_real_T(&vr_int, 2);
  i1 = vr_int->size[0] * vr_int->size[1];
  vr_int->size[0] = 6;
  i2 = input_sizes_idx_1 + b_input_sizes_idx_1;
  vr_int->size[1] = i2 + 3;
  emxEnsureCapacity_real_T(vr_int, i1);
  for (i1 = 0; i1 < 6; i1++) {
    vr_int->data[i1] = vr->data[i1];
    vr_int->data[i1 + 6] = reshapes_f2[i1];
  }

  for (i1 = 0; i1 < input_sizes_idx_1; i1++) {
    for (i3 = 0; i3 < 6; i3++) {
      vr_int->data[i3 + 6 * (i1 + 2)] = vr->data[i3 + 6 * ((i + i1) + 1)];
    }
  }

  if (0 <= reshapes_f4_size_idx_1 - 1) {
    for (i = 0; i < 6; i++) {
      vr_int->data[i + 6 * (input_sizes_idx_1 + 2)] = reshapes_f4_data[i];
    }
  }

  for (i = 0; i < 6; i++) {
    vr_int->data[i + 6 * (i2 + 2)] = vr->data[i + 6 * (vr->size[1] - 1)];
  }

  emxFree_real_T(&vr);
  emxInit_real_T(&c_qr, 2);
  loop_ub = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = qr->contents->data[6 * i];
  }

  emxInit_real_T(&b_vr_int, 2);
  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i];
  }

  emxInit_real_T(&b_tim, 2);
  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q1, 2);
  emxInit_real_T(&a_con1, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q1, a_con1);
  loop_ub = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 1];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 1];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q2, 2);
  emxInit_real_T(&a_con2, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q2, a_con2);
  loop_ub = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 2];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 2];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q3, 2);
  emxInit_real_T(&a_con3, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q3, a_con3);
  loop_ub = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 3];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 3];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q4, 2);
  emxInit_real_T(&a_con4, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q4, a_con4);
  loop_ub = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 4];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 4];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q5, 2);
  emxInit_real_T(&a_con5, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q5, a_con5);
  loop_ub = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = loop_ub;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 5];
  }

  loop_ub = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < loop_ub; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 5];
  }

  emxFree_real_T(&vr_int);
  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  loop_ub = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q6, 2);
  emxInit_real_T(&a_con6, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q6, a_con6);
  nx = q1->size[1] - 1;
  loop_ub = q1->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q1->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  emxFree_real_T(&b_tim);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q1->data[3 * i + 1];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q1->data[3 *
      reshapes_f4_size_idx_1 + 1]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      tim_tmp = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      tim_tmp = b_vr_int->data[1];
    } else {
      tim_tmp = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      tim_tmp = b_vr_int->data[0];
    } else {
      tim_tmp = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (tim_tmp < d) {
          tim_tmp = d;
        }
      }
    }
  }

  nx = q1->size[1] - 1;
  loop_ub = q1->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q1->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q1->data[3 * i + 2];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q1->data[3 *
      reshapes_f4_size_idx_1 + 2]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      ex = b_vr_int->data[1];
    } else {
      ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      ex = b_vr_int->data[0];
    } else {
      ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (ex < d) {
          ex = d;
        }
      }
    }
  }

  nx = q2->size[1] - 1;
  loop_ub = q2->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q2->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q2->data[3 * i + 1];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q2->data[3 *
      reshapes_f4_size_idx_1 + 1]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      b_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      b_ex = b_vr_int->data[1];
    } else {
      b_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      b_ex = b_vr_int->data[0];
    } else {
      b_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (b_ex < d) {
          b_ex = d;
        }
      }
    }
  }

  nx = q2->size[1] - 1;
  loop_ub = q2->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q2->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q2->data[3 * i + 2];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q2->data[3 *
      reshapes_f4_size_idx_1 + 2]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      c_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      c_ex = b_vr_int->data[1];
    } else {
      c_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      c_ex = b_vr_int->data[0];
    } else {
      c_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (c_ex < d) {
          c_ex = d;
        }
      }
    }
  }

  nx = q3->size[1] - 1;
  loop_ub = q3->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q3->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q3->data[3 * i + 1];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q3->data[3 *
      reshapes_f4_size_idx_1 + 1]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      d_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      d_ex = b_vr_int->data[1];
    } else {
      d_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      d_ex = b_vr_int->data[0];
    } else {
      d_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (d_ex < d) {
          d_ex = d;
        }
      }
    }
  }

  nx = q3->size[1] - 1;
  loop_ub = q3->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q3->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q3->data[3 * i + 2];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q3->data[3 *
      reshapes_f4_size_idx_1 + 2]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      e_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      e_ex = b_vr_int->data[1];
    } else {
      e_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      e_ex = b_vr_int->data[0];
    } else {
      e_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (e_ex < d) {
          e_ex = d;
        }
      }
    }
  }

  nx = q4->size[1] - 1;
  loop_ub = q4->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q4->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q4->data[3 * i + 1];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q4->data[3 *
      reshapes_f4_size_idx_1 + 1]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      f_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      f_ex = b_vr_int->data[1];
    } else {
      f_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      f_ex = b_vr_int->data[0];
    } else {
      f_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (f_ex < d) {
          f_ex = d;
        }
      }
    }
  }

  nx = q4->size[1] - 1;
  loop_ub = q4->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q4->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q4->data[3 * i + 2];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q4->data[3 *
      reshapes_f4_size_idx_1 + 2]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      g_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      g_ex = b_vr_int->data[1];
    } else {
      g_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      g_ex = b_vr_int->data[0];
    } else {
      g_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (g_ex < d) {
          g_ex = d;
        }
      }
    }
  }

  nx = q5->size[1] - 1;
  loop_ub = q5->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q5->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q5->data[3 * i + 1];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q5->data[3 *
      reshapes_f4_size_idx_1 + 1]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      h_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      h_ex = b_vr_int->data[1];
    } else {
      h_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      h_ex = b_vr_int->data[0];
    } else {
      h_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (h_ex < d) {
          h_ex = d;
        }
      }
    }
  }

  nx = q5->size[1] - 1;
  loop_ub = q5->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q5->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q5->data[3 * i + 2];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q5->data[3 *
      reshapes_f4_size_idx_1 + 2]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      i_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      i_ex = b_vr_int->data[1];
    } else {
      i_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      i_ex = b_vr_int->data[0];
    } else {
      i_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (i_ex < d) {
          i_ex = d;
        }
      }
    }
  }

  nx = q6->size[1] - 1;
  loop_ub = q6->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q6->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q6->data[3 * i + 1];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q6->data[3 *
      reshapes_f4_size_idx_1 + 1]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      j_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      j_ex = b_vr_int->data[1];
    } else {
      j_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      j_ex = b_vr_int->data[0];
    } else {
      j_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (j_ex < d) {
          j_ex = d;
        }
      }
    }
  }

  nx = q6->size[1] - 1;
  loop_ub = q6->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q6->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = q6->data[3 * i + 2];
  }

  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  emxFree_real_T(&c_qr);
  for (reshapes_f4_size_idx_1 = 0; reshapes_f4_size_idx_1 <= nx;
       reshapes_f4_size_idx_1++) {
    b_vr_int->data[reshapes_f4_size_idx_1] = std::abs(q6->data[3 *
      reshapes_f4_size_idx_1 + 2]);
  }

  input_sizes_idx_1 = b_vr_int->size[1];
  if (b_vr_int->size[1] <= 2) {
    if (b_vr_int->size[1] == 1) {
      k_ex = b_vr_int->data[0];
    } else if ((b_vr_int->data[0] < b_vr_int->data[1]) || (rtIsNaN
                (b_vr_int->data[0]) && (!rtIsNaN(b_vr_int->data[1])))) {
      k_ex = b_vr_int->data[1];
    } else {
      k_ex = b_vr_int->data[0];
    }
  } else {
    if (!rtIsNaN(b_vr_int->data[0])) {
      nx = 1;
    } else {
      nx = 0;
      reshapes_f4_size_idx_1 = 2;
      exitg1 = false;
      while ((!exitg1) && (reshapes_f4_size_idx_1 <= b_vr_int->size[1])) {
        if (!rtIsNaN(b_vr_int->data[reshapes_f4_size_idx_1 - 1])) {
          nx = reshapes_f4_size_idx_1;
          exitg1 = true;
        } else {
          reshapes_f4_size_idx_1++;
        }
      }
    }

    if (nx == 0) {
      k_ex = b_vr_int->data[0];
    } else {
      k_ex = b_vr_int->data[nx - 1];
      i = nx + 1;
      for (reshapes_f4_size_idx_1 = i; reshapes_f4_size_idx_1 <=
           input_sizes_idx_1; reshapes_f4_size_idx_1++) {
        d = b_vr_int->data[reshapes_f4_size_idx_1 - 1];
        if (k_ex < d) {
          k_ex = d;
        }
      }
    }
  }

  emxFree_real_T(&b_vr_int);
  i = varargout_1->size[0];
  varargout_1->size[0] = tim->size[1] + 12;
  emxEnsureCapacity_real_T(varargout_1, i);
  varargout_1->data[0] = tim_tmp - v_max[0];
  varargout_1->data[1] = ex - a_max[0];
  varargout_1->data[2] = b_ex - v_max[1];
  varargout_1->data[3] = c_ex - a_max[1];
  varargout_1->data[4] = d_ex - v_max[2];
  varargout_1->data[5] = e_ex - a_max[2];
  varargout_1->data[6] = f_ex - v_max[3];
  varargout_1->data[7] = g_ex - a_max[3];
  varargout_1->data[8] = h_ex - v_max[4];
  varargout_1->data[9] = i_ex - a_max[4];
  varargout_1->data[10] = j_ex - v_max[5];
  varargout_1->data[11] = k_ex - a_max[5];
  loop_ub = tim->size[1];
  for (i = 0; i < loop_ub; i++) {
    varargout_1->data[i + 12] = -tim->data[i];
  }

  emxFree_real_T(&tim);
  i = varargout_2->size[0];
  varargout_2->size[0] = (((((a_con1->size[0] + a_con2->size[0]) + a_con3->size
    [0]) + a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) + 12;
  emxEnsureCapacity_real_T(varargout_2, i);
  loop_ub = a_con1->size[0];
  for (i = 0; i < loop_ub; i++) {
    varargout_2->data[i] = a_con1->data[i];
  }

  loop_ub = a_con2->size[0];
  for (i = 0; i < loop_ub; i++) {
    varargout_2->data[i + a_con1->size[0]] = a_con2->data[i];
  }

  loop_ub = a_con3->size[0];
  for (i = 0; i < loop_ub; i++) {
    varargout_2->data[(i + a_con1->size[0]) + a_con2->size[0]] = a_con3->data[i];
  }

  loop_ub = a_con4->size[0];
  for (i = 0; i < loop_ub; i++) {
    varargout_2->data[((i + a_con1->size[0]) + a_con2->size[0]) + a_con3->size[0]]
      = a_con4->data[i];
  }

  loop_ub = a_con5->size[0];
  for (i = 0; i < loop_ub; i++) {
    varargout_2->data[(((i + a_con1->size[0]) + a_con2->size[0]) + a_con3->size
                       [0]) + a_con4->size[0]] = a_con5->data[i];
  }

  loop_ub = a_con6->size[0];
  for (i = 0; i < loop_ub; i++) {
    varargout_2->data[((((i + a_con1->size[0]) + a_con2->size[0]) + a_con3->
                        size[0]) + a_con4->size[0]) + a_con5->size[0]] =
      a_con6->data[i];
  }

  varargout_2->data[((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                      a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]] =
    q1->data[2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    1] = q1->data[3 * (q1->size[1] - 1) + 2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    2] = q2->data[2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    3] = q2->data[3 * (q2->size[1] - 1) + 2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    4] = q3->data[2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    5] = q3->data[3 * (q3->size[1] - 1) + 2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    6] = q4->data[2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    7] = q4->data[3 * (q4->size[1] - 1) + 2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    8] = q5->data[2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    9] = q5->data[3 * (q5->size[1] - 1) + 2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    10] = q6->data[2];
  varargout_2->data[(((((a_con1->size[0] + a_con2->size[0]) + a_con3->size[0]) +
                       a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) +
    11] = q6->data[3 * (q6->size[1] - 1) + 2];
  emxFree_real_T(&a_con6);
  emxFree_real_T(&q6);
  emxFree_real_T(&a_con5);
  emxFree_real_T(&q5);
  emxFree_real_T(&a_con4);
  emxFree_real_T(&q4);
  emxFree_real_T(&a_con3);
  emxFree_real_T(&q3);
  emxFree_real_T(&a_con2);
  emxFree_real_T(&q2);
  emxFree_real_T(&a_con1);
  emxFree_real_T(&q1);
}

//
// Arguments    : const emxArray_real_T *qr
//                const double v_max[6]
//                const double a_max[6]
//                double precision
//                emxArray_real_T *w
//                double *cost_out
//                double *flag
// Return Type  : void
//
void timeOpt6DofGen(const emxArray_real_T *qr, const double v_max[6], const
                    double a_max[6], double precision, emxArray_real_T *w,
                    double *cost_out, double *flag)
{
  coder_internal_ref b_qr;
  int i;
  int iy;
  emxArray_real_T *c_qr;
  emxArray_real_T *qdr;
  int b_i;
  emxArray_real_T *heu;
  bool y;
  double x;
  double b_x;
  bool exitg1;
  double v_im1[6];
  double v_ip1[6];
  double c_x[6];
  double d_x[6];
  double qd_i_data[6];
  emxArray_int8_T *a;
  emxArray_real_T *w_guess;
  int loop_ub;
  int b_loop_ub;
  int c_loop_ub;
  int d_loop_ub;
  int e_loop_ub;
  emxArray_real_T *nlcon_tunableEnvironment_f2;
  emxArray_real_T *Aeq;
  if (isInitialized_timeOpt6DofGen == false) {
    timeOpt6DofGen_initialize();
  }

  c_emxInitStruct_coder_internal_(&b_qr);
  i = b_qr.contents->size[0] * b_qr.contents->size[1];
  b_qr.contents->size[0] = 6;
  b_qr.contents->size[1] = qr->size[1];
  emxEnsureCapacity_real_T(b_qr.contents, i);
  iy = qr->size[0] * qr->size[1];
  for (i = 0; i < iy; i++) {
    b_qr.contents->data[i] = qr->data[i];
  }

  emxInit_real_T(&c_qr, 2);

  //      vvec1 = @(w)w(1:(numel(w)-24+1)/7);
  //      vvec2 = @(w)w((numel(w)-24+1)/7+1:(numel(w)-24+1)/7*2);
  //      vvec3 = @(w)w((numel(w)-24+1)/7*2+1:(numel(w)-24+1)/7*3);
  //      vvec4 = @(w)w((numel(w)-24+1)/7*3+1:(numel(w)-24+1)/7*4);
  //      vvec5 = @(w)w((numel(w)-24+1)/7*4+1:(numel(w)-24+1)/7*5);
  //      vvec6 = @(w)w((numel(w)-24+1)/7*5+1:(numel(w)-24+1)/7*6);
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 6;
  c_qr->size[1] = b_qr.contents->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  iy = b_qr.contents->size[0] * b_qr.contents->size[1];
  for (i = 0; i < iy; i++) {
    c_qr->data[i] = b_qr.contents->data[i];
  }

  emxInit_real_T(&qdr, 2);
  i = qdr->size[0] * qdr->size[1];
  qdr->size[0] = 6;
  qdr->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(qdr, i);
  iy = 6 * c_qr->size[1];
  for (i = 0; i < iy; i++) {
    qdr->data[i] = 0.0;
  }

  i = c_qr->size[1];
  for (b_i = 0; b_i <= i - 3; b_i++) {
    for (iy = 0; iy < 6; iy++) {
      x = c_qr->data[iy + 6 * (b_i + 1)];
      b_x = x - c_qr->data[iy + 6 * b_i];
      v_im1[iy] = b_x;
      x = c_qr->data[iy + 6 * (b_i + 2)] - x;
      v_ip1[iy] = x;
      if (b_x < 0.0) {
        b_x = -1.0;
      } else if (b_x > 0.0) {
        b_x = 1.0;
      } else {
        if (b_x == 0.0) {
          b_x = 0.0;
        }
      }

      c_x[iy] = b_x;
      if (x < 0.0) {
        x = -1.0;
      } else if (x > 0.0) {
        x = 1.0;
      } else {
        if (x == 0.0) {
          x = 0.0;
        }
      }

      d_x[iy] = x;
    }

    y = true;
    iy = 0;
    exitg1 = false;
    while ((!exitg1) && (iy < 6)) {
      if (!(c_x[iy] + d_x[iy] == 0.0)) {
        y = false;
        exitg1 = true;
      } else {
        iy++;
      }
    }

    if (y) {
      qd_i_data[0] = 0.0;
    } else {
      for (iy = 0; iy < 6; iy++) {
        qd_i_data[iy] = (v_im1[iy] + v_ip1[iy]) / 2.0;
      }
    }

    for (iy = 0; iy < 6; iy++) {
      qdr->data[iy + 6 * (b_i + 1)] = qd_i_data[iy];
    }
  }

  emxInit_real_T(&heu, 3);
  i = heu->size[0] * heu->size[1] * heu->size[2];
  heu->size[0] = 6;
  heu->size[1] = c_qr->size[1];
  heu->size[2] = 2;
  emxEnsureCapacity_real_T(heu, i);
  iy = -1;
  i = 6 * c_qr->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    iy++;
    heu->data[iy] = c_qr->data[b_i];
  }

  emxFree_real_T(&c_qr);
  i = 6 * qdr->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    iy++;
    heu->data[iy] = qdr->data[b_i];
  }

  emxFree_real_T(&qdr);
  emxInit_int8_T(&a, 2);
  i = a->size[0] * a->size[1];
  a->size[0] = 1;
  a->size[1] = b_qr.contents->size[1] - 1;
  emxEnsureCapacity_int8_T(a, i);
  iy = b_qr.contents->size[1] - 1;
  for (i = 0; i < iy; i++) {
    a->data[i] = 1;
  }

  emxInit_real_T(&w_guess, 2);
  iy = heu->size[1];
  b_i = heu->size[1];
  loop_ub = heu->size[1];
  b_loop_ub = heu->size[1];
  c_loop_ub = heu->size[1];
  d_loop_ub = heu->size[1];
  i = w_guess->size[0] * w_guess->size[1];
  w_guess->size[0] = 1;
  w_guess->size[1] = ((((((heu->size[1] + heu->size[1]) + heu->size[1]) +
    heu->size[1]) + heu->size[1]) + heu->size[1]) + a->size[1]) + 24;
  emxEnsureCapacity_real_T(w_guess, i);
  for (i = 0; i < iy; i++) {
    w_guess->data[i] = heu->data[6 * i + 6 * heu->size[1]];
  }

  for (i = 0; i < b_i; i++) {
    w_guess->data[i + iy] = heu->data[(6 * i + 6 * heu->size[1]) + 1];
  }

  for (i = 0; i < loop_ub; i++) {
    w_guess->data[(i + iy) + b_i] = heu->data[(6 * i + 6 * heu->size[1]) + 2];
  }

  for (i = 0; i < b_loop_ub; i++) {
    w_guess->data[((i + iy) + b_i) + loop_ub] = heu->data[(6 * i + 6 * heu->
      size[1]) + 3];
  }

  for (i = 0; i < c_loop_ub; i++) {
    w_guess->data[(((i + iy) + b_i) + loop_ub) + b_loop_ub] = heu->data[(6 * i +
      6 * heu->size[1]) + 4];
  }

  for (i = 0; i < d_loop_ub; i++) {
    w_guess->data[((((i + iy) + b_i) + loop_ub) + b_loop_ub) + c_loop_ub] =
      heu->data[(6 * i + 6 * heu->size[1]) + 5];
  }

  emxFree_real_T(&heu);
  e_loop_ub = a->size[1];
  for (i = 0; i < e_loop_ub; i++) {
    w_guess->data[(((((i + iy) + b_i) + loop_ub) + b_loop_ub) + c_loop_ub) +
      d_loop_ub] = a->data[i];
  }

  iy = ((iy + b_i) + loop_ub) + b_loop_ub;
  for (i = 0; i < 12; i++) {
    w_guess->data[(((i + iy) + c_loop_ub) + d_loop_ub) + a->size[1]] = 0.0;
    w_guess->data[((((i + iy) + c_loop_ub) + d_loop_ub) + a->size[1]) + 12] =
      0.0;
  }

  emxFree_int8_T(&a);
  emxInit_real_T(&nlcon_tunableEnvironment_f2, 2);

  //
  i = nlcon_tunableEnvironment_f2->size[0] * nlcon_tunableEnvironment_f2->size[1];
  nlcon_tunableEnvironment_f2->size[0] = 6;
  nlcon_tunableEnvironment_f2->size[1] = b_qr.contents->size[1];
  emxEnsureCapacity_real_T(nlcon_tunableEnvironment_f2, i);
  iy = b_qr.contents->size[0] * b_qr.contents->size[1];
  for (i = 0; i < iy; i++) {
    nlcon_tunableEnvironment_f2->data[i] = b_qr.contents->data[i];
  }

  emxInit_real_T(&Aeq, 2);
  i = Aeq->size[0] * Aeq->size[1];
  Aeq->size[0] = 12;
  Aeq->size[1] = w_guess->size[1];
  emxEnsureCapacity_real_T(Aeq, i);
  iy = 12 * w_guess->size[1];
  for (i = 0; i < iy; i++) {
    Aeq->data[i] = 0.0;
  }

  Aeq->data[0] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 + 1.0)) - 1) + 1] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 * 2.0 + 1.0)) - 1) + 2] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0)) - 1) + 3] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 * 2.0)) - 1) + 4] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 * 3.0)) - 1) + 5] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 * 3.0 + 1.0)) - 1) + 6] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 * 4.0 + 1.0)) - 1) + 7] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 * 5.0 + 1.0)) - 1) + 8] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 * 4.0)) - 1) + 9] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 * 5.0)) - 1) + 10] = 1.0;
  Aeq->data[12 * (static_cast<int>((((static_cast<double>(w_guess->size[1]) -
    24.0) + 1.0) / 7.0 * 6.0)) - 1) + 11] = 1.0;
  fmincon(w_guess, Aeq, &b_qr, nlcon_tunableEnvironment_f2, v_max, a_max,
          precision, w, cost_out, flag);
  emxFree_real_T(&Aeq);
  emxFree_real_T(&nlcon_tunableEnvironment_f2);
  emxFree_real_T(&w_guess);
  c_emxFreeStruct_coder_internal_(&b_qr);
}

//
// File trailer for timeOpt6DofGen.cpp
//
// [EOF]
//
