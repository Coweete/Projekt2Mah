/*
* Navi.c
*
* Created: 2017-05-09 10:34:30
*  Authormodified : Elias H
*/

#include <asf.h>
#include <inttypes.h>
#include "Navi.h"
#include <math.h>
#include "Motor/Motorfunctions.h"
#include "Motor/PID_Controller.h"
float PI = M_PI;
int startposition[2] = {0,0};
int endposition[2] = {12,5};
int middleposition[2];
int currentposition[2];
int road1[2],road2[2];

uint16_t xPositionArlo=0;
uint16_t yPositionArlo=0;
uint16_t xpositionering1=0;
uint16_t ypositionering1=0;
uint16_t xpositionering2;
uint16_t ypositionering2;
double definedangle;
/*double deltaXangle, deltaYangle;*/
/*float deltaXangle,deltaYangle,deltaPS;*/

//double deltaX;
//double deltaY;


//uint64_t test = 0x0004000300020001;

//Det vi får ut från positionering__
// typedef struct allpositions{
// 	uint16_t xpos1;
// 	uint16_t ypos1;
// 	uint16_t xpos2;
// 	uint16_t ypos2;
// };

/*
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

// void calculate_rut(){
// 	middleposition[0] = startposition[0];
// 	middleposition[1] = endposition [1];
// 	road1[0] = middleposition[0] - startposition[0];
// 	road1[1] = middleposition[1] - startposition[1];
// 	print_values(road1[0],road1[1]);
// }
// 
// void print_values(int xPosition,int yPosition){
// 	char *xpos[10];
// 	char *ypos[10];
// 	sprintf(xpos,"X: %d\n",xPosition);
// 	sprintf(ypos,"Y: %d\n",yPosition);
// 	printf(xpos);
// 	printf(ypos);
//}


// void movePositionCalculated(int objekt)
// 	//	if (kloss != objekt)
// 	//Riktning mot objketet
// 	deltaXangle = cos(objekt*PI/180);
// 	deltaYangle = sin(objekt*PI/180);
// 	//Ta reda på platformens positions, ge kord till Arlo
// 	CalculateArloPosition();
// 	//Förändring i rörelsen, Uppdaterar nuvarande positionen sen för platformen
// 	PositionDifferences();
// 	moveForward1(1650,1650);
// 	//Därefter lagra positionskillnad i deltaPS:
// 	deltaPS=(deltaXangle,deltaYangle);
// }
// Current Pos = Previous Pos + Current Velo

//Ta reda på platformens positions, ge kord till Arlo
void calculateArloPosition(){
	//Ger kord till Arlo från positioneringen
	xPositionArlo = xpositionering1;
	printf("Where to? %d", xPositionArlo);
	yPositionArlo = ypositionering1;
	printf("Where to? %d", yPositionArlo);
}

//__________//
//			//
//			//
//			//
//__________//
	//Arlo vinklen.
	double arloAngleCalculate(double deltaXangle, double deltaYangle){
	deltaXangle = pow(deltaXangle,2);
	deltaYangle = pow(deltaYangle,2);
	double deltaX; // närliggande kateten. 
	double hypo = (sqrt(deltaXangle+deltaYangle)); // hypotenusan
	double valueangle = (180 / PI);
	definedangle = acos(deltaX/hypo) * valueangle; //arcos * när/hypo = grader.
	printf("Arccos %lf är %lf grader", hypo, definedangle); 
	return definedangle;
}

// Beräknar skillnad mellan positionerings kordinater och arlos positionering.
// Sedan retunerar.
double deltaArloDiff(double xpositionering1, double xPositionArlo,double ypositionering1, double yPositionArlo){			
	double fromPosToAlroX = xpositionering1 - xPositionArlo;
	double fromPosToAlroY = ypositionering1 - yPositionArlo;
	return fromPosToAlroX;
	return fromPosToAlroY;
}

// Förändring i rörelsen, Uppdaterar nuvarande positionen sen för platformen
double positionUpdateDiff(double deltaX, double deltaY ){
	deltaX += definedangle;
	deltaY += definedangle;
	xPositionArlo = deltaX;
	yPositionArlo = deltaY;
}
