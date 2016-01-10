/*
* PIDTask.c
*
* Created: 2015-12-14 22:05:28
*  Author: Stefan
*/
#include <asf.h>
#include "PIDTask.h"
#include "global_variables.h"
#include "PIDRegulation.h"
#include "testFunctions.h"

void PIDRegulationTask (void *pvParameters)
{
	//	printf("PID Task initialized and PAUSED\n\r");
	
	// Pause here untill Matlab sent values
	xSemaphoreTake(sem, portMAX_DELAY);
	xSemaphoreTake(sem, portMAX_DELAY);
	
	portTickType xLastWakeTime = xTaskGetTickCount();
	const portTickType xFrequency =  DTIME_MS; // Run between 50-100ms
	
	for(;;){
		vTaskDelayUntil(&xLastWakeTime,xFrequency);	// Samplingstid
		PIDRegulate(); // Run PID
	}
}
