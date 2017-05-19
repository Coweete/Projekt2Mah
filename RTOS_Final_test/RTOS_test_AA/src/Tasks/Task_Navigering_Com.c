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
	
	// Någon Metod/ Ingen.
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1){
	//	if(xSemaphoreTake(signal_semafor_Nav,100){
			
		// Kod här.
		//xSemaphoreGive(signal_semafor_Nav);
	//	}
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
	//vTaskDelete( NULL );  // För en clean exit av tasken (Kasnke ej behövs)!
}