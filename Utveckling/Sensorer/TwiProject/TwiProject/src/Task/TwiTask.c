/*
 * TwiTask.c
 *
 * Created: 2017-05-08 14:38:25
 *  Author: Jounne
 */ 
#include <asf.h>
#include <freertos_twi_master.h>
#include <conf_board.h>

#include "TwiTask.h"
/*
#define TWI_SPEED			100000
#define TWI_SLAVE_ADDR		0x02				//Twi slave address
#define TWI_SLAVE_MEM_ADDR	0x00				//Twi slave  memory address
#define PACKAGE_TO_SEND_LENGT sizeof(sendData)
#define PATTERN_TEST_LENGTH     6

freertos_twi_if freertos_twi;


uint8_t sendData[] = {
	0x10
};

twi_package_t packet = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,	//TWI slave memory address data MSB
	.addr[1]		= 0,						//TWI slave memory address data LSB
	.addr_length	= 0,						//TWI slave memory address data size
	.chip			= TWI_SLAVE_ADDR,			//TWI slave bus address
	.buffer			= (void *) sendData,		//transfer data source buffer
	.length			= sizeof(sendData)			//transfer data size(bytes)
};

/*
void init_twi_task(){
	freertos_twi = freertos_twi_master_init(TWI_MASTER,&driver_options);
	/*
	if(freertos_twi != NULL){
		twi_set_speed(freertos_twi,TWI_SPEED,sysclk_get_cpu_hz());
	}
	
}


static void write_page_to_eeprom(){
	twi_package_t write_parameters;
	uint16_t calculated_address;
	const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;
	
	//calculated_address = page * PAGE_SIZE;
	
	write_parameters.chip			= 0x02;
	write_parameters.buffer			= (void*) sendData;
	write_parameters.length			= sizeof(sendData);//PAGE_SIZE;
	write_parameters.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8;//(uint8_t)((calculated_address >> 8) & 0xff);
	write_parameters.addr[1]		= 0;//(uint8_t)(calculated_address & 0xff);
	write_parameters.addr_length	= 2;
	
	if(freertos_twi_write_packet(freertos_twi,&write_parameters,max_block_time_ticks) != STATUS_OK){
		printf("FEL MED SEND");
	}
}


void task_twi_com(void *pvParameters){
	
}
*/