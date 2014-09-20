/*
 * Test runner, add your tests here
 *
 * Created by: Theodor Lindquist
 * Date: 2014-09-10
 */

#include "unity.h"
#include "test_runner.h"

#include "test_foobar.h"
#include "test_dacc.h"

void run_tests(void) {
	Unity.TestFile = "test/test_foobar.c";
	Unity.TestFile = "test/test_dacc.c";
	UnityBegin();

	// Run foobar tests
	RUN_TEST(test_foobar, 0);

	// Run DACC tests
	RUN_TEST(test_dacc_channel_0_enable, 0);
	RUN_TEST(test_dacc_channel_1_enable, 0);

	UnityEnd();
}

