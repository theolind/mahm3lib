#include "unity/unity.h"
#include "test_runner.h"

#include "test/test_delay.h"


int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	//run_tests();

	// run delay tests
	test_delay_l_led(5000000);
	//test_delay_pin_46(10);

	return 0;
}
