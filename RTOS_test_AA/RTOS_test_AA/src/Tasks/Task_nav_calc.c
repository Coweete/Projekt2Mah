/*
 * Task_Nav_Calc.c
 *
 * Created: 2017-05-17 13:10:45
 *  Author: Andr� Ahlbertz 
 *  Modified: Elias H
 */ 

#include "Tasks/Task_Nav_Calc.h"


void task_nav_calc(void *pvParameters){
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



