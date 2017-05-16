
#include <asf.h>
#include <ioport.h>
#include <stdio.h>

#include "DelayFunctions.h"
#include "CalculateAngle.h"
#include "Regulator.h"
#include "Motorfunctions.h"
#include "Rotate.h"
#include "Drive.h"
#include "soundSensor.h"
#include "TwiFunctions/TwiComHandler.h"
#include "TwiFunctions/TwiFunctions.h"

#include <setjmp.h>
#include <stdio_serial.h>
#include "conf_board.h"
#include "consoleFunctions.h"
// #include "../unity/unity.h"					/* Contains declarations of all functions that Unity provides */
// #include "../Test/test_CalculateAngle.h"
 
#define SIGNAL_IN PIO_PC14_IDX
#define PICKUP PIO_PC13_IDX
#define DELIVER PIO_PC12_IDX


int OB1x= 20;
int OB1y = 30;
int OB2x = 30;
int OB2y = 30;
int OB3x = 40;
int OB3y = 50;   

int objDist = 40;
int sensor = 0;
int drive_dist = 0;

uint8_t c_counter = 0;
char rx[16];
int casen=0;

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


// static void configure_console(void)
// /* Enables feedback through the USB-cable back to terminal within Atmel Studio */
// /* Note that  the baudrate, parity and other parameters must be set in conf/conf_uart_serial.h */
// {
// 	const usart_serial_options_t uart_serial_options = {
// 		.baudrate = CONF_UART_BAUDRATE,
// 		.paritytype = CONF_UART_PARITY,
// 		.charlength = CONF_UART_CHAR_LENGTH,
// 		.stopbits = CONF_UART_STOP_BITS
// 	};
// 
// 	/* Configure console UART. */
// 	sysclk_enable_peripheral_clock(BOARD_USART1_BASE);
// 	usart_serial_init(CONF_UART, &uart_serial_options);
// }

// void USART1_Handler() {
// 	CONF_UART->US_CR |= (1 << US_CR_RSTRX);
// 	rx[c_counter++] = CONF_UART->US_RHR & US_RHR_RXCHR_Msk;
// 	if (c_counter > 15)
// 	{
// 		c_counter = 0;
// 		/*x1 = (rx[0] << 8) | (rx[1] << 0);
// 		y1 = (rx[2] << 8) | (rx[3] << 0);
// 		x2 = (rx[4] << 8) | (rx[5] << 0);
// 		y2 = (rx[6] << 8) | (rx[7] << 0);*/
// 	}
// 	
// }

// void stringToInt(uint16_t *p_variable, char *p_string) {
// 			*p_variable = (*p_string++ - '0') * 1000;
// 			*p_variable = *p_variable + (*p_string++ - '0') * 100;
// 			*p_variable = *p_variable + (*p_string++ - '0') * 10;
// 			*p_variable = *p_variable + (*p_string - '0');
// }

extern uint8_t data_received_pab[];
int main (void)
{
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	initRegulator();
	initMotor();
	initRotateMotor();
	configure_console();
	initDrive();
	init_sensor();
	init_twi_functions();
	
	ioport_set_pin_dir(SIGNAL_IN,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(PICKUP,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(DELIVER,IOPORT_DIR_OUTPUT);
	
	
// 	startupMeasure1(0,0);
// 	moveForward(1650,1650);
// 	delayMicroseconds(1000000);
// 	moveForward(1500,1500);
// 	startupMeasure2(20,20);
// 	delayMicroseconds(500000);
	
	
	
// 	char str1[4];
// 	char str2[4];
// 	char str3[4];
// 	char str4[4];
	uint16_t x1 = 0;
	uint16_t y1 = 0;
// 	uint16_t x2 = 0;
// 	uint16_t x3 = 0; //irrelevant
// 	uint16_t x4 = 0; //irrelevant
	
// 	UnityBegin("../Test/test_CalculateAngle.c");
// 	RUN_TEST(test_getX_diff,10);
// 	RUN_TEST(test_getY_diff,20);
// 	RUN_TEST(test_CalculateAngle,30);
// 	RUN_TEST(test_CalculatesetPoint,40);
// 	RUN_TEST(test_CalculateDistance,50);
	while(1){
		
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
// 		stringToInt(&x1, str1);
// 		stringToInt(&x2, str2);
// 		stringToInt(&x3, str3);
// 		stringToInt(&x4, str4);
// 			

// 	rotate(135);
// 	delayMicroseconds(500000);
// 	rotate(270);
// 	delayMicroseconds(500000);
		
		//sensor = readSensorValue();
		
		
 		char str[20];
//  	sprintf(str,"\nVinkel: %d",d);
//  	printf (str);

// 		
// 		sprintf(str,"\nSensor: %d",sensor);
//  		printf (str);
		 
		
		
		switch (casen)
		{
		case 0:
			//drive_dist = (sensor - objDist) / 1.36;
			//driveTo(objDist);
// 			sprintf(str,"\ndrive_dist: %d",drive_dist);
// 			printf (str);
// 			sprintf(str,"\nSensor: %d",sensor);
// 			printf (str);
		 	//break;
// 			 printf("case 0");
// 			 pa_sendstatus(TWI_CMD_PICKUP_START,SOCK);
			 ioport_set_pin_level(PICKUP,HIGH);
			 casen = 1;
			 break;
		case 1:
			
			if(ioport_get_pin_level(SIGNAL_IN)){
				casen = 2;
			}
			
// 			printf("case 1");
// 			printf ("\nPåbyggnad hämta");
// 			int conter = 1;
// 			while(conter){
// 				pa_sendstatus(TWI_CMD_PICKUP_STATUS,1);
// 				sprintf(str,"data recive %d",data_received_pab[1]);
// 				printf(str);
// 				if (data_received_pab[1] == 2){
// 					//pa_sendstatus(TWI_CMD_DROPOFF_START,1);
// 					casen = 2;
// 					}else{
// 						casen = 1;
// 				}
// 			}
			break;
		case 2:
			
			printf("case 2");
			rotate(90);
			casen = 3;
			break;
		case 3:	
			ioport_set_pin_level(DELIVER,HIGH);
// 			printf("\nPåbyggnad lämna");
// 			pa_sendstatus(TWI_CMD_DROPOFF_START,0);
			casen = 4;
			break;
		}
 		//casen++;

		
		

		
// 		switch (casen)
// 		{
// 		case 0:
// 			
// 			rotate(90);
// 		
// // 			sprintf(str,"\nCase: %d",casen);
// // 			printf (str);
// // 			rotate(calculateAngle(getY_diff(OB1x,x1),getX_diff(OB1y,y1)));
//  			delayMicroseconds(500000);
// 			break;
// 		case 1:
// 		
// 			rotate(225);
// // 			sprintf(str,"\nCase: %d",casen);
// // 			printf (str);
// // 			driveTo(calculateDistance(getY_diff(OB1x,x1),getX_diff(OB1y,y1)));
//  			delayMicroseconds(500000);
// 			break;
// // 		case 2:
// // 			sprintf(str,"\nCase: %d",casen);
// // 			printf (str);
// // 			rotate(calculateAngle(getY_diff(OB2x,OB1x),getX_diff(OB2y,OB1y)));
// // 			delayMicroseconds(500000);
// // 			break;
// // 		case 3:
// // 			sprintf(str,"\nCase: %d",casen);
// // 			printf (str);
// // 			driveTo(calculateDistance(getY_diff(OB2x,OB1x),getX_diff(OB2y,OB1y)));
// // 			delayMicroseconds(500000);
// // 			break;
// // 		case 4:
// // 			sprintf(str,"\nCase: %d",casen);
// // 			printf (str);
// // 			rotate(calculateAngle(getY_diff(OB3x,OB2x),getX_diff(OB3y,OB2y)));
// // 			delayMicroseconds(500000);
// // 			break;
// // 		case 5:
// // 			sprintf(str,"\nCase: %d",casen);
// // 			printf (str);
// // 			driveTo(calculateDistance(getY_diff(OB3x,OB2x),getX_diff(OB3y,OB2y)));	
// // 			delayMicroseconds(500000);	
// // 			break;
// 		default:
// 			
// 			moveForward(1500,1500);	
// 			delayMicroseconds(500000);
// 			break;
// 		}
// 		casen++;
	}
}