/*
 * Task_Regulate.c
 *
 * Created: 2017-05-17 13:12:20
 *  Author: André Ahlbertz
 *  Modified: Elias H
 */ 
#include "Tasks/Task_Regulate.h"
#include <asf.h>

// extern int stop;
// 
// xSemaphoreHandle signal_semafor =0;
// 
// void task_Regulate(void *pvParameters){
// 	
// 	printf("\nTask Regulate");
// 	
// 	vSemaphoreCreateBinary(signal_semafor);
// 	
// 	portTickType xLastWakeTime;
// 	const portTickType xTimeIncrement = 150;
// 	xLastWakeTime = xTaskGetTickCount();
// 	while(1){
// 		if (xSemaphoreTake(signal_semafor,100)){
// 			printf("\nDrive 0");
// 			moveForward(1500,1500);
// 		}else {
// 			printf("\nDrive 100");
// 			driveTo(100);
// 		}
// 		//vTaskDelay(xTimeIncrement);
// 		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
// 	}
//  //	vTaskDelete( NULL );  // För en clean exit av tasken (Kasnke ej behövs)!
// }

// void addOne(uint32_t id, uint32_t index){
// 	printf("\nInterrupt");
// 	if ((id == ID_PIOC) && (index == PIO_PC9)){
// 		xSemaphoreGiveFromISR(signal_semafor,NULL);
// 		printf ("\nOk");
// 		}else{
// 		printf("\nError");
// 	}
// }

// void init_interrupt(void){
// 	printf("\nInit_interrupt ok");
// 	
// 	pmc_enable_periph_clk(ID_PIOC);
// 	
// 	pio_set_input(PIOC,PIO_PC9,PIO_PULLUP);			//INPUT VIKTIGT!!!
// 	
// 	pio_handler_set(PIOC,ID_PIOC,PIO_PC9,PIO_IT_HIGH_LEVEL,addOne);
// 	
// 	NVIC_EnableIRQ(PIOC_IRQn);
// 	
// 	pio_enable_interrupt(PIOC,PIO_PC9);
// 	
// 	
// }