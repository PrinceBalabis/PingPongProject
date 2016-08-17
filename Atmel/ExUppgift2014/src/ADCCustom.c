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
	
	if (tempADCValue <= CENTIMETER_50_MAX)
	{
		return 50;
	} else if(tempADCValue > CENTIMETER_50_MAX && tempADCValue <= CENTIMETER_45_MAX)
	{
		return 45;
	}else if(tempADCValue > CENTIMETER_45_MAX && tempADCValue <= CENTIMETER_40_MAX)
	{
		return 40;
	}else if(tempADCValue > CENTIMETER_40_MAX && tempADCValue <= CENTIMETER_35_MAX)
	{
		return 35;
	}else if(tempADCValue > CENTIMETER_35_MAX && tempADCValue <= CENTIMETER_30_MAX)
	{
		return 30;
	}else if(tempADCValue > CENTIMETER_30_MAX && tempADCValue <= CENTIMETER_25_MAX)
	{
		return 25;
	}else if(tempADCValue > CENTIMETER_25_MAX && tempADCValue <= CENTIMETER_20_MAX)
	{
		return 20;
	}else if(tempADCValue > CENTIMETER_20_MAX && tempADCValue <= CENTIMETER_15_MAX)
	{
		return 15;
	}else if(tempADCValue > CENTIMETER_15_MAX)
	{
		return 10;
	}
}