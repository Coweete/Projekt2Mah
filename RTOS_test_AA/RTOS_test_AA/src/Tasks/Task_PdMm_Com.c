/*
 * Task_PdMm_Com.c
 *
 * Created: 2017-05-17 14:04:52
 *  Author: Elias H
 */ 
#include "Tasks/Task_PdMm_Com.h"

void task_pdmm_Com(void *pvParameters){
	// N�gon Metod/ Ingen.
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1){
		// Kod h�r.
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}