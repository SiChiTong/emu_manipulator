/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_timeOpt6DofGen_mex.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 24-Jun-2020 08:27:59
 */

/* Include Files */
#include "_coder_timeOpt6DofGen_mex.h"
#include "_coder_timeOpt6DofGen_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void timeOpt6DofGen_mexFunction(int32_T nlhs, mxArray *plhs
  [3], int32_T nrhs, const mxArray *prhs[4]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[3]
 *                int32_T nrhs
 *                const mxArray *prhs[4]
 * Return Type  : void
 */
void timeOpt6DofGen_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs,
  const mxArray *prhs[4])
{
  const mxArray *outputs[3];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 4) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 4, 4,
                        14, "timeOpt6DofGen");
  }

  if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "timeOpt6DofGen");
  }

  /* Call the function. */
  timeOpt6DofGen_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[]
 *                int32_T nrhs
 *                const mxArray *prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(timeOpt6DofGen_atexit);

  /* Module initialization. */
  timeOpt6DofGen_initialize();

  /* Dispatch the entry-point. */
  timeOpt6DofGen_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  timeOpt6DofGen_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_timeOpt6DofGen_mex.c
 *
 * [EOF]
 */
