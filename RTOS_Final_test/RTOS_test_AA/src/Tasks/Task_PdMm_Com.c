/*
 * Task_PdMm_Com.c
 *
 * Created: 2017-05-17 14:04:52
 *  Author: Elias H
 */ 
#include "Tasks/Task_PdMm_Com.h"
xSemaphoreHandle signal_semafor_pdmm = 0;

void task_pdmm_Com(void *pvParameters){
	vSemaphoreCreateBinary(signal_semafor_pdmm);
	// N�gon Metod/ Ingen.
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	
	while(1){
			//	if(xSemaphoreTake(signal_semafor_pdmm,100){
			
			// Kod h�r.
			//xSemaphoreGive(signal_semafor_pdmm);
			//	}
		
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
	//vTaskDelete( NULL );  // F�r en clean exit av tasken (Kasnke ej beh�vs)!
}