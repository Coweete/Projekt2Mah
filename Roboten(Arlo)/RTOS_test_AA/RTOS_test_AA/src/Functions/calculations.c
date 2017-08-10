/*
 * calculations.c
 *
 * Created: 2017-05-17 16:37:22
 *  Author: Andre
 */ 

#include "Functions/calculations.h"

int calculateDistance (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){ //Avståndet för x1 & y1 = Position, x2 & y2 = Destination
	
	int mot, nar;
	
	nar = x2 - x1;
	mot = y2 - y1;
	
	int dist = sqrt((mot*mot)+(nar*nar));
	
	char strCalc[20];
	sprintf(strCalc,"\nCalc = %d",dist);
	printf(strCalc);	
	printf("Hello?");
	return dist;
	
}

int calculateAngle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 ){	//Vinkeln för x1 & y1 = Position, x2 & y2 = Destination
	
	int mot, nar;
	nar = x2 - x1;
	mot = y2 - y1;
	
	
	int angle = (acos(nar/(sqrt((mot*mot)+(nar*nar)))) * (180/M_PI));
	
	if(nar < 0 && mot > 0){
		angle = angle + 90;
	}
	else if(nar < 0 && mot < 0){
		angle = angle + 180;
	}
	else if(nar > 0 && mot < 0){
		angle = angle + 270;
	}
	
	angle = angle % 360;
	
	return angle;
}

int calculateSetPoint(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1 ){		//Räkna ut börvärdet, x2 = Position av Roboten, x3 = Startpunkt positionen, (y1/x1) Position av objektet.
	
	int set_point;
	
	if(x2-x3){
		set_point = ((x2-x3)*(y1/x1));					
	}else{
		set_point = 0;
	}
	
	return set_point;
}

int calculateDirection(uint16_t xLeft, uint16_t yLeft, uint16_t xRight, uint16_t yRight){				//Ena lampan och andra lampan, beräknar vilket håll roboten är svängd åt
	int mot, nar;
	nar = xRight - xLeft;
	mot = yRight - yLeft;
	
	
	int dir = (acos(nar/(sqrt((mot*mot)+(nar*nar)))) * (180/M_PI));
	
	if(nar < 0 && mot > 0){
		dir = dir + 90;
	}
	else if(nar < 0 && mot < 0){
		dir = dir + 180;
	}
	else if(nar > 0 && mot < 0){
		dir = dir + 270;
	}
	
	dir = (dir + 90) % 360;
	
	return dir;
	
}

