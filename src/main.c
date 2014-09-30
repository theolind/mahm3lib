/*
 * main.c
 *
 * Author:	Mathias Beckius
 *
 * Date:	29 September, 2014
 */

#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/pmc.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/dacc.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();
	// run unit tests
	run_tests();

	const dacc_settings_t dacc_settings = {
		.speed_mode = 0,
		.refresh = 1,
		.startup_time = 0,
		.word_transfer = 0
	};
	// remove the pins from under the control of PIO
	//pio_disable_pin(PIOB, 15);	//DAC0
	//pio_disable_pin(PIOB, 16);	//DAC1
	// Enable Peripheral clock for DACC
	pmc_enable_peripheral_clock(ID_DACC);
	// initialize the DACC
	dacc_init(&dacc_settings);
	// enable channels
	dacc_enable_channel(DACC_CHANNEL_0);
	//dacc_enable_channel(DACC_CHANNEL_1);
	// write to channel 0
	dacc_select_channel(DACC_CHANNEL_0);
	while (!(dacc_tx_ready()));
	dacc_write(2048);
	// write to channel 1
//	dacc_select_channel(DACC_CHANNEL_1);
//	dacc_write(2048);

	while (1);
	return 0;
}
