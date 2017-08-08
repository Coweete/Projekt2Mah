/*
 * TwiFunctions.h
 *
 * Created: 2017-05-05 10:24:22
 *  Author: Jounne
 */ 


#ifndef TWIFUNCTIONS_H_
#define TWIFUNCTIONS_H_

typedef enum messageType{
	Identifiering				= 0x10,
	Placering_relativt_objekt	= 0x11,
	Placering_relativt_lada		= 0x12,
	Maxhastighet				= 0x13,
	Lyckat_lyft					= 0x14,
	Misslyckat_lyft				= 0x15,
	Lyckad_avlamning			= 0x16,
	Misslyckad_avlamning		= 0x17,
	Justera_position			= 0x18,
	Avbryt_justering			= 0x19,
	Uppstart_pabyggnad			= 0x20,
	Lyft_kloss					= 0x21,
	Lyft_glas					= 0x22,
	Lyft_strumpa				= 0x23,
	Avbryt_lyft					= 0x24,
	Lamna_av_objekt				= 0x25,
	Position_av_lada			= 0x30,
	Aktuell_position_robot		= 0x31,
	Start_position_strumpa		= 0x32,
	Start_position_kloss		= 0x33,
	Start_position_glas			= 0x34,
	Uppstart_Position			= 0x40
} message_twi;

typedef struct platform_info {
	uint8_t id;					//Platformens id
	uint8_t distance_object;	//Avstånd till objeket
	uint8_t angle_object;		//Vinkel till objektet
	uint8_t distance_box;		//Avstånd till lådan
	uint8_t angle_box;			//Vinkel till lådan
	uint8_t max_speed;			//Maxhastigheten

 };

void init_twi_functions();
void send_package(uint8_t twi_state);
uint8_t recive_package();


#endif /* TWIFUNCTIONS_H_ */