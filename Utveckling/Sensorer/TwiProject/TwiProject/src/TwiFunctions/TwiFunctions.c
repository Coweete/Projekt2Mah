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

#define TWI_SPEED					100000				//Twi communication speed
#define TWI_SLAVE_PABYGGNAD			0x02				//Twi slave adress för påbyggnad
#define TWI_SLAVE_NAVIGERING		0x03				//Twi slave adress för navigering
#define TWI_SLAVE_MEM_ADDR			0x00				//Twi slave  memory address 
#define TWI_MASTER					CONF_BOARD_TWI0
#define PACKAGE_TO_SEND_LENGT		sizeof(sendData)
#define TWI_DATA_RECIEVE_LENGTH		3
#define TWI_DATA_SEND_LENGTH		1

struct platform_info pl_info;

uint8_t data_received[TWI_DATA_RECIEVE_LENGTH] = {};
uint8_t sendData[TWI_DATA_SEND_LENGTH] = {};

twi_package_t packet = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,	//TWI slave memory address data MSB
	.addr[1]		= 0,						//TWI slave memory address data LSB
	.addr_length	= 0,						//TWI slave memory address data size 
	.chip			= TWI_SLAVE_PABYGGNAD,			//TWI slave bus address	
	.buffer			= (void *) sendData,		//transfer data source buffer
	.length			= sizeof(sendData)			//transfer data size(bytes)
};

twi_package_t packet_recived ={
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,
	.addr[0]		= 0,
	.addr_length	= 0,
	.chip			= TWI_SLAVE_PABYGGNAD,
	.buffer			= (void*) data_received,
	.length			= TWI_DATA_RECIEVE_LENGTH
};

void init_twi_functions(){
	twi_master_options_t opt;
	opt.speed = TWI_SPEED;
	opt.chip = TWI_SLAVE_PABYGGNAD;
	if(twi_master_setup(TWI_MASTER,&opt) == TWI_SUCCESS){
		printf("TWI master setput \n");
		send_package(Identifiering);
		recive_package();
		pl_info.id = data_received[1];
		send_package(Placering_relativt_objekt);
		recive_package();
		pl_info.distance_object = data_received[1];
		pl_info.angle_object = data_received[2];
		send_package(Placering_relativt_lada);
		recive_package();
		pl_info.distance_box = data_received[1];
		pl_info.angle_box = data_received[2];
		send_package(Maxhastighet);
		recive_package();
		pl_info.max_speed = data_received[1];
	}
}

void send_package(uint8_t twi_state){
	printf("in send\n");
	sendData[0] = twi_state;
	printf("TRYING TO SEND\n");
	while(twi_master_write(TWI_MASTER, &packet) != TWI_SUCCESS);
	printf("DONE SENDING\n");     
}

uint8_t recive_package(){
	printf("Start of recive\n");
	while(twi_master_read(TWI_MASTER, &packet_recived) != TWI_SUCCESS);
	char str[20];
	sprintf(str,"Medelande: %i\n",data_received[0]);
	printf(str);
	sprintf(str,"Data 1: %i\n",data_received[1]);
	printf(str);
	sprintf(str,"Data 2: %i\n",data_received[2]);
	printf(str);
	printf("\n");
	return data_received;
}
