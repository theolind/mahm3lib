#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/bitwise_operations.h"
#include "sam3x8e/pwm.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/pmc.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	run_tests();

	return 0;
}

