/*
 * calculations.h
 *
 * Created: 2017-05-17 16:37:35
 *  Author: Andre & ELias
 */ 

#include <asf.h>
#include <math.h>

#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

int calculateDistance(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
int calculateAngle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
int calculateSetPoint(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1 );
int calculateDirection(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1);


#endif /* CALCULATIONS_H_ */