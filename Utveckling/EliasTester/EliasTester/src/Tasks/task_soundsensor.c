/*
 * task_soundsensor.c
 *
 * Created: 2017-05-02 10:15:24
 *  Author: Jounne
 */ 

#include <FreeRTOS.h>
#include <asf.h>
//#include "Sensor/soundSensor.h"
#include "Delays/DelayFunctions.h"

//DigitalPin 23
//#define EchoPin PIO_PA14_IDX
//DigitalPin 24
//#define TriggerPin PIO_PA15_IDX
//DIGITAL PIN 7
#define EchoPin PIO_PC23_IDX
//digital pin 8
#define TriggerPin PIO_PC22_IDX
#define Channel2

long sensordistance = 0;

int pulseins(){
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

void init_sensor(){
	ioport_set_pin_dir(TriggerPin,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EchoPin,IOPORT_DIR_INPUT);
}

void task_soundsensor(void *pvParameters){
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
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
	//vTaskDelete(NULL);
}
