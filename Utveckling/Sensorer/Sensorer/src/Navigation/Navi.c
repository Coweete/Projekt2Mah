/*
 * Navi.c
 *
 * Created: 2017-05-02 08:34:30
 *  Author: Jounne
 */ 

#include <asf.h>
#include <inttypes.h>
#include "Navi.h"

int startposition[2] = {0,0};
int endposition[2] = {12,5};
int middleposition[2];
int currentposition[2];
int road1[2],road2[2];




//uint64_t test = 0x0004000300020001;
typedef struct allpositions{
	uint16_t xpos1;
	uint16_t ypos1;
	uint16_t xpos2;
	uint16_t ypos2;
};

/*
 * Modoefied by : Elias 
 *  
 */

	//uint64_t Positionering = 0x00 04 0003 0020001;
	
// 	uint64_t Positionering = 0x00000000000000FF;
// 	printf("Positionering %llu \n", Positionering );
// 	
// 	uint16_t X1 = X1 & 0xFFFF;
// 	printf("X1 %llu \n", X1);
// 
// 	Positionering = Positionering <<1;
// 	printf("Positionering %llu \n", Positionering );
// 	
// 	uint16_t X2 = X2 << 0x0000000000FF00;
// 	printf("X2 %llu \n", X2);


// uint64_t konvertera64till16(uint16_t X1, uint16_t X2, uint16_t Y1, uint16_t Y2) {
// 	uint64_t Positionering = 0x0004000300020001;
// 	//Positionering = X1;
// 	X1 = Positionering & 0x00FF;
// 	printf("%d \n", X1);
// 	Positionering = Positionering <<8;
// 	X1 = X1 <<8;
// 	X2 = Positionering & 0xFF00;
// 	printf("%d \n", X2);
// 	Positionering = Positionering <<8;
// 	Y1 = Positionering & 0x00FF;
// 	printf("%d \n", Y1);
// 	Positionering = Positionering <<8;
// 	Y2 = Positionering & 0xFF00;
// 	printf("%d \n", Y2);
// }



// uint64_t konvertera64till16(int16_t X1, int16_t X2, int16_t Y1, int16_t Y2) {
//     //uint16_t arrayData[4] = { 0x0000, 0x0000,0x0000 ,0x0000  };
// 	uint64_t Positionering = 0x0004000300020001;
// 	//Positionering = X1;
// 	X1 = Positionering & 0x00FF;
// 	Positionering = Positionering <<8;
// 	X2 = Positionering & 0xFF00;
// 	Positionering = Positionering <<8;
// 	Y1 = Positionering & 0x00FF;
// 	Positionering = Positionering <<8;
// 	Y2 = Positionering & 0xFF00;
// }



// uint64_t test = 0x0004000300020001;
// typedef struct allpositions{
// 	uint16_t X1pos,X2pos,Y1pos,Y2pos;
// 	};
// 
// struct allpositions test ={
// 	.X1pos = 0x00FF, 
// 	.X2pos = 0xFF00, 
// 	.Y1pos = 0xFF00, 
// 	.Y2pos = 0xFF00,
// 	};




	
// uint16_t test = 0x0004000300020001;
// typedef struct allpositions{
// 	int16_t xxpos1,
// 	int16_t xxpos2,
// 	int16_t yypos1,
// 	int16_t yypos2,
// };




void calculate_rut(){
	middleposition[0] = startposition[0];
	middleposition[1] = endposition [1];
	road1[0] = middleposition[0] - startposition[0];
	road1[1] = middleposition[1] - startposition[1];
	print_values(road1[0],road1[1]);
}


void print_values(int xPosition,int yPosition){
	char *xpos[10];
	char *ypos[10];
	sprintf(xpos,"X: %d\n",xPosition);
	sprintf(ypos,"Y: %d\n",yPosition);
	printf(xpos);
	printf(ypos);
}

void getCurrentPosition(){
	//something here
}
