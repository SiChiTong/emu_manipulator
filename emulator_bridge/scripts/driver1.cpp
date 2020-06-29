//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: driver1.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 24-Jun-2020 08:27:59
//

// Include Files
#include "driver1.h"
#include "PresolveWorkingSet.h"
#include "computeFval.h"
#include "iterate.h"
#include "maxConstraintViolation.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include "timeOpt6DofGen.h"
#include "timeOpt6DofGen_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *H
//                const emxArray_real_T *f
//                e_struct_T *solution
//                c_struct_T *memspace
//                h_struct_T *workingset
//                i_struct_T *qrmanager
//                k_struct_T *cholmanager
//                g_struct_T *objective
//                b_struct_T options
// Return Type  : void
//
void b_driver(const emxArray_real_T *H, const emxArray_real_T *f, e_struct_T
              *solution, c_struct_T *memspace, h_struct_T *workingset,
              i_struct_T *qrmanager, k_struct_T *cholmanager, g_struct_T
              *objective, b_struct_T options)
{
  int nVar;
  double maxConstr;
  h_struct_T b_workingset;
  e_struct_T b_solution;
  h_struct_T c_workingset;
  int idxStartIneq;
  int idxEndIneq;
  int idx_global;
  bool exitg1;
  int TYPE_tmp;
  int i;
  double maxConstr_new;
  nVar = workingset->nVar - 1;
  PresolveWorkingSet(solution, memspace, workingset, qrmanager);
  if (solution->state >= 0) {
    maxConstr = maxConstraintViolation(workingset, solution->xstar);
    emxInitStruct_struct_T5(&b_workingset);
    emxInitStruct_struct_T(&b_solution);
    emxInitStruct_struct_T5(&c_workingset);
    if (maxConstr > 0.001) {
      emxCopyStruct_struct_T2(&c_workingset, workingset);
      solution->maxConstr = maxConstraintViolation(&c_workingset,
        solution->xstar);
      solution->xstar->data[c_workingset.nVar] = solution->maxConstr + 1.0;
      emxCopyStruct_struct_T2(&b_workingset, &c_workingset);
      idxStartIneq = (b_workingset.nWConstr[0] + b_workingset.nWConstr[1]) + 1;
      idxEndIneq = b_workingset.nActiveConstr;
      for (idx_global = idxStartIneq; idx_global <= idxEndIneq; idx_global++) {
        b_workingset.isActiveConstr->data
          [(b_workingset.isActiveIdx[b_workingset.Wid->data[idx_global - 1] - 1]
            + b_workingset.Wlocalidx->data[idx_global - 1]) - 2] = false;
      }

      b_workingset.nWConstr[2] = 0;
      b_workingset.nWConstr[3] = 0;
      b_workingset.nWConstr[4] = 0;
      b_workingset.nActiveConstr = b_workingset.nWConstr[0] +
        b_workingset.nWConstr[1];
      if (workingset->probType == 3) {
        idxStartIneq = 1;
      } else {
        idxStartIneq = 4;
      }

      setProblemType(&b_workingset, idxStartIneq);
      objective->prev_objtype = objective->objtype;
      objective->prev_nvar = objective->nvar;
      objective->prev_hasLinear = objective->hasLinear;
      objective->objtype = 5;
      objective->nvar = c_workingset.nVar + 1;
      objective->gammaScalar = 1.0;
      objective->hasLinear = true;
      solution->iterations = 0;
      solution->fstar = computeFval(objective, memspace->workspace_double, H, f,
        solution->xstar);
      solution->state = 5;
      iterate(H, f, solution, memspace, &b_workingset, qrmanager, cholmanager,
              objective, options.MaxIterations, 1.4901161193847657E-10, 0.001);
      if (b_workingset.isActiveConstr->data[(b_workingset.isActiveIdx[3] +
           b_workingset.sizes[3]) - 2]) {
        idxEndIneq = b_workingset.sizes[1];
        exitg1 = false;
        while ((!exitg1) && (idxEndIneq + 1 <= b_workingset.nActiveConstr)) {
          if ((b_workingset.Wid->data[idxEndIneq] == 4) &&
              (b_workingset.Wlocalidx->data[idxEndIneq] == b_workingset.sizes[3]))
          {
            idx_global = idxEndIneq + 1;
            TYPE_tmp = b_workingset.Wid->data[idx_global - 1] - 1;
            b_workingset.isActiveConstr->data[(b_workingset.isActiveIdx[TYPE_tmp]
              + b_workingset.Wlocalidx->data[idx_global - 1]) - 2] = false;
            b_workingset.Wid->data[idx_global - 1] = b_workingset.Wid->
              data[b_workingset.nActiveConstr - 1];
            b_workingset.Wlocalidx->data[idx_global - 1] =
              b_workingset.Wlocalidx->data[b_workingset.nActiveConstr - 1];
            i = b_workingset.nVar;
            for (idxEndIneq = 0; idxEndIneq < i; idxEndIneq++) {
              b_workingset.ATwset->data[idxEndIneq + b_workingset.ATwset->size[0]
                * (idx_global - 1)] = b_workingset.ATwset->data[idxEndIneq +
                b_workingset.ATwset->size[0] * (b_workingset.nActiveConstr - 1)];
            }

            b_workingset.bwset->data[idx_global - 1] = b_workingset.bwset->
              data[b_workingset.nActiveConstr - 1];
            b_workingset.nActiveConstr--;
            b_workingset.nWConstr[TYPE_tmp]--;
            exitg1 = true;
          } else {
            idxEndIneq++;
          }
        }
      }

      idxStartIneq = b_workingset.nActiveConstr;
      while ((idxStartIneq > b_workingset.sizes[1]) && (idxStartIneq >
              c_workingset.nVar)) {
        TYPE_tmp = b_workingset.Wid->data[idxStartIneq - 1] - 1;
        b_workingset.isActiveConstr->data[(b_workingset.isActiveIdx[TYPE_tmp] +
          b_workingset.Wlocalidx->data[idxStartIneq - 1]) - 2] = false;
        b_workingset.Wid->data[idxStartIneq - 1] = b_workingset.Wid->
          data[b_workingset.nActiveConstr - 1];
        b_workingset.Wlocalidx->data[idxStartIneq - 1] =
          b_workingset.Wlocalidx->data[b_workingset.nActiveConstr - 1];
        i = b_workingset.nVar;
        for (idxEndIneq = 0; idxEndIneq < i; idxEndIneq++) {
          b_workingset.ATwset->data[idxEndIneq + b_workingset.ATwset->size[0] *
            (idxStartIneq - 1)] = b_workingset.ATwset->data[idxEndIneq +
            b_workingset.ATwset->size[0] * (b_workingset.nActiveConstr - 1)];
        }

        b_workingset.bwset->data[idxStartIneq - 1] = b_workingset.bwset->
          data[b_workingset.nActiveConstr - 1];
        b_workingset.nActiveConstr--;
        b_workingset.nWConstr[TYPE_tmp]--;
        idxStartIneq--;
      }

      solution->maxConstr = solution->xstar->data[c_workingset.nVar];
      setProblemType(&b_workingset, workingset->probType);
      objective->objtype = objective->prev_objtype;
      objective->nvar = objective->prev_nvar;
      objective->hasLinear = objective->prev_hasLinear;
      options.ObjectiveLimit = -1.0E+20;
      options.StepTolerance = 1.0E-6;
      emxCopyStruct_struct_T2(workingset, &b_workingset);
      maxConstr = maxConstraintViolation(workingset, solution->xstar);
      if (maxConstr > 0.001) {
        idxEndIneq = workingset->mConstrMax;
        for (idxStartIneq = 0; idxStartIneq < idxEndIneq; idxStartIneq++) {
          solution->lambda->data[idxStartIneq] = 0.0;
        }

        solution->fstar = computeFval(objective, memspace->workspace_double, H,
          f, solution->xstar);
        solution->state = -2;
      } else {
        if (maxConstr > 0.0) {
          for (idxStartIneq = 0; idxStartIneq <= nVar; idxStartIneq++) {
            solution->searchDir->data[idxStartIneq] = solution->xstar->
              data[idxStartIneq];
          }

          emxCopyStruct_struct_T1(&b_solution, solution);
          PresolveWorkingSet(&b_solution, memspace, workingset, qrmanager);
          emxCopyStruct_struct_T1(solution, &b_solution);
          maxConstr_new = maxConstraintViolation(workingset, b_solution.xstar);
          if (maxConstr_new >= maxConstr) {
            i = solution->xstar->size[0];
            solution->xstar->size[0] = b_solution.xstar->size[0];
            emxEnsureCapacity_real_T(solution->xstar, i);
            idxEndIneq = b_solution.xstar->size[0];
            for (i = 0; i < idxEndIneq; i++) {
              solution->xstar->data[i] = b_solution.xstar->data[i];
            }

            for (idxStartIneq = 0; idxStartIneq <= nVar; idxStartIneq++) {
              solution->xstar->data[idxStartIneq] = b_solution.searchDir->
                data[idxStartIneq];
            }
          }
        }

        iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
                objective, options.MaxIterations, options.StepTolerance,
                options.ObjectiveLimit);
      }
    } else {
      iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
              objective, options.MaxIterations, options.StepTolerance,
              options.ObjectiveLimit);
    }

    emxFreeStruct_struct_T5(&c_workingset);
    emxFreeStruct_struct_T(&b_solution);
    emxFreeStruct_struct_T5(&b_workingset);
  }
}

//
// File trailer for driver1.cpp
//
// [EOF]
//
