/*
* Task_Kamera.c
*
* Created: 2017-05-17 14:03:36
*  Author: Elias H
*/
#include "Tasks/Task_Kamera.h"

void task_kamera(void *pvParameters){
	// Någon Metod/ Ingen.
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1){
		// Kod här.
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
	//vTaskDelete( NULL );  // För en clean exit av tasken (Kasnke ej behövs)!
}