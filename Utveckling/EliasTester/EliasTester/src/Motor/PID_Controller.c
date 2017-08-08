/*
* PID_Controller.c
*
* Created: 2017-05-02 11:02:25
*  Author: zoz
*/
#include <asf.h>
#include <ioport.h>
#include <inttypes.h>
#include "Delays/DelayFunctions.h"
#include "PID_Controller.h"
double input, output;
double error;
double dError;
double iError;
double K = 5;
double Ti = 1; //0.5 * period
double Td = 0.25; //0.125 * 2
double Ts = 0.12;
double w = 0;
double last_err= 0;
int r_count;
int l_count;
int speed1=1650;
int r_speed1=0;
int l_speed1=0;


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
void initMotor2(void){
	ioport_set_pin_dir(LEFT,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(RIGHT,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(R_RESET,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(L_RESET,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(R0,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R1,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R2,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R3,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R4,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R5,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L0,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L1,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L2,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L3,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L4,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L5,IOPORT_DIR_INPUT);
	
}

void pidCompute(double setpoint){
	r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
	+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
	ioport_set_pin_level(R_RESET,HIGH);	                                                          //hämta input värde frå pinnarna
	l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
	+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
	ioport_set_pin_level(L_RESET,HIGH);
	r_speed1=speed1;
	l_speed1=speed1;

	input = (r_count - l_count);
	error = (setpoint-input); //propotionella
	w = (w + error);
	iError = (w* (Ts/Ti)); //integral
	dError = ((error-last_err)* (Td/Ts)); // derivative
	output = (K * (error + iError + dError));
	last_err = error;
	
	if(output<0){
		r_speed1=speed1+output;
		l_speed1=speed1-output;
	}else if (output>0)
	{
		r_speed1=speed1-output;
		l_speed1=speed1+output;
	}
	
	moveForward1(l_speed1,r_speed1);
	ioport_set_pin_level(R_RESET,LOW);
	ioport_set_pin_level(L_RESET,LOW);
	
}
void pulseLeft1(int p1){
	ioport_set_pin_level(LEFT,HIGH);
	delayMicroseconds(p1);
	ioport_set_pin_level(LEFT,LOW);
}
void pulseRight1(int p2){
	ioport_set_pin_level(RIGHT,HIGH);
	delayMicroseconds(p2);
	ioport_set_pin_level(RIGHT,LOW);
}
void moveForward1(int l,int r){
	pulseLeft1(l);
	pulseRight1(r);
	delayMicroseconds(5250);
	//printf (" Felvarde:%d\n",e);
}