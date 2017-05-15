/*
* TwiFunctions.c
*
* Created: 2017-05-05 10:24:13
*  Author: Jounne
*/
#include <asf.h>
#include <twi_master.h>
#include <conf_board.h>

#include "TwiFunctions.h"
#include "TwiComHandler.h"

#define TWI_SPEED					100000				//Twi communication speed
#define TWI_SLAVE_MEM_ADDR			0x00				//Twi slave  memory address
#define TWI_MASTER					CONF_BOARD_TWI0
#define PACKAGE_TO_SEND_LENGT		sizeof(sendData)
#define TWI_DATA_RECIEVE_LENGTH		3
#define TWI_DATA_SEND_LENGTH		3

struct ArmInfo arminformation;

uint8_t data_received_pab[TWI_DATA_RECIEVE_LENGTH] = {};
uint16_t data_received_nav[TWI_DATA_RECIEVE_LENGTH] = {};
uint8_t send_data_pab[TWI_DATA_SEND_LENGTH] = {};
uint8_t send_data_nav[TWI_DATA_SEND_LENGTH] = {};

twi_package_t packet_pab = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,	//TWI slave memory address data MSB
	.addr[1]		= 0,						//TWI slave memory address data LSB
	.addr_length	= 0,						//TWI slave memory address data size
	.chip			= TWI_SLAVE_PABYGGNAD,		//TWI slave bus address
	.buffer			= (void *) send_data_pab,		//transfer data source buffer
	.length			= TWI_DATA_SEND_LENGTH			//transfer data size(bytes)
};

twi_package_t packet_nav = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,	//TWI slave memory address data MSB
	.addr[1]		= 0,						//TWI slave memory address data LSB
	.addr_length	= 0,						//TWI slave memory address data size
	.chip			= TWI_SLAVE_NAVIGERING,		//TWI slave bus address
	.buffer			= (void *) send_data_nav,		//transfer data source buffer
	.length			= TWI_DATA_SEND_LENGTH			//transfer data size(bytes)
	
};

twi_package_t packet_received_pab ={
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,
	.addr[0]		= 0,
	.addr_length	= 0,
	.chip			= TWI_SLAVE_PABYGGNAD,
	.buffer			= (void*) data_received_pab,
	.length			= TWI_DATA_RECIEVE_LENGTH
};

twi_package_t packet_received_nav ={
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,
	.addr[0]		= 0,
	.addr_length	= 0,
	.chip			= TWI_SLAVE_NAVIGERING,
	.buffer			= (void*) data_received_nav,
	.length			= TWI_DATA_RECIEVE_LENGTH
};

void init_twi_functions(){
	twi_master_options_t opt;
	opt.speed = TWI_SPEED;
	if(twi_master_setup(TWI_MASTER,&opt) == TWI_SUCCESS){
		pa_sendstatus(TWI_CMD_ARM_INIT,0);
	}
}

void pa_sendstatus(TwiCmd twi_state, uint8_t underState){
	switch (twi_state){
		case TWI_CMD_ARM_INIT:
			send_data_pab[1] = TWI_CMD_ARM_REQ_BOX_INFO;
			send_package(TWI_CMD_ARM_INIT,TWI_SLAVE_PABYGGNAD);
			delay_ms(10);
			receive_package(TWI_SLAVE_PABYGGNAD);
			arminformation.boxDistance		=  data_received_pab[1];
			arminformation.boxAngle			=  data_received_pab[2];
			send_data_pab[1] = TWI_CMD_ARM_REQ_OBJ_INFO;
			send_package(TWI_CMD_ARM_INIT, TWI_SLAVE_PABYGGNAD);
			delay_ms(10);
			receive_package(TWI_SLAVE_PABYGGNAD);
			arminformation.objectDistance	=	data_received_pab[1];
			arminformation.objectAngle		=	data_received_pab[2];
			send_data_pab[1] = TWI_CMD_ARM_REQ_COLLECT_INFO;
			send_package(TWI_CMD_ARM_INIT,TWI_SLAVE_PABYGGNAD);
			delay_ms(10);
			receive_package(TWI_SLAVE_PABYGGNAD);
			arminformation.collectAll		= data_received_pab[1];
			arminformation.hasData			= data_received_pab[2];
		break;
		
		case TWI_CMD_DROPOFF_START:
			send_package(TWI_CMD_DROPOFF_START,TWI_SLAVE_PABYGGNAD);
		break;
		
		case TWI_CMD_PICKUP_START:
			if(underState == SOCK){
				send_data_pab[1] = SOCK;
				send_package(TWI_CMD_PICKUP_START,TWI_SLAVE_PABYGGNAD);
			}else if(underState == SQUARE){
				send_data_pab[1] = SQUARE;
				send_package(TWI_CMD_PICKUP_START,TWI_SLAVE_PABYGGNAD);
			}else if(underState == GLASS){
				send_data_pab[1] = SQUARE;
				send_package(TWI_CMD_PICKUP_START,TWI_SLAVE_PABYGGNAD);
			}
		break;
		
		case TWI_CMD_PICKUP_STATUS:
			send_package(TWI_CMD_PICKUP_STATUS,TWI_SLAVE_PABYGGNAD);
			delay_ms(10);
			receive_package(TWI_SLAVE_PABYGGNAD);
		break;
		
		case TWI_CMD_DROPOFF_STATUS:
			send_package(TWI_CMD_DROPOFF_STATUS,TWI_SLAVE_PABYGGNAD);
		break;
		
		case TWI_CMD_ERROR:
			send_package(TWI_CMD_ERROR,TWI_SLAVE_PABYGGNAD);
		break;
	}	
}

void  send_package(uint8_t twi_state,uint8_t slave){
	printf("in send\n");
	char sts[20];
	if(TWI_SLAVE_NAVIGERING == slave){
		printf("NAV PACK");
		send_data_nav[0] = twi_state;
		packet_nav.chip = slave;
		packet_nav.buffer = (void *) send_data_nav;
		printf("TRYING TO SEND\n");
		while(twi_master_write(TWI_MASTER,&packet_nav));
		printf("done sending nav\n");
		}else if(TWI_SLAVE_PABYGGNAD == slave){
		printf("PAB PACK0");
		send_data_pab[0] = twi_state;
		packet_pab.chip = slave;
		packet_pab.buffer = (void *)send_data_pab;
		printf("TRYING TO SEND\n");
		while(twi_master_write(TWI_MASTER,&packet_pab));
		printf("done sending pab\n");
	}
}


void receive_package(uint8_t slave){
	printf("Start of receive\n");
	char str[20];
	if (slave == TWI_SLAVE_NAVIGERING){
		printf("TRYing to receive nav");
		while(twi_master_read(TWI_MASTER, &packet_received_nav) != TWI_SUCCESS);
		printf("done sending");
		return data_received_nav;
		}else if(slave == TWI_SLAVE_PABYGGNAD){
		printf("TRYing to receive Pa");
		while(twi_master_read(TWI_MASTER, &packet_received_pab) != TWI_SUCCESS);
		printf("done sending");
	}
}
