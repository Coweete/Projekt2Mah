/*
 * Task_ultraLjud.c
 *
 * Created: 2017-05-17 14:10:01
 *  Author: Elias H & André A
 */ 

#include "Tasks/Tasks.h"
#include "Functions/TaskFunctions.h"


long sensordistance = 0;

int n = 1;
int angle = 90;
int dir = 45;
char str[10];


xSemaphoreHandle signal_semafor =0;
xSemaphoreHandle regulate_semafor = 0;

xQueueHandle taskQueue = 0;

void task_ultraLjud(void *pvParameters){
	
	taskQueue = xQueueCreate(5,sizeof(int));
	
	
	printf("\nTask Ultraljud");
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 10;
	xLastWakeTime = xTaskGetTickCount();
	
	
	
	while (1){
		
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
		
		long duration;
		ioport_set_pin_level(TriggerPin,HIGH);
		delayMicroseconds(10000);
		ioport_set_pin_level(TriggerPin,LOW);
		duration = pulseins();
		sensordistance = (duration/42)/58.2;
		
		if(sensordistance <= 35){
			xSemaphoreGiveFromISR(signal_semafor,NULL);
		}
		if(!xSemaphoreTake(signal_semafor,20)){
				xSemaphoreGive(regulate_semafor);
				printf("\nOk");
				if(!xQueueSendToBack(taskQueue,&n,20)){
					printf("\nFailed to send");
					
				}
				//vTaskDelay(500);
		}
		else{
				moveForward(1500,1500);
				printf("\nStopp");
		}
		
		
		/*vTaskDelay(100);*/
		
	}
	// vTaskDelete( NULL );  // För en clean exit av tasken (Kasnke ej behövs)!
}




int pulseins(void){
	int state = 1;
	int flag = 0,clocktime;
	while(state){
		if(ioport_get_pin_level(EchoPin) && !flag){
			tc_start(TC0,0);
			flag = 1;
		}
		if(!ioport_get_pin_level(EchoPin) && flag)
		{
			clocktime = tc_read_cv(TC0,0);
			tc_stop(TC0,0);
			flag = 0;
			state = 0;
		}
	}
	return clocktime;
}

void init_sensor(void){
	printf("\nInit sensor OK");
	ioport_set_pin_dir(TriggerPin,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EchoPin,IOPORT_DIR_INPUT);
	printf("\nSet Echo & Trigger OK");
	
	vSemaphoreCreateBinary(signal_semafor);
	vSemaphoreCreateBinary(regulate_semafor);
	
	
}

void task_Regulate(void *pvParameters){
	
	
	
	int ir;
	
	
	
	portTickType xLastWakeTimeRegulate;
	const portTickType xTimeIncrementRegulate = 10;
	xLastWakeTimeRegulate = xTaskGetTickCount();
	
	
	
	while(1){
		
		vTaskDelayUntil(&xLastWakeTimeRegulate,xTimeIncrementRegulate);
		

		if(xSemaphoreTake(regulate_semafor,100)){
			
			if(xQueueReceive(taskQueue,&ir,20)){
				sprintf(str, "\nReceived: %d", ir);
				printf(str);
				}else{
				printf("\nFailed to receive");
			}
			
			switch (ir)
			{
			case 0:					//Kör framåt
				driveForward();					//Kör tills den inte gör det
				break;
			case 1:					//Sväng
				if(rotate(angle, dir)){			//angle = slut-riktning, dir = nuvarande riktning
					n=1;
				}
				break;
			case 2:					//Sensor-sök
				
				break;
			default:
				printf("\nDefault");
				break;
			}
			
			//moveForward(1500,1500);
			
			
		}
		
		
	}
	
	
	
	//vTaskDelay(100);
}

void task_nav_calc(void *pvParameters){
	
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 50;
	xLastWakeTime = xTaskGetTickCount();
	
/*	int ir = 0;*/
	
	while(1){
		
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
		
// 		if(xQueueReceive(taskQueue,&ir,0)){
// 			printf("\nReceived");
// 		}else{
// 			printf("\nFailed to receive");
// 		}
		// Kod här.
		
	}
	//vTaskDelete( NULL );  // För en clean exit av tasken (Kasnke ej behövs)!
}
