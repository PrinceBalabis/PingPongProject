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
	const uint8_t divider = 100;
	const uint8_t timeDivider = 10;
	
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	}
	uart_read(CONF_UART, &P_CONSTANT_temp);
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	uart_read(CONF_UART, &I_CONSTANT_temp);
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	uart_read(CONF_UART, &D_CONSTANT_temp);
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	uart_read(CONF_UART, &dTime_temp);
	while (!uart_is_rx_ready (CONF_UART)){
		vTaskDelay(1);
	};
	uart_read(CONF_UART, &distanceSetCM_temp);
	
	P_CONSTANT = (double) ((double) P_CONSTANT_temp / divider);
	I_CONSTANT = (double) (I_CONSTANT_temp / divider);
	D_CONSTANT = (double) (D_CONSTANT_temp / divider);
	
	distanceSetCM = (uint8_t) distanceSetCM_temp;

	dTime = (double) ((double)dTime_temp / timeDivider);
	dTimeRtos = (uint8_t) (dTime_temp * 10);
	
	switch(distanceSetCM){
		case 10 :
		distanceSetCM = 3340; // 3270 - 3470
		break;
		
		case 20:
		distanceSetCM = 1850; // 1780 - 1900
		break;
		
		case 30 :
		distanceSetCM = 1600; // 1550 - 1650
		break;
		
		case 40 :
		distanceSetCM = 1500; // 1450 - 1550
		break;
		
		case 50 :
		distanceSetCM = 1300; // 1250 - 1350
		break;
		
		default:
		printf("Invalid distance\n");
	}
}
/* Function that sends values to Matlab */
void sendValues(){
	printf("%i\n\r", error);
	printf("%i\n\r", output_value);
	printf("%i\n\r", distance);
	printf("%i\n\r", distanceSetCM);
}
