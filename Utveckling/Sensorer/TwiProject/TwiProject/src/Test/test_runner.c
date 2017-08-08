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
	
	UnityBegin("../test/test_TwiFunctions");
	RUN_TEST(test_platid,10);
	RUN_TEST(test_plat_ob_info,20);
	RUN_TEST(test_plat_speed,30);
	RUN_TEST(test_plat_box_info,40);

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