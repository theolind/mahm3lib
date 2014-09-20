/**
 * @author Stefan Angelov
 */


//  TODO:
//- testa funktionen channel enable tv� g�nger, en f�r kanal 0 och en f�r kanal 1
//- testa funktionen channel disable tv� g�nger, en f�r kanal 0 och en f�r kanal 1
//- testa funktionen init, genom att l�sa mode register att dem st�memr �verrens med vad som ska st�llas in (du f�r prata med jonathan om det)
//- testa funktionen channel enabled, genom att sj�lv l�sa av registret och kontrollera att b�de funktionen och testet svarar samma

#include "dacc.h"
#include "test_dacc.h"
#include "unity.h"

<<<<<<< HEAD
void test_dacc_channel_0_enabled(){
	TEST_ASSERT_TRUE(dacc_enable_channel_0);
}

void test_dacc_channel_1_enabled(){
	TEST_ASSERT_TRUE(dacc_enable_channel_1);	
=======
void test_dacc_channel_0(){
	TEST_ASSERT_TRUE(dacc_enable_channel(0));
}

void test_dacc_channel_1(){
	TEST_ASSERT_TRUE(dacc_enable_channel(1));
>>>>>>> origin/dacc
}

void test_dacc_chanel_1_disabled(){
}
