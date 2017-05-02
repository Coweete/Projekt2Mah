/*
 * task_motor.c
 *
 * Created: 2017-05-02 10:15:57
 *  Author: Jounne
 */ 
#include <asf.h>

#include "task_motor.h"
#include "Motor/Motorfunctions.h"

extern long sensordistance;

void task_motor(void *pvParameters){
	initMotor();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		if(sensordistance<10){
			moveForward(1500,1500);
		}else{
			P_regulator(0);
			vTaskDelay(1000);
		}
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}