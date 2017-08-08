/*
 * TestVikingarna.c
 *
 * Created: 2017-05-18 15:05:15
 *  Author: Jounne
 */ 

#include <asf.h>
#include "TestVikingarna.h"
#include "TwiFunctions/TwiFunctions.h"

extern uint8_t data_received_pab[];

void testloop(){
		char str[20];
		printf("Start pickup\n");
		pa_sendstatus(TWI_CMD_PICKUP_START,GLASS);
		pa_sendstatus(TWI_CMD_PICKUP_STATUS,1);
		int conter = 1;
		while(conter){
			pa_sendstatus(TWI_CMD_PICKUP_STATUS,1);
			sprintf(str,"data recive 1%d",data_received_pab[1]);
			printf(str);
			sprintf(str,"data recive 2%d",data_received_pab[2]);
			printf(str);
			if (data_received_pab[1] == 2){
				pa_sendstatus(TWI_CMD_DROPOFF_START,1);
				}else{
			}
			delay_ms(1000);
		}
}