/*
 * Motorfunctions.c
 *
 * Created: 2017-05-08 09:35:47
 *  Author: Andr� Ahlbertz
 */ 

#include <asf.h>
#include <ioport.h>
#include <inttypes.h>
#include "Functions/DelayFunctions.h"
#include "Functions/MotorFunctions.h"

#define LEFT PIO_PC4_IDX
#define RIGHT PIO_PC5_IDX


//Initierar pinnarna till motorn
void initMotor(void){
		ioport_set_pin_dir(LEFT,IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(RIGHT,IOPORT_DIR_OUTPUT);
}



//Skickar en puls till v�nster hjul
void pulseLeft(int p1){
	ioport_set_pin_level(LEFT,HIGH);
	delayMicroseconds(p1);
	ioport_set_pin_level(LEFT,LOW);
}
//Skickar en puls till h�ger hjul
void pulseRight(int p2){
	ioport_set_pin_level(RIGHT,HIGH);
	delayMicroseconds(p2);
	ioport_set_pin_level(RIGHT,LOW);
}
//K�r med b�gge hjulen. 
void moveForward(int l,int r){
	pulseLeft(l);
	pulseRight(r);
	delayMicroseconds(5250);
	
}
