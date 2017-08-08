/*
 * StateMachine.c
 *
 * Created: 2017-05-08 16:03:49
 *  Author: zoz
 */ 
/*
 * stateMachine.c
 *
 * Created: 2015-08-05 11:10:34
 *  Author: Uek
 */ 

#include "stateMachine.h"

codeLockType SM;			/* The memory area for the state machine */
codeLockPtrType instance;	/* A pointer to a state machine of this type */

/* 
 * The assignment of the pointer to the memory area for the state machine,
 * instance = &SM, is done in test_FSM_runner.c
 */

void startCodeLock(codeLockPtrType foo) /* Maing sure the FSM starts in the right state */
{
	foo->state = Locked;	// första status är låst 
}

void pushButton1(codeLockPtrType foo)		/* Yellow button is pushed */
{
	/* Write code here */
	switch(foo->state){
		case Locked:
		foo->state = PushOne; // när man trycker på rätt knapp pushOne alltså den gula = 1
		break;
		case ReleaseOne:
		foo->state = Locked;
		break;
		case ReleaseTwo:
		foo->state = Locked;
		break;
		case ReleaseThree:
		foo->state = Locked;
		break;
	}
}

void pushButton2(codeLockPtrType foo)		/* white button is pushed */
{
	/* Write code here */
		switch(foo->state){
			case Locked:
			foo->state = Locked;
			break;
			case ReleaseOne:
			foo->state = Locked;
			break;
			case ReleaseTwo:
			foo->state = Locked;
			break;
		}
	
}

void pushButton3(codeLockPtrType foo)		/* Red button is pushed */
{
	/* Write code here */
	switch(foo->state){
		case Locked:
		foo->state = Locked;
		break;
		case ReleaseOne:
		foo->state = PushTwo;//när man trycker på rätt knapp pushTwo alltså den röda =3
		break;
		case ReleaseTwo:
		foo->state = PushThree;//när man trycker på rätt knapp pushThree alltså den röda =3
		break;
		case ReleaseThree:
		foo->state = Locked;
		break;
		
	}
	
}

void releaseButton(codeLockPtrType foo)	/* No button is pushed */
{
	/* Write code here */
		switch(foo->state){
			case PushOne:
			foo->state=ReleaseOne; //efter första knapptryckning 
			break;
			case PushTwo:
			foo->state=ReleaseTwo;//efter andra knapptryckning
			break;
			case PushThree:
			foo->state = ReleaseThree;//efter tredje knapptryckning
			break;
		}
	
}

