/*
 * task_soundsensor.h
 *
 * Created: 2017-05-02 10:15:37
 *  Author: Jounne
 */ 


#ifndef TASK_SOUNDSENSOR_H_
#define TASK_SOUNDSENSOR_H_
#define TASK_SOUNDSENSOR_STACK_SIZE (1024/sizeof(portSTACK_TYPE))
#define TASK_SOUNDSENSOR_STACK_PRIORITY (3)


void task_soundsensor(void *pvParameters);
int pulseins();

#endif /* TASK_SOUNDSENSOR_H_ */