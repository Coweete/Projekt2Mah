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
void pin_edge_handler(const uint32_t id, const uint32_t index);

#endif /* INTERRUPT_HANDLER_H_ */