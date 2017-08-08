/*
* task_BLINKA.c
*
* Created: 2017-04-15 13:03:31
*  Author: Elias Hussein
*/
#include <asf.h>
#include "task_BLINKA.h"

void task_BLINKA(void *pvParameters)
{
//	xSemaphoreHandle signal_semafor = 0;
//	signal_semafor = xSemaphoreCreateMutex();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /*Wait for the next cycle. */
	//	if(xSemaphoreTake(signal_semafor,100)){
		//	puts("BLINKA TASKEN");
		//	ioport_set_pin_level(BlinkaGreen,HIGH);
			ioport_set_pin_level(BlinkaYellow,HIGH);
		//	ioport_set_pin_level(BlinkaRed,HIGH);
			delayMicroseconds(100000);
		//	ioport_set_pin_level(BlinkaGreen,LOW);
			ioport_set_pin_level(BlinkaYellow,LOW);
			//ioport_set_pin_level(BlinkaRed,LOW);
			delayMicroseconds(100000);
		//	xSemaphoreGive(signal_semafor);
 	//	}
		//vTaskDelay(500);
	}
	vTaskDelete( NULL );  // För en clean exit av tasken ( Kanske ej behövs)
}