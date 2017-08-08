/*
 * delay.c
 *
 * Created: 2017-04-11 23:39:21
 *  Author: Lenovo
 */ 
#include "asf.h"
#include "delay.h"

void delayInit(void)		/* Initializes the timer used for delays */
{
	pmc_enable_periph_clk(ID_TC0);
	tc_init(TC0,0,0);		 /* TC0, channel 0, TCLK1 och capturemode */
	tc_set_block_mode(TC0,0);
	tc_stop(TC0,0);			/* making sure the timer does not run  */
}


void delayMicroseconds(uint32_t us)		/* A simple implementation for a delay in us (not calibrated) */
{
	tc_start(TC0,0);
	while (tc_read_cv(TC0,0) < us*42); /* Only works in newere version of ASF */
	tc_stop(TC0,0);
}