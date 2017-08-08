/*
 * task_LED.h
 *
 * Created: 2017-04-12 22:46:37
 *  Author: Elias
 */ 


#ifndef TASK_LED_H_
#define TASK_LED_H_
#define TASK_LED_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY    (3)//tskIDLE_PRIORITY


void task_LED(void *pvParameters);


#endif /* TASK_LED_H_ */