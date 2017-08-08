/*
* task_BLINKA.c
*
* Created: 2017-04-12 13:33:53
*  Author: Elias
*/
#include <asf.h>
#include "task_BLINKA.h"

#define Blinkared PIO_PB26_IDX
#define Blinkayellow PIO_PA14_IDX

void task_BLINKA(void *pvParameters)
{
	xSemaphoreHandle signal_semafor = 0;
	signal_semafor = xSemaphoreCreateMutex();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /*Wait for the next cycle. */
		if(xSemaphoreTake(signal_semafor,1000)){
			ioport_set_pin_level(Blinkared,HIGH);
			delayMicroseconds(100000);
			ioport_set_pin_level(Blinkared,LOW);
			delayMicroseconds(100000);
			ioport_set_pin_level(Blinkayellow,HIGH);
			delayMicroseconds(500000);
			ioport_set_pin_level(Blinkayellow,LOW);
			delayMicroseconds(500000);
			xSemaphoreGive(signal_semafor);
		}
		else{
			printf("Failed");
		}
		vTaskDelay(100);
	}
	vTaskDelete( NULL );  // För en clean exit av tasken ( Kanske ej behövs)
}