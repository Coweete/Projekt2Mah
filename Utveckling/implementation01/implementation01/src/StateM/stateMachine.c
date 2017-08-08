/*
 * stateMachine.c
 *
 * Created: 2017-05-05 05:14:18
 *  Author: Elias H
 */ 

//F�rs�k till implementering av en switch-state machine, kanske kan va ngt?.

#include <asf.h>
#include "StateM/stateMachine.h"
#include "Motor/PID_Controller.h"
#include "Task/task_motor.h"

RobTypen minneSM;   //Minnesplats f�r  statemachinen
RobTypenPekar instans; //Pekar mot statemachin av denne typ.

void turnOff(){
	moveForward1(1500,1500);
}

void MovingArlofooStanna(RobTypenPekar foo){	/* Arlo i r�relse */
	switch(foo->state)
	{
		case moveFram:      //K�ra fram g�r till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
	
		case moveBak:      //K�ra bak g�r till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
	
		case TurnLeft:      //K�ra v�nster g�r till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
		
		case TurnRight:      //K�ra h�ger g�r till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
		
		case Stop:      //K�ra h�ger g�r till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
		
		default:
		/* Inget */
		break;
		}
		
}

 void MovingArloForth(RobTypenPekar foo){	/* Arlo sv�nger */
	switch(foo->state)
	{
		case Stop:      //Stop fram g�r till state Fram.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;
		
		case moveFram:      //K�ra fram g�r till state Fram.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;		
		
		case moveBak:      //K�ra fram g�r till state Stop.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;
		
		case TurnLeft:      //v�nster g�r till state Fram.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;
		
		case TurnRight:      // h�ger g�r till state Fram.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;	
		
		default:
		/* Inget */
		break;
	}
	
}		
 void MovingArloBack(RobTypenPekar foo){	/* Arlo sv�nger */
	 switch(foo->state)
	 {		
		case Stop:      //Stop fram g�r till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;
		
		case moveFram:      //K�ra fram g�r till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;
		
		case moveBak:      //Bak fram g�r till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;
		
		case TurnLeft:      //v�nster g�r till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;
		
		case TurnRight:      // H�ger g�r till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;		
		
		
		default:
		/* Inget */
		break;
	}
	
}	

void TurningArloLeft(RobTypenPekar foo){	/* Arlo sv�nger */
	switch(foo->state)
	{
		//Hur snabbt skall den sv�nga?
		case Stop:      
		(foo->state) = TurnLeft;
		moveForward1(1500,1500);
		break;
		
		case moveFram:      
		(foo->state) = TurnLeft;
		moveForward1(1500,1500);
		break;
		
		case moveBak:     
		(foo->state) = TurnLeft;
		moveForward1(1500,1500);
		break;
		
		case TurnLeft:     
		(foo->state) = TurnLeft;
		moveForward1(1500,1500);
		break;
		
		case TurnRight:     
		(foo->state) = TurnLeft;
		moveForward1(1500,1500);
		break;
		
		default:
		/* Inget */
		break;
	}
	
}		
		
void TurningArloRight(RobTypenPekar foo){	/* Arlo sv�nger */
	switch(foo->state)
	{		

		case Stop:
		(foo->state) = TurnRight;
		moveForward1(1500,1500);
		break;
		
		case moveFram:
		(foo->state) = TurnRight;
		moveForward1(1500,1500);
		break;
		
		case moveBak:
		(foo->state) = TurnRight;
		moveForward1(1500,1500);
		break;
		
		case TurnLeft:
		(foo->state) = TurnRight;
		moveForward1(1500,1500);
		break;
		
		case TurnRight:
		(foo->state) = TurnRight;
		moveForward1(1500,1500);
		break;		
		
		default:
		/* Inget */
		break;
	}
	
}