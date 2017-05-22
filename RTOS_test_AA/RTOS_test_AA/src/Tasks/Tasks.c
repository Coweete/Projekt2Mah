/*
 * Task_ultraLjud.c
 *
 * Created: 2017-05-17 14:10:01
 *  Author: Elias H & André A
 */ 

#include "Tasks/Tasks.h"
#include "Functions/TaskFunctions.h"
#include "TwiFunctions/TwiFunctions.h"

long sensordistance = 10;

int n = 0;
int angle = 135;
int dir = 45;
char str[30];

extern uint8_t data_received_pab[];
extern uint8_t data_received_nav[];
extern struct ObjectInfo objectinfo[4];
extern struct ArmInfo arminformation;

int flag_test = 1;
int main_case = 1;

int targetAngle = 0;
int currentAngle = 90; // 0 till höger, 90 till vänster, 
int addAngle = 0;
int targetDistance = 0;
int drivenToTarget = 0;

uint16_t xtest1 = 0;
uint16_t ytest1 = 0;
uint16_t xtest2 = 200;
uint16_t ytest2 = 200;
extern int16_t currentPos[4];

xSemaphoreHandle signal_semafor =0;
xSemaphoreHandle regulate_semafor = 0;
xSemaphoreHandle main_semafor = 0;


xQueueHandle taskQueue = 0;

void task_ultraLjud(void *pvParameters){
	
	vSemaphoreCreateBinary(signal_semafor);
	vSemaphoreCreateBinary(regulate_semafor);
	vSemaphoreCreateBinary(main_semafor);
	
	taskQueue = xQueueCreate(5,sizeof(int));
	
	
	printf("\nTask Ultraljud");
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 500;
	xLastWakeTime = xTaskGetTickCount();
	
	printf("\nGet start data");
	getStartData();
	sprintf(str,"\nstart data. x=%d y=%d",objectinfo[0].xpos,objectinfo[0].ypox);
	printf(str);
	
	while (1){
		
		vTaskDelayUntil(&xLastWakeTime,xTimeIncrement);
		
		long duration;
		ioport_set_pin_level(TriggerPin,HIGH);
		delayMicroseconds(10000);
		ioport_set_pin_level(TriggerPin,LOW);
		duration = pulseins();
		sensordistance = (duration/42)/58.2;
		
		switch (main_case)
		{
		case 1:
			printf("\nMain case 1");
			getStartData();
			targetAngle = calculateAngle(currentPos[0],currentPos[1],objectinfo[0].xpos,objectinfo[0].ypox);		//Fungerar
			sprintf(str,"\ntarget angle = %d",targetAngle);
			printf(str);	
			addAngle = rotate(targetAngle,currentAngle);
			
			currentAngle = (currentAngle + 360 + addAngle) % 360;
			
			sprintf(str,"\ncurrentAngle = %d",currentAngle);
			printf(str);
				
			main_case = 2;

			break;
		case 2:
			printf("\nMain case 2");
			targetDistance = calculateDistance(xtest1,ytest1,xtest2,ytest2);
			
			sprintf(str,"\ndistance to target = %d",targetDistance);
			printf(str);
			
			
			
			drivenToTarget = drivenToTarget + (driveForward() * 1.36);
			printf("\nDistance drive");
			
			sprintf(str,"\ndriven to target = %d",drivenToTarget);
			printf(str);
			
			

			if(30 > (targetDistance-drivenToTarget)){
				moveForward(1500,1500);
				printf("\nDistance stop");
				main_case = 3;
			} 
			
			break;
		case 3:
			printf("\nMain case 3");
			
			break;
		default:	
			printf("\nmain default");
			break;
			
		}
		
		
		
		
		
		
// 		if(sensordistance <= 5){
// 			xSemaphoreGiveFromISR(signal_semafor,NULL);
// 		}
// 		
// 		if(!xSemaphoreTake(signal_semafor,20)){
// 				xSemaphoreGive(regulate_semafor);
// 				//printf("\nOk");
// 				if(!xQueueSendToBack(taskQueue,&n,20)){
// 					//printf("\nFailed to send");
// 					
// 				}
// 		}
// 		else{
// 			
// 			
// 			
// 			//vTaskDelay(500);	
// 			moveForward(1500,1500);
// 			printf("\nStopp");
//			getCurrentPos();
			//vTaskDelay(100);
// 			if(flag_test){
// 				printf("Start pa\n");
// 				pa_sendstatus(TWI_CMD_PICKUP_START,SOCK);
// 				flag_test=0;
// 				}else{
// 				printf("done sending\n");
// 				pa_sendstatus(TWI_CMD_PICKUP_STATUS,0);
// 				if (data_received_pab[1]==2){
// 					flag_test=1;
// 					pa_sendstatus(TWI_CMD_DROPOFF_START,0);
// 				}
// 			}
				
//		}
		
		
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
					n=3;
				}else{
					printf("\nRotate not completed");
				}
				break;
			case 2:					//Sensor-sök
				if(cameraSearch()){
					n=3;
				}else{
					printf("\nObject not found");
				}
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
