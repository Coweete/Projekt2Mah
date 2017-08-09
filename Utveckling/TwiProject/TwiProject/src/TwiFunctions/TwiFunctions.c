/*
* TwiFunctions.c
*
* Created: 2017-05-05 10:24:13
*  Author: Jonatan Fridsten
*/
#include <asf.h>
#include <twi_master.h>
#include <conf_board.h>

#include "TwiFunctions.h"
#include "TwiComHandler.h"

#define TWI_SPEED					100000						//Hastigheten på twi bussen
#define TWI_SLAVE_MEM_ADDR			0x00						//Twi slav addressen
#define TWI_MASTER_NAV				CONF_BOARD_TWI0				//Sätter TWI till TWIO på due kortet
#define TWI_MASTER_PAB				CONF_BOARD_TWI1
#define TWI_DATA_RECIEVE_LENGTH_PA		3						//Längden på paketet för skicka till påbyggnad
#define TWI_DATA_SEND_LENGTH_PA			3						//Längden på paketet för att ta emot från påbyggnaden
#define TWI_DATA_RECIEVE_LENGTH_NA		5						//Längden på paketet för att ta emot från posititonssystemet
#define TWI_DATA_SEND_LENGTH_NA			1						//Längden på paketet för att skicka till positionssystemet

struct ArmInfo arminformation;									//Information om påbyggnaden kommer att sparas i denna structen
struct ObjectInfo objectinfo[4];								//Information om objekten kommer att lagras i denna lista med structer
//[0] = Strumpa,[1] = Kloss,[2] = Glas,[3] = En positionen av lådan, den andra ligger i origo

uint8_t data_received_pab[TWI_DATA_RECIEVE_LENGTH_PA] = {};		//Datan som kommer att hittas från paketet från påbyggnaden
uint8_t data_received_nav[TWI_DATA_RECIEVE_LENGTH_NA] = {};		//Datan från positionssystemet
uint8_t send_data_pab[TWI_DATA_SEND_LENGTH_PA] = {};			//Datan som skickas till påbyggnaden
uint8_t send_data_nav[TWI_DATA_SEND_LENGTH_NA] = {};			//Datan som skickas till positionssystemet

//Paketet som skickas till påbyggnaden
twi_package_t packet_pab = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,					//TWI slav, Minnes adressen MSB
	.addr[1]		= 0,										//TWI slav, Minnes adressen LSB
	.addr_length	= 0,										//TWI slav, storleken på minnes adressen
	.chip			= TWI_SLAVE_PABYGGNAD,						//TWI slav, adressen
	.buffer			= (void *) send_data_pab,					//Pekare till datan
	.length			= TWI_DATA_SEND_LENGTH_PA					//Storleken på datan
};

//Paketet som skickas till positionssystemet
twi_package_t packet_nav = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,					//TWI slave memory address data MSB
	.addr[1]		= 0,										//TWI slave memory address data LSB
	.addr_length	= 0,										//TWI slave memory address data size
	.chip			= TWI_SLAVE_NAVIGERING,						//TWI slave bus address
	.buffer			= (void *) send_data_nav,					//Pekare till datan
	.length			= TWI_DATA_SEND_LENGTH_NA					//Storleken på datan
	
};

//Hämtningspacket för påbyggnaden
twi_package_t packet_received_pab ={
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,
	.addr[0]		= 0,
	.addr_length	= 0,
	.chip			= TWI_SLAVE_PABYGGNAD,
	.buffer			= (void*) data_received_pab,
	.length			= TWI_DATA_RECIEVE_LENGTH_PA
};

//Hämtnings paketet för positionssystemet
twi_package_t packet_received_nav ={
	.addr[0]		= TWI_SLAVE_MEM_ADDR >> 8,
	.addr[0]		= 0,
	.addr_length	= 0,
	.chip			= TWI_SLAVE_NAVIGERING,
	.buffer			= (void*) data_received_nav,
	.length			= TWI_DATA_RECIEVE_LENGTH_NA
};

/************************************************************************/
/*Sätter Ardunino Due till Master på twi bussen		                    */
/************************************************************************/
void init_twi_functions(){
	twi_master_options_t opt;
	opt.speed = TWI_SPEED;
	if(twi_master_setup(TWI_MASTER_NAV,&opt) == TWI_SUCCESS){
		printf("TWI NAV OK");
	}
	if(twi_master_setup(TWI_MASTER_PAB,&opt) == TWI_SUCCESS){
		printf("TWI PAB OK");
	}
}

/************************************************************************/
/* Tar han om kommunikationen mellan mastern och						*/
/* slaven för positionssytemet											*/
/************************************************************************/
void na_sendstatus(TwiCmd twi_state){
	char ar[20];
	switch(twi_state){
		//Led 1 position
		case XY1:
		send_package(XY1,TWI_SLAVE_NAVIGERING);
		vTaskDelay(10);
		receive_package(TWI_SLAVE_NAVIGERING);
		break;
		
		//Led 2 position
		case XY2:
		send_package(XY2,TWI_SLAVE_NAVIGERING);
		receive_package(TWI_SLAVE_NAVIGERING);
		break;
		
		//socket position
		case SOCKETXY:
		send_package(SOCKETXY,TWI_SLAVE_NAVIGERING);
		//delayMicroseconds(50000);
		receive_package(TWI_SLAVE_NAVIGERING);
		objectinfo[0].theObject = SOCK;
		objectinfo[0].xpos = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
		objectinfo[0].ypox = ((data_received_nav[3] << 8) | (data_received_nav[4] <<0));
		break;
		
		//Square position
		case SQUAREXY:
		send_package(SQUAREXY,TWI_SLAVE_NAVIGERING);
		receive_package(TWI_SLAVE_NAVIGERING);
		objectinfo[1].theObject = SQUARE;
		objectinfo[1].xpos = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
		objectinfo[1].ypox = ((data_received_nav[3] << 8) | (data_received_nav[4] <<0));
		break;
		
		//Glass position
		case GLASSXY:
		send_package(GLASSXY,TWI_SLAVE_NAVIGERING);
		receive_package(TWI_SLAVE_NAVIGERING);
		objectinfo[2].theObject = GLASS;
		objectinfo[2].xpos = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
		objectinfo[2].ypox = ((data_received_nav[3] << 8) | (data_received_nav[4] <<0));
		break;
		
		//Boxgal info
		case BOXGOALXY:
		send_package(BOXGOALXY,TWI_SLAVE_NAVIGERING);
		receive_package(TWI_SLAVE_NAVIGERING);
		objectinfo[3].theObject = BOXGOALXY;
		objectinfo[3].xpos = ((data_received_nav[1] << 8) | (data_received_nav[2] << 0));
		objectinfo[3].ypox = ((data_received_nav[3] << 8) | (data_received_nav[4] <<0));
		break;
	}
	

}

/************************************************************************/
/* Tar han om kommunikationen mellan mastern och						*/
/* slaven för positionssytemet											*/
/************************************************************************/
void pa_sendstatus(TwiCmd twi_state, uint8_t underState){
	switch (twi_state){
		//Hämtar information om påbyggnaden och sparar undan den 
		case TWI_CMD_ARM_INIT:
		send_data_pab[1] = TWI_CMD_ARM_REQ_BOX_INFO;
		send_package(TWI_CMD_ARM_INIT,TWI_SLAVE_PABYGGNAD);
		receive_package(TWI_SLAVE_PABYGGNAD);
		arminformation.boxDistance		=  data_received_pab[1];
		arminformation.boxAngle			=  data_received_pab[2];
		send_data_pab[1] = TWI_CMD_ARM_REQ_OBJ_INFO;
		send_package(TWI_CMD_ARM_INIT, TWI_SLAVE_PABYGGNAD);
		receive_package(TWI_SLAVE_PABYGGNAD);
		arminformation.objectDistance	=	data_received_pab[1];
		arminformation.objectAngle		=	data_received_pab[2];
		send_data_pab[1] = TWI_CMD_ARM_REQ_COLLECT_INFO;
		send_package(TWI_CMD_ARM_INIT,TWI_SLAVE_PABYGGNAD);
		receive_package(TWI_SLAVE_PABYGGNAD);
		arminformation.collectAll		= data_received_pab[1];
		arminformation.hasData			= data_received_pab[2];
		break;
		
		//Startar avlämningen
		case TWI_CMD_DROPOFF_START:
		send_package(TWI_CMD_DROPOFF_START,TWI_SLAVE_PABYGGNAD);
		break;
		
		//Startar uppplockningen
		case TWI_CMD_PICKUP_START:
		if(underState == SOCK){
			send_data_pab[1] = SOCK;
			send_package(TWI_CMD_PICKUP_START,TWI_SLAVE_PABYGGNAD);
			}else if(underState == SQUARE){
			send_data_pab[1] = SQUARE;
			send_package(TWI_CMD_PICKUP_START,TWI_SLAVE_PABYGGNAD);
			}else if(underState == GLASS){
			send_data_pab[1] = GLASS;
			send_package(TWI_CMD_PICKUP_START,TWI_SLAVE_PABYGGNAD);
		}
		break;
		
		//Kontrollerar hur det går med upp plockningen
		case TWI_CMD_PICKUP_STATUS:
		send_package(TWI_CMD_PICKUP_STATUS,TWI_SLAVE_PABYGGNAD);
		delay_ms(10);
		receive_package(TWI_SLAVE_PABYGGNAD);
		break;
		
		//Kontrollerar om hur det går med avlämningen
		case TWI_CMD_DROPOFF_STATUS:
		send_package(TWI_CMD_DROPOFF_STATUS,TWI_SLAVE_PABYGGNAD);
		break;
		
		//Skickar ett error medelande
		case TWI_CMD_ERROR:
		send_package(TWI_CMD_ERROR,TWI_SLAVE_PABYGGNAD);
		break;
	}
}

/************************************************************************/
/* Huvudfunktionen för att skicka ett packet till angiven slav.			*/
/* 																		*/
/************************************************************************/
void  send_package(uint8_t twi_state,uint8_t slave){
	printf("in send\n");
	char sts[20];
	
	if(TWI_SLAVE_NAVIGERING == slave){
		printf("NAV PACK");
		send_data_nav[0] = twi_state;
		packet_nav.chip = slave;
		packet_nav.buffer = (void *)send_data_nav;
		printf("TRYING TO SEND\n");
		while(twi_master_write(TWI_MASTER_NAV,&packet_nav));
		printf("done sending nav\n");
		
		}else if(TWI_SLAVE_PABYGGNAD == slave){
		printf("PAB PACK0");
		send_data_pab[0] = twi_state;
		packet_pab.chip = slave;
		packet_pab.buffer = (void *)send_data_pab;
		printf("TRYING TO SEND\n");
		while(twi_master_write(TWI_MASTER_PAB,&packet_pab));
		printf("done sending pab\n");
	}
}

/************************************************************************/
/* Tar emot ett packet från den angivna slaven som skickas med i metoden*/
/************************************************************************/
void receive_package(uint8_t slave){
	printf("Start of receive\n");
	char str[20];
	
	if (slave == TWI_SLAVE_NAVIGERING){
		printf("TRYing to receive nav");
		while(twi_master_read(TWI_MASTER_NAV, &packet_received_nav) != TWI_SUCCESS);
		printf("done sending");
		
		}else if(slave == TWI_SLAVE_PABYGGNAD){
		printf("TRYing to receive Pa");
		while(twi_master_read(TWI_MASTER_PAB, &packet_received_pab) != TWI_SUCCESS);
		printf("done sending");
	}
}
