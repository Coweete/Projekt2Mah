/*
 * Task_PdMm_Com.h
 *
 * Created: 2017-05-17 14:04:20
 *  Author: Elias H
 */ 
#include <asf.h>
#include <FreeRTOS.h>

#ifndef TASK_PDMM_COM_H_
#define TASK_PDMM_COM_H_
#define TASK_PDMM_COM_STACK_SIZE (1024/sizeof(portSTACK_TYPE))
#define TASK_PDMM_COM_STACK_PRIORITY (2)

void task_pdmm_Com(void *pvParameters);




#endif /* TASK_PDMM_COM_H_ */