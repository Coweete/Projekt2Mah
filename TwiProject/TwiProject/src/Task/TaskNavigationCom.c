/*
 * TaskNavigationCom.c
 *
 * Created: 2017-05-12 14:57:34
 *  Author: Jounne
 */ 

#include <asf.h>
#include "TaskNavigationCom.h"
#include "TwiFunctions/TwiFunctions.h"

//extern data_received_nav[];
//xSemaphoreHandle signal_semafors = 0;
/*
void task_nav_com(void *pvParameters){
/*
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 5000;
	xLastWakeTime = xTaskGetTickCount();
	uint8_t arr[3];	
	while(1){
		printf("In nav task");
		//send_test_package(Lyckat_lyft,TWI_SLAVE_NAVIGERING);
		receive_package(TWI_SLAVE_NAVIGERING);
		printf("End of nav task");
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}
*/