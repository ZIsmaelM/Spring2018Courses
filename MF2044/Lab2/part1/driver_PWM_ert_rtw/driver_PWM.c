/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: driver_PWM.c
 *
 * Code generated for Simulink model 'driver_PWM'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Apr 17 17:08:15 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "driver_PWM.h"
#include "driver_PWM_private.h"
#include "driver_PWM_dt.h"

/* Block states (auto storage) */
DW_driver_PWM_T driver_PWM_DW;

/* Real-time model */
RT_MODEL_driver_PWM_T driver_PWM_M_;
RT_MODEL_driver_PWM_T *const driver_PWM_M = &driver_PWM_M_;

/* Model step function */
void driver_PWM_step(void)
{
  /* S-Function (PWM_Driver): '<Root>/S-Function Builder' incorporates:
   *  Constant: '<Root>/Constant'
   */
  PWM_Driver_Outputs_wrapper(&driver_PWM_P.Constant_Value,
    &driver_PWM_DW.SFunctionBuilder_DSTATE);

  /* Update for S-Function (PWM_Driver): '<Root>/S-Function Builder' incorporates:
   *  Constant: '<Root>/Constant'
   */

  /* S-Function "PWM_Driver_wrapper" Block: <Root>/S-Function Builder */
  PWM_Driver_Update_wrapper(&driver_PWM_P.Constant_Value,
    &driver_PWM_DW.SFunctionBuilder_DSTATE);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.05s, 0.0s] */
    rtExtModeUpload(0, driver_PWM_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.05s, 0.0s] */
    if ((rtmGetTFinal(driver_PWM_M)!=-1) &&
        !((rtmGetTFinal(driver_PWM_M)-driver_PWM_M->Timing.taskTime0) >
          driver_PWM_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(driver_PWM_M, "Simulation finished");
    }

    if (rtmGetStopRequested(driver_PWM_M)) {
      rtmSetErrorStatus(driver_PWM_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  driver_PWM_M->Timing.taskTime0 =
    (++driver_PWM_M->Timing.clockTick0) * driver_PWM_M->Timing.stepSize0;
}

/* Model initialize function */
void driver_PWM_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)driver_PWM_M, 0,
                sizeof(RT_MODEL_driver_PWM_T));
  rtmSetTFinal(driver_PWM_M, -1);
  driver_PWM_M->Timing.stepSize0 = 0.05;

  /* External mode info */
  driver_PWM_M->Sizes.checksums[0] = (2755483502U);
  driver_PWM_M->Sizes.checksums[1] = (678996360U);
  driver_PWM_M->Sizes.checksums[2] = (2137845673U);
  driver_PWM_M->Sizes.checksums[3] = (527561207U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    driver_PWM_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(driver_PWM_M->extModeInfo,
      &driver_PWM_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(driver_PWM_M->extModeInfo, driver_PWM_M->Sizes.checksums);
    rteiSetTPtr(driver_PWM_M->extModeInfo, rtmGetTPtr(driver_PWM_M));
  }

  /* states (dwork) */
  (void) memset((void *)&driver_PWM_DW, 0,
                sizeof(DW_driver_PWM_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    driver_PWM_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* InitializeConditions for S-Function (PWM_Driver): '<Root>/S-Function Builder' incorporates:
   *  Constant: '<Root>/Constant'
   */

  /* S-Function Block: <Root>/S-Function Builder */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        driver_PWM_DW.SFunctionBuilder_DSTATE = initVector[0];
      }
    }
  }
}

/* Model terminate function */
void driver_PWM_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
