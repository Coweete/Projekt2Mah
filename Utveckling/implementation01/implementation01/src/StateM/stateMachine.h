/*
 * stateMachine.h
 *
 * Created: 2017-05-05 05:14:29
 *  Author: Elias H
 */ 

//F�rs�k till implementering av en switch-state machine.

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

typedef enum      //De olika tillst�nden
{
	moveFram,
	TurnLeft, TurnRight,
	Stop, moveBak
} states;

typedef struct Robot
{
	states state;	/* L�ter en variabel f�r att inneha tillst�nd av objekt. */
} RobTypen;

typedef RobTypen*RobTypenPekar;
void turnOffArloMotors();		//St�nger ner/Stannar
void MovingArloForth(RobTypenPekar foo);	/* Arlo i r�relse */
void MovingArloBack(RobTypenPekar foo);	/* Arlo i r�relse */
void TurningArloLeft(RobTypenPekar foo);	/* Arlo sv�nger */
void TurningArloRight(RobTypenPekar foo);	/* Arlo sv�nger */
void MovingArlofooStanna(RobTypenPekar foo);	/* Arlo Stannar */

#endif /* STATEMACHINE_H_ */