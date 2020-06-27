//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeOpt6DofGen_initialize.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 25-Jun-2020 20:47:06
//

// Include Files
#include "timeOpt6DofGen_initialize.h"
#include "rt_nonfinite.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_data.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void timeOpt6DofGen_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_timeOpt6DofGen = true;
}

//
// File trailer for timeOpt6DofGen_initialize.cpp
//
// [EOF]
//
