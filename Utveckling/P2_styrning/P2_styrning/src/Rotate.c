/*
 * CFile1.c
 *
 * Created: 2017-05-04 14:35:36
 *  Author: André Ahlbertz
 */
#include <asf.h>
#include <ioport.h>
#include <stdlib.h>
#include <inttypes.h>
#include "DelayFunctions.h"
#include "Motorfunctions.h"
#include "Rotate.h"

#define LEFT PIO_PC4_IDX
#define RIGHT PIO_PC5_IDX

int r_count2 = 0;
int l_count2 = 0;
int count2 = 0;


//högra räknare
#define R0 PIO_PA15_IDX
#define R1 PIO_PD1_IDX
#define R2 PIO_PD3_IDX
#define R3 PIO_PD9_IDX
#define R4 PIO_PD10_IDX
#define R5 PIO_PC2_IDX
#define R_RESET PIO_PB26_IDX
//vänstra räknaren
#define L0 PIO_PD0_IDX
#define L1 PIO_PD2_IDX
#define L2 PIO_PD6_IDX
#define L3 PIO_PA7_IDX
#define L4 PIO_PC1_IDX
#define L5 PIO_PC3_IDX
#define L_RESET PIO_PA14_IDX
void initMotor3(void){
    ioport_set_pin_dir(LEFT,IOPORT_DIR_OUTPUT);
    ioport_set_pin_dir(RIGHT,IOPORT_DIR_OUTPUT);
    ioport_set_pin_dir(R_RESET,IOPORT_DIR_OUTPUT);
    ioport_set_pin_dir(L_RESET,IOPORT_DIR_OUTPUT);
    ioport_set_pin_dir(R0,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(R1,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(R2,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(R3,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(R4,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(R5,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(L0,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(L1,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(L2,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(L3,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(L4,IOPORT_DIR_INPUT);
    ioport_set_pin_dir(L5,IOPORT_DIR_INPUT);
   
    ioport_set_pin_level(L_RESET,HIGH);
    ioport_set_pin_level(R_RESET,HIGH);
}

void rotate(int d){
    int ticks = d * 0.25;

    char str[20];
    sprintf(str,"början: %d\n",ticks);
    printf (str);
   
//     r_count2 = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
//     +ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
//     ioport_set_pin_level(R_RESET,HIGH);                                                              //hämta input värde frå pinnarna
//     l_count2 = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
//     +ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
//     ioport_set_pin_level(L_RESET,HIGH);
   
   
    if(ticks>0){                    //Positivt ticks svänger höger
        while(l_count2 < abs(ticks)){
           
            l_count2 = ioport_get_pin_level(L0)+ioport_get_pin_level(L1)*2+ioport_get_pin_level(L2)*4+ioport_get_pin_level(L3)*8
            +ioport_get_pin_level(L4)*16+ioport_get_pin_level(L5)*32;
            //ioport_set_pin_level(L_RESET,HIGH);   
           
            moveForward2(1600,1400);

            sprintf(str,"höger: %d\n",l_count2);
            printf (str);
        }
        moveForward2(1500,1500);
    }
    else if(ticks<0){                //Negativt ticks svänger vänster
        while(r_count2 < abs(ticks)){
           
            r_count2 = ioport_get_pin_level(R0)+ioport_get_pin_level(R1)*2+ioport_get_pin_level(R2)*4+ioport_get_pin_level(R3)*8
            +ioport_get_pin_level(R4)*16+ioport_get_pin_level(R5)*32;
            //ioport_set_pin_level(R_RESET,HIGH);           
            
            moveForward2(1400,1600);
            sprintf(str,"vänster: %d\n",r_count2);
            printf (str);
        }
        moveForward2(1500,1500);
    }
    //moveForward2(1500,1500);
    count2=0;
}



void pulseLeft2(int p){
    ioport_set_pin_level(LEFT,HIGH);
    delayMicroseconds(p);
    ioport_set_pin_level(LEFT,LOW);
}
void pulseRight2(int p){
    ioport_set_pin_level(RIGHT,HIGH);
    delayMicroseconds(p);
    ioport_set_pin_level(RIGHT,LOW);
}


void moveForward2(int l,int r){
    pulseLeft(l);
    pulseRight(r);
    delayMicroseconds(5250);
}