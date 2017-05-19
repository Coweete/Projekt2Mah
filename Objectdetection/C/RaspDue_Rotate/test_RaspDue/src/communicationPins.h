/*
 * CommunicationPins.h
 *
 *  Author: Adnan Begovic
 */ 

#ifndef COMMUNICATIONPINS_H_
#define COMMUNICATIONPINS_H_


#define getPin ioport_get_pin_level
#define setPin ioport_set_pin_level

//Pin that starts the communication between due-rasp:
#define START_COM			PIO_PC7_IDX		//Pin 39

//Pins that are reading output from raspberry:
#define RIGHT_IN			PIO_PC8_IDX		//Pin 40
#define TARGET_IN			PIO_PA19_IDX	//Pin 42
#define LEFT_IN				PIO_PC19_IDX    //Pin 44 
#define NODETECTION_IN		PIO_PC17_IDX	//Pin 46 
#define STOP_TARGET_IN        PIO_PC15_IDX    //Pin 48

//Output-pins that are setting rotation of the robot 
//#define RIGHT_OUT			PIO_PC9_IDX		//Pin 41 for led
#define TARGET_OUT			PIO_PA20_IDX	//Pin 43 for led
//#define LEFT_OUT			PIO_PC18_IDX	//Pin 45 for led
#define NODETECTION_OUT	    PIO_PC16_IDX	//Pin 47 for led

#define LEFT_OUT PIO_PC4_IDX //37
#define RIGHT_OUT PIO_PC5_IDX //36

#endif /* COMMUNICATIONPINS_H_ */