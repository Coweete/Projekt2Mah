/*
 * task_vinkelGivare.c
 *
 * Created: 2017-04-10 10:45:06
 *  Author: Elias
 */ 
#include <asf.h>
#include "task_VinkelGivare.h"

void task_VinkelGivare(void *pvParameters)

{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
	while (1) {
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /*
		Wait for the next cycle. */
		

	}
	vTaskDelete( NULL );  // För en clean exit av tasken ( Kanske ej behövs)
}