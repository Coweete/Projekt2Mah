/*
 * CalculateAngle.c
 *
 * Created: 2017-05-08 13:48:07
 *  Author: André Ahlbertz
 */ 

#include "CalculateAngle.h"

#include <stdio.h>
#include <math.h>

int getX_diff(int dest, int pos){					//pos = current x position, dest = destination
	
	int diffx = dest - pos;
	
	return diffx;
}

int getY_diff(int dest, int pos){					//pos = current y position, dest = destination
	
	int diffy = dest - pos;
	
	return diffy;
}


int calculateAngle(int mot, int nar){				//mot = motstående (y), nar = närliggande (x)
	
	
	int angle = acos(nar/(sqrt((mot*mot)+(nar*nar)))) * (180/M_PI);
	
	if(nar < 0 && mot > 0){
		angle = angle + 90;
	}
	else if(nar < 0 && mot < 0){
		angle = angle + 180;
	}
	else if(nar > 0 && mot < 0){
		angle = angle + 270;
	}
	
	return angle;
}


int calculateSetPoint(int y_pos, int y_dest){							//Räkna ut börvärde
	
	int set_point = y_pos - y_dest;
	
	return set_point;
}


int calculateDistance(int mot, int nar){
	
	int dist = sqrt((mot*mot)+(nar*nar));
	
	return dist;
}

