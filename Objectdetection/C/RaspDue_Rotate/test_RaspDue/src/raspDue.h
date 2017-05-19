/*
 * RaspDue.h
 *
 *  Author: Adnan Begovic
 */ 

#include <asf.h>

#ifndef RASPDUE_H_
#define RASPDUE_H_
	
void initCommunication_pins(void);
void startCOM(void);
void camera_detection(void);

#endif /* RASPDUE_H_ */