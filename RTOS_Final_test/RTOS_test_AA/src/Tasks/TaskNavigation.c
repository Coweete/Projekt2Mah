/*
 * TaskNavigation.c
 *
 * Created: 2017-05-19 15:34:47
 *  Author: Jonatan Fridsten
 */ 

#include <asf.h>
#include "TaskNavigation.h"
#include "TwiFunctions/TwiFunctions.h"
#include "Functions/calculations.h"

extern struct ArmInfo arminformation;
extern struct ObjectInfo objectinfo[];
extern int16_t currentX1,currentY1,currentX2,currentY2;
int16_t distanceToObject,angleToObject;
uint8_t vag = 0;
uint8_t state = 0;

void task_navigation(){
	
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 1000;
	xLastWakeTime = xTaskGetTickCount();
	
// 	if(1 == arminformation.collectAll){
// 		vag = {objectinfo[0].xpos,objectinfo[0].ypox};
// 	}else{
// 		vag[] = {SQUAREXY,BOXGOALXY,SQUAREXY,BOXGOALXY,GLASSXY,BOXGOALXY};
// 	}
	
	while(1){
		
		switch(state){
			case 1: // Till objekt
				angleToObject		=	calculateAngle(currentX1,currentY1,objectinfo[vag].xpos,objectinfo[vag].ypox);
				distanceToObject	=	calculateDistance(currentX1,currentY1,objectinfo[vag].xpos,objectinfo[vag].ypox);
				//Skall köra börja köra till objektet?????????
				
			break;
					
			case 2:	// Leta efter objektet
			break;
			
			case 3: // Ta upp objekt 
			break;
			
			case 4: // Lämna av objekt
			break;
			
		}
		
	}
}