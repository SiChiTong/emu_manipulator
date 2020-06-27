//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cubicGenCodeGen.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "cubicGenCodeGen.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"
#include <cmath>
#include <math.h>

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

//
// Arguments    : const emxArray_real_T *qr
//                const emxArray_real_T *qdr
//                emxArray_real_T *T
//                double Tk
//                emxArray_real_T *traj
//                emxArray_real_T *con
// Return Type  : void
//
void cubicGenCodeGen(const emxArray_real_T *qr, const emxArray_real_T *qdr,
                     emxArray_real_T *T, double Tk, emxArray_real_T *traj,
                     emxArray_real_T *con)
{
  int i;
  int c;
  emxArray_real_T *Tc;
  double T_prev;
  double q_len;
  emxArray_real_T *tempa;
  int j;
  double Ts;
  double a;
  int b_i;
  double t_end;
  double subStart;
  double c_i;
  emxArray_real_T *sub_tvec;
  emxArray_real_T *temp_ts;
  emxArray_real_T *b;
  emxArray_real_T *b_tmp;
  double d;
  double d1;
  double d2;
  double ci_idx_2_tmp;
  double b_ci_idx_2_tmp;
  double ci_idx_3_tmp;
  int traj_tmp;
  int i1;
  i = T->size[1];
  for (c = 0; c < i; c++) {
    if (T->data[c] == 0.0) {
      T->data[c] = 1.0E-5;
    }
  }

  emxInit_real_T(&Tc, 2);
  T_prev = 0.0;
  i = Tc->size[0] * Tc->size[1];
  Tc->size[0] = 1;
  Tc->size[1] = T->size[1];
  emxEnsureCapacity_real_T(Tc, i);
  c = T->size[0] * T->size[1];
  for (i = 0; i < c; i++) {
    Tc->data[i] = T->data[i];
  }

  if ((T->size[1] != 0) && (T->size[1] != 1)) {
    i = T->size[1];
    for (c = 0; c <= i - 2; c++) {
      Tc->data[c + 1] += Tc->data[c];
    }
  }

  q_len = 0.0;
  i = T->size[1];
  emxInit_real_T(&tempa, 2);
  for (j = 0; j < i; j++) {
    Ts = T->data[j] / Tk;
    a = T_prev;
    t_end = Tc->data[j] - Ts;
    T_prev = t_end + Ts;
    if (rtIsNaN(a) || rtIsNaN(Ts) || rtIsNaN(t_end)) {
      b_i = 1;
    } else if ((Ts == 0.0) || ((a < t_end) && (Ts < 0.0)) || ((t_end < a) && (Ts
      > 0.0))) {
      b_i = 0;
    } else if ((rtIsInf(a) || rtIsInf(t_end)) && (rtIsInf(Ts) || (a == t_end)))
    {
      b_i = 1;
    } else if (rtIsInf(Ts)) {
      b_i = 1;
    } else if ((std::floor(a) == a) && (std::floor(Ts) == Ts)) {
      b_i = static_cast<int>(std::floor((t_end - a) / Ts)) + 1;
    } else {
      eml_float_colon(a, Ts, t_end, tempa);
      b_i = tempa->size[1];
    }

    q_len += static_cast<double>(b_i);
  }

  i = traj->size[0] * traj->size[1];
  traj->size[0] = 3;
  b_i = static_cast<int>(q_len);
  traj->size[1] = b_i;
  emxEnsureCapacity_real_T(traj, i);
  c = 3 * b_i;
  for (i = 0; i < c; i++) {
    traj->data[i] = 0.0;
  }

  i = tempa->size[0] * tempa->size[1];
  tempa->size[0] = 1;
  tempa->size[1] = 2 * T->size[1];
  emxEnsureCapacity_real_T(tempa, i);
  c = 2 * T->size[1];
  for (i = 0; i < c; i++) {
    tempa->data[i] = 0.0;
  }

  T_prev = 0.0;
  subStart = 1.0;
  c_i = 1.0;
  i = T->size[1];
  emxInit_real_T(&sub_tvec, 2);
  emxInit_real_T(&temp_ts, 2);
  emxInit_real_T(&b, 2);
  emxInit_real_T(&b_tmp, 2);
  for (j = 0; j < i; j++) {
    d = T->data[j];
    Ts = d / Tk;
    d1 = qr->data[j];
    d2 = qdr->data[j];
    q_len = qdr->data[j + 1];
    t_end = qr->data[j + 1] - d1;
    ci_idx_2_tmp = d * d;
    b_ci_idx_2_tmp = 3.0 * t_end / ci_idx_2_tmp - (q_len + 2.0 * d2) / d;
    ci_idx_3_tmp = -2.0 * t_end / rt_powd_snf(d, 3.0) + (q_len + d2) /
      ci_idx_2_tmp;
    q_len = T_prev;
    t_end = Tc->data[j] - Ts;
    T_prev = t_end + Ts;
    if (rtIsNaN(q_len) || rtIsNaN(Ts) || rtIsNaN(t_end)) {
      b_i = sub_tvec->size[0] * sub_tvec->size[1];
      sub_tvec->size[0] = 1;
      sub_tvec->size[1] = 1;
      emxEnsureCapacity_real_T(sub_tvec, b_i);
      sub_tvec->data[0] = rtNaN;
    } else if ((Ts == 0.0) || ((q_len < t_end) && (Ts < 0.0)) || ((t_end < q_len)
                && (Ts > 0.0))) {
      sub_tvec->size[0] = 1;
      sub_tvec->size[1] = 0;
    } else if ((rtIsInf(q_len) || rtIsInf(t_end)) && (rtIsInf(Ts) || (q_len ==
                 t_end))) {
      b_i = sub_tvec->size[0] * sub_tvec->size[1];
      sub_tvec->size[0] = 1;
      sub_tvec->size[1] = 1;
      emxEnsureCapacity_real_T(sub_tvec, b_i);
      sub_tvec->data[0] = rtNaN;
    } else if (rtIsInf(Ts)) {
      b_i = sub_tvec->size[0] * sub_tvec->size[1];
      sub_tvec->size[0] = 1;
      sub_tvec->size[1] = 1;
      emxEnsureCapacity_real_T(sub_tvec, b_i);
      sub_tvec->data[0] = q_len;
    } else if ((std::floor(q_len) == q_len) && (std::floor(Ts) == Ts)) {
      b_i = sub_tvec->size[0] * sub_tvec->size[1];
      sub_tvec->size[0] = 1;
      c = static_cast<int>(std::floor((t_end - q_len) / Ts));
      sub_tvec->size[1] = c + 1;
      emxEnsureCapacity_real_T(sub_tvec, b_i);
      for (b_i = 0; b_i <= c; b_i++) {
        sub_tvec->data[b_i] = q_len + Ts * static_cast<double>(b_i);
      }
    } else {
      eml_float_colon(q_len, Ts, t_end, sub_tvec);
    }

    t_end = subStart + static_cast<double>(sub_tvec->size[1]);
    b_i = sub_tvec->size[0] * sub_tvec->size[1];
    i1 = sub_tvec->size[0] * sub_tvec->size[1];
    sub_tvec->size[0] = 1;
    emxEnsureCapacity_real_T(sub_tvec, i1);
    c = b_i - 1;
    for (b_i = 0; b_i <= c; b_i++) {
      sub_tvec->data[b_i] -= q_len;
    }

    b_i = b_tmp->size[0] * b_tmp->size[1];
    b_tmp->size[0] = 1;
    i1 = sub_tvec->size[1];
    b_tmp->size[1] = sub_tvec->size[1];
    emxEnsureCapacity_real_T(b_tmp, b_i);
    for (c = 0; c < i1; c++) {
      d = sub_tvec->data[c];
      b_tmp->data[c] = d * d;
    }

    b_i = b->size[0] * b->size[1];
    b->size[0] = 1;
    i1 = sub_tvec->size[1];
    b->size[1] = sub_tvec->size[1];
    emxEnsureCapacity_real_T(b, b_i);
    for (c = 0; c < i1; c++) {
      b->data[c] = rt_powd_snf(sub_tvec->data[c], 3.0);
    }

    a = 2.0 * b_ci_idx_2_tmp;
    q_len = 3.0 * ci_idx_3_tmp;
    ci_idx_2_tmp = 6.0 * ci_idx_3_tmp;
    d = 2.0 * b_ci_idx_2_tmp;
    b_i = temp_ts->size[0] * temp_ts->size[1];
    temp_ts->size[0] = 3;
    temp_ts->size[1] = sub_tvec->size[1];
    emxEnsureCapacity_real_T(temp_ts, b_i);
    c = sub_tvec->size[1];
    for (b_i = 0; b_i < c; b_i++) {
      temp_ts->data[3 * b_i] = ((d1 + d2 * sub_tvec->data[b_i]) + b_ci_idx_2_tmp
        * b_tmp->data[b_i]) + ci_idx_3_tmp * b->data[b_i];
    }

    c = sub_tvec->size[1];
    for (b_i = 0; b_i < c; b_i++) {
      temp_ts->data[3 * b_i + 1] = (d2 + a * sub_tvec->data[b_i]) + q_len *
        b_tmp->data[b_i];
    }

    c = sub_tvec->size[1];
    for (b_i = 0; b_i < c; b_i++) {
      temp_ts->data[3 * b_i + 2] = d + ci_idx_2_tmp * sub_tvec->data[b_i];
    }

    tempa->data[static_cast<int>(c_i) - 1] = temp_ts->data[2];
    tempa->data[static_cast<int>((c_i + 1.0)) - 1] = temp_ts->data[3 *
      (temp_ts->size[1] - 1) + 2];
    if (subStart > t_end - 1.0) {
      b_i = 1;
    } else {
      b_i = static_cast<int>(subStart);
    }

    c = temp_ts->size[1];
    for (i1 = 0; i1 < c; i1++) {
      traj_tmp = (b_i + i1) - 1;
      traj->data[3 * traj_tmp] = temp_ts->data[3 * i1];
      traj->data[3 * traj_tmp + 1] = temp_ts->data[3 * i1 + 1];
      traj->data[3 * traj_tmp + 2] = temp_ts->data[3 * i1 + 2];
    }

    subStart = t_end;
    c_i += 2.0;
  }

  emxFree_real_T(&b_tmp);
  emxFree_real_T(&b);
  emxFree_real_T(&temp_ts);
  emxFree_real_T(&sub_tvec);
  emxFree_real_T(&Tc);
  i = con->size[0];
  con->size[0] = static_cast<int>(((static_cast<double>(tempa->size[1]) - 2.0) /
    2.0));
  emxEnsureCapacity_real_T(con, i);
  c = static_cast<int>(((static_cast<double>(tempa->size[1]) - 2.0) / 2.0));
  for (i = 0; i < c; i++) {
    con->data[i] = 0.0;
  }

  //      tempa
  c = 0;
  i = static_cast<int>((((static_cast<double>(tempa->size[1]) - 3.0) + 1.0) /
                        2.0));
  for (b_i = 0; b_i < i; b_i++) {
    //          tempa(i+1)
    //          tempa(i+2)
    traj_tmp = b_i * 2 + 1;
    con->data[c] = tempa->data[traj_tmp] - tempa->data[traj_tmp + 1];
    c++;
  }

  emxFree_real_T(&tempa);

  //      a_con
}

//
// File trailer for cubicGenCodeGen.cpp
//
// [EOF]
//
