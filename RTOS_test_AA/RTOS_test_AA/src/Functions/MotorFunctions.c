/*
 * Motorfunctions.c
 *
 * Created: 2017-05-08 09:35:47
 *  Author: André Ahlbertz
 */ 

#include <asf.h>
#include <ioport.h>
#include <inttypes.h>
#include "Functions/DelayFunctions.h"
#include "Functions/MotorFunctions.h"

#define LEFT PIO_PC5_IDX
#define RIGHT PIO_PC6_IDX



void initMotor(void){
		ioport_set_pin_dir(LEFT,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(RIGHT,IOPORT_DIR_OUTPUT);
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

void moveForward(int l,int r){
	pulseLeft(l);
	pulseRight(r);
	delayMicroseconds(5250);
	
}
