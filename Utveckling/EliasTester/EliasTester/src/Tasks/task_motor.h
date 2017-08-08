/*
 * task_motor.h
 *
 * Created: 2017-05-02 10:16:09
 *  Author: Jounne
 */ 


#ifndef TASK_MOTOR_H_
#define TASK_MOTOR_H_
#define TASK_MOTOR_STACK_SIZE 1024/(sizeof(portSTACK_TYPE))
#define TASK_MOTOR_PRIORITY (1)

void task_motor(void *pvParameters);


#endif /* TASK_MOTOR_H_ */