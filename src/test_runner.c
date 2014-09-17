/*
 * Test runner, add your tests here
 *
 * Created by: Theodor Lindquist
 * Date: 2014-09-10
 */

#include "unity.h"
#include "test_runner.h"

#include "test_foobar.h"
#include "test_pmc.h"

void run_tests(void) {
	// run the foobar test
	Unity.TestFile = "test/test_foobar.c";
	Unity.TestFile = "test/test_pmc.c";
	UnityBegin();
	RUN_TEST(test_foobar, 10);
	RUN_TEST(test_pmc, 10);
	UnityEnd();
}

