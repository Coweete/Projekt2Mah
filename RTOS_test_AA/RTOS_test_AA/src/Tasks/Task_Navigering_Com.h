/*
 * Task_Navigering_Com.h
 *
 * Created: 2017-05-17 14:02:43
 *  Author: Elias H
 */ 
#include <asf.h>
#include <FreeRTOS.h>

#ifndef TASK_NAVIGERING_COM_H_
#define TASK_NAVIGERING_COM_H_
#define TASK_NAVIGERING_COM_STACK_SIZE (1024/sizeof(portSTACK_TYPE))
#define TASK_NAVIGERING_COM_STACK_PRIORITY (4)

void task_nav_com(void *pvParameters);




#endif /* TASK_NAVIGERING_COM_H_ */