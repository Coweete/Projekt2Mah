/*
 * Task_ultraLjud.c
 *
 * Created: 2017-05-17 14:10:01
 *  Author: Elias H & André A
 */ 

#include "Tasks/Tasks.h"

//Höger
#define R0 PIO_PA15_IDX
#define R1 PIO_PD1_IDX
#define R2 PIO_PD3_IDX
#define R3 PIO_PD9_IDX
#define R4 PIO_PD10_IDX
#define R5 PIO_PC2_IDX
#define R_RESET PIO_PB26_IDX

//Vänster
#define L0 PIO_PD0_IDX
#define L1 PIO_PD2_IDX
#define L2 PIO_PD6_IDX
#define L3 PIO_PA7_IDX
#define L4 PIO_PC1_IDX
#define L5 PIO_PC3_IDX
#define L_RESET PIO_PA14_IDX


long sensordistance = 0;

int n = 0;
int angle = 90;



xSemaphoreHandle signal_semafor =0;
xSemaphoreHandle regulate_semafor = 0;

//xQueueHandle taskQueue = 0;

void task_ultraLjud(void *pvParameters){
	
	//taskQueue = xQueueCreate(5,sizeof(int));
	
	
	printf("\nTask Ultraljud");
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 10;
	xLastWakeTime = xTaskGetTickCount();
	
	/*int i = 0;*/
	
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
		if(!xSemaphoreTake(signal_semafor,200)){
				xSemaphoreGive(regulate_semafor);
// 				if(!xQueueSendToBack(taskQueue,&i,0)){
// 					printf("\nFailed to send");
// 				}
				//vTaskDelay(500);
				printf("\nKör");
		}
		else{
				moveForward(1500,1500);
				printf("\nStop");
		}
		/*i++;*/
		
		
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
	
	ioport_set_pin_dir(R_RESET,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(L_RESET,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(R0,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R1,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R2,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R3,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R4,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(R5,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L0,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L1,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L2,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L3,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L4,IOPORT_DIR_INPUT);
	ioport_set_pin_dir(L5,IOPORT_DIR_INPUT);
	printf("\nPins OK");
}

void task_Regulate(void *pvParameters){
	
	int newcount = 0;
	int r_count = 0;
	int l_count = 0;
	int e = 0;
	int Kp = 4;
	int speed = 1650;
	int r_speed = 0;
	int l_speed = 0;
	
	r_speed=speed;
	l_speed=speed;
	
	portTickType xLastWakeTimeRegulate;
	const portTickType xTimeIncrementRegulate = 10;
	xLastWakeTimeRegulate = xTaskGetTickCount();
	
	
	
	while(1){
		
		vTaskDelayUntil(&xLastWakeTimeRegulate,xTimeIncrementRegulate);
		
		moveForward(l_speed,r_speed);
		
		
		
		if(xSemaphoreTake(regulate_semafor,100)){
			
			ioport_set_pin_level(R_RESET,LOW);
			ioport_set_pin_level(L_RESET,LOW);
			
			r_count = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
			+ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
			
			
			
			l_count = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
			+ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
			
			e = 0 - (r_count - l_count);
			
			r_speed=speed;
			l_speed=speed;
			if(e > 0) {

				r_speed=speed-(e*Kp);
				l_speed=speed+(e*Kp);
				
			}
			else if (e < 0){
				
				r_speed=speed+(e*Kp);
				l_speed=speed-(e*Kp);
			}
			else{
				moveForward(l_speed,r_speed);
			}
			
			newcount = newcount + r_count;
			
			r_count = 0;
			l_count = 0;

			ioport_set_pin_level(R_RESET,HIGH);
			ioport_set_pin_level(L_RESET,HIGH);
			
		}
		newcount = 0;
		moveForward(1500,1500);
		
	}
	
	
	
	//vTaskDelay(100);
}


