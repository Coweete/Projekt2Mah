/*
 * Motorfunctions.h
 *
 * Created: 2017-04-26 09:32:59
 *  Author: Jounne
 */ 


#ifndef MOTORFUNCTIONS_H_
#define MOTORFUNCTIONS_H_



void initMotor(void);
void P_regulator(int b,int u);
void pulseLeft(int p1);
void pulseRight(int p2);
void turn(int a);
void moveForward(int l,int r);
#endif /* MOTORFUNCTIONS_H_ */