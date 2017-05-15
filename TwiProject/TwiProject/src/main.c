/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "FreeRTOS.h"
#include "consoleFunctions.h"
#include "TwiFunctions/TwiFunctions.h"
#include "Task/TaskTwiEgen.h"
#include "Task/task_blink.h"
#include "TwiFunctions/TwiComHandler.h"
#include "Task/TaskNavigationCom.h"
#include "PiCom/piCom.h"

#define TASK_TWI_SIZE	(1024/sizeof(portSTACK_TYPE))
#define TASK_TWI_NAV    3
#define TASK_TWI_PRIO	2
#define TASK_BLINK		1

extern uint8_t data_received_nav[];

int main (void)
{

	board_init();
	sysclk_init();
	configureConsole();
	ioport_init();
	//delay_init();
	init_twi_functions();
	

	printf("start sending to navigation");
	send_package(TWI_CMD_ERROR,TWI_SLAVE_NAVIGERING);
	receive_package(TWI_SLAVE_NAVIGERING);
	char str[20];
	sprintf(str,"Data receive %d",data_received_nav[1]);
	printf(str);
	sprintf(str,"Data receive %d",data_received_nav[2]);
	printf(str);
	
	
	/*
	xTaskCreate(task_nav_com,(const signed char* const) "navigation",TASK_TWI_SIZE,NULL,TASK_TWI_NAV,NULL);
	xTaskCreate(task_blink,(const signed char* const) "blink",TASK_TWI_SIZE,NULL,TASK_BLINK,NULL);
	xTaskCreate(task_twi,(const signed char* const) "com",TASK_TWI_SIZE,NULL,TASK_TWI_PRIO,NULL);
	vTaskStartScheduler();
	*/
	while (1){
		
	}
}


	/*
	//send_package(16);
	printf("SEND TO FIRST\n");
	send_package(Identifiering);
	printf("Recive from first\n");
	recive_package();
	printf("skriv i consolen \n");
	sscanf("%i",*sa);
	sprintf(sa,"input: %i",tesas);
	printf("Input: ");
	printf(sa);
	*/
	