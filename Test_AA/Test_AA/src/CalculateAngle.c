/*
 * CalculateAngle.c
 *
 * Created: 2017-05-08 13:48:07
 *  Author: Andr� Ahlbertz
 */ 

#include "CalculateAngle.h"

#include <stdio.h>
#include <math.h>

int getX_diff(int pos, int dest){
	
	int diff = dest - pos;
	
	return diff;
}

int getY_diff(int pos, int dest){
	
	int diff = dest - pos;
	
	return diff;
}


int calculateAngle(int mot, int nar){				//mot = motst�ende, nar = n�rliggande
	
	int angle = atan(mot/nar) * (180/M_PI);
	
	return angle;
}