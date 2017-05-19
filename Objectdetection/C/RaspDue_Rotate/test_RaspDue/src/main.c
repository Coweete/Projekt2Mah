/*
* Author: Adnan Begovic
*/

#include <inttypes.h>
#include <asf.h>
#include <ioport.h>
#include "console/consoleFunctions.h"
#include "raspDue.h"
#include "communicationPins.h"
#include "DelayFunctions.h"
#include "Motorfunctions.h"
#include "Rotate.h"

int main (void)
{
	board_init();
	sysclk_init();
	ioport_init();
	configureConsole();
	delayInit();
	startCOM();
	camera_detection();	
	initMotor();
}
