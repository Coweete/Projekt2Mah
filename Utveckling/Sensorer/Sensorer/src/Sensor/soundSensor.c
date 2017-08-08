/*
 * soundSensor.c
 *
 * Created: 2017-04-10 12:41:08
 *  Author: Jonatan Fridsten
 */ 

#include "asf.h"
#include "soundSensor.h"
#include "DelayFunctions.h"
#include <ioport.h>
#include <delay.h>
#include <time.h>

//DigitalPin 23
#define EchoPin PIO_PA14_IDX
//DigitalPin 24
#define TriggerPin PIO_PA15_IDX


void init_sensor(){
	ioport_init();
	ioport_set_pin_dir(TriggerPin,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EchoPin,IOPORT_DIR_INPUT);
}

int readSensorValue(){
	long duration,distance;
	ioport_set_pin_level(TriggerPin,LOW);
	delayMicroseconds(2000);
	ioport_set_pin_level(TriggerPin,HIGH);
	delayMicroseconds(10000);
	ioport_set_pin_level(TriggerPin,LOW);
	duration = pulsein();
	distance = (duration/42)/58.2;
	return distance;
}

int pulsein(){
	int state = 1;
	int flag = 0,clocktime;
	while(state){
		if(ioport_get_pin_level(EchoPin) && !flag){
			tc_start(TC0,0);
			flag = 1;
		}
		if(!ioport_get_pin_level(EchoPin) && flag)
		{
			clocktime = tc_read_cv(TC0,0);
			tc_stop(TC0,0);
			flag = 0;
			state = 0;
		}
	}
	return clocktime;
}
