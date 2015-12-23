/*
* UARTFunctions.c
*
* Created: 2015-11-14 01:49:37
*  Author: Stefan
*/

#include <asf.h>
#include "UARTFunctions.h"
#include "uart.h"
#include "conf_uart_serial.h"
#include "global_variables.h"

void configure_console(void){
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
	.paritytype = CONF_UART_PARITY};
	// Configure console UART.
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	// configure RX0 pin as pull-up otherwise it won't receive anything (only receive 0)
	ioport_set_pin_mode(PIO_PA8_IDX, IOPORT_MODE_PULLUP);
}

/* Function that receives values from Matlab */
void getPIDValues()
{
	// divier which is used to decode encoded doubles sent from Matlab
	const uint8_t divider = 100;
	
	isMatlab = 0; // 1 for matlab, 0 for terminal debugging
	uint8_t kP_Gain_temp = 0;
	uint8_t kI_Gain_temp = 0;
	uint8_t kD_Gain_temp = 0;
	uint8_t setPointCm = 0;
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	}
	uart_read(CONF_UART, &isMatlab);
	if(!isMatlab){
		printf("Terminal debugging enabled\n");
	}
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	}
	uart_read(CONF_UART, &kP_Gain_temp);
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	uart_read(CONF_UART, &kI_Gain_temp);
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	uart_read(CONF_UART, &kD_Gain_temp);
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	uart_read(CONF_UART, &setPointCm);
	
	//Convert to correct data types
	kP_Gain = (double) ((double) kP_Gain_temp / divider);
	kI_Gain = (double) (kI_Gain_temp / divider);
	kD_Gain = (double) (kD_Gain_temp / divider);
	
	//kP_Gain = (double) ((double) kP_Gain);
	//kI_Gain = (double) (kI_Gain);
	//kD_Gain = (double) (kD_Gain);
	
	//kP_Gain = 1.5;
	//kI_Gain = 0;
	//kD_Gain = 0;
	//distanceSetCM = 40;
	
	//distanceSetCM = (uint8_t) distanceSetCM_temp;
	
	switch(setPointCm){
		case 10 :
		setPoint = 3340;
		break;
		
		case 20:
		setPoint = 1800;
		break;
		
		case 30 :
		setPoint = 1550;
		break;
		
		case 40 :
		setPoint = 1350;
		break;
		
		case 50 :
		setPoint = 1250;
		break;
		
		default:
		setPoint = 1350;
		break;
		printf("Invalid distance\n");
	}
	
	printf("Received:\n");
	if(!isMatlab){
		printf("Received:\n");
		printf("%u", kP_Gain_temp);
		printf("%u", kI_Gain_temp);
		printf("%u", kD_Gain_temp);
		printf("%u", setPointCm);
	}
	
}

/* Function that sends values to Matlab */
void sendValues(){
	if(!isMatlab){
		printf("Values:\n");
	}
	printf("%i\n\r", error);
	printf("%i\n\r", output_value);
	printf("%i\n\r", distance);
	printf("%i\n\r", setPoint);
}
