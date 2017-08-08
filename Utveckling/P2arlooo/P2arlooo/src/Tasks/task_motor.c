/*,
 * task_motor.c
 *
 * Created: 2017-05-02 10:15:57
 *  Author: Jounne
 */ 
#include <asf.h>

#include "task_motor.h"
#include "Motor/PID_Controller.h"
#include "Motor/Motorfunctions.h"
#include "Motor/Rotate.h"
extern long sensordistance;
int x_pos = 0;
int x_dest = 25;
int b =0 ;		//Börvärde
int u=0;		//Ärvärde

int n=0;

uint8_t c_counter = 0;
char rx[16];

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

void task_motor(void *pvParameters){
	initMotor2();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount();
	
	char str1[4];
	char str2[4];
	char str3[4];
	char str4[4];
	uint16_t x1 = 0;
	uint16_t x2 = 0;
	uint16_t x3 = 0; //irrelevant
	uint16_t x4 = 0; //irrelevant
	
	n=x2;
	
	while (1)
	{	
		
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
		
		stringToInt(&x1, str1);			//x1
		stringToInt(&x2, str2);			//y1
		stringToInt(&x3, str3);			//x2
		stringToInt(&x4, str4);			//y2
		
		if(x1 == 300){
			moveForward(1500,1500);
		}else{
			//P_regulator(3,5);	
		}
		
		
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}


