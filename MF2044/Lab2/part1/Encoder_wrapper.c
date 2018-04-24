

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

    int encoderCounts = 0;
    int revolutions = 0;
    float velocity = 0;

ISR(TIMER5_OVF_vect){
  velocity = (revolutions+(float)encoderCounts/ppr)*30.5*60;
  encoderCounts = 0;
  revolutions = 0;
}
void readEncoderA(void){
      if(digitalRead(pinA)==HIGH){
        if(digitalRead(pinB)==HIGH){ 
          encoderCounts = encoderCounts + 1; //CW
          if(encoderCounts==ppr){
            revolutions += 1;
            encoderCounts = 0;
          }

        }else{
          encoderCounts = encoderCounts - 1; //CCW
          if(encoderCounts==-ppr){
            revolutions -= 1;
            encoderCounts = 0;
          }
        }
      }else{
        if(digitalRead(pinB)==LOW){ 
          encoderCounts = encoderCounts + 1; //CW
          if(encoderCounts==ppr){
            revolutions += 1;
            encoderCounts = 0;
          }
        }else{
          encoderCounts = encoderCounts - 1; //CCW
          if(encoderCounts==-ppr){
            revolutions -= 1;
            encoderCounts = 0;
          }
        }
      }
      //Serial.println(encoderCounts);
    }

    void readEncoderB(void){
      if(digitalRead(pinB)==HIGH){
        if(digitalRead(pinA)==LOW){ 
          encoderCounts = encoderCounts + 1; //CW
          if(encoderCounts==ppr){
            revolutions += 1;
            encoderCounts = 0;
          }
        }else{
          encoderCounts = encoderCounts - 1; //CCW
          if(encoderCounts==-ppr){
            revolutions -= 1;
            encoderCounts = 0;
          }
        }
      }else{
        if(digitalRead(pinA)==HIGH){ 
          encoderCounts = encoderCounts + 1; //CW
          if(encoderCounts==ppr){
            revolutions += 1;
            encoderCounts = 0;
          }
        }else{
          encoderCounts = encoderCounts - 1; //CCW
          if(encoderCounts==-ppr){
            revolutions -= 1;
            encoderCounts = 0;
          }
        }
      }
      //Serial.println(encoderCounts);
    }
#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define y_width 1
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
void Encoder_Outputs_wrapper(real_T *spd,
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
    spd[0] = velocity;
    encoderCounts = 0;
    revolutions = 0;
}

#endif
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Updates function
 *
 */
void Encoder_Update_wrapper(real_T *spd,
			real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
#define pinA 2
#define pinB 3

if(xD[0] != 1)
{   
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    
    attachInterrupt(pinA, readEncoderA, CHANGE);
    attachInterrupt(pinB, readEncoderB, CHANGE);
    
    // Configure timer interrupt
    TCCR5A = 0;
    TCCR5B = B00000010;
    TIMSK5 = 1;
    
    xD[0] = 1;
}
#endif
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
