/*
 * TwiFunctions.h
 *
 * Created: 2017-05-05 10:24:22
 *  Author: Jounne
 */ 


#ifndef TWIFUNCTIONS_H_
#define TWIFUNCTIONS_H_

#include "TwiComHandler.h"
#define TWI_SLAVE_PABYGGNAD			2				//Twi slave adress för påbyggnad
#define TWI_SLAVE_NAVIGERING		3				//Twi slave adress för navigering

void init_twi_functions(void);
void send_package(uint8_t twi_state,uint8_t slave);
void receive_package(uint8_t slave);
void pa_sendstatus(TwiCmd twi_state, uint8_t understate);
//void send_test_package(uint8_t twi_state,uint8_t slave);
//void test_recieve(uint8_t slave);

#endif /* TWIFUNCTIONS_H_ */