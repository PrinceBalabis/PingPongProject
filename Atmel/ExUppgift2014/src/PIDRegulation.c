/*
* PIDRegulation.c
*
* Created: 2015-10-10 16:05:52
*  Author: Stefan
*/
#include <asf.h>
#include "PIDRegulation.h"
#include "inttypes.h"
#include "PWMCustom.h"
#include "ADCCustom.h"
#include "global_variables.h"
#include "UARTFunctions.h"

/* PID Function */
void PIDRegulate(void){
	
	// moving average filter of sampled sensor values
	const int readingsAmount = 10;
	int valuesTotal = 0;
	for(int i = 0; i<readingsAmount-1; i++){
		valuesTotal += ADCReadSensor();
	}
	distance = valuesTotal / readingsAmount;
	
	// P-regulation
	error = (setPoint - distance);
	
	// I-regulation
	error_sum = (double)error_sum + (double)error;
	double I_Output;
	if(kI_Gain == 0)
	{
		I_Output = 0;
		} else {
		I_Output = (double)(DT_SECONDS/((double)kI_Gain))*error_sum;
	}
	
	// D-regulation
	double D_Output;
	
	if(error == 1)
	{
		D_Output = 0;
		} else {
		D_Output = (double)((kD_Gain*(error - error_old))/DT_SECONDS);
	}
	error_old = error;
	
	// Add up P, I and D outputs
	output_value = (double)((double)kP_Gain*(double)(error+I_Output+D_Output));
	
	// Protection vs overflow/underflow
	if (output_value < PID_PWM_MIN)
	{
		output_value = PID_PWM_MIN;
	}
	else if (output_value > PID_PWM_MAX)
	{
		output_value = PID_PWM_MAX;
	}

	// Write PID value to PWM
	PWMDutyCycle(output_value);
}
