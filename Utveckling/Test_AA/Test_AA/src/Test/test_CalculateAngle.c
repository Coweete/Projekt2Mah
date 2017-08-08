/*
 * test_Regulator.c
 *
 * Created: 2017-05-11 00:58:16
 *  Author: zoz
 */ 
#include <asf.h>
#include "../unity/unity.h"
#include "CalculateAngle.h"
#include "test_CalculateAngle.h"



void test_getX_diff(void){
	TEST_ASSERT_TRUE(getX_diff(5,2));
}
void test_getY_diff(void){
	TEST_ASSERT_TRUE(getY_diff(2,5));
}
void test_CalculateAngle(void){
	TEST_ASSERT_FALSE(calculateAngle(2,2));
}
void test_CalculatesetPoint(void){
	TEST_ASSERT_TRUE(calculateSetPoint(0,0));
}
void test_CalculateDistance(void){
	TEST_ASSERT_FALSE(calculateDistance(0,0));
}