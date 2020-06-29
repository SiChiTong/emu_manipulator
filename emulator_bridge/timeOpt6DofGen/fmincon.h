//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fmincon.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//
#ifndef FMINCON_H
#define FMINCON_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "timeOpt6DofGen_types.h"

// Function Declarations
extern void fmincon(const emxArray_real_T *x0, const emxArray_real_T *Aeq,
                    coder_internal_ref *nonlcon_tunableEnvironment_f1, const
                    emxArray_real_T *nonlcon_tunableEnvironment_f2, const double
                    nonlcon_tunableEnvironment_f3[6], const double
                    nonlcon_tunableEnvironment_f4[6], double
                    nonlcon_tunableEnvironment_f5, emxArray_real_T *x, double
                    *fval, double *exitflag);

#endif

//
// File trailer for fmincon.h
//
// [EOF]
//
