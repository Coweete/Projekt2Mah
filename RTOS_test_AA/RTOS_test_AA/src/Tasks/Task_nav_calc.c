/*
 * Task_Nav_Calc.c
 *
 * Created: 2017-05-17 13:10:45
 *  Author: André Ahlbertz 
 *  Modified: Elias H
 */ 

#include "Tasks/Task_Nav_Calc.h"


void task_nav_calc(void *pvParameters){
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



