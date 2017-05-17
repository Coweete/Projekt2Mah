
#include <asf.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <stdio.h>
#include <ioport.h>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "Tasks/Task_nav_calc.h"
#include "Tasks/Task_regulate.h"
#include "Functions/Motorfunctions.h"
#include "Functions/DelayFunctions.h"
#include "Functions/ConsoleFunctions.h"


int main (void)
{
	board_init();
	sysclk_init();
	ioport_init();
	delayInit();
	ioport_init();
	configure_Console();
	
		if (xTaskCreate(task_x, (const signed char * const) "task_x", TASK_X_STACK_SIZE, NULL, TASK_X_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the X Task\r\n");
		}
		
		if (xTaskCreate(task_x, (const signed char * const) "task_x", TASK_X_STACK_SIZE, NULL, TASK_X_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the X Task\r\n");
		}
		
		if (xTaskCreate(task_x, (const signed char * const) "task_x", TASK_X_STACK_SIZE, NULL, TASK_X_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the X Task\r\n");
		}
		
		if (xTaskCreate(task_x, (const signed char * const) "task_x", TASK_X_STACK_SIZE, NULL, TASK_X_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the X Task\r\n");
		}
		
		if (xTaskCreate(task_x, (const signed char * const) "task_x", TASK_X_STACK_SIZE, NULL, TASK_X_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the X Task\r\n");
		}
		
		if (xTaskCreate(task_x, (const signed char * const) "task_x", TASK_X_STACK_SIZE, NULL, TASK_X_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the X Task\r\n");
		}
		
		if (xTaskCreate(task_x, (const signed char * const) "task_x", TASK_X_STACK_SIZE, NULL, TASK_X_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the X Task\r\n");
		}
	
	
//	xTaskCreate();
//	xTaskCreate();
//	xTaskCreate();
//	xTaskCreate();
//	xTaskCreate();
//	xTaskCreate();
		
		
	vTaskStartScheduler();
	
	
}
