/*
 * test_runner.c
 *
 * Created: 2017-05-09 19:41:19
 *  Author: Jounne
 */ 
#include <asf.h>
#include "../unity/unity.h"
#include "test_TwiFunctions.h"
#include "../consoleFunctions.h"

void setUp(void);
void tearDown(void);
void resetTest(void);

/*
int main(void){
	sysclk_init();
	board_init();
	configureConsole();
	init_test_com();
	
	printf("\n");
	UnityBegin("../test/test_TwiFunctions");
	RUN_TEST(test_collect,10);
	RUN_TEST(test_hasData,20);
	RUN_TEST(test_box_angle,30);
	RUN_TEST(test_object_angle,40);
	RUN_TEST(test_box_distance,50);
	RUN_TEST(test_object_distance,60);

	UnityEnd();
	return 0;
}
*/
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