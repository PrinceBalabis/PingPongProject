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

/* PID Function */
void PIDRegulate(void){

	// moving average filter of sampled sensor values
// 	uint32_t valuesTotal = 0;
// 	for(int i = 0; i<FILTER_AVERAGE_SAMPLES-1; i++){
// 		valuesTotal += ADCReadSensor();
// 	}
// 	distance = valuesTotal / FILTER_AVERAGE_SAMPLES;
	distance = ADCLinearValues();

	// P-regulation
	error = (setPoint - distance);

	// D-regulation
	double D_Output;

	//if(error == 1)
	//{
	//D_Output = 0;
	//} else {
	D_Output = (double)(kD_Gain * (error-error_old) * 1000.0 / DTIME_MS);
	//}
	error_old = error;

	// I-regulation
	double I_Output;
	//if(kI_Gain == 0)
	//{
	//	I_Output = 0;
	//} else {
		I_Output = (double)(I_Output_old + kI_Gain * error * DT_SECONDS);
		I_Output_old = I_Output;
	//}

	// Add up P, I and D outputs
	output_value = (kP_Gain*error)+I_Output+D_Output;
	
	//Apply output from PID to pwm control 
	pwm_val = pwm_val+(output_value*0.5); 
	
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
