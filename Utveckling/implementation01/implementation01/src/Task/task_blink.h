/*
 * task_blink.h
 *
 * Created: 2017-05-02 11:06:17
 *  Author: Jounne
 */ 


#ifndef TASK_BLINK_H_
#define TASK_BLINK_H_
#define TASK_BLINK_STACK_SIZE 1024/(sizeof(portSTACK_TYPE))
#define TASK_BLINK_PRIORITY (1)

void task_blink(void *pvParameters);

#endif /* TASK_BLINK_H_ */