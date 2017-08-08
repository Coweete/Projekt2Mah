/*
 * Servo.c
 *
 * Created: 2017-04-27 22:05:06
 *  Author: Jounne
 */ 

#include <asf.h>
#include <ioport.h>

#include "Servo.h"
#include "DelayFunctions.h"


#define servoPin PIO_PC23_IDX // Arduino Due pin 7

void init_servo(){
	ioport_set_pin_dir(servoPin,IOPORT_DIR_OUTPUT);
}

void center_servo(){
	ioport_set_pin_level(servoPin,HIGH);
	delayMicroseconds(1550);
	ioport_set_pin_level(servoPin,LOW);
}

void move_servo_left_max(){
	ioport_set_pin_level(servoPin,HIGH);
	delayMicroseconds(1000);
	ioport_set_pin_level(servoPin,LOW);
}

void move_servo_rigth_max(){
	ioport_set_pin_level(servoPin,HIGH);
	delayMicroseconds(2000);
	ioport_set_pin_level(servoPin,LOW);
}