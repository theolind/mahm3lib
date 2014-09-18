/*
 * Test runner, add your tests here
 *
 * Created by: Theodor Lindquist
 * Date: 2014-09-10
 */

#include "unity.h"
#include "test_runner.h"

#include "test_adc.h"

void run_tests(void) {
	Unity.TestFile = "test/test_adc.c";
	UnityBegin();

	RUN_TEST(test_adc_channel_enabled, 10);
	RUN_TEST(test_adc_12bit, 10);
	RUN_TEST(test_adc_10bit, 10);

	UnityEnd();
}

