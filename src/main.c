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
	//	run_tests();

		mux_shield_init(); //Initialize mux shield
		mux_shield_set_mode(MUX0, 1); // Set mux0 as DIGITAL OUTPUT
		mux_shield_set_channel(0); // Set channel to 0
		mux_shield_set_datapin(MUX0, 1); // Set mux0 to HIGH
}
