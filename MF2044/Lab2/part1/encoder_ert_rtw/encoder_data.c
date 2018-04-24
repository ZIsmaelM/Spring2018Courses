/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: encoder_data.c
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

/* Block parameters (auto storage) */
P_encoder_T encoder_P = {
  0.02,                                /* Mask Parameter: DiscretePIDController_I
                                        * Referenced by: '<S1>/Integral Gain'
                                        */
  -50.0,                               /* Mask Parameter: DiscretePIDController_LowerSatu
                                        * Referenced by: '<S1>/Saturate'
                                        */
  0.02,                                /* Mask Parameter: DiscretePIDController_P
                                        * Referenced by: '<S1>/Proportional Gain'
                                        */
  50.0,                                /* Mask Parameter: DiscretePIDController_UpperSatu
                                        * Referenced by: '<S1>/Saturate'
                                        */
  2000.0,                              /* Expression: 2000
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  200.0,                               /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  100.0,                               /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  0.05,                                /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  1000.0F,                             /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<Root>/Constant1'
                                        */
  50.0F                                /* Computed Parameter: Constant_Value
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
