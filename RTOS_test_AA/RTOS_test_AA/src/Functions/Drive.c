/*
 * Drive.c
 *
 * Created: 2017-05-08 16:52:33
 *  Author: André Ahlbertz
 */ 

#include <asf.h>
#include <ioport.h>
#include <stdlib.h>
#include <inttypes.h>
#include "Functions/Regulator.h"
#include "Functions/Motorfunctions.h"
#include "Functions/DelayFunctions.h"
#include "Functions/Drive.h"
//#include "soundSensor.h"

//Höger
#define R0 PIO_PA15_IDX
#define R1 PIO_PD1_IDX
#define R2 PIO_PD3_IDX
#define R3 PIO_PD9_IDX
#define R4 PIO_PD10_IDX
#define R5 PIO_PC2_IDX
#define R_RESET PIO_PB26_IDX

//Vänster
#define L0 PIO_PD0_IDX
#define L1 PIO_PD2_IDX
#define L2 PIO_PD6_IDX
#define L3 PIO_PA7_IDX
#define L4 PIO_PC1_IDX
#define L5 PIO_PC3_IDX
#define L_RESET PIO_PA14_IDX






void initDrive(void){
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


// void testStuff(void){
// 	
// 	
// 		
// }

void driveTo(int obj){
	
	char str[20];
	sprintf(str,"\nDrive: %d",obj);
	printf (str);
	
	int newcount = 0;
	int r_count = 0;
	int l_count = 0;
	
	ioport_set_pin_level(R_RESET,LOW);
	ioport_set_pin_level(L_RESET,LOW);
	
	while(newcount < obj){    // && obj > readSensorValue()
				
		ioport_set_pin_level(R_RESET,LOW);
		ioport_set_pin_level(L_RESET,LOW);
		
		delayMicroseconds(500000);
		
		r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
		+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
		
		
		
		l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
		+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
		
		
		int disp = r_count - l_count;
		
		P_regulator(0,disp);
		
		//delayMicroseconds(400000);

		newcount = newcount + r_count;
		
// 		char str[20];
// 		sprintf(str,"\nHöger: %d",r_count);
// 		printf (str);
// 
// 		sprintf(str,"\nVänster: %d",l_count);
// 		printf (str);
// 		
// 		sprintf(str,"\nTotal: %d",newcount);
// 		printf (str);
	 
		r_count = 0;
		l_count = 0;

		ioport_set_pin_level(R_RESET,HIGH);
		ioport_set_pin_level(L_RESET,HIGH);
	}
	
// 	char str[20];
// 	sprintf(str,"\nTotal: %d",newcount);
// 	printf (str);
	
	newcount = 0;
	moveForward(1500,1500);
}


