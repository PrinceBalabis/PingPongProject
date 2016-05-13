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
	distance = ADCLinearValues();
	
	//uncomment for linear calibration
	//distance = ADCReadSensor();
	
	// P-regulation and invert error
	error = -1*(setPoint - distance);
	
	// I-regulation
	I_Output += error*DT_SECONDS;
	if(I_Output > 20){ // Remove windup induced lag
		I_Output = 20;
		} else if(I_Output < -20){
		I_Output = -20;
	}
	
	// D-regulation
	D_Output = (float)(error-error_old);
	error_old = error;
	
	// Add up P, I and D outputs
	if(kI_Gain != 0 && kD_Gain != 0){ // PID
		output_value = kP_Gain * (error +  (I_Output/kI_Gain) + (kD_Gain*D_Output));
		} else if(kI_Gain != 0 && kD_Gain == 0){ // PI
		output_value = kP_Gain * (error +  (I_Output/kI_Gain));
		} else if(kI_Gain == 0 && kD_Gain != 0){ // PD
		output_value = kP_Gain * (error + (kD_Gain*D_Output));
		} else if(kI_Gain == 0 && kD_Gain == 0){ //P
		output_value = kP_Gain * error;
		} else {
		output_value = kP_Gain * (error +  (I_Output/kI_Gain) + (kD_Gain*D_Output));
	}
	//output_value = (kP_Gain * (error + (I_Output / kI_Gain))); // PI regulering
	//output_value = (kP_Gain * (error + (kD_Gain * D_Output))); // PD regulering
	//output_value = (kP_Gain*error)+I_Output+D_Output;
	//output_value = (kP_Gain*error); // P regulator
	
	//Apply output from PID to pwm control
	//pwm_val = pwm_val+(float)(output_value*PWM_CHANGE_GAIN);
	pwm_val = pwm_val+output_value;
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
