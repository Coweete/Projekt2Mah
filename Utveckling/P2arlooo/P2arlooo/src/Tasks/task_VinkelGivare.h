/*
 * task_VinkelGivare.h
 *
 * Created: 2017-04-10 10:44:55
 *  Author: Elias Hussein
 */ 

#ifndef TASK_VINKELGIVARE_H_
#define TASK_VINKELGIVARE_H_
#define TASK_VINKELGIVARE_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_VINKELGIVARE_STACK_PRIORITY    (4)//tskIDLE_PRIORITY
#define M 3
void task_VinkelGivare(void *pvParameters);


#endif /* TASK_VINKELGIVARE_H_ */