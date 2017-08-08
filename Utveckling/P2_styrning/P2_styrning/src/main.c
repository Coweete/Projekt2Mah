/**
 * \file
 *
 * \brief Empty user application template
 *
 */

//Styrning


#include <asf.h>
#include <ioport.h>
#include "DelayFunctions.h"
#include "conf_board.h"
#include "Motorfunctions.h"
#include "PID_Controller.h"
#include "Rotate.h"
#include "Position.h"
#include "StateMachine.h"
//#define LED PIO_PB27_IDX

#define LEFT PIO_PC4_IDX
#define RIGHT PIO_PC5_IDX
//högra räknare
#define R0 PIO_PA15_IDX
#define R1 PIO_PD1_IDX
#define R2 PIO_PD3_IDX
#define R3 PIO_PD9_IDX
#define R4 PIO_PD10_IDX
#define R5 PIO_PC2_IDX
#define R_RESET PIO_PB26_IDX
//vänstra räknaren
#define L0 PIO_PD0_IDX
#define L1 PIO_PD2_IDX
#define L2 PIO_PD6_IDX
#define L3 PIO_PA7_IDX
#define L4 PIO_PC1_IDX
#define L5 PIO_PC3_IDX
#define L_RESET PIO_PA14_IDX
#define k1 PIO_PC28_IDX 
#define LED1 PIO_PC22_IDX 
#define LED3 PIO_PC29_IDX  //pin10
//definition för omvandling från bool till int
#define TRUE 1 
#define FALSE 0

#define TESTPINOUT11 PIO_PD7_IDX
#define TESPININ12 PIO_PD8_IDX
int n=0;
int state;

uint8_t c_counter = 0;
char rx[16];

//int i=0;
//int speed=1500;
void USART1_Handler() {
	CONF_UART->US_CR |= (1 << US_CR_RSTRX);
	rx[c_counter++] = CONF_UART->US_RHR & US_RHR_RXCHR_Msk;
	if (c_counter > 15)
	{
		c_counter = 0;
	}
	
}

void stringToInt(uint16_t *p_variable, char *p_string) {
	*p_variable = (*p_string++ - '0') * 1000;
	*p_variable = *p_variable + (*p_string++ - '0') * 100;
	*p_variable = *p_variable + (*p_string++ - '0') * 10;
	*p_variable = *p_variable + (*p_string - '0');
}
//int d=0;			//0=left, 1=right
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
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	configure_console();
	initMotor();
	initMotor3();
	ioportinit();
	//pulseOut(1850);
	//delayMicroseconds(1100);
	//pulseOut(1850);
	//delayMicroseconds(5250);
//	delayMicroseconds(1000);
	ioport_set_pin_dir(TESTPINOUT11,IOPORT_DIR_OUTPUT);
	printf("HEJ");
		/*ioport_set_pin_level(R_RESET,HIGH);
		ioport_set_pin_level(L_RESET,HIGH);
	
		ioport_set_pin_dir(TESPININ12,IOPORT_DIR_INPUT);
		ioport_set_pin_level(TESTPINOUT11,HIGH);
	//	int counter =0;*/
		char str1[4];
		char str2[4];
		char str3[4];
		char str4[4];
		uint16_t x1 = 0;
		uint16_t x2 = 0;
		uint16_t x3 = 0; //irrelevant
		uint16_t x4 = 0; //irrelevant
		n = x1;
	while(1){	
		str1[0] = rx[0];
		str1[1] = rx[1];
		str1[2] = rx[2];
		str1[3] = rx[3];
		
		str2[0] = rx[4];
		str2[1] = rx[5];
		str2[2] = rx[6];
		str2[3] = rx[7];
		
		str3[0] = rx[8];
		str3[1] = rx[9];
		str3[2] = rx[10];
		str3[3] = rx[11];
		
		str4[0] = rx[12];
		str4[1] = rx[13];
		str4[2] = rx[14];
		str4[3] = rx[15];
		
		stringToInt(&x1, str1);
		stringToInt(&x2, str2);
		stringToInt(&x3, str3);
		stringToInt(&x4, str4);
		ioport_set_pin_level(TESTPINOUT11,HIGH);
	//	P_regulator(0);
		//pidCompute(0);
	//	P_regulator(2,4);
		//rotate(180);
		moveForward(1850,1850);
		delayMicroseconds(1000);
		ioport_set_pin_level(TESTPINOUT11,LOW);
		delayMicroseconds(500000);
		int knapp;
		knapp = ioport_get_pin_level(k1);
		if (knapp==1)
		{
			//pushButton1(instance);
			//ioport_set_pin_level(LED3,knapp);
			int state =0;			
		}
	if(knapp==2)
	{
		int state = 1;
	}	
		switch(state){
			case 0:
			ioport_set_pin_level(LED3,HIGH);
			delayMicroseconds(100000);
			case 1:
			P_regulator(2,2);
			break;
		}
	}

}





