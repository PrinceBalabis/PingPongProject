/*
* global_variables.c
*
* Created: 2015-12-07 00:18:21
*  Author: Stefan
*/
#include <asf.h>
#include "global_variables.h"

xSemaphoreHandle sem = NULL;

/* PID */
// Processed values for the PID regulator, p_temp / divider ..
uint8_t P_CONSTANT_temp = 0;
uint8_t I_CONSTANT_temp = 0;
uint8_t D_CONSTANT_temp = 0;
double P_CONSTANT = 0;
double I_CONSTANT = 0;
double D_CONSTANT = 0;

uint8_t distanceSetCM_temp = 0;
int distanceSetCM = 0;

uint8_t dTime_temp = 0;
double dTime = 0;
uint8_t dTimeRtos = 0;

int output_value = 0;
int distance = 0;
int error = 0;
int old_error = 0;

uint8_t testByte;
uint8_t testByte2;





