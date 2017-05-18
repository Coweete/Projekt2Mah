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

//xSemaphoreHandle signal_semafor = 0;
uint8_t cases = 1, flag = 1,state = SOCK;
extern uint8_t data_received_pab[];

void task_twi(void *pvParameters){
	
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 5000;
	xLastWakeTime = xTaskGetTickCount();
	ioport_set_pin_dir(Pinne,IOPORT_DIR_INPUT);
	pa_sendstatus(TWI_CMD_ARM_INIT,0);
	int counter = 1;
	
	while (1){
		printf("In send task\n");
		switch(cases){
			case 1:
					printf("CASE 1");
					if (HIGH == flag){
						pa_sendstatus(TWI_CMD_PICKUP_START,SOCK);
						flag = 0;
					}
					receive_package(TWI_SLAVE_PABYGGNAD);
					if(2 == data_received_pab[1]){
						cases = 2;
						flag = 1;
					}
			break;
			case 2:
					printf("Case 2");
					if (HIGH == flag){
						pa_sendstatus(TWI_CMD_DROPOFF_START,0);
						flag = 0;
					}
					receive_package(TWI_SLAVE_PABYGGNAD);
					if(2 == data_received_pab[1]){
						cases = 2;
						flag = 1;
					}									
			break;
			case 3:
				if(LOW == ioport_get_pin_level(Pinne)){
					cases = 1;
				}
			break;	
		}
		printf("END OF TASK\n");
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}