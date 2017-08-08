/*
 * PID_Controller.h
 *
 * Created: 2017-05-02 11:02:51
 *  Author: zoz
 */ 


#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

void pidCompute(double setpoint);
void initMotor2(void);
void moveForward1(int l,int r);
void pulseRight1(int p2);
void pulseLeft1(int p1);

#endif /* PID_CONTROLLER_H_ */