/*
 * Interrupt_Handler.h
 *
 * Created: 2017-04-24 09:50:43
 *  Author: Elias Hussein
 */ 


#ifndef INTERRUPT_HANDLER_H_
#define INTERRUPT_HANDLER_H_

void ToggleLedISR();
void hanldler();
void ToggleLedTask(void *pvParameters) ;


#endif /* INTERRUPT_HANDLER_H_ */