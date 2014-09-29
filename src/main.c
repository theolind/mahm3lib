/*
 * main.c
 *
 * Author:	Mathias Beckius
 *
 * Date:	29 September, 2014
 */

#include "unity/unity.h"
#include "test_runner.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();
	// run unit tests
	run_tests();

	while (1);
	return 0;
}
