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


	RUN_TEST(test_pmc_start_peripheral_clock_when_successful, 10);
	RUN_TEST(test_pmc_status_peripheral_clock_when_inactive, 10);
	RUN_TEST(test_pmc_status_peripheral_clock_when_active, 10);
	RUN_TEST(test_pmc_stop_peripheral_clock_when_successful, 10);
	UnityEnd();
}

