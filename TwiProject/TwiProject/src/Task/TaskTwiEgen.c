/*
 * TaskTwiEgen.c
 *
 * Created: 2017-05-10 09:49:32
 *  Author: Jounne
 */ 
#include <asf.h>
#include <ioport.h>
#include "TwiFunctions/TwiFunctions.h"

//Digital pin 7
#define Pinne PIO_PC23_IDX

xSemaphoreHandle signal_semafor = 0;

void task_twi(void *pvParameters){
	
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 2000;
	xLastWakeTime = xTaskGetTickCount();
	ioport_set_pin_dir(Pinne,IOPORT_DIR_OUTPUT);
	vSemaphoreCreateBinary(signal_semafor);
	
	int counter = 1;
	
	while (1){
		printf("In send task\n");
		//GOOGLA UPP FREERTOS macro för att byta från ticks till ms
		//xSemaphoreTake(signal_semafor,1000);
		ioport_set_pin_level(Pinne,HIGH);
		//send_test_package(Maxhastighet,TWI_SLAVE_PABYGGNAD);
		receive_package(TWI_SLAVE_PABYGGNAD);
		ioport_set_pin_level(Pinne,LOW);
		printf("END OF TASK\n");
		//xSemaphoreGive(signal_semafor);
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}