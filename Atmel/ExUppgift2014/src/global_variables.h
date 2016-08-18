/*
* global_variables.h
*
* Created: 2015-12-07 00:18:34
*  Author: Stefan & Prince
*/


#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_
// -------------------------------CALIBRATION CONFIG-------------------------------------
// CALIBRATION CONFIG AREA

//PWM Change Gain
#define PWM_CHANGE_GAIN 0.6

// The ADC value at each centimeter. Also used for the setpoint function to convert cm to adc value for sensor
#define CENTIMETER_15_MAX 780 // På 10
#define CENTIMETER_20_MAX 590 // På 15
#define CENTIMETER_25_MAX 450 // På 20
#define CENTIMETER_30_MAX 320 // På 25
#define CENTIMETER_35_MAX 240 // På 30
#define CENTIMETER_40_MAX 190 // På 35
#define CENTIMETER_45_MAX 150 // På 40
#define CENTIMETER_50_MAX 130 // På 45
//#define CENTIMETER_DEFAULT 30

//Minimum/Maximum PWM output from PID-regulation
// #define PID_PWM_MIN 360
#define PID_PWM_MIN 0
#define PID_PWM_MAX 100

// ------------------------------CALIBRATION CONFIG--------------------------------------

// -------------------------------DEBUGGING CONFIG-------------------------------------
// DEBUGGING CONFIG AREA

/**
	P,I and D values
	set value 100 times bigger, for instance if you want 5.0, set P, I or D to 500.
	example for kP=5.0  insert "KP_GAIN_DEBUGGING 500"

	WORKING PID VALUES WITH SETPOINT
#define KP_GAIN_DEBUGGING 600
#define KI_GAIN_DEBUGGING 99
#define KD_GAIN_DEBUGGING 400
#define SETPOINT_DEBUGGING 10
**/
#define KP_GAIN_DEBUGGING 60
#define KI_GAIN_DEBUGGING 9
#define KD_GAIN_DEBUGGING 60
#define SETPOINT_DEBUGGING 20
// ------------------------------DEBUGGING CONFIG--------------------------------------




extern xSemaphoreHandle sem;

/* PID / UART */
// Variables bellow are used for both PID calculation and storing values sent from Matlab
extern double kP_Gain;
extern double kI_Gain;
extern double kD_Gain;
extern int32_t setPoint;

// dt �r 50ms-100ms
#define DTIME_MS 100
#define DT_SECONDS 0.1

// Convert ms to s
//#define DTIME_SECONDS DTIME_MS/1000

extern uint8_t isMatlab;
extern int32_t output_value;
extern int32_t distance;
extern int32_t error;
extern float I_Output;
extern float D_Output;
extern int32_t error_old;
extern int32_t pwm_val;
extern int32_t adc_filter_values[];

extern int distanceTemp;

/* PWM */
pwm_channel_t pwm_channel;

#endif /* GLOBAL_VARIABLES_H_ */
