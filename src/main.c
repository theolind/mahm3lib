#include <stdio.h>
#include <inttypes.h>
#include "unity/unity_hw_setup.h"
#include "unity/unity.h"
#include "test_runner.h"
#include "sam3x8e/delay.h"
#include "sam3x8e/arduino_due.h"
#include "sam3x8e/info.h"
#include "sam3x8e/mux_shield.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/pmc.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	run_tests();

	mux_shield_init();
	mux_shield_set_mode(MUX_DIGITAL_0, DIGITAL_OUTPUT);
	mux_shield_set_mode(MUX_DIGITAL_1, DIGITAL_INPUT);
	mux_shield_set_mode(MUX_ADC_2, ADC_INPUT);

	while(1){
		mux_shield_set_datapin(MUX_DIGITAL_0, 1);
		mux_shield_read_datapin(MUX_DIGITAL_1);
		mux_shield_read_analog_datapin(MUX_ADC_2);
	}
}
