/*
 * test_Runner.c
 *
 * Created: 2017-05-11 16:10:37
 *  Author: zoz
 */ 
#include <inttypes.h>
#include <setjmp.h>
#include <stdio_serial.h>
#include "conf_board.h"
#include "consoleFunctions.h"
#include "../unity/unity.h"					/* Contains declarations of all functions that Unity provides */
//#include "../test/test_delayFunctions.h"	/* Contains declarations of the tests for the delay used */
#include "../Test/test_CalculateAngle.h"
#include "../src/CalculateAngle.h"

void setUp(void);
void tearDown(void);
void resetTest(void);
// int main(void){
// 	sysclk_init();	/* Insert system clock initialization code here (sysclk_init()). */
// 	board_init();
// 	configureConsole();
// 	
// 	UnityBegin("../Test/test_CalculateAngle.c");
// 	RUN_TEST(test_getX_diff,10);
// }
void setUp(void)
{
	/* Do nothing */
}

void tearDown(void)
{
	/* Do nothing */
}

void resetTest(void)
{
	tearDown();
	setUp();
}