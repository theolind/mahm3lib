#include "main.h"
#include "unity/unity_hw_setup.h"
#include "test_runner.h"


int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	run_tests();

	return 0;
}
