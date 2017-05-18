/*
* Author: Adnan Begovic
*/

#include <asf.h>
#include <ioport.h>
#include "console/consoleFunctions.h"
#include "raspDue.h"
#include "communicationPins.h"

int main (void)
{
	board_init();
	sysclk_init();
	ioport_init();
	configureConsole();
	initCommunication_pins();
	startCOM();
	camera_detection();		
}
