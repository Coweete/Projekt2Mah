/*
* task_KNAPP.c
*
* Created: 2017-04-17 15:50:22
*  Author: Elias Hussein
*/
#include <asf.h>
#include "task_KNAPP.h"

void task_KNAPP(void *pvParameters)
#define Knapp PIO_PD0_IDX
#define BLINKAKNAPP PIO_PB26_IDX
{
	xSemaphoreHandle signal_semafor = 0;
	signal_semafor = xSemaphoreCreateMutex();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /*Wait for the next cycle. */
		if(xSemaphoreTake(signal_semafor,100)&& (ioport_get_pin_level(Knapp)==HIGH)){
			ioport_set_pin_level(BLINKAKNAPP,LOW);
			delayMicroseconds(500000);
			xSemaphoreGive(signal_semafor);
		}
		else{
				printf("ehej");
		}
		vTaskDelay(xTimeIncrement);
	}
	vTaskDelete( NULL );  // För en clean exit av tasken ( Kanske ej behövs)
}