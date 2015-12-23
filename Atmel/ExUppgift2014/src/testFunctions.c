/*
* testFunctions.c
*
* Created: 2015-10-10 16:06:54
*  Author: Stefan
*/
#include "asf.h"
#include "testFunctions.h"
#include "PWMCustom.h"
#include "global_variables.h"
#include "ADCCustom.h"
#include "delay.h"
#include "PIDRegulation.h"

// Cycles between 0,50 and 100% Duty Cycle on PWM
void testFans()
{
	while(1){
		PWMDutyCycle(999);
		printf("100\n");
		delay_ms(3000);
		
		PWMDutyCycle(0);
		printf("0\n");
		delay_ms(3000);
		
		PWMDutyCycle(500);
		printf("50\n");
		delay_ms(3000);
	}
}

void blinkTest()
{
	ioport_set_pin_dir(LED13, IOPORT_DIR_OUTPUT);
	
	int delay = 1000000;
	
	for(int i=0; i < delay; i++){
		ioport_set_pin_level(LED13, HIGH);

	}
	for (int i=0; i < delay; i++){
		
		ioport_set_pin_level(LED13, LOW);
	}
}

//void testReceive()
//{
	//ioport_set_pin_dir(LEDUART, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_dir(LEDUART2, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_dir(LED13, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_level(LED13, LOW);
	//
	////int a = 1;
	////	if(testByte == 0){
	//while (!uart_is_rx_ready (CONF_UART)){};
	//uart_read(CONF_UART, &testByte);
	//while (!uart_is_rx_ready (CONF_UART)){};
	//uart_read(CONF_UART, &testByte2);
	//delay_ms(100);
	////		}
	//if(testByte > 0)
	//{
		//ioport_set_pin_level(LEDUART, HIGH);
	//}
	//if(testByte2 > 0)
	//{
		//ioport_set_pin_level(LEDUART2, HIGH);
	//}
	//printf("%i\n", testByte);
//}

void testADC()
{
	while(1){
		// Read raw sensor distance from ADC
		distance = ADCReadSensor();
		printf("%i\n", distance);
		delay_ms(50);
	}
}
//
//void testFilter()
//{
	//while(1){
			//float temp = 0;
			//int k;
			//static float xbuff[M+1] = {0};
			//static float b[M+1] = {0.25,0.25,0.25,0.25};
//
			//// Read raw sensor distance from ADC
			//distance = ADCReadSensor();
//
			//for(k = M-1;k >= 0;k--)
			//{
				//xbuff[k+1] = xbuff[k];
			//}
			//xbuff[0] = distance;
//
			//for(k = 0;k <= M;k++)
			//{
				//temp += b[k]*xbuff[k];
			//}
			//distance = (uint16_t)temp;
//
			//printf("%i\n", distance);
			//delay_ms(50);
	//}
//}
//
