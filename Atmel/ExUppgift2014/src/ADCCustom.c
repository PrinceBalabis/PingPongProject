/*
* ADCCustom.c
*
* Created: 2015-10-10 16:03:29
*  Author: Stefan & Prince
*/
#include <asf.h>
#include "ADCCustom.h"
#include "global_variables.h"
#include "PWMCustom.h"

/* Setup Function for ADC */
void ADCSetup()
{
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 20000000, 0);		// Configure for maximum frequency @ 20 MHz
	adc_configure_timing(ADC, 0, 0, 0);
	adc_set_resolution(ADC, ADC_MR_LOWRES);			// 0-1024
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);				// trig just by software
	adc_enable_channel(ADC, ADC_CHANNEL_10);				// PB17 - AD8 for Arduino Due
}

/* Read ADC value*/
int ADCReadSensor()
{
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);  // Wait until DRDY(Data Ready) is HIGH
	return adc_get_latest_value(ADC);
}

/* Linear ADC Value*/
int ADCLinearValues()
{
	for(int i = 0; i<4; i++){ // Remove the oldest value
		adc_filter_values[i] = adc_filter_values[i+1];
	}
	adc_filter_values[4] = ADCReadSensor(); // Save the latest ADC value at the back of the array.
	uint32_t adc_filter_values_total = 0;
	for(int i = 0; i<5; i++) {// Add up all the values
		adc_filter_values_total += adc_filter_values[i];
	}
	int tempADCValue = adc_filter_values_total / 5; // Get the average

	if(tempADCValue < CENTIMETER_50){
		return 50;
		} else if(tempADCValue > CENTIMETER_50 && tempADCValue < CENTIMETER_45){
		return 50;
		} else if(tempADCValue > CENTIMETER_45 && tempADCValue < CENTIMETER_40){
		return 45;
		} else if(tempADCValue > CENTIMETER_40 && tempADCValue < CENTIMETER_35){
		return 40;
		} else if(tempADCValue > CENTIMETER_35 && tempADCValue < CENTIMETER_30){
		return 35;
		} else if(tempADCValue > CENTIMETER_30 && tempADCValue < CENTIMETER_25){
		return 30;
		} else if(tempADCValue > CENTIMETER_25 && tempADCValue < CENTIMETER_20){
		return 25;
		} else if(tempADCValue > CENTIMETER_20 && tempADCValue < CENTIMETER_15){
		return 20;
		} else if(tempADCValue > CENTIMETER_15 && tempADCValue < CENTIMETER_10){
		return 15;
		} else if(tempADCValue > CENTIMETER_10){
		return 10;
	}
	return CENTIMETER_DEFAULT;
}

int readThrough()
{
	static float xbuff[M+1] = {0};
	static float b[M+1] = {0.25,0.25,0.25,0.25};
	int k;
	float temp = 0;
	
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);  // Wait until DRDY(Data Ready) is HIGH
	distanceTemp = adc_get_latest_value(ADC);
	
	for(k = M-1;k >= 0;k--)
	{
		xbuff[k+1] = xbuff[k];
	}
	xbuff[0] = distanceTemp;
	
	for(k = 0;k <= M;k++)
	{
		temp += b[k]*xbuff[k];
	}
	distanceTemp = (uint16_t)temp;
	
	if (distanceTemp <= 290)
	{
		return 50;
	} else if(distanceTemp > 290 && distanceTemp <= 310)
	{
		return 45;
	}else if(distanceTemp > 310 && distanceTemp <= 340)
	{
		return 40;
	}else if(distanceTemp > 340 && distanceTemp <= 360)
	{
		return 35;
	}else if(distanceTemp > 360 && distanceTemp <= 405)
	{
		return 30;
	}else if(distanceTemp > 405 && distanceTemp <= 470)
	{
		return 25;
	}else if(distanceTemp > 470 && distanceTemp <= 525)
	{
		return 20;
	}else if(distanceTemp > 525 && distanceTemp <= 650)
	{
		return 15;
	}else if(distanceTemp > 650)
	{
		return 10;
	}
}
