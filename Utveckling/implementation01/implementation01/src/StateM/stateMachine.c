/*
 * stateMachine.c
 *
 * Created: 2017-05-05 05:14:18
 *  Author: Elias H
 */ 

//Försök till implementering av en switch-state machine, kanske kan va ngt?.

#include <asf.h>
#include "StateM/stateMachine.h"
#include "Motor/PID_Controller.h"
#include "Task/task_motor.h"

RobTypen minneSM;   //Minnesplats för  statemachinen
RobTypenPekar instans; //Pekar mot statemachin av denne typ.

void turnOff(){
	moveForward1(1500,1500);
}

void MovingArlofooStanna(RobTypenPekar foo){	/* Arlo i rörelse */
	switch(foo->state)
	{
		case moveFram:      //Köra fram går till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
	
		case moveBak:      //Köra bak går till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
	
		case TurnLeft:      //Köra vänster går till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
		
		case TurnRight:      //Köra höger går till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
		
		case Stop:      //Köra höger går till state Stop.
		(foo->state) = Stop;
		turnOff();
		break;
		
		default:
		/* Inget */
		break;
		}
		
}

 void MovingArloForth(RobTypenPekar foo){	/* Arlo svänger */
	switch(foo->state)
	{
		case Stop:      //Stop fram går till state Fram.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;
		
		case moveFram:      //Köra fram går till state Fram.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;		
		
		case moveBak:      //Köra fram går till state Stop.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;
		
		case TurnLeft:      //vänster går till state Fram.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;
		
		case TurnRight:      // höger går till state Fram.
		(foo->state) = moveFram;
		moveForward1(1650,1650);
		break;	
		
		default:
		/* Inget */
		break;
	}
	
}		
 void MovingArloBack(RobTypenPekar foo){	/* Arlo svänger */
	 switch(foo->state)
	 {		
		case Stop:      //Stop fram går till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;
		
		case moveFram:      //Köra fram går till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;
		
		case moveBak:      //Bak fram går till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;
		
		case TurnLeft:      //vänster går till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;
		
		case TurnRight:      // Höger går till state Bak.
		(foo->state) = moveBak;
		moveForward1(1450,1450);
		break;		
		
		
		default:
		/* Inget */
		break;
	}
	
}	

void TurningArloLeft(RobTypenPekar foo){	/* Arlo svänger */
	switch(foo->state)
	{
		//Hur snabbt skall den svänga?
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
		
void TurningArloRight(RobTypenPekar foo){	/* Arlo svänger */
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