/*
 * task_blink.c
 *
 * Created: 2017-05-02 11:06:07
 *  Author: Jounne
 */ 
#include <asf.h>
#include <ioport.h>
#include <inttypes.h>
#include "task_blink.h"

//led pin
#define BlinkPib PIO_PB27_IDX

void task_blink(void *pvParameters){
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 500;
	xLastWakeTime = xTaskGetTickCount();
	ioport_set_pin_dir(BlinkPib,IOPORT_DIR_OUTPUT);
	uint8_t counter = 0;
	while (1){
		//puts("Task BLINKA");
		printf("BLINK\n");
		ioport_set_pin_level(BlinkPib,counter);
		//vTaskDelay(xTimeIncrement);
		counter = ~counter;
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}