#include <stdio.h>
#include <inttypes.h>
#include "unity_hw_setup.h"
#include "unity.h"
#include "test_runner.h"

#include "adc.h"
#include "dacc.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();


	run_tests();

	return 0;
}