

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
#define ARDUINO 100
#include <Arduino.h>
#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void PWM_Driver_Outputs_wrapper(const real_T *duty,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
*/
#ifndef MATLAB_MEX_FILE

if(xD[0] == 1)
{
    // set PWM
    OCR4B = (int)duty[0]*319/100;
}

#endif
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Updates function
 *
 */
void PWM_Driver_Update_wrapper(const real_T *duty,
			real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
#define pwm_pin 7
#define pinA 2
#define pinB 3
if(xD[0] != 1)
{
  // put your setup code here, to run once:
  //Serial.begin(115200);
  pinMode(pwm_pin, OUTPUT);
  //pinMode(pinA, INPUT);
  //pinMode(pinB, INPUT);
  
  // configure PWM:
  TCCR4A = B00100011; //Mode 15, no prescaler (=1)
  TCCR4B = B00011001;
  OCR4AH = B00000001; //319 TOP value
  OCR4AL = B00111111;
  OCR4B = 160; // Default 50% duty cycle
    
  xD[0] = 1;
}
#endif
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
