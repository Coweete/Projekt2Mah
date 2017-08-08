/*
 * task_KNAPP.h
 *
 * Created: 2017-04-17 15:50:32
 *  Author: Elias Hussein
 */ 



#ifndef TASK_KNAPP_H_
#define TASK_KNAPP_H_
#define TASK_KNAPP_STACK_SIZE     (2048/sizeof(portSTACK_TYPE))
#define TASK_KNAPP_STACK_PRIORITY    (5)//tskIDLE_PRIORITY


void task_KNAPP(void *pvParameters);


#endif /* KNAPP_H_ */