/*
 * Task_Navigering_Com.c
 *
 * Created: 2017-05-17 14:02:28
 *  Author: Elias H
 */ 
#include "Tasks/Task_Navigering_Com.h"

void task_nav_com(void *pvParameters){
	// N�gon Metod/ Ingen.
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1){
		// Kod h�r.
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}