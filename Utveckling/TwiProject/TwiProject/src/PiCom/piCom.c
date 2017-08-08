/*
 * piCom.c
 *
 * Created: 2017-05-12 14:16:34
 *  Author: Jounne
 */ 

#include <asf.h>

#include "piCom.h"

void init_piCom(){
	
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};
}

char read_pi(){
	char pi_position;
	printf("data");
	scanf(pi_position);
	return pi_position;
}