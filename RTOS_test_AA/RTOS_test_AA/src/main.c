
// Elias & André.
// Main Program, includes necessary libraries and header files. Initiates methods, Tasks are created and Task Scheduler executes.
#include <asf.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <stdio.h>
#include <ioport.h>
#include "task.h"
// #include "Tasks/Task_Kamera.h"
// #include "Tasks/Task_nav_calc.h"
// #include "Tasks/Task_Navigering_Com.h"
// #include "Tasks/Task_PdMm_Com.h"
#include "Tasks/Tasks.h"
//#include "Tasks/Task_regulate.h"
#include "Functions/Motorfunctions.h"
#include "Functions/DelayFunctions.h"
#include "Functions/ConsoleFunctions.h"
#include "Functions/calculations.h"
#include "Functions/TaskFunctions.h"

// Antagligen bättre skapa för de olika tasken istället.
//xSemaphoreHandle xBinarySemaphore;

// xSemaphoreHandle signal_semafor =0;
// 
// void addOne(uint32_t id, uint32_t index);
// void init_interrupt(void);
// 
// void addOne(uint32_t id, uint32_t index){
// 	printf("\nInterrupt");
// 	if ((id == ID_PIOC) && (index == PIO_PC9)){
// 		printf ("\nOk");
// 		}else{
// 		printf("\nError");
// 	}
// }
// 
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



int main (void)
{
	board_init();
	sysclk_init();
	ioport_init();
	delayInit();
	ioport_init();
	configure_console();
	init_sensor();
	initMotor();
	//initDrive();
	//initRegulator();
	init_taskFunctions();		
	
	
	
	
	printf("\nInit ok");
	
// Behövs inte men kan vara bra att kolla ifall icke är null!
	
//	vSemaphoreCreateBinary( xBinarySemaphore );
//	if( xBinarySemaphore != NULL ){
		
// 		if (xTaskCreate(task_kamera, (const signed char * const) "KAMERA", TASK_KAMERA_STACK_SIZE, NULL, TASK_KAMERA_STACK_PRIORITY, NULL) != pdPASS) {
// 			printf("Failed the Camera Task\r\n");
// 		}
// 		
		if (xTaskCreate(task_nav_calc, (const signed char * const) "NAV_CALCULATOR", TASK_NAV_CALC_STACK_SIZE, NULL, TASK_NAV_CALC_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the Navigation Calculator Task\r\n");
		}
		
// 		if (xTaskCreate(task_nav_com, (const signed char * const) "NAV_COMMUNICATION", TASK_NAVIGERING_COM_STACK_SIZE, NULL, TASK_NAVIGERING_COM_STACK_PRIORITY, NULL) != pdPASS) {
// 			printf("Failed the Navigation Communication Task\r\n");
// 		}
// 		
// 		if (xTaskCreate(task_pdmm_Com, (const signed char * const) "PDMM_COMMUNICATION", TASK_PDMM_COM_STACK_SIZE, NULL, TASK_PDMM_COM_STACK_PRIORITY, NULL) != pdPASS) {
// 			printf("Failed the PDMM Communication Task\r\n");
// 		}
		
		if (xTaskCreate(task_Regulate, (const signed char * const) "REGULATOR", TASK_REGULATE_STACK_SIZE, NULL, TASK_REGULATE_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the Regulator Task\r\n");
		}
 		
		if (xTaskCreate(task_ultraLjud, (const signed char * const) "ULTRALJUD SENSOR", TASK_ULTRALJUD_STACK_SIZE, NULL, TASK_ULTRALJUD_STACK_PRIORITY, NULL) != pdPASS) {
			printf("Failed the UltraDistance Sensor Task\r\n");
		}
		
		
		vTaskStartScheduler();
		
		
	//}
}

