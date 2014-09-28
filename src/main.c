#include <stdio.h>
#include <inttypes.h>
#include "sam3x8e/global_entities.h"
#include "unity/unity_hw_setup.h"
#include "unity/unity.h"
#include "test_runner.h"
/*
int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	run_tests();

	return 0;
}
*/

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	pmc_start_peripheral_clock(ID_PWM);
	pmc_start_peripheral_clock(ID_P);


	return 0;
}
