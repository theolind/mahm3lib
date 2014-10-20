#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/pmc.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/twi.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	run_tests();

	while(1);

	return 0;
}
