/*
 * Task_ultraLjud.h
 *
 * Created: 2017-05-17 14:12:27
 *  Author: Elias H
 */ 
#include <asf.h>
#include <FreeRTOS.h>
#include <asf.h>
//#include "Sensor/soundSensor.h"
#include "Functions/DelayFunctions.h"

//DigitalPin 23
//#define EchoPin PIO_PA14_IDX
//DigitalPin 24
//#define TriggerPin PIO_PA15_IDX
//DIGITAL PIN 7
#define EchoPin PIO_PC23_IDX
//digital pin 8
#define TriggerPin PIO_PC22_IDX
#define Channel2

#ifndef TASK_ULTRALJUD_H_
#define TASK_ULTRALJUD_H_
#define TASK_ULTRALJUD_STACK_SIZE (1024/sizeof(portSTACK_TYPE))
#define TASK_ULTRALJUD_STACK_PRIORITY (5)

int pulseins(void); 
void init_sensor(void);
void task_ultraLjud(void *pvParameters);
int distanceStop(void);



#endif /* TASK_SENSOR_H_ */