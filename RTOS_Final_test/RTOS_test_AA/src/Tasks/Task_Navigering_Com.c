/*
 * Task_Navigering_Com.c
 *
 * Created: 2017-05-17 14:02:28
 *  Author: Elias H
 */ 
#include "Tasks/Task_Navigering_Com.h"

xSemaphoreHandle signal_semafor_Nav = 0;

void task_nav_com(void *pvParameters){
	vSemaphoreCreateBinary(signal_semafor_Nav);
	
	// N�gon Metod/ Ingen.
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1){
	//	if(xSemaphoreTake(signal_semafor_Nav,100){
			
		// Kod h�r.
		//xSemaphoreGive(signal_semafor_Nav);
	//	}
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
	//vTaskDelete( NULL );  // F�r en clean exit av tasken (Kasnke ej beh�vs)!
}