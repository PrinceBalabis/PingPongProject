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
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);			// 0-4095
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
	int tempADCValue = ADCReadSensor();
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