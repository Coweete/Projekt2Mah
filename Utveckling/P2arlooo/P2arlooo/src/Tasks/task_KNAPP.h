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


#define Knapp PIO_PA15_IDX			//Digital Pinne 24
#define BlinkaGreen PIO_PD9_IDX		//Digital Pinne 30
#define BlinkaYellow PIO_PD1_IDX	//Digital Pinne 26
#define BlinkaRed PIO_PD3_IDX		//Digital Pinne 28

void task_KNAPP(void *pvParameters);
void pin_edge_handler(const uint32_t id, const uint32_t index);
void knapp_handler();



#endif /* KNAPP_H_ */