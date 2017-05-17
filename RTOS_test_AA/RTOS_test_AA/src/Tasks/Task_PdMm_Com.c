/*
 * Task_PdMm_Com.c
 *
 * Created: 2017-05-17 14:04:52
 *  Author: Elias H
 */ 
#include "Tasks/Task_PdMm_Com.h"

void task_pdmm_Com(void *pvParameters){
	// Någon Metod/ Ingen.
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1){
		// Kod här.
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}