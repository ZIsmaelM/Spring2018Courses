/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: driver_PWM_private.h
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

#ifndef RTW_HEADER_driver_PWM_private_h_
#define RTW_HEADER_driver_PWM_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void PWM_Driver_Outputs_wrapper(const real32_T *duty,
    const real_T *xD);
  extern void PWM_Driver_Update_wrapper(const real32_T *duty,
    real_T *xD);

#ifdef __cplusplus

}
#endif
#endif                                 /* RTW_HEADER_driver_PWM_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
