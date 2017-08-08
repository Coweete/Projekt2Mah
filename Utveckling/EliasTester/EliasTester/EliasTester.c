/*
 * EliasTester.c
 *
 * Created: 2017-05-08 13:08:48
 *  Author: Elias H
 */ 
//	Inkluderar bibiloteken.
#include <asf.h>
#include <stdio.h>
#include <ioport.h>
#include <math.h>
#include "task.h"
#include "FreeRTOSConfig.h"
#include "delay.h"
#include "conf_board.h"
#include "Delays/DelayFunctions.h"
#include "Motor/Motorfunctions.h"
#include "Motor/PID_Controller.h"
/*#include "StateM/stateMachine.h"*/
// #include "Tasks/task_blink.h"
// #include "Tasks/task_motor.h"
// #include "Tasks/task_soundsensor.h"
#include "Interrupts/Interrupt_Handler.h"
#include "Navigering/Navi.h"


//För att hålla reda vad de mappade pinnarna motsvarar i SAM3x pin namn.
//https://www.arduino.cc/en/Hacking/PinMappingSAM3X

//	Definierar pinnar som jag använder.
#define LED PIO_PB27_IDX			//Digital Pinne 13 / Amber LED "L"
#define BlinkaGreen PIO_PD9_IDX		//Digital Pinne 30
#define BlinkaYellow PIO_PD1_IDX	//Digital Pinne 26
#define BlinkaRed PIO_PD3_IDX		//Digital Pinne 28
#define Knapp PIO_PA15_IDX			//Digital Pinne 24

/*Tillåter feedback till terminafönstret */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};
	
	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	printf("Konsolen reado\n");
	printf("===============\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	printf("Whilesatsen");
}
//handler();
int main (void)
{
	
	// Initialisera Due kortet */
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	initMotor2();
	ioport_init();
	configure_console();

uint16_t xPositionArlo=100;
uint16_t yPositionArlo=100;
uint16_t xpositionering1=10;
uint16_t ypositionering1=20;
double deltaX, deltaY, deltaXangle, deltaYangle;
//uint16_t xpositionering2;
//uint16_t ypositionering2;
double definedangle;

while(1){

double diff = deltaArloDiff(xpositionering1,xPositionArlo,ypositionering1,yPositionArlo);
double posUpdated = positionUpdateDiff(deltaX, deltaY);
double angulate = arloAngleCalculate(deltaXangle, deltaYangle);	
	calculateArloPosition();
	
			
		//xTaskCreate(task_motor,(const signed char* const) "Motor",TASK_MOTOR_STACK_SIZE,NULL,TASK_MOTOR_PRIORITY,NULL);
		//xTaskCreate(task_soundsensor,(const signed char* const) "Soundsensor",TASK_SOUNDSENSOR_STACK_SIZE,NULL,TASK_SOUNDSENSOR_STACK_PRIORITY,NULL);
		//xTaskCreate(task_blink,(const signed char* const) "BlINK",TASK_BLINK_STACK_SIZE,NULL,TASK_BLINK_PRIORITY,NULL);
		//xTaskCreate(task_stateMachine,(const signed char* const) "StateMachine",TASK_STATEMACHINE_STACK_SIZE,NULL,TASK_STATEMACHINE_PRIORITY,NULL);
	//Ser till att köra tasken.
	//vTaskStartScheduler();
}
}