/*
 * Task_ultraLjud.c
 *
 * Created: 2017-05-17 14:10:01
 *  Author: Elias H
 */ 
#include "Tasks/Task_ultraLjud.h"

int stop=0;
long sensordistance = 0;
xSemaphoreHandle xBinarySemaphore;

void task_ultraLjud(void *pvParameters){
	
	vSemaphoreCreateBinary( xBinarySemaphore );
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	init_sensor();
	
	while (1){
		puts("Task SENSORRRRR");
		long duration;
		ioport_set_pin_level(TriggerPin,HIGH);
		delayMicroseconds(10000);
		ioport_set_pin_level(TriggerPin,LOW);
		duration = pulseins();
		sensordistance = (duration/42)/58.2;
		if(sensordistance <= 20){
			stop = 1;
		}else{
			stop = 0;
		}
		
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
	//vTaskDelete(NULL);
}

int pulseins(void){
	int state = 1;
	int flag = 0,clocktime;
	while(state){
		if(ioport_get_pin_level(EchoPin) && !flag){
			tc_start(TC0,0);
			flag = 1;
		}
		if(!ioport_get_pin_level(EchoPin) && flag)
		{
			clocktime = tc_read_cv(TC0,0);
			tc_stop(TC0,0);
			flag = 0;
			state = 0;
		}
	}
	return clocktime;
}

void init_sensor(void){
	ioport_set_pin_dir(TriggerPin,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EchoPin,IOPORT_DIR_INPUT);
}

int distanceStop(void){
	return stop;
}