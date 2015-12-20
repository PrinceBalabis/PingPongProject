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
	// double P_SET = 0;
	double I_SET = 0;
	double D_SET = 0;
	float temp = 0;
	int k;
	static float xbuff[M+1] = {0};
	static float b[M+1] = {0.25,0.25,0.25,0.25};
	
	// Read raw sensor distance from ADC
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);
	distance = adc_get_latest_value(ADC);
	
	/* FIR filter */
	for(k = M-1;k >= 0;k--)
	{
		xbuff[k+1] = xbuff[k];
	}
	xbuff[0] = distance;
	
	for(k = 0;k <= M;k++)
	{
		temp += b[k]*xbuff[k];
	}
	
	distance = (uint16_t)temp;
	

	/* Count moving average */
	// 	const int calminReadings = 100;
	// 	int readTotalMin = 0;
	// 	for(int i = 0; i<calminReadings-1; i++){
	// 		readTotalMin += ADCReadSensor();
	// 	}
	// 	distance = readTotalMin / calminReading
	// Calculate error
	error = (distanceSetCM - distance);
	
	I_SET = (I_SET + (old_error * dTime));
	D_SET = (double) ((error - old_error) / dTime);
	old_error = error;
	
	output_value = (P_CONSTANT * (error + (I_CONSTANT*I_SET) + (D_SET * D_CONSTANT)));

	/* Protection vs overflow */
	if (output_value <= 0)
	{
		output_value = 0;
	}
	else if (output_value > 999)
	{
		output_value = 999;
	}

	// Write PID value to PWM
	PWMDutyCycle(output_value);
}
