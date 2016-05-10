/*
* PIDRegulation.c
*
* Created: 2015-10-10 16:05:52
*  Author: Stefan & Prince
*/
#include <asf.h>
#include "PIDRegulation.h"
#include "inttypes.h"
#include "PWMCustom.h"
#include "ADCCustom.h"
#include "global_variables.h"
#include "UARTFunctions.h"

void PRegulatorZN(void){
	distance = ADCLinearValues();
	
	// P-regulation
	error = (setPoint - distance);
	output_value = 525+(error*kP_Gain);
	pwm_val = output_value;
	// Write PID value to PWM
	PWMDutyCycle(pwm_val);
}

/* PID Function */
void PIDRegulate(void){

	// moving average filter of sampled sensor values
	for(int i = 0; i<4; i++){ // Remove the oldest value
		adc_filter_values[i] = adc_filter_values[i+1];
	}
	adc_filter_values[4] = ADCLinearValues(); // Save the latest ADC value at the back of the array.
	uint32_t adc_filter_values_total = 0;
	for(int i = 0; i<5; i++) {// Add up all the values
		adc_filter_values_total += adc_filter_values[i];
	}
	distance = adc_filter_values_total / 5; // Get the average
	
	//uncomment for linear calibration
	//distance = ADCReadSensor();
	
	// P-regulation
	error = -1*(setPoint - distance);
	
	// D-regulation
	
	//if(error == 1)
	//{
	//D_Output = 0;
	//} else {
	D_Output = (float)((error-error_old) / DTIME_MS);
	//}
	error_old = error;
	
	// I-regulation
	//if(kI_Gain == 0)
	//{
	//	I_Output = 0;
	//} else {
	I_Output += (error * DTIME_MS);
	//}
	
	// Add up P, I and D outputs
	output_value = (kP_Gain * error) + (kD_Gain * D_Output) + (kI_Gain * I_Output);
	//output_value = (kP_Gain * (error + (I_Output / kI_Gain))); // PI regulering
	//output_value = (kP_Gain * (error + (kD_Gain * D_Output))); // PD regulering
	//output_value = (kP_Gain*error)+I_Output+D_Output;
	//output_value = (kP_Gain*error); // P regulator
	
	//Apply output from PID to pwm control
	pwm_val = pwm_val+(float)(output_value*PWM_CHANGE_GAIN);
	//pwm_val = output_value;
	
	// Protection vs overflow/underflow
	if (pwm_val < PID_PWM_MIN)
	{
		pwm_val = PID_PWM_MIN;
	}
	else if (pwm_val > PID_PWM_MAX)
	{
		pwm_val = PID_PWM_MAX;
	}
	
	// Write PID value to PWM
	PWMDutyCycle(pwm_val);
	
}
