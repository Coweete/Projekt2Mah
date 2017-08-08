/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <stdio.h>
#include <ioport.h>
#include "DelayFunctions.h"
#include "Sensor/soundSensor.h"
#include "consoleFunctions.h"
#include "Sensor/Servo.h"
#include "Navigation/Navi.h"

#define LED PIO_PB27_IDX
void testSounSensor(void){
	int sensorValue = 10;
	char *str[20];
	sensorValue = readSensorValue();
	sprintf(str, "%d",sensorValue);
	printf(str);
	printf("TESING\n");
	delayMicroseconds(1000000);
}
int main (void)
{
	uint64_t *value;
	uint64_t value1 = 64;
	uint64_t value0 = 0x0000;
	sysclk_init();
	board_init();
	ioport_init();
	delayInit();
	init_sensor();
	configureConsole();
	init_servo();
	ioport_set_pin_dir(LED,IOPORT_DIR_OUTPUT);
	
	
			
	//calculate_rut();
		
/*	uint64_t test = 0x0004000300020001;
	struct allpositions coordinates;
	coordinates.xpos1 = test;
	coordinates.xpos2 = test;
	coordinates.ypos1 = test;
	coordinates.ypos2 = test;
		
		*/
uint16_t *convertFrom64to16(uint64_t xy){
/*	static uint16_t arrayData[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	*(arrayData) = (data >> 16) & 0x00FF;
	arrayData[1] = data & 0x00FF;
	return arrayData;
	*/
uint16_t dataAll = 0x0000;
dataAll = xy;
dataAll = dataAll >> 64;

return dataAll;

}
		
		value0 = convertFrom64to16(value1);
		printf("value1:%02X\n", value1);
		return 0;
		
	while (1)
	{
		int sensorValue = 10;
		char *str[20];
		ioport_set_pin_level(LED,HIGH);
		sensorValue = readSensorValue();
		ioport_set_pin_level(LED,LOW);
		sprintf(str, "%d",sensorValue);
		printf(str);
		printf("TESING\n");
		//delayMicroseconds(1000000);
		
		//center_servo();
		//delayMicroseconds(200000);
		//move_servo_left_max();
		//delayMicroseconds(200000);
		//move_servo_rigth_max();
		//delayMicroseconds(200000);	
	}
	
}

