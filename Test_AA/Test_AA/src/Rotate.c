/*
 * Rotate.c
 *
 * Created: 2017-05-04 14:35:36
 *  Author: André Ahlbertz
 */
#include <asf.h>
#include <ioport.h>
#include <stdlib.h>
#include <inttypes.h>
#include "Rotate.h"
#include "DelayFunctions.h"
#include "Motorfunctions.h"
#include "CalculateAngle.h"





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

int direction = 0;
int r_count = 0;
int l_count = 0;


uint16_t firstx = 0;
uint16_t firsty = 0;
uint16_t secondx = 0;
uint16_t secondy = 0;

void initRotateMotor(void){
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

void rotate(int d){					//Minimum d is 4
    //double ticks = d * 0.25;
	
	int reverse_angle = (direction + 180) % 360;
	
	int direct_angle = ((abs(reverse_angle - 360) + d) % 360) - 180;
	
	char str[20];
	
	sprintf(str,"\nNew angle: %d", d);
	printf(str);
	
	sprintf(str,"\ndirect_angle = %d", direct_angle);
	printf(str);
	
	ioport_set_pin_level(L_RESET,LOW);
	ioport_set_pin_level(R_RESET,LOW);
	
	//Turn left
	
	if(direct_angle > 0){								
		while(r_count < (abs(direct_angle) * 0.25)){
			r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
			+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
			//ioport_set_pin_level(R_RESET,HIGH);
			
			moveForward(1400,1600);
			
		}
		
		int count_right = r_count * 4;
		sprintf(str,"\nr_count = %d", r_count);
		printf(str);
		sprintf(str,"\ncount_right = %d", count_right);
		printf(str);
		updateDirection(d);
		//direction = (d + 360 - direction) % 360;
		moveForward(1500,1500);	
	}
	
	//Turn right
	
	else if(direct_angle < 0){
		while(l_count < (abs(direct_angle) * 0.25)){			
			l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
			+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
			//ioport_set_pin_level(L_RESET,HIGH);
			
			moveForward(1600,1400);

		}
		
		int count_left = l_count * 4;
		sprintf(str,"\nl_count = %d", l_count);
		printf(str);
		sprintf(str,"\ncount_left = %d", count_left);
		printf(str);
		updateDirection(d);
		//direction = (d + 360 - direction) % 360;
		moveForward(1500,1500);	
	}
	
	else{
		moveForward(1500,1500);
	}
	
	l_count = 0;
	r_count = 0;
	
	ioport_set_pin_level(L_RESET,HIGH);
	ioport_set_pin_level(R_RESET,HIGH);	
	
	
	
// 	char str[20];
// 	sprintf(str,"\nVinkel: %d",d);
// 	printf (str);
// 	sprintf(str,"\nTicks: %f",ticks);
// 	printf (str);
	
}
int getDirection(void){
	return direction;
}

void startupMeasure1(uint16_t x1,uint16_t x2){
	firstx = x1;
	firsty = x2;
}

void startupMeasure2(uint16_t x1,uint16_t x2){
	secondx = x1;
	secondy = x2;
	
	int xdiff = getX_diff(secondx,firstx);
	int ydiff = getY_diff(secondy,firsty);
	
	direction = calculateAngle(ydiff,xdiff);
	char str[20];
	sprintf(str,"\nDirection: %d",direction);
	printf (str);
}

void updateDirection(int d){
	direction = d;	
	//direction = (d + 360 - direction) % 360;
	char str[20];
	sprintf(str,"\nNew direction: %d",direction);
	printf (str);
}
