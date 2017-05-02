/*
 * Interrupt_Handler.c
 *
 * Created: 2017-04-24 09:50:32
 *  Author: Elias Hussein
 */ 
// #include <asf.h>
// #include "task_KNAPP.h"
// #include "Interrupt_Handler.h"
// #include "FreeRTOSConfig.h"
// #include "FreeRTOS.h"
// 
// 
// void ToggleLedISR()
// #define Knapp PIO_PA15_IDX			//Digital Pinne 24
// {
// 	//int status;
// 	static portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
// 	if(xHigherPriorityTaskWoken == pdTRUE) {
// 	//	portYIELD_FROM_ISR();
// 	puts("F�R JAG ETT INTERRUPT D�?!!!!");
// 	}
// }
// 
// void ToggleLedTask(void *pvParameters) {
// 		xSemaphoreHandle xSemaphore;
// 		 vSemaphoreCreateBinary(xSemaphore);
// 	while(1) {
// 		puts("F�R JAG ETT INTERRUPT D�?!!!!");
// 		xSemaphoreTake(xSemaphore, portMAX_DELAY);
// 	}
// }
// 
// // Interrupt handler f�r vald pinne, dvs knappen just nu...
// // Handler kommer kallas vid trigging av pinnen som dess parameter s� fort ett interrupt sker
// 
// void hanldler(){
// 	puts("");
// 	pmc_enable_periph_clk(ID_PIOA);
// 	pio_set_input(PIOA, Knapp, PIO_PULLUP);
// 	pio_handler_set(PIOA, ID_PIOA, Knapp, PIO_IT_RISE_EDGE, task_KNAPP);
// 	pio_enable_interrupt(PIOA, Knapp);
// 	NVIC_EnableIRQ(PIOA_IRQn);
// 	puts("F�R JAG ETT INTERRUPT D�adasdasdasdasdasd?!!!!");
// }
// 
// void pin_edge_handler(const uint32_t id, const uint32_t index)
// {
// 	if ((id == ID_PIOA) && (index == Knapp)){
// 		if (pio_get(PIOA, PIO_TYPE_PIO_INPUT, Knapp))
// 		pio_clear(PIOA, PIO_PA23);
// 		else
// 		pio_set(PIOA, PIO_PA23);
// 		puts("F�R JAG ETT INTERRUPT D�adasdasdasdasdasd?!!!!");
// 	}
// }