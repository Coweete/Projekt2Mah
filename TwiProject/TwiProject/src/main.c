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
#include "Test/TestVikingarna.h"

#define TASK_TWI_SIZE	(1024/sizeof(portSTACK_TYPE))
#define TASK_TWI_NAV    3
#define TASK_TWI_PRIO	2
#define TASK_BLINK		1


int main (void)
{

	board_init();
	sysclk_init();
	configureConsole();
	ioport_init();
	delay_init();
	printf("Start of inint\n");
	init_twi_functions();
	
	//testloop();

	//pa_sendstatus(TWI_CMD_PICKUP_START,0);
	//na_sendstatus(XY1);
	
	xTaskCreate(task_nav_com,(const signed char* const) "navigation",TASK_TWI_SIZE,NULL,TASK_TWI_NAV,NULL);
	//xTaskCreate(task_blink,(const signed char* const) "blink",TASK_TWI_SIZE,NULL,TASK_BLINK,NULL);
	//xTaskCreate(task_twi,(const signed char* const) "com",TASK_TWI_SIZE,NULL,TASK_TWI_PRIO,NULL);
	vTaskStartScheduler();
	
	while (1){
		
	}
}

//För att testa med skicka till påbyggnaden!
// 	printf("Start pickup\n");
// 	pa_sendstatus(TWI_CMD_PICKUP_START,SOCK);
//
// 	pa_sendstatus(TWI_CMD_PICKUP_STATUS,1);
// 	int conter = 1;
// 	while(conter){
// 		pa_sendstatus(TWI_CMD_PICKUP_STATUS,1);
// 		sprintf(str,"data recive 1%d",data_received_pab[1]);
// 		printf(str);
// 		sprintf(str,"data recive 2%d",data_received_pab[2]);
// 		printf(str);
// 		if (data_received_pab[1] == 2){
// 			pa_sendstatus(TWI_CMD_DROPOFF_START,1);
// 		}else{
// 		}
// 		delay_ms(1000);
// 	}
//
