#include <stdio.h>
#include <inttypes.h>
#include "unity/unity_hw_setup.h"
#include "unity/unity.h"
#include "test_runner.h"
#include "sam3x8e/mux_shield.h"
#include "sam3x8e/uart.h"


int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	run_tests();

//	-----Manual tests for the MUX SHIELD API-----

	// DON'T FORGET TO INCLUDE:


		// Initialize the UART for printing the read functions

		uart_init();
		uart_tx_ready();

		// Initialize the multiplexer shield
		mux_shield_init();

		// Set shield mode
		mux_shield_set_mode(MUX_DIGITAL_0, DIGITAL_OUTPUT);
		mux_shield_set_mode(MUX_DIGITAL_1, DIGITAL_INPUT);
		mux_shield_set_mode(MUX_ADC_2, ADC_INPUT);


		while(1){
			mux_shield_set_datapin(MUX_DIGITAL_0, 1);

			mux_shield_read_datapin(MUX_DIGITAL_1);
			uart_write_str(MUX_DIGITAL_1);

			mux_shield_read_analog_datapin(MUX_ADC_2);
			uart_write_str(MUX_ADC_2);


		}

}
