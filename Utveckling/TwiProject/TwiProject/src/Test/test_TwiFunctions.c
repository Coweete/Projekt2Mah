/*
 * test_TwiFunctions.c
 *
 * Created: 2017-05-09 19:22:11
 *  Author: Jounne
 */ 
#include <asf.h>

#include "test_TwiFunctions.h"
#include "Task/TaskNavigationCom.h"
#include "../TwiFunctions/TwiFunctions.h"
#include "../unity/unity.h"

#define distance_obj 10
#define distance_box 11
#define angle_obj 5
#define angle_box 6
#define collect 1
#define data 244

extern struct ArmInfo arminformation;


void init_test_com(void){
	init_twi_functions();
}

void test_box_distance(void){
	TEST_ASSERT_EQUAL(distance_box,arminformation.boxDistance);
}

void test_box_angle(void){
	TEST_ASSERT_EQUAL(angle_box,arminformation.boxAngle);
}

void test_object_angle(void){
	TEST_ASSERT_EQUAL(angle_obj,arminformation.objectAngle);
}

void test_object_distance(void){
	TEST_ASSERT_EQUAL(distance_obj,arminformation.objectDistance);
}

void test_collect(void){
	TEST_ASSERT_EQUAL(collect,arminformation.collectAll);
}

void test_hasData(void){
	TEST_ASSERT_EQUAL(data,arminformation.hasData);
}