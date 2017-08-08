/*
 * Position.h
 *
 * Created: 2017-05-08 10:16:52
 *  Author: zoz
 */ 


#ifndef POSITION_H_
#define POSITION_H_
/*float getDistance(float x1,float x2,float y1,float y2);*/
#define k1 PIO_PC28_IDX   //pin3 gula knappen
#define k2 PIO_PC26_IDX   //pin4 röda knappen
#define k3 PIO_PC25_IDX   //pin5 vita knappen

#define LED1 PIO_PC22_IDX  //pin8
#define LED2 PIO_PC21_IDX //pin9
#define LED3 PIO_PC29_IDX  //pin10
int ioportinit(void);


#endif /* POSITION_H_ */