/*
 * calculations.c
 *
 * Created: 2017-05-17 16:37:22
 *  Author: Andre & Elias
 */ 

#include "Functions/calculations.h"

int calculateDistance (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){ //Avst�ndet f�r x1 & y1 = Position, x2 & y2 = Destination
	
	int mot, nar;
	
	nar = x2 - x1;
	mot = y2 - y1;
	
	int dist = sqrt((mot*mot)+(nar*nar));
		
		
	return dist;
	
}

int calculateAngle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 ){	//Vinkeln f�r x1 & y1 = Position, x2 & y2 = Destination
	
	int mot, nar;
	nar = x2 - x1;
	mot = y2 - y1;
	
	
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

int calculateSetPoint(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1 ){		//R�kna ut b�rv�rdet, x2 = Position av Roboten, x3 = Startpunkt positionen, (y1/x1) Position av objektet.
	
	int set_point;
	
	if(x2-x3){
		set_point = ((x2-x3)*(y1/x1));					
	}else{
		set_point = 0;
	}
	
	return set_point;
}