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
int16_t x1,y1,x2,y2;
void task_nav_com(void *pvParameters){
	char ar[20];
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 1000;
	xLastWakeTime = xTaskGetTickCount();
	uint8_t arr[3];
	

	
	while(1){
		if(LOW == navigation_break){
			na_sendstatus(SOCKETXY);
// 			na_sendstatus(SQUAREXY);
// 			na_sendstatus(GLASSXY);
// 			na_sendstatus(BOXGOALXY);
			na_sendstatus(XY1);
			x1 = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
			y1 = ((data_received_nav[3] << 8) | (data_received_nav[4] << 0));
// 			na_sendstatus(XY2);
// 			x2 = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
// 			y2 = ((data_received_nav[3] << 8) | (data_received_nav[4] << 0));
			printf("recieved\n");
			sprintf(ar,"16 bitar x1 :%d \n",x1);
			printf(ar);
			sprintf(ar,"16 bitar y1 :%d \n",y1);
			printf(ar);
// 			sprintf(ar,"16 bitar x2 :%d \n",x2);
// 			printf(ar);
// 			sprintf(ar,"16 bitar y2 :%d \n",y2);
// 			printf(ar);
		}
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}
