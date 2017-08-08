/*
 * Regulator.c
 *
 * Created: 2017-05-08 14:04:12
 *  Author: André Ahlbertz
 */ 


#include <asf.h>
#include <ioport.h>
#include <inttypes.h>
#include "DelayFunctions.h"
#include "Regulator.h"
#include "Motorfunctions.h"

// #define R_RESET PIO_PB26_IDX
// #define L_RESET PIO_PA14_IDX


int Kp = 4;
int speed=1650;
int r_speed=0;
int l_speed=0;


void initRegulator(void){
	
// 			ioport_set_pin_dir(R_RESET,IOPORT_DIR_OUTPUT);
// 			ioport_set_pin_dir(L_RESET,IOPORT_DIR_OUTPUT);
}



void P_regulator(int b,int u)
{
	
// 	ioport_set_pin_level(R_RESET,HIGH);
// 	ioport_set_pin_level(L_RESET,HIGH);

	r_speed=speed;
	l_speed=speed;
	int e = b - u; //Felvärde = Börvärde - ärvärde
	if(e > 0) {

		r_speed=speed-(e*Kp);
		l_speed=speed+(e*Kp);
		moveForward(l_speed,r_speed);
		
	}
	else if (e<0){
		
		r_speed=speed+(e*Kp);
		l_speed=speed-(e*Kp);
		moveForward(l_speed,r_speed);
	}
	else{
		moveForward(l_speed,r_speed);
	}
	delayMicroseconds(500000);


// 	ioport_set_pin_level(R_RESET,LOW);
// 	ioport_set_pin_level(L_RESET,LOW);
}