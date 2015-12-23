#include <asf.h>
#include "delay.h"
#include "config/conf_board.h"
#include "config/conf_clock.h "
#include "global_variables.h"
#include "ADCCustom.h"
#include "PIDRegulation.h"
#include "PWMCustom.h"
#include "testFunctions.h"
#include "UARTFunctions.h"
#include "UARTTask.h"
#include "PIDTask.h"

int main (void)
{
	// Board init
	sysclk_init();
	board_init();
	ioport_init();

	delay_init();
	configure_console(); // Initialize UART

	PWMSetup();
	shieldInit();
	ADCSetup();
	
	//testFans(); // Loops fan speed
	//testFilter(); // Loops FIR-filtered sensor values
	//testADC(); // Loops sensor values
	
	//initialize binary semaphore
	vSemaphoreCreateBinary(sem);
	if( sem != NULL )
	{
		// The semaphore was created successfully.
		// The semaphore can now be used.
	}
	
	/* Creating the PID regulation task */
	//	printf("Created PIDRegulationTask\n\r");
	if (xTaskCreate(PIDRegulationTask, (const signed char * const) "PIDRegulation",
	TASK_PIDRegulation_STACK_SIZE, NULL, TASK_PIDRegulation_STACK_PRIORITY, NULL) != pdPASS)
	{
		printf("Failed to create PIDRegulationTask\r\n");
	}
	
	/* Creating the serial communication task */
	//	printf("Created SerialComTask\n\r");
	if (xTaskCreate(SerialComTask, (const signed char * const) "SerialComTask",
	TASK_SerialComTask_STACK_SIZE, NULL, TASK_SerialComTask_STACK_PRIORITY, NULL) != pdPASS)
	{
		printf("Failed to create SerialComTask\r\n");
	}
	
	///* Start the FreeRTOS scheduler running all tasks indefinitely*/
	vTaskStartScheduler();
	printf("Insufficient RAM\r\n");
	while(1);
	
}