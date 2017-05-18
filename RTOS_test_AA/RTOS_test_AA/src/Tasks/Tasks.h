/*
 * Task_ultraLjud.h
 *
 * Created: 2017-05-17 14:12:27
 *  Author: Elias H & André A
 */ 
#include <asf.h>
#include <FreeRTOS.h>
#include <ioport.h>
#include <stdlib.h>
#include <inttypes.h>
#include <queue.h>
//#include "Sensor/soundSensor.h"
#include "Functions/Motorfunctions.h"
#include "Functions/DelayFunctions.h"
//#include "Functions/Drive.h"
//#include "Functions/Regulator.h"
#include "Functions/Rotate.h"
#include "Functions/calculations.h"





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

#define TASK_REGULATE_H_
#define TASK_REGULATE_STACK_SIZE (1024/sizeof(portSTACK_TYPE))
#define TASK_REGULATE_STACK_PRIORITY (3)

#define TASK_NAV_CALC_H_
#define TASK_NAV_CALC_STACK_SIZE (1024/sizeof(portSTACK_TYPE))
#define TASK_NAV_CALC_STACK_PRIORITY (2)

int pulseins(void); 
void init_sensor(void);
void task_ultraLjud(void *pvParameters);
void task_Regulate(void *pvParameters);
void task_nav_calc(void *pvParameters);

#endif /* TASK_SENSOR_H_ */