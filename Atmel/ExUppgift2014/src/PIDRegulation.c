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
	
	// Calculate errors for P,I and D
	error = (setPoint - distance);
	double I_Output = (I_Output + ((double)old_error * DTIME_MS));
	double D_Output = (double) (((double)error - (double)old_error) / DTIME_MS);
	old_error = error;
	
	// Add up P, I and D outputs with gains
	//output_value = (P_CONSTANT * (error + (I_CONSTANT*I_SET) + (D_SET * D_CONSTANT)));
	output_value = ((kP_Gain*error) + (kI_Gain*I_Output) + (kD_Gain*D_Output));

	// Protection vs overflow/underflow
	if (output_value <= 300)
	{
		output_value = 300;
	}
	else if (output_value > 999)
	{
		output_value = 999;
	}

	// Write PID value to PWM
	PWMDutyCycle(output_value);
}
