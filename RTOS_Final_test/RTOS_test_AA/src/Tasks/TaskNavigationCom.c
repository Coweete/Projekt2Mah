/*
 * TaskNavigationCom.c
 *
 * Created: 2017-05-12 14:57:34
 *  Author: Jounne
 */ 

#include <asf.h>
#include "TaskNavigationCom.h"
#include "TwiFunctions/TwiFunctions.h"

extern uint8_t data_received_nav[];
//xSemaphoreHandle signal_semafors = 0;
uint8_t navigation_break = 0;
int16_t currentX1,currentY1,currentX2,currentY2;
void task_nav_com(void *pvParameters){
	char ar[20];
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 1000;
	xLastWakeTime = xTaskGetTickCount();
	uint8_t arr[3];
	
	na_sendstatus(SOCKETXY);
	na_sendstatus(SQUAREXY);
	na_sendstatus(GLASSXY);
	na_sendstatus(BOXGOALXY);
	
	while(1){
		if(LOW == navigation_break){

			na_sendstatus(XY1);
			currentX1 = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
			currentY1 = ((data_received_nav[3] << 8) | (data_received_nav[4] << 0));
			na_sendstatus(XY2);
			currentX2 = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
			currentY2 = ((data_received_nav[3] << 8) | (data_received_nav[4] << 0));
			printf("recieved\n");
		}
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}
