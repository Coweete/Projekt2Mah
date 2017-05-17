/*
 * Task_Regulate.h
 *
 * Created: 2017-05-17 13:12:30
 *  Author: André Ahlbertz
 *  Modified: Elias H
 */ 
#include <asf.h>
#include <FreeRTOS.h>

#ifndef TASK_REGULATE_H_
#define TASK_REGULATE_H_
#define TASK_REGULATE_STACK_SIZE (1024/sizeof(portSTACK_TYPE))
#define TASK_REGULATE_STACK_PRIORITY (3)

void task_Regulate(void *pvParameters);




#endif /* TASK_REGULATE_H_ */