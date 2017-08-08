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
#include <ioport.h>
#include <FreeRTOSConfig.h>

#include "Configs/DelayFunctions.h"
#include "Sensor/soundSensor.h"
#include "Motor/PID_Controller.h"
#include "Motor/Rotate.h"
#include "Motor/Motorfunctions.h"
#include "Task/task_soundsensor.h"
#include "Task/task_blink.h"
#include "Task/task_motor.h"
#include "StateM/stateMachine.h"

// uint8_t c_counter = 0;
// char rx[16];
// 
// void USART1_Handler() {
// 	CONF_UART->US_CR |= (1 << US_CR_RSTRX);
// 	rx[c_counter++] = CONF_UART->US_RHR & US_RHR_RXCHR_Msk;
// 	if (c_counter > 15)
// 	{
// 		c_counter = 0;
// 	}
// }
// 
// void stringToInt(uint16_t *p_variable, char *p_string) {
// 	*p_variable = (*p_string++ - '0') * 1000;
// 	*p_variable = *p_variable + (*p_string++ - '0') * 100;
// 	*p_variable = *p_variable + (*p_string++ - '0') * 10;
// 	*p_variable = *p_variable + (*p_string - '0');
// }



static void configure_console(void)
/* Enables feedback through the USB-cable back to terminal within Atmel Studio */
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY,
		.charlength = CONF_UART_CHAR_LENGTH,
		.stopbits = CONF_UART_STOP_BITS
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(BOARD_USART1_BASE);
	usart_serial_init(CONF_UART, &uart_serial_options);
	
// 	
// 	
// 	const usart_serial_options_t uart_serial_options = {
// 		.baudrate = CONF_UART_BAUDRATE,
// 		.paritytype = CONF_UART_PARITY
// 	};
// 
// 	/* Configure console UART. */
// 	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
// 	stdio_serial_init(CONF_UART, &uart_serial_options);
}

int main (void)
{
	
	
	//alla inits
	board_init();
	sysclk_init();
	init_sensor();
	delayInit();
	initMotor2();
	ioport_init();
	configure_console();
	P_regulator(3,5);
	
	xTaskCreate(task_motor,(const signed char* const) "Motor",TASK_MOTOR_STACK_SIZE,NULL,TASK_MOTOR_PRIORITY,NULL);
	xTaskCreate(task_soundsensor,(const signed char* const) "Soundsensor",TASK_SOUNDSENSOR_STACK_SIZE,NULL,TASK_SOUNDSENSOR_STACK_PRIORITY,NULL);
	//xTaskCreate(task_blink,(const signed char* const) "BlINK",TASK_BLINK_STACK_SIZE,NULL,TASK_BLINK_PRIORITY,NULL);
	vTaskStartScheduler();
	
	
// 	char str1[4];
// 	char str2[4];
// 	char str3[4];
// 	char str4[4];
// 	uint16_t x1 = 0;
// 	uint16_t x2 = 0;
// 	uint16_t x3 = 0; //irrelevant
// 	uint16_t x4 = 0; //irrelevant
	while (1)
	{
			
// 		str1[0] = rx[0];
// 		str1[1] = rx[1];
// 		str1[2] = rx[2];
// 		str1[3] = rx[3];
// 		
// 		str2[0] = rx[4];
// 		str2[1] = rx[5];
// 		str2[2] = rx[6];
// 		str2[3] = rx[7];
// 		
// 		str3[0] = rx[8];
// 		str3[1] = rx[9];
// 		str3[2] = rx[10];
// 		str3[3] = rx[11];
// 		
// 		str4[0] = rx[12];
// 		str4[1] = rx[13];
// 		str4[2] = rx[14];
// 		str4[3] = rx[15];
// 		
// 		stringToInt(&x1, str1);			//x1
// 		stringToInt(&x2, str2);			//y1
// 		stringToInt(&x3, str3);			//x2
// 		stringToInt(&x4, str4);			//y2
		}
	
}
