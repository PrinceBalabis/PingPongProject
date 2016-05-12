/*
* global_variables.c
*
* Created: 2015-12-07 00:18:21
*  Author: Stefan & Prince
*/
#include <asf.h>
#include "global_variables.h"

xSemaphoreHandle sem = NULL;

/* PID */
// Processed values for the PID regulator, p_temp / divider ..
double kP_Gain = 0;
double kI_Gain = 0;
double kD_Gain = 0;
int32_t setPoint = 0;

uint8_t isMatlab = 1; // 1 for matlab, 0 for terminal debugging
int32_t output_value = 0;
int32_t distance = 0;
int32_t error = 0;
float I_Output = 0;
float D_Output = 0;
int32_t error_old = 0;
int32_t pwm_val = 0;
int32_t adc_filter_values[] = {1,1,1,1,1}; // 5 values array
	
	
int distanceTemp;