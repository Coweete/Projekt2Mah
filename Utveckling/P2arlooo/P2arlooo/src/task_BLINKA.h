/*
* task_BLINKA.h
*
* Created: 2017-04-12 13:33:32
*  Author: Elias
*/

#ifndef TASK_BLINKA_H_
#define TASK_BLINKA_H_
#define TASK_BLINKA_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_BLINKA_STACK_PRIORITY    (2)//tskIDLE_PRIORITY


void task_BLINKA(void *pvParameters);


#endif /* TASK_BLINKA_H_ */