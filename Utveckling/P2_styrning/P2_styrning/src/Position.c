/*
 * Position.c
 *
 * Created: 2017-05-08 10:16:21
 *  Author: zoz
 */ 
#include "Position.h"
#include <asf.h>
#include "DelayFunctions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "StateMachine.h"
/*
struct point{
	int x;
	int y;

	};*/

// float getDistance(float x1,float x2,float y1,float y2){
// 	float distance;
// 	distance =  sqrt((x1-y1)*(x1-y1)+(x2-y2)*(x2-y2));
// 	return distance;
// }
int ioportinit(void)
{
extern codeLockType SM;
extern codeLockPtrType instance;


bool knapp,knapp2,knapp3;
while(1)
{
	instance = &SM;
	knapp = ioport_get_pin_level(k1);
	knapp2 = ioport_get_pin_level(k2);
	knapp3 = ioport_get_pin_level(k3);
	if (knapp==true)
	{
		pushButton1(instance);
		//ioport_set_pin_level(LED3,knapp);
		delayMicroseconds(100000);
		
	}
	
	if (knapp2==true)
	{
		pushButton2(instance);
		//ioport_set_pin_level(LED2,knapp2);
		
		delayMicroseconds(100000);
	}
	if (knapp3==true)
	{
		pushButton3(instance);
		//ioport_set_pin_level(LED4,knapp3);
		delayMicroseconds(100000);
	}
	if (~knapp||~knapp2||~knapp3)
	{
		releaseButton(instance);
	}
	startCodeLock(instance);
	switch(instance->state){
		case ReleaseOne:
		ioport_set_pin_level(LED3,HIGH);
		break;
		case ReleaseTwo:
		ioport_set_pin_level(LED2,HIGH);
		break;
		case ReleaseThree:
		ioport_set_pin_level(LED1,HIGH);
		break;
		
		
	}
}
}