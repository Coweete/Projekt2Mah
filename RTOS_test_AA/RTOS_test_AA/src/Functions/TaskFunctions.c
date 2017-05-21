/*
 * TaskFunctions.c
 *
 * Created: 2017-05-19 22:04:44
 *  Author: Spellabbet
 */ 

#include <ioport.h>

#include "Functions/MotorFunctions.h"
#include "Functions/TaskFunctions.h"
#include "TwiFunctions/TwiFunctions.h"


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

//Kamera
#define START_CAMERA PIO_PC7_IDX	//Pinne 39

#define TURN_LEFT PIO_PC8_IDX		//Pinne 40
#define ON_TARGET PIO_PA19_IDX		//Pinne 42
#define TURN_RIGHT PIO_PC19_IDX		//Pinne 44
#define OFF_TARGET PIO_PC17_IDX		//Pinne 46



int r_count = 0;
int l_count = 0;
int e = 0;
int Kp = 4;
int speed = 1650;
int r_speed = 0;
int l_speed = 0;
extern uint8_t data_received_nav[];
int16_t currentx1,currenty1;


char str[20];

void init_taskFunctions(void){
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
	
	ioport_set_pin_dir(TURN_LEFT,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(TURN_RIGHT,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(ON_TARGET,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(OFF_TARGET,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(START_CAMERA,IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_level(START_CAMERA,LOW);

	
	
	printf("\nPins OK");
	
	
	
	
	
}




void driveForward(void){
	moveForward(l_speed,r_speed);
	
	r_speed=speed;
	l_speed=speed;
	
	
	ioport_set_pin_level(R_RESET,LOW);
	ioport_set_pin_level(L_RESET,LOW);
	
	r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
	+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
	
	l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
	+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
	
	e = 0 - (r_count - l_count);
	
	
	sprintf(str,"\nFelvärde: %d",e);
	printf(str);
	
	r_speed=speed;
	l_speed=speed;
	if(e > 0) {
		
		r_speed=speed-(e*Kp);
		l_speed=speed+(e*Kp);
		
	}
	else if (e < 0){
		
		r_speed=speed+(e*Kp);
		l_speed=speed-(e*Kp);
	}
	else{
		moveForward(l_speed,r_speed);
	}
	
	r_count = 0;
	l_count = 0;
	
	ioport_set_pin_level(R_RESET,HIGH);
	ioport_set_pin_level(L_RESET,HIGH);
}

int rotate(int turn_angle, int direction){		//Minimum vinkel är fyra

	int reverse_angle = (direction + 180) % 360;

	int direct_angle = ((abs(reverse_angle - 360) + turn_angle) % 360) - 180;

// 	char str[10];
// 
// 	sprintf(str,"\nNew angle: %d", d);
// 	printf(str);
// 
// 	sprintf(str,"\ndirect_angle = %d", direct_angle);
// 	printf(str);

	ioport_set_pin_level(L_RESET,LOW);
	ioport_set_pin_level(R_RESET,LOW);

	//Sväng vänster

	if(direct_angle > 0){
		while(r_count < (abs(direct_angle) * 0.25)){
			r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
			+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
			

			moveForward(1400,1600);

		}

		int count_right = r_count * 4;
		sprintf(str,"\ncount_right = %d", count_right);
		printf(str);
		
	}

	//Sväng höger

	else if(direct_angle < 0){
		while(l_count < (abs(direct_angle) * 0.25)){
			l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
			+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
			

			moveForward(1600,1400);

		}


		int count_left = l_count * 4;
		sprintf(str,"\ncount_left = %d", count_left);
		printf(str);
	}

	//Stoppa

	else{
		moveForward(1500,1500);
	}
	
	l_count = 0;
	r_count = 0;

	ioport_set_pin_level(L_RESET,HIGH);
	ioport_set_pin_level(R_RESET,HIGH);
	
	return 1;
}

int cameraSearch(void){
	
	ioport_set_pin_level(START_CAMERA,HIGH);
	
	int r = 0;
	
	while(0 == r){
		if(ioport_get_pin_level(TURN_LEFT)){
			moveForward(1400,1600);
			printf("\nTurn left");
		} 
		else if(ioport_get_pin_level(TURN_RIGHT)){
			moveForward(1600,1400);	
			printf("\nTurn right");
		}
		else if(ioport_get_pin_level(OFF_TARGET)){
			moveForward(1600,1400);
			printf("\nTurn around");
		}else if(ioport_get_pin_level(ON_TARGET)){
			r=1;
			printf("\nOn target");
		}else{
			printf("\nError");
		}
	}
	
	ioport_set_pin_level(START_CAMERA,LOW);
	
	moveForward(1500,1500);
	
	return r;	
}

void getCurrentPos(){
	na_sendstatus(XY1);
	currentx1 = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
	currenty1 = ((data_received_nav[3] << 8) | (data_received_nav[4] << 0));
	sprintf(str, "\ncurrent x=%d y=%d",currentx1,currenty1);
	printf(str);
}

void getStartData(){
	na_sendstatus(SOCKETXY);
}

