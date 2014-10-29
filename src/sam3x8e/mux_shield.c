/*
 * mux.c
 *
 *  Created on: 25 okt 2014
 *      Author: Stefan & Prince
 *
 *      To Do:
 *      -Check with architect if ADC initialization settings are okay
 *      -Finish documentation
 *      -Move documentation to .h file
 *     	-Write manual tests for each mode
 */

#include <sam3x8e/mux_shield.h>

static uint8_t chosenmode = 0;

/**
 * Initializes the multiplex shield
 */
void mux_shield_init(void) {
	// Control(0-3) pins
	pio_conf_pin(MUXSPORT0, MUXS3, 0, 0); // S3, Digital pin 5
	pio_conf_pin(MUXSPORT0, MUXS2, 0, 0); // S2, Digital pin 4
	pio_conf_pin(MUXSPORT0, MUXS1, 0, 0); // S1, Digital pin 3
	pio_conf_pin(MUXSPORT1, MUXS0, 0, 0); // S0, Digital pin 2

	// Set to channel 0 as default
	pio_set_pin(MUXSPORT0, MUXS3, 0); // S3, Digital pin 5
	pio_set_pin(MUXSPORT0, MUXS2, 0); // S2, Digital pin 4
	pio_set_pin(MUXSPORT0, MUXS1, 0); // S1, Digital pin 3
	pio_set_pin(MUXSPORT1, MUXS0, 0); // S0, Digital pin 2
}

/**
 * Sets a specific channel over all multiplexes(mux0, mux1 & mux2)
 */
void mux_shield_set_channel(uint32_t channel) {
	pio_set_pin(MUXSPORT0, MUXS3, (channel & 8)); // S3, Digital pin 5
	pio_set_pin(MUXSPORT0, MUXS2, (channel & 4)); // S2, Digital pin 4
	pio_set_pin(MUXSPORT0, MUXS1, (channel & 2)); // S1, Digital pin 3
	pio_set_pin(MUXSPORT1, MUXS0, (channel & 1)); // S0, Digital pin 2
}

/**
 * This function sets the chosen multiplex as digital input,
 * digital output or analog input
 *
 * Modes:
 * 1 : Digital output
 * 2 : Digital input
 * 3 : Analog input
 *
 */
void mux_shield_set_mode(uint32_t mux, uint32_t mode) {
	if (mode == 1) {
		pio_conf_pin(MUXPORT, mux, 0, 0); // Set multiplex chosen as output
		pio_set_pin(MUXPORT, mux, 1); // Set multiplex data pin as HIGH, for default behavior
		chosenmode = 1;
	} else if (mode == 2) {
		pio_conf_pin(MUXPORT, mux, 1, 1); // Set multiplex chosen as input, pullup on
		chosenmode = 1;
	} else if (mode == 3) {
		// Enable Peripheral clock for ADC
		pmc_enable_peripheral_clock(37);

		// Initialize the ADC
		adc_settings_t adc_settings = {
				.startup_time = 0,
				.prescaler = 0
		};
		adc_init(&adc_settings);

		// Enable multiplex channel and start reading
		adc_enable_channel(mux);

		// the resolution you want to test
		adc_set_resolution(ADC_RESOLUTION_12_BIT);
		adc_start();
		chosenmode = 3;
	}
}

/**
 * Sets the level of the chosen multiplex which is set as DIGITAL OUTPUT.
 */
void mux_shield_set_datapin(uint32_t mux, uint32_t level) {
	if(chosenmode == 1) {
		pio_set_pin(MUXPORT, mux, level);
	}
}

/**
 * Returns the level of the chosen multiplex which is set as DIGITAL INPUT.
 */
uint32_t mux_shield_read_datapin(uint32_t mux) {
	if(chosenmode == 2){
		return pio_read_pin(MUXPORT, mux);
	} else {
		return 0;
	}
}


/**
 * Returns the level of the chosen multiplex which is set as ANALOG INPUT.
 */
uint32_t mux_shield_read_analog_datapin(uint32_t mux) {
	if(chosenmode == 3){
		return pio_read_pin(MUXPORT, mux);
	} else {
		return 0;
	}
}

