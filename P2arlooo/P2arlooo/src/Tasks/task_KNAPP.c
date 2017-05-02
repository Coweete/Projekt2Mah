/*
* task_KNAPP.c
*
* Created: 2017-04-17 15:50:22
*  Author: Elias Hussein
*/
#include <asf.h>
#include <FreeRTOS.h>
#include "task_KNAPP.h"

xSemaphoreHandle signal_semafor = 0;

void task_KNAPP(void *pvParameters)
{
	vSemaphoreCreateBinary(signal_semafor);
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
	while(1){
		short xHigherPriorityTaskWoken = pdFALSE;
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /*Wait for the next cycle. */
		if(xSemaphoreTakeFromISR(signal_semafor,100)&&(ioport_get_pin_level(Knapp)==1)){
			puts("Knappen-------------INTRYCKT");
			ioport_set_pin_level(BlinkaGreen,HIGH);
			ioport_set_pin_level(BlinkaRed,LOW);
			xSemaphoreGiveFromISR(signal_semafor, &xHigherPriorityTaskWoken);
			//portYIELD();
			
		}
		else{
			ioport_set_pin_level(BlinkaGreen,LOW);
			ioport_set_pin_level(BlinkaRed,HIGH);
			puts("Knappen ------------ ej intryckt!");
			xSemaphoreGiveFromISR(signal_semafor, &xHigherPriorityTaskWoken);
		}
		vTaskDelay(1); //vTaskDelay(xTimeIncrement);
	}
	vTaskDelete( NULL );  // F�r en clean exit av tasken ( Kanske ej beh�vs)
}


void hanldler(){
	puts("123123213");
	pmc_enable_periph_clk(ID_PIOA);
	pio_set_input(PIOA, Knapp, PIO_PULLUP);
	pio_handler_set(PIOA, ID_PIOA, Knapp, PIO_IT_RISE_EDGE, task_KNAPP);
	pio_enable_interrupt(PIOA, Knapp);
	NVIC_EnableIRQ(PIOA_IRQn);
	puts("F�R JAG ETT INTERRUPT D�adasdasdasdasdasd?!!!!");
}

void pin_edge_handler(const uint32_t id, const uint32_t index)
{
	
	
	if ((id == ID_PIOA) && (index == Knapp)){
void task_KNAPP(void *pvParameters);
	}
}