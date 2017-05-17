/*
 * Task_Kamera.h
 *
 * Created: 2017-05-17 14:03:23
 *  Author: Elias H
 */ 
#include <asf.h>
#include <FreeRTOS.h>

#ifndef TASK_KAMERA_H_
#define TASK_KAMERA_H_
#define TASK_KAMERA_STACK_SIZE (1024/sizeof(portSTACK_TYPE))
#define TASK_KAMERA_STACK_PRIORITY (1)

void task_kamera(void *pvParameters);

#endif /* TASK_KAMERA_H_ */