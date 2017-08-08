/*,
 * task_motor.c
 *
 * Created: 2017-05-02 10:15:57
 *  Author: Jounne
 */ 
#include <asf.h>

#include "task_motor.h"
#include "Motor/PID_Controller.h"
#include "Motor/Motorfunctions.h"
extern long sensordistance;
int x_pos = 20;
int x_dest = 25;
// Modified ELias
void task_motor(void *pvParameters){
//	initMotor2();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 300;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
// 		puts("Task motor");
// 		if(sensordistance<30 || x_pos>x_dest){
// 			moveForward1(1500,1500);
// 			}else{
// 			pidCompute(0);
// 			//P_regulator(2,2);	
// 		//	stop(10);
// 			//vTaskDelay(1000);
		}
				
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
	}
}


