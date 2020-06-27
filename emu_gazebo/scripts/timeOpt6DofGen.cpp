//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeOpt6DofGen.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "timeOpt6DofGen.h"
#include "cubicGenCodeGen.h"
#include "fmincon.h"
#include "parseOptimalVar.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen_data.h"
#include "timeOpt6DofGen_emxutil.h"
#include "timeOpt6DofGen_initialize.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const emxArray_real_T *w
// Return Type  : double
//
double __anon_fcn(const emxArray_real_T *w)
{
  double varargout_1;
  double d;
  int i;
  int vlen_tmp;
  int k;
  d = ((static_cast<double>(w->size[1]) - 24.0) + 1.0) / 7.0 * 6.0 + 1.0;
  if (d > static_cast<double>(w->size[1]) - 24.0) {
    i = -1;
    vlen_tmp = -1;
  } else {
    i = static_cast<int>(d) - 2;
    vlen_tmp = w->size[1] - 25;
  }

  vlen_tmp -= i;
  if (vlen_tmp == 0) {
    varargout_1 = 0.0;
  } else {
    varargout_1 = w->data[i + 1];
    for (k = 2; k <= vlen_tmp; k++) {
      varargout_1 += w->data[i + k];
    }
  }

  return varargout_1;
}

//
// Arguments    : coder_internal_ref *qr
//                const emxArray_real_T *b_qr
//                const double v_max[6]
//                const double a_max[6]
//                double precision
//                const emxArray_real_T *w
//                double varargout_1[12]
//                emxArray_real_T *varargout_2
// Return Type  : void
//
void b___anon_fcn(coder_internal_ref *qr, const emxArray_real_T *b_qr, const
                  double v_max[6], const double a_max[6], double precision,
                  const emxArray_real_T *w, double varargout_1[12],
                  emxArray_real_T *varargout_2)
{
  emxArray_real_T *vr_int;
  emxArray_real_T *tim;
  emxArray_real_T *c_qr;
  int idx;
  int i;
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
  int nx;
  int k;
  double ex;
  bool exitg1;
  double d;
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
  double l_ex;
  emxInit_real_T(&vr_int, 2);
  emxInit_real_T(&tim, 2);
  emxInit_real_T(&c_qr, 2);
  parseOptimalVar(b_qr, w, qr->contents, vr_int, tim);
  idx = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = idx;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = qr->contents->data[6 * i];
  }

  emxInit_real_T(&b_vr_int, 2);
  idx = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < idx; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i];
  }

  emxInit_real_T(&b_tim, 2);
  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  idx = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= idx; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q1, 2);
  emxInit_real_T(&a_con1, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q1, a_con1);
  idx = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = idx;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 1];
  }

  idx = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < idx; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 1];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  idx = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= idx; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q2, 2);
  emxInit_real_T(&a_con2, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q2, a_con2);
  idx = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = idx;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 2];
  }

  idx = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < idx; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 2];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  idx = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= idx; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q3, 2);
  emxInit_real_T(&a_con3, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q3, a_con3);
  idx = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = idx;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 3];
  }

  idx = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < idx; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 3];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  idx = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= idx; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q4, 2);
  emxInit_real_T(&a_con4, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q4, a_con4);
  idx = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = idx;
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 4];
  }

  idx = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < idx; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 4];
  }

  i = b_tim->size[0] * b_tim->size[1];
  b_tim->size[0] = 1;
  b_tim->size[1] = tim->size[1];
  emxEnsureCapacity_real_T(b_tim, i);
  idx = tim->size[0] * tim->size[1] - 1;
  for (i = 0; i <= idx; i++) {
    b_tim->data[i] = tim->data[i];
  }

  emxInit_real_T(&q5, 2);
  emxInit_real_T(&a_con5, 1);
  cubicGenCodeGen(c_qr, b_vr_int, b_tim, precision, q5, a_con5);
  idx = qr->contents->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = idx;
  emxEnsureCapacity_real_T(c_qr, i);
  emxFree_real_T(&b_tim);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = qr->contents->data[6 * i + 5];
  }

  idx = vr_int->size[1];
  i = b_vr_int->size[0] * b_vr_int->size[1];
  b_vr_int->size[0] = 1;
  b_vr_int->size[1] = vr_int->size[1];
  emxEnsureCapacity_real_T(b_vr_int, i);
  for (i = 0; i < idx; i++) {
    b_vr_int->data[i] = vr_int->data[6 * i + 5];
  }

  emxFree_real_T(&vr_int);
  emxInit_real_T(&q6, 2);
  emxInit_real_T(&a_con6, 1);
  cubicGenCodeGen(c_qr, b_vr_int, tim, precision, q6, a_con6);
  nx = q1->size[1] - 1;
  idx = q1->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q1->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  emxFree_real_T(&b_vr_int);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q1->data[3 * i + 1];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q1->data[3 * k + 1]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      ex = tim->data[1];
    } else {
      ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ex = tim->data[0];
    } else {
      ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (ex < d) {
          ex = d;
        }
      }
    }
  }

  nx = q1->size[1] - 1;
  idx = q1->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q1->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q1->data[3 * i + 2];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q1->data[3 * k + 2]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      b_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      b_ex = tim->data[1];
    } else {
      b_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      b_ex = tim->data[0];
    } else {
      b_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (b_ex < d) {
          b_ex = d;
        }
      }
    }
  }

  nx = q2->size[1] - 1;
  idx = q2->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q2->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q2->data[3 * i + 1];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q2->data[3 * k + 1]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      c_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      c_ex = tim->data[1];
    } else {
      c_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      c_ex = tim->data[0];
    } else {
      c_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (c_ex < d) {
          c_ex = d;
        }
      }
    }
  }

  nx = q2->size[1] - 1;
  idx = q2->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q2->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q2->data[3 * i + 2];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q2->data[3 * k + 2]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      d_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      d_ex = tim->data[1];
    } else {
      d_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      d_ex = tim->data[0];
    } else {
      d_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (d_ex < d) {
          d_ex = d;
        }
      }
    }
  }

  nx = q3->size[1] - 1;
  idx = q3->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q3->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q3->data[3 * i + 1];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q3->data[3 * k + 1]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      e_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      e_ex = tim->data[1];
    } else {
      e_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      e_ex = tim->data[0];
    } else {
      e_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (e_ex < d) {
          e_ex = d;
        }
      }
    }
  }

  nx = q3->size[1] - 1;
  idx = q3->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q3->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q3->data[3 * i + 2];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q3->data[3 * k + 2]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      f_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      f_ex = tim->data[1];
    } else {
      f_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      f_ex = tim->data[0];
    } else {
      f_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (f_ex < d) {
          f_ex = d;
        }
      }
    }
  }

  nx = q4->size[1] - 1;
  idx = q4->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q4->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q4->data[3 * i + 1];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q4->data[3 * k + 1]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      g_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      g_ex = tim->data[1];
    } else {
      g_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      g_ex = tim->data[0];
    } else {
      g_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (g_ex < d) {
          g_ex = d;
        }
      }
    }
  }

  nx = q4->size[1] - 1;
  idx = q4->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q4->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q4->data[3 * i + 2];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q4->data[3 * k + 2]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      h_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      h_ex = tim->data[1];
    } else {
      h_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      h_ex = tim->data[0];
    } else {
      h_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (h_ex < d) {
          h_ex = d;
        }
      }
    }
  }

  nx = q5->size[1] - 1;
  idx = q5->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q5->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q5->data[3 * i + 1];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q5->data[3 * k + 1]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      i_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      i_ex = tim->data[1];
    } else {
      i_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      i_ex = tim->data[0];
    } else {
      i_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (i_ex < d) {
          i_ex = d;
        }
      }
    }
  }

  nx = q5->size[1] - 1;
  idx = q5->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q5->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q5->data[3 * i + 2];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q5->data[3 * k + 2]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      j_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      j_ex = tim->data[1];
    } else {
      j_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      j_ex = tim->data[0];
    } else {
      j_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (j_ex < d) {
          j_ex = d;
        }
      }
    }
  }

  nx = q6->size[1] - 1;
  idx = q6->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q6->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q6->data[3 * i + 1];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q6->data[3 * k + 1]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      k_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      k_ex = tim->data[1];
    } else {
      k_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      k_ex = tim->data[0];
    } else {
      k_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (k_ex < d) {
          k_ex = d;
        }
      }
    }
  }

  nx = q6->size[1] - 1;
  idx = q6->size[1];
  i = c_qr->size[0] * c_qr->size[1];
  c_qr->size[0] = 1;
  c_qr->size[1] = q6->size[1];
  emxEnsureCapacity_real_T(c_qr, i);
  for (i = 0; i < idx; i++) {
    c_qr->data[i] = q6->data[3 * i + 2];
  }

  i = tim->size[0] * tim->size[1];
  tim->size[0] = 1;
  tim->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(tim, i);
  emxFree_real_T(&c_qr);
  for (k = 0; k <= nx; k++) {
    tim->data[k] = std::abs(q6->data[3 * k + 2]);
  }

  nx = tim->size[1];
  if (tim->size[1] <= 2) {
    if (tim->size[1] == 1) {
      l_ex = tim->data[0];
    } else if ((tim->data[0] < tim->data[1]) || (rtIsNaN(tim->data[0]) &&
                (!rtIsNaN(tim->data[1])))) {
      l_ex = tim->data[1];
    } else {
      l_ex = tim->data[0];
    }
  } else {
    if (!rtIsNaN(tim->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= tim->size[1])) {
        if (!rtIsNaN(tim->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      l_ex = tim->data[0];
    } else {
      l_ex = tim->data[idx - 1];
      i = idx + 1;
      for (k = i; k <= nx; k++) {
        d = tim->data[k - 1];
        if (l_ex < d) {
          l_ex = d;
        }
      }
    }
  }

  emxFree_real_T(&tim);
  varargout_1[0] = ex - v_max[0];
  varargout_1[1] = b_ex - a_max[0];
  varargout_1[2] = c_ex - v_max[1];
  varargout_1[3] = d_ex - a_max[1];
  varargout_1[4] = e_ex - v_max[2];
  varargout_1[5] = f_ex - a_max[2];
  varargout_1[6] = g_ex - v_max[3];
  varargout_1[7] = h_ex - a_max[3];
  varargout_1[8] = i_ex - v_max[4];
  varargout_1[9] = j_ex - a_max[4];
  varargout_1[10] = k_ex - v_max[5];
  varargout_1[11] = l_ex - a_max[5];
  i = varargout_2->size[0];
  varargout_2->size[0] = (((((a_con1->size[0] + a_con2->size[0]) + a_con3->size
    [0]) + a_con4->size[0]) + a_con5->size[0]) + a_con6->size[0]) + 12;
  emxEnsureCapacity_real_T(varargout_2, i);
  idx = a_con1->size[0];
  for (i = 0; i < idx; i++) {
    varargout_2->data[i] = a_con1->data[i];
  }

  idx = a_con2->size[0];
  for (i = 0; i < idx; i++) {
    varargout_2->data[i + a_con1->size[0]] = a_con2->data[i];
  }

  idx = a_con3->size[0];
  for (i = 0; i < idx; i++) {
    varargout_2->data[(i + a_con1->size[0]) + a_con2->size[0]] = a_con3->data[i];
  }

  idx = a_con4->size[0];
  for (i = 0; i < idx; i++) {
    varargout_2->data[((i + a_con1->size[0]) + a_con2->size[0]) + a_con3->size[0]]
      = a_con4->data[i];
  }

  idx = a_con5->size[0];
  for (i = 0; i < idx; i++) {
    varargout_2->data[(((i + a_con1->size[0]) + a_con2->size[0]) + a_con3->size
                       [0]) + a_con4->size[0]] = a_con5->data[i];
  }

  idx = a_con6->size[0];
  for (i = 0; i < idx; i++) {
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
  int loop_ub;
  emxArray_real_T *c_qr;
  emxArray_real_T *qdr;
  int b_i;
  emxArray_real_T *heu;
  int iy;
  bool y;
  double x;
  double b_x;
  bool exitg1;
  double v_im1[6];
  double v_ip1[6];
  double c_x[6];
  double d_x[6];
  emxArray_real_T *lb;
  emxArray_real_T *w_guess;
  int b_loop_ub;
  int c_loop_ub;
  int d_loop_ub;
  int e_loop_ub;
  emxArray_real_T *nlcon_tunableEnvironment_f2;
  emxArray_real_T *Aeq;
  emxArray_real_T *ub;
  if (isInitialized_timeOpt6DofGen == false) {
    timeOpt6DofGen_initialize();
  }

  c_emxInitStruct_coder_internal_(&b_qr);
  i = b_qr.contents->size[0] * b_qr.contents->size[1];
  b_qr.contents->size[0] = 6;
  b_qr.contents->size[1] = qr->size[1];
  emxEnsureCapacity_real_T(b_qr.contents, i);
  loop_ub = qr->size[0] * qr->size[1];
  for (i = 0; i < loop_ub; i++) {
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
  loop_ub = b_qr.contents->size[0] * b_qr.contents->size[1];
  for (i = 0; i < loop_ub; i++) {
    c_qr->data[i] = b_qr.contents->data[i];
  }

  emxInit_real_T(&qdr, 2);
  i = qdr->size[0] * qdr->size[1];
  qdr->size[0] = 6;
  qdr->size[1] = c_qr->size[1];
  emxEnsureCapacity_real_T(qdr, i);
  loop_ub = 6 * c_qr->size[1];
  for (i = 0; i < loop_ub; i++) {
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
      for (iy = 0; iy < 6; iy++) {
        qdr->data[iy + 6 * (b_i + 1)] = 0.0;
      }
    } else {
      for (iy = 0; iy < 6; iy++) {
        qdr->data[iy + 6 * (b_i + 1)] = (v_im1[iy] + v_ip1[iy]) / 2.0;
      }
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
  emxInit_real_T(&lb, 2);
  i = lb->size[0] * lb->size[1];
  lb->size[0] = 1;
  lb->size[1] = b_qr.contents->size[1] - 1;
  emxEnsureCapacity_real_T(lb, i);
  loop_ub = b_qr.contents->size[1] - 1;
  for (i = 0; i < loop_ub; i++) {
    lb->data[i] = 1.0;
  }

  emxInit_real_T(&w_guess, 2);
  loop_ub = heu->size[1];
  iy = heu->size[1];
  b_i = heu->size[1];
  b_loop_ub = heu->size[1];
  c_loop_ub = heu->size[1];
  d_loop_ub = heu->size[1];
  i = w_guess->size[0] * w_guess->size[1];
  w_guess->size[0] = 1;
  w_guess->size[1] = ((((((heu->size[1] + heu->size[1]) + heu->size[1]) +
    heu->size[1]) + heu->size[1]) + heu->size[1]) + lb->size[1]) + 24;
  emxEnsureCapacity_real_T(w_guess, i);
  for (i = 0; i < loop_ub; i++) {
    w_guess->data[i] = heu->data[6 * i + 6 * heu->size[1]];
  }

  for (i = 0; i < iy; i++) {
    w_guess->data[i + loop_ub] = heu->data[(6 * i + 6 * heu->size[1]) + 1];
  }

  for (i = 0; i < b_i; i++) {
    w_guess->data[(i + loop_ub) + iy] = heu->data[(6 * i + 6 * heu->size[1]) + 2];
  }

  for (i = 0; i < b_loop_ub; i++) {
    w_guess->data[((i + loop_ub) + iy) + b_i] = heu->data[(6 * i + 6 * heu->
      size[1]) + 3];
  }

  for (i = 0; i < c_loop_ub; i++) {
    w_guess->data[(((i + loop_ub) + iy) + b_i) + b_loop_ub] = heu->data[(6 * i +
      6 * heu->size[1]) + 4];
  }

  for (i = 0; i < d_loop_ub; i++) {
    w_guess->data[((((i + loop_ub) + iy) + b_i) + b_loop_ub) + c_loop_ub] =
      heu->data[(6 * i + 6 * heu->size[1]) + 5];
  }

  emxFree_real_T(&heu);
  e_loop_ub = lb->size[1];
  for (i = 0; i < e_loop_ub; i++) {
    w_guess->data[(((((i + loop_ub) + iy) + b_i) + b_loop_ub) + c_loop_ub) +
      d_loop_ub] = lb->data[i] * 2.0;
  }

  iy = ((loop_ub + iy) + b_i) + b_loop_ub;
  for (i = 0; i < 12; i++) {
    w_guess->data[(((i + iy) + c_loop_ub) + d_loop_ub) + lb->size[1]] = 0.0;
    w_guess->data[((((i + iy) + c_loop_ub) + d_loop_ub) + lb->size[1]) + 12] =
      0.0;
  }

  emxInit_real_T(&nlcon_tunableEnvironment_f2, 2);

  //
  i = nlcon_tunableEnvironment_f2->size[0] * nlcon_tunableEnvironment_f2->size[1];
  nlcon_tunableEnvironment_f2->size[0] = 6;
  nlcon_tunableEnvironment_f2->size[1] = b_qr.contents->size[1];
  emxEnsureCapacity_real_T(nlcon_tunableEnvironment_f2, i);
  loop_ub = b_qr.contents->size[0] * b_qr.contents->size[1];
  for (i = 0; i < loop_ub; i++) {
    nlcon_tunableEnvironment_f2->data[i] = b_qr.contents->data[i];
  }

  emxInit_real_T(&Aeq, 2);
  i = Aeq->size[0] * Aeq->size[1];
  Aeq->size[0] = 12;
  Aeq->size[1] = w_guess->size[1];
  emxEnsureCapacity_real_T(Aeq, i);
  loop_ub = 12 * w_guess->size[1];
  for (i = 0; i < loop_ub; i++) {
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
  i = lb->size[0] * lb->size[1];
  lb->size[0] = 1;
  lb->size[1] = w_guess->size[1];
  emxEnsureCapacity_real_T(lb, i);
  loop_ub = w_guess->size[1];
  for (i = 0; i < loop_ub; i++) {
    lb->data[i] = rtMinusInf;
  }

  emxInit_real_T(&ub, 2);
  i = ub->size[0] * ub->size[1];
  ub->size[0] = 1;
  ub->size[1] = w_guess->size[1];
  emxEnsureCapacity_real_T(ub, i);
  loop_ub = w_guess->size[1];
  for (i = 0; i < loop_ub; i++) {
    ub->data[i] = rtInf;
  }

  x = ((static_cast<double>(lb->size[1]) - 24.0) + 1.0) / 7.0 * 6.0 + 1.0;
  if (x > static_cast<double>(lb->size[1]) - 24.0) {
    i = -1;
    iy = 24;
  } else {
    i = static_cast<int>(x) - 2;
    iy = lb->size[1];
  }

  loop_ub = (iy - i) - 25;
  for (iy = 0; iy < loop_ub; iy++) {
    lb->data[(i + iy) + 1] = 1.0E-5;
  }

  x = ((static_cast<double>(lb->size[1]) - 24.0) + 1.0) / 7.0 * 6.0 + 1.0;
  if (x > static_cast<double>(lb->size[1]) - 24.0) {
    i = -1;
    iy = 24;
  } else {
    i = static_cast<int>(x) - 2;
    iy = lb->size[1];
  }

  loop_ub = (iy - i) - 25;
  for (iy = 0; iy < loop_ub; iy++) {
    ub->data[(i + iy) + 1] = rtInf;
  }

  fmincon(w_guess, Aeq, lb, ub, &b_qr, nlcon_tunableEnvironment_f2, v_max, a_max,
          precision, w, cost_out, flag);
  emxFree_real_T(&ub);
  emxFree_real_T(&lb);
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
