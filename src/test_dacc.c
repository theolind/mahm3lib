/**
 * @author Stefan Angelov
 */


//  TODO:
//- testa funktionen channel enable två gånger, en för kanal 0 och en för kanal 1
//- testa funktionen channel disable två gånger, en för kanal 0 och en för kanal 1
//- testa funktionen init, genom att läsa mode register att dem stämemr överrens med vad som ska ställas in (du får prata med jonathan om det)
//- testa funktionen channel enabled, genom att själv läsa av registret och kontrollera att både funktionen och testet svarar samma

#include "dacc_test.h"
#include "unity.c"
#include "dacc.h"

void setUp(void){
	
}

void tearDown(void){
	
}

void test_dacc_channel_0(){
	TEST_ASSERT_TRUE(dacc_enable_channel_0);
}

void test_dacc_channel_1(){
	TEST_ASSERT_TRUE(dacc_enable_channel_1);	
}
