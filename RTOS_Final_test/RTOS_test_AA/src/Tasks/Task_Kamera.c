/*
* Task_Kamera.c
*
* Created: 2017-05-17 14:03:36
*  Author: Elias H
*/
#include "Tasks/Task_Kamera.h"

void task_kamera(void *pvParameters){
	// N�gon Metod/ Ingen.
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1){
		// Kod h�r.
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
	//vTaskDelete( NULL );  // F�r en clean exit av tasken (Kasnke ej beh�vs)!
}