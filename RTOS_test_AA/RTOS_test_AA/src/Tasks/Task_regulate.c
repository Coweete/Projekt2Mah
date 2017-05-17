/*
 * Task_Regulate.c
 *
 * Created: 2017-05-17 13:12:20
 *  Author: André Ahlbertz
 *  Modified: Elias H
 */ 
#include "Tasks/Task_Regulate.h"



void task_Regulate(void *pvParameters){
	initMotor();
	initDrive();
	initRegulator();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	while(1){
		if (distanceStop()){
			driveTo(0);
		}else {
			driveTo(100);
		}
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
 //	vTaskDelete( NULL );  // För en clean exit av tasken (Kasnke ej behövs)!
}