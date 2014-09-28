#include <stdio.h>
#include <inttypes.h>
#include "unity/unity_hw_setup.h"
#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/pmc.h"
#include "sam3x8e/adc.h"


int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	run_tests();


	return 0;
}
