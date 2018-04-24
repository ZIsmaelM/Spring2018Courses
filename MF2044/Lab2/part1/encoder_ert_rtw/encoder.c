/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: encoder.c
 *
 * Code generated for Simulink model 'encoder'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Apr 17 17:54:55 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "encoder.h"
#include "encoder_private.h"
#include "encoder_dt.h"

/* Block signals (auto storage) */
B_encoder_T encoder_B;

/* Block states (auto storage) */
DW_encoder_T encoder_DW;

/* Real-time model */
RT_MODEL_encoder_T encoder_M_;
RT_MODEL_encoder_T *const encoder_M = &encoder_M_;

/* Model step function */
void encoder_step(void)
{
  real_T rtb_Sum1;
  real_T u0;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_Sum1 = (encoder_DW.clockTickCounter < encoder_P.PulseGenerator_Duty) &&
    (encoder_DW.clockTickCounter >= 0L) ? encoder_P.PulseGenerator_Amp : 0.0;
  if (encoder_DW.clockTickCounter >= encoder_P.PulseGenerator_Period - 1.0) {
    encoder_DW.clockTickCounter = 0L;
  } else {
    encoder_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  encoder_B.Sum = rtb_Sum1 - encoder_P.Constant1_Value;

  /* S-Function (Encoder): '<Root>/S-Function Builder1' */
  Encoder_Outputs_wrapper(&encoder_B.SFunctionBuilder1,
    &encoder_DW.SFunctionBuilder1_DSTATE);

  /* Sum: '<Root>/Sum1' */
  rtb_Sum1 = encoder_B.Sum - encoder_B.SFunctionBuilder1;

  /* Sum: '<S1>/Sum' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  Gain: '<S1>/Proportional Gain'
   */
  u0 = encoder_P.DiscretePIDController_P * rtb_Sum1 +
    encoder_DW.Integrator_DSTATE;

  /* Saturate: '<S1>/Saturate' */
  if (u0 > encoder_P.DiscretePIDController_UpperSatu) {
    encoder_B.Saturate = encoder_P.DiscretePIDController_UpperSatu;
  } else if (u0 < encoder_P.DiscretePIDController_LowerSatu) {
    encoder_B.Saturate = encoder_P.DiscretePIDController_LowerSatu;
  } else {
    encoder_B.Saturate = u0;
  }

  /* End of Saturate: '<S1>/Saturate' */

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Constant'
   */
  encoder_B.Sum2 = encoder_B.Saturate + encoder_P.Constant_Value;

  /* S-Function (PWM_Driver): '<Root>/S-Function Builder' */
  PWM_Driver_Outputs_wrapper(&encoder_B.Sum2,
    &encoder_DW.SFunctionBuilder_DSTATE);

  /* Update for S-Function (Encoder): '<Root>/S-Function Builder1' */

  /* S-Function "Encoder_wrapper" Block: <Root>/S-Function Builder1 */
  Encoder_Update_wrapper(&encoder_B.SFunctionBuilder1,
    &encoder_DW.SFunctionBuilder1_DSTATE);

  /* Update for DiscreteIntegrator: '<S1>/Integrator' incorporates:
   *  Gain: '<S1>/Integral Gain'
   */
  encoder_DW.Integrator_DSTATE += encoder_P.DiscretePIDController_I * rtb_Sum1 *
    encoder_P.Integrator_gainval;

  /* Update for S-Function (PWM_Driver): '<Root>/S-Function Builder' */

  /* S-Function "PWM_Driver_wrapper" Block: <Root>/S-Function Builder */
  PWM_Driver_Update_wrapper(&encoder_B.Sum2, &encoder_DW.SFunctionBuilder_DSTATE);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.05s, 0.0s] */
    rtExtModeUpload(0, encoder_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.05s, 0.0s] */
    if ((rtmGetTFinal(encoder_M)!=-1) &&
        !((rtmGetTFinal(encoder_M)-encoder_M->Timing.taskTime0) >
          encoder_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(encoder_M, "Simulation finished");
    }

    if (rtmGetStopRequested(encoder_M)) {
      rtmSetErrorStatus(encoder_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  encoder_M->Timing.taskTime0 =
    (++encoder_M->Timing.clockTick0) * encoder_M->Timing.stepSize0;
}

/* Model initialize function */
void encoder_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)encoder_M, 0,
                sizeof(RT_MODEL_encoder_T));
  rtmSetTFinal(encoder_M, -1);
  encoder_M->Timing.stepSize0 = 0.05;

  /* External mode info */
  encoder_M->Sizes.checksums[0] = (842116208U);
  encoder_M->Sizes.checksums[1] = (3529333590U);
  encoder_M->Sizes.checksums[2] = (1504760694U);
  encoder_M->Sizes.checksums[3] = (2316979843U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    encoder_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(encoder_M->extModeInfo,
      &encoder_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(encoder_M->extModeInfo, encoder_M->Sizes.checksums);
    rteiSetTPtr(encoder_M->extModeInfo, rtmGetTPtr(encoder_M));
  }

  /* block I/O */
  (void) memset(((void *) &encoder_B), 0,
                sizeof(B_encoder_T));

  /* states (dwork) */
  (void) memset((void *)&encoder_DW, 0,
                sizeof(DW_encoder_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    encoder_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  encoder_DW.clockTickCounter = 0L;

  /* InitializeConditions for S-Function (Encoder): '<Root>/S-Function Builder1' */

  /* S-Function Block: <Root>/S-Function Builder1 */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        encoder_DW.SFunctionBuilder1_DSTATE = initVector[0];
      }
    }
  }

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Integrator' */
  encoder_DW.Integrator_DSTATE = encoder_P.Integrator_IC;

  /* InitializeConditions for S-Function (PWM_Driver): '<Root>/S-Function Builder' */

  /* S-Function Block: <Root>/S-Function Builder */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        encoder_DW.SFunctionBuilder_DSTATE = initVector[0];
      }
    }
  }
}

/* Model terminate function */
void encoder_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
