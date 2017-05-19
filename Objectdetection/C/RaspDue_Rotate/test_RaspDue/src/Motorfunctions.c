/*
 * Motorfunctions.c
 *
 * Created: 2017-05-08 09:35:47
 *  Author: André Ahlbertz
 */ 

#include <asf.h>
#include <ioport.h>
#include <inttypes.h>
#include "DelayFunctions.h"
#include "Motorfunctions.h"
#include "communicationPins.h"

void initMotor(void){
		ioport_set_pin_dir(LEFT_OUT,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(RIGHT_OUT,IOPORT_DIR_OUTPUT);
}

void pulseLeft(int p1){
	ioport_set_pin_level(LEFT_OUT,HIGH);
	delayMicroseconds(p1);
	ioport_set_pin_level(LEFT_OUT,LOW);
}
void pulseRight(int p2){
	ioport_set_pin_level(RIGHT_OUT,HIGH);
	delayMicroseconds(p2);
	ioport_set_pin_level(RIGHT_OUT,LOW);
}

void moveForward(int l,int r){
	pulseLeft(l);
	pulseRight(r);
	delayMicroseconds(5250);
}
