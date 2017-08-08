/*
 * stateMachine.h
 *
 * Created: 2017-05-05 05:14:29
 *  Author: Elias H
 */ 

//Försök till implementering av en switch-state machine.

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#define TASK_STATEMACHINE_STACK_SIZE 1024/(sizeof(portSTACK_TYPE))
#define TASK_STATEMACHINE_PRIORITY (4)

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
void task_stateMachine();
void turnOffArloMotors();		//Stänger ner/Stannar
void MovingArloForth(RobTypenPekar foo);	/* Arlo i rörelse */
void MovingArloBack(RobTypenPekar foo);	/* Arlo i rörelse */
void TurningArloLeft(RobTypenPekar foo);	/* Arlo svänger */
void TurningArloRight(RobTypenPekar foo);	/* Arlo svänger */
void MovingArlofooStanna(RobTypenPekar foo);	/* Arlo Stannar */

#endif /* STATEMACHINE_H_ */