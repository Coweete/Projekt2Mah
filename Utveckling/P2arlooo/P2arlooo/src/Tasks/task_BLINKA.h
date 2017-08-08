/*
* task_BLINKA.h
*
* Created: 2017-04-12 13:33:32
*  Author: Elias Hussein
*/

#ifndef TASK_BLINKA_H_
#define TASK_BLINKA_H_
#define TASK_BLINKA_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_BLINKA_STACK_PRIORITY    (2)//tskIDLE_PRIORITY

#define BlinkaGreen PIO_PD9_IDX		//Digital Pinne 30
#define BlinkaYellow PIO_PD1_IDX	//Digital Pinne 26
#define BlinkaRed PIO_PD3_IDX		//Digital Pinne 28
void task_BLINKA(void *pvParameters);


#endif /* TASK_BLINKA_H_ */