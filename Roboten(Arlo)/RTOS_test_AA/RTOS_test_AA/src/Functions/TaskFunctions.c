/*
 * TaskFunctions.c
 *
 * Created: 2017-05-19 22:04:44
 *  Author: Andr� Ahlbertz
 */ 

#include <asf.h>
#include <ioport.h>
#include <stdio.h>

#include "Functions/MotorFunctions.h"
#include "Functions/TaskFunctions.h"
#include "TwiFunctions/TwiFunctions.h"
#include "Functions/calculations.h"
#include <math.h>


//H�ger
#define R0 PIO_PA15_IDX
#define R1 PIO_PD1_IDX
#define R2 PIO_PD3_IDX
#define R3 PIO_PD9_IDX
#define R4 PIO_PD10_IDX
#define R5 PIO_PC2_IDX
#define R_RESET PIO_PB26_IDX

//V�nster
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

extern struct ObjectInfo objectinfo[4];

uint16_t startx = 0;

int interruptCounter = 0;

int direction = 0;


int r_count = 0;
int l_count = 0;
int e = 0;
int Kp = 4;
int speed = 1650;
int r_speed = 0;
int l_speed = 0;
extern uint8_t data_received_nav[];
int16_t currentPos[4];
int16_t currentx1,currenty1,currentx2,currenty2;


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

	
	//Printar "Pins OK" efter lyckad initiering. 
	printf("\nPins OK");
	
	
	
	
	
}


//Anv�nds inte, den �r till interrupt. 
void addOne(uint32_t id, uint32_t index){
// 	printf("\nInterrupt");
// 	if ((id == ID_PIOC) && (index == PIO_PC9)){
// 		printf ("\nOk");
// 		}else{
// 		printf("\nError");
// 	}
	//printf("\nOk");
	interruptCounter++;
}
//Anv�nds inte, �r f�r interrupt
void init_interrupt(void){
	
	pmc_enable_periph_clk(ID_PIOC);

	pio_set_input(PIOC,PIO_PC9,PIO_PULLUP);

	pio_handler_set(PIOC,ID_PIOC,PIO_PC9,PIO_IT_HIGH_LEVEL,addOne);

	NVIC_EnableIRQ(PIOC_IRQn);

	pio_enable_interrupt(PIOC,PIO_PC9);
	
	printf("\nInit_interrupt ok");
}

void resetCounter(void){
	interruptCounter = 0;
}

//Roboten k�r fram�t tills den �r inom 70cm fr�n objektet. 
int driveForward(int tarDist){
	
	 sprintf(str,"\nTarget Distance: %d",tarDist);
	 printf(str);
	
	r_count = 0;
	l_count = 0;
	
	int driveCount = 0;
	int testing = 0;
// 	int v_test = 0;
// 	int h_test = 0;
	int e_test = 0;
	
	r_speed=speed;
	l_speed=speed;
	
	moveForward(l_speed,r_speed);
	
	
	if (70 < tarDist){
		moveForward(1650,1650);
	} 
	else{
		moveForward(1500,1500);
		testing = 1;
	}
		
// 		if(testing){
// 			startx = currentPos[0];
// 			testing = 0;
// 		}else{
// 			//b�rv�rde
// 			v_test = calculateSetPoint(currentPos[0],startx,objectinfo[1].xpos,objectinfo[1].ypox);
// 			//�rv�rde
// 			h_test = currentPos[0];
// 			
// 			e_test = v_test - h_test;
// 			
// 			sprintf(str,"\nv: %d h: %d e: %d",v_test,h_test,e_test);
// 			printf(str);
// 			
// 		}	
	

// 	ioport_set_pin_level(R_RESET,LOW);
// 	ioport_set_pin_level(L_RESET,LOW);
	
		r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
		+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
	
		l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
		+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
	
		ioport_set_pin_level(R_RESET,HIGH);
		ioport_set_pin_level(L_RESET,HIGH);
		vTaskDelay(3);
		ioport_set_pin_level(R_RESET,LOW);
		ioport_set_pin_level(L_RESET,LOW);
	
	
	
	
	
		e_test = 0 -	(r_count - l_count);
	
	
	sprintf(str,"\nFelv�rde: %d",e);
	printf(str);
	
	r_speed=speed;
	l_speed=speed;
		if(e_test > 0) {
		
			r_speed=speed-(e*Kp);
			l_speed=speed+(e*Kp);
		
		}
		else if (e_test < 0){
		
			r_speed=speed+(e*Kp);
			l_speed=speed-(e*Kp);
		}
		else{
			moveForward(l_speed,r_speed);
		}
	


	driveCount = (r_count+l_count)/2;
	
	sprintf(str,"\ndriveCount = %d",driveCount);
	printf(str);
	
	return testing;
}

int rotate(int turn_angle){		//Minimum vinkel �r fyra

// 	sprintf(str,"\nturn_angle: %d",turn_angle);
// 	printf(str);
// 	
// 	sprintf(str,"\ndirection: %d",direction);
// 	printf(str);
	
	direction = calculateDirection(currentx1,currenty1,currentx2,currenty2);
	
	sprintf(str,"\nDirection: %d",direction);
	printf(str);
	
	int ret = 0;
	
	int reverse_angle = (direction + 180) % 360;
	

	int direct_angle = ((abs(reverse_angle - 360) + turn_angle) % 360) - 180;

	sprintf(str,"\ndirect_angle: %d",direct_angle);
	printf(str);

	r_count = 0;
	l_count = 0;

	printf("\ncount null");

	//returnCounter();

	ioport_set_pin_level(L_RESET,LOW);
	ioport_set_pin_level(R_RESET,LOW);

	//Sv�ng v�nster

	if(direct_angle > 0){
		while(r_count < (abs(direct_angle) / 4)){
			r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
			+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
			
			sprintf(str,"\nr_count = %d", r_count);
			printf(str);

			moveForward(1400,1600);

		}
		
		
		
		int count_total = r_count * 4;
		//printf("RCOUNT =%d ",r_count);
		sprintf(str,"\ncount_right = %d", count_total);
		printf(str);

		ret = 1;
		
	}

	//Sv�ng h�ger

	else if(direct_angle < 0){
		while(l_count < (abs(direct_angle) / 4)){
			l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
			+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
			
			sprintf(str,"\nl_count = %d", l_count);
			printf(str);

			moveForward(1600,1400);

		}
		
		int count_total = -l_count * 4;
		sprintf(str,"\ncount_left = %d", count_total);
		printf(str);
		
		ret = 1;
		
		
	}

	//Stoppa

	else{
		moveForward(1500,1500);
		
	}
	
	sprintf(str,"\nCounter = %d",interruptCounter);
	printf(str);


	ioport_set_pin_level(L_RESET,HIGH);
	ioport_set_pin_level(R_RESET,HIGH);

	return ret;
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

void getCurrentPos(void){
	na_sendstatus(XY1);
	currentx1 = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
	currenty1 = ((data_received_nav[3] << 8) | (data_received_nav[4] << 0));
	sprintf(str, "\ncurrent x1=%d y1=%d",currentx1,currenty1);
	printf(str);
	
	//Tv� rader in h�r
	
	sprintf(str, "\ncurrent x2=%d y2=%d",currentx2,currenty2);
	printf(str);
	
	currentPos[0] = currentx1;
	currentPos[1] = currenty1;
	currentPos[2] = currentx2;
	currentPos[3] = currentx2;
}

void getStartData(void){
	na_sendstatus(SQUAREXY);
}

