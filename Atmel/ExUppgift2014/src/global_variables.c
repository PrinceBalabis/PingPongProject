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
int setPoint = 0;

uint8_t isMatlab = 1; // 1 for matlab, 0 for terminal debugging
int output_value = 0;
int distance = 0;
int error = 0;
int error_sum = 0;
int error_old = 0;
