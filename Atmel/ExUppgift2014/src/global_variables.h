/*
* global_variables.h
*
* Created: 2015-12-07 00:18:34
*  Author: Stefan
*/


#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_

extern xSemaphoreHandle sem;

/* PID / UART */
// Variables bellow are used for both PID calculation and storing values sent from Matlab
extern double kP_Gain;
extern double kI_Gain;
extern double kD_Gain;
extern int setPoint;

#define DTIME_MS 50
// Convert ms to s
//#define DTIME_SECONDS DTIME_MS/1000

extern uint8_t isMatlab;
extern int output_value;
extern int distance;
extern int error;
extern int old_error;

/* PWM */
pwm_channel_t pwm_channel;

#endif /* GLOBAL_VARIABLES_H_ */