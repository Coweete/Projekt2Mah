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
		//	puts("Knappen-------------INTRYCKT");
			ioport_set_pin_level(BlinkaGreen,HIGH);
			ioport_set_pin_level(BlinkaRed,LOW);
			xSemaphoreGiveFromISR(signal_semafor, &xHigherPriorityTaskWoken);
			knapp_handler(); // FUNGERAR INTERRUPT NU F?!?!?!? NEJ VAD ÄR DETTA FÖR SKIT JAG KALLAR JU PÅ METODEN?
			//portYIELD();
			
		}
		else{
			ioport_set_pin_level(BlinkaGreen,LOW);
			ioport_set_pin_level(BlinkaRed,HIGH);
		//	puts("Knappen ------------ ej intryckt!");
			xSemaphoreGiveFromISR(signal_semafor, &xHigherPriorityTaskWoken);
		}
		vTaskDelay(100); //vTaskDelay(xTimeIncrement);
	}
	vTaskDelete( NULL );  // För en clean exit av tasken ( Kanske ej behövs)
}



void knapp_handler(){
	puts("123123213");
	pmc_enable_periph_clk(ID_PIOA);
	pio_set_input(PIOA, Knapp, PIO_PULLUP);
	pio_handler_set(PIOA, ID_PIOA, Knapp, PIO_IT_RISE_EDGE, pin_edge_handler);
	pio_enable_interrupt(PIOA, Knapp);
	NVIC_EnableIRQ(PIOA_IRQn);
//	puts("FÅR JAG ETT INTERRUPT DÅadasdasdasdasdasd?!!!!");
}



void pin_edge_handler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOA) && (index == Knapp)){
		 if (pio_get(PIOA, PIO_TYPE_PIO_INPUT, Knapp)){
		//	 puts("lal");
	}
}
}