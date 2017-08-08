/*
* task_LED.c
*
* Created: 2017-04-12 22:47:02
*  Author: Elias Hussein
*/
#include <asf.h>
#include "task_LED.h"

void task_LED(void *pvParameters)
{
	xSemaphoreHandle signal_semafor=0;
	signal_semafor = xSemaphoreCreateMutex();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
	
	while(1){
		
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* Wait for the next cycle. */
		if(xSemaphoreTake(signal_semafor,100)){
			puts("LED TASKENnnn");
			ioport_set_pin_level(LED,HIGH);
			delayMicroseconds(100000);
			ioport_set_pin_level(LED,LOW);
			delayMicroseconds(100000);
			xSemaphoreGive(signal_semafor);
			
		}
 		else{
 			printf("Failed");
 		}
		vTaskDelay(500);
	}
	vTaskDelete( NULL );  // För en clean exit av tasken ( Kanske ej behövs)
}