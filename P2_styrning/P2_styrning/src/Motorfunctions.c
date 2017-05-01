/*
 * Motorfunctions.c
 *
 * Created: 2017-04-26 09:32:47
 *  Author: Jounne
 */ 

#include <asf.h>
#include <ioport.h>
#include <inttypes.h>
#include "DelayFunctions.h"
#include "Motorfunctions.h"
#define LEFT PIO_PC4_IDX
#define RIGHT PIO_PC5_IDX
//h�gra r�knare
#define R0 PIO_PA15_IDX
#define R1 PIO_PD1_IDX
#define R2 PIO_PD3_IDX
#define R3 PIO_PD9_IDX
#define R4 PIO_PD10_IDX
#define R5 PIO_PC2_IDX
#define R_RESET PIO_PB26_IDX
//v�nstra r�knaren
#define L0 PIO_PD0_IDX
#define L1 PIO_PD2_IDX
#define L2 PIO_PD6_IDX
#define L3 PIO_PA7_IDX
#define L4 PIO_PC1_IDX
#define L5 PIO_PC3_IDX
#define L_RESET PIO_PA14_IDX

int r_count=0;
int counter = 0;
int l_count=0;
int Kp = 4;
int angle=0;
int speed=1650;
int r_speed=0;
int l_speed=0;
void initMotor(void){
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


void P_regulator(int b)
{
	r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
	+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;   
	ioport_set_pin_level(R_RESET,HIGH);	                                                          //h�mta input v�rde fr� pinnarna
	l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
	+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
	ioport_set_pin_level(L_RESET,HIGH);	

	char str[20];
	sprintf(str,"h�gerhjul: %d\n",r_count);
	printf (str);
	r_speed=speed;
	l_speed=speed;
	int e = b-(r_count - l_count); //r�kna felv�rde
		if(e>0){
		r_speed=speed-(e*Kp);
		l_speed=speed+(e*Kp);
	}else if (e<0)
	{
		r_speed=speed+(e*Kp);
		l_speed=speed-(e*Kp);
	}
	sprintf(str,"felv�rde: %d\n",e);
	printf (str);
	moveForward(l_speed,r_speed);
	delayMicroseconds(500000);
	sprintf(str,"r-speed: %d\n",r_speed);
	printf (str);
		sprintf(str,"l-speed: %d\n",l_speed);
		printf (str);
	ioport_set_pin_level(R_RESET,LOW);
	ioport_set_pin_level(L_RESET,LOW);
}


void pulseLeft(int p1){
	ioport_set_pin_level(LEFT,HIGH);
	delayMicroseconds(p1);
	ioport_set_pin_level(LEFT,LOW);
}
void pulseRight(int p2){
	ioport_set_pin_level(RIGHT,HIGH);
	delayMicroseconds(p2);
	ioport_set_pin_level(RIGHT,LOW);
}
/*
void turn(int a){
		
		if(a>250){						//Turning left
			for(int i=0;i<a-250;i++){		
				pulseOut(1850-i);
				delayMicroseconds(1100);
				pulseOut(1850+i);
				delayMicroseconds(5250);
					
			}
			
		}
		else if(a<250){					//Turning right
			for(int i=0;i<a;i++){
				
				pulseOut(1850+i);
				delayMicroseconds(1100);
				pulseOut(1850-i);
				delayMicroseconds(5250);
				
			}
			
		}
		else{								//Forward
				pulseOut(1850);
				delayMicroseconds(1100);
				pulseOut(1850);
				delayMicroseconds(5250);			
		}
		angle=250;
		
		pulseOut(1550);
		delayMicroseconds(1100);
		pulseOut(1550);
		delayMicroseconds(5250);
}
*/
void moveForward(int l,int r){
	pulseLeft(l);
	pulseRight(r);
	delayMicroseconds(5250);
	//printf (" Felvarde:%d\n",e);
}