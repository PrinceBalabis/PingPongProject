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

	//double I_Output = (I_Output + ((double)error_sum);
	
	// D-regulation
	double D_Output;
	
	if(error == 1)
	{
		D_Output = 0;
		} else {
		D_Output = (double)((kD_Gain*(error - error_old))/DT_SECONDS);
		//double D_Output = (double) (((double)error - (double)error_sum) / DTIME_MS);
	}
	error_old = error;
	
	// Add up P, I and D outputs
	//output_value = (double)kP_Gain*error;
	output_value = (double)((double)kP_Gain*(double)(error+I_Output+D_Output));
	
	//printf("oP: %u\n\r", (uint16_t)(output_value));
	//printf("oP: %u\n\r", (uint16_t)(error));
	//printf("oI: %u\n\r", (uint16_t)(I_Output));
	//printf("oD: %u\n\r", (uint16_t)(D_Output));
	
	//printf("kP: %u\n\r", (uint16_t)(kP_Gain));
	//printf("error: %u\n\r", (uint16_t)(error));
	//printf("output_value: %u\n\r", (uint16_t)(output_value));
	
	//output_value = (P_CONSTANT * (error + (I_CONSTANT*I_SET) + (D_SET * D_CONSTANT)));
	//output_value = ((kP_Gain*error) + (kI_Gain*I_Output) + (kD_Gain*D_Output));

	// Protection vs overflow/underflow
	if (output_value < 300)
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
