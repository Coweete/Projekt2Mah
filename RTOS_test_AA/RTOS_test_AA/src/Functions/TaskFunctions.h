/*
 * TaskFunctions.h
 *
 * Created: 2017-05-19 22:04:57
 *  Author: Spellabbet
 */ 


#ifndef TASKFUNCTIONS_H_
#define TASKFUNCTIONS_H_

void init_taskFunctions(void);

void addOne(uint32_t id, uint32_t index);
void init_interrupt(void);
void resetCounter(void);

int driveForward(void);
int rotate(int turn_angle, int direction);
int cameraSearch(void);
void getCurrentPos();
void getStartData();

#endif /* TASKFUNCTIONS_H_ */