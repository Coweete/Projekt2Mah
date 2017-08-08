/*
 * stateMachine.h
 *
 * Created: 2017-05-05 05:14:29
 *  Author: Elias H
 */ 

//Försök till implementering av en switch-state machine.

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

typedef enum      //De olika tillstånden
{
	moveFram,
	TurnLeft, TurnRight,
	Stop, moveBak
} states;

typedef struct Robot
{
	states state;	/* Låter en variabel för att inneha tillstånd av objekt. */
} RobTypen;

typedef RobTypen*RobTypenPekar;
void turnOffArloMotors();		//Stänger ner/Stannar
void MovingArloForth(RobTypenPekar foo);	/* Arlo i rörelse */
void MovingArloBack(RobTypenPekar foo);	/* Arlo i rörelse */
void TurningArloLeft(RobTypenPekar foo);	/* Arlo svänger */
void TurningArloRight(RobTypenPekar foo);	/* Arlo svänger */
void MovingArlofooStanna(RobTypenPekar foo);	/* Arlo Stannar */

#endif /* STATEMACHINE_H_ */