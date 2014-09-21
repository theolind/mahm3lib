/*
 * Test runner, add your tests here
 *
 * Author: Theodor Lindquist
 * Author: Soded Alatia
 * Date: 2014-09-18
 */

#include "unity.h"
#include "test_runner.h"

#include "test_foobar.h"

#include "test_pmc.h"

#include "test_pio.h"
#include "pio.h"


void run_tests(void) {
	// run the foobar test
	Unity.TestFile = "test/test_pio.c";
	Unity.TestFile = "test/test_pmc.c";
	UnityBegin();

	/*
	// run pio tests
	RUN_TEST(test_pio_pullup, 0);
	RUN_TEST(test_pio_output, 0);
	RUN_TEST(test_pio_read_pin, 0);
	RUN_TEST(test_pio_set_output, 0);
	*/
	// run pmc tests
	RUN_TEST(test_pmc_start_peripheral_clock_when_successful, 10);
	RUN_TEST(test_pmc_status_peripheral_clock_when_inactive, 10);
	RUN_TEST(test_pmc_status_peripheral_clock_when_active, 10);
	RUN_TEST(test_pmc_stop_peripheral_clock_when_successful, 10);
	UnityEnd();

}
