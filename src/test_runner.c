/*
 * Test runner, add your tests here
 *
 * Created by: Theodor Lindquist
 * Date: 2014-09-10
 */

#include "unity.h"
#include "test_runner.h"

#include "test_foobar.h"
#include "test_pio.h"

void run_tests(void) {
	// run the foobar test
	Unity.TestFile = "test/test_foobar.c";
	UnityBegin();
	RUN_TEST(test_foobar, 10);
	UnityEnd();

	// run pio tests
	Unity.TestFile = "test/test_pio.c";
	UnityBegin();
	RUN_TEST(test_pio_pullup, 0);
	RUN_TEST(test_pio_output, 0);
	RUN_TEST(test_pio_read_pin, 0);
	RUN_TEST(test_pio_set_output, 0);
	UnityEnd();
}
