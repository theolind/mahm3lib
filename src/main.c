#include "unity/unity.h"
#include "test_runner.h
#include "sam3x8e/mux.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/delay.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/adc.h"


int main(void) {
	// basic initialization of hardware and UART communication.
//	unity_hw_setup();
//
//	// run unit tests
//	run_tests();

	pio_conf_pin(PIOC, 25, 0, 1);
	pio_set_pin(PIOC, 25, 1);

}
