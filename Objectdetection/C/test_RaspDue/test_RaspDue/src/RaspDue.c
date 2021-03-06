/*
 *  RaspDue.c
 *
 *  Author: Adnan Begovic
 */ 

#include <asf.h>
#include <ioport.h>
#include "raspDue.h" 
#include "communicationPins.h" 

void initCommunication_pins(void){
	
	//Pin that starts the communication between due-rasp:
	ioport_set_pin_dir(START_COM, IOPORT_DIR_OUTPUT);		//Pin 39
	
	//input pins that are reading output from raspberry:
	ioport_set_pin_dir(RIGHT_IN, IOPORT_DIR_INPUT);			//Pin 40
	ioport_set_pin_dir(TARGET_IN, IOPORT_DIR_INPUT);		//Pin 42
	ioport_set_pin_dir(LEFT_IN, IOPORT_DIR_INPUT);			//Pin 44
	ioport_set_pin_dir(NODETECTION_IN, IOPORT_DIR_INPUT);	//Pin 46
	
	//output-pins that will set the rotation off the robot depending on the detection in frame of the pi-camera.
	ioport_set_pin_dir(RIGHT_OUT, IOPORT_DIR_OUTPUT);		//Pin 41
	ioport_set_pin_dir(TARGET_OUT, IOPORT_DIR_OUTPUT);		//Pin 43
	ioport_set_pin_dir(LEFT_OUT, IOPORT_DIR_OUTPUT);		//Pin 45
	ioport_set_pin_dir(NODETECTION_OUT, IOPORT_DIR_OUTPUT); //Pin 47
}

void startCOM(void){
	setPin(START_COM, 1);	
}

void camera_detection(void)
{ 
	while(1){
		if(getPin(RIGHT_IN) == HIGH){
			setPin(RIGHT_OUT, HIGH);
			setPin(TARGET_OUT, LOW);
			setPin(LEFT_OUT, LOW);
			setPin(NODETECTION_OUT, LOW);
			printf("rotate left\n");
		}
		else if(getPin(TARGET_IN) == HIGH){
			setPin(TARGET_OUT, HIGH);
			setPin(RIGHT_OUT, LOW);
			setPin(LEFT_OUT, LOW);
			setPin(NODETECTION_OUT, LOW);
			printf("stop and move forward\n");
		}
		else if(getPin(LEFT_IN) == HIGH){
			setPin(LEFT_OUT, HIGH);
			setPin(TARGET_OUT, LOW);
			setPin(RIGHT_OUT, LOW);
			setPin(NODETECTION_OUT, LOW);
			printf("rotate right\n");
		}
		else if(getPin(NODETECTION_IN)== HIGH){
			setPin(NODETECTION_OUT, HIGH);
			setPin(LEFT_OUT, LOW);
			setPin(TARGET_OUT, LOW);
			setPin(RIGHT_OUT, LOW);
			printf("no object\n");
		}
		else {
			   //Do nothing.
		}
	}
}

