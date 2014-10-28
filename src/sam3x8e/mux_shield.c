/*
 * mux.c
 *
 *  Created on: 25 okt 2014
 *      Author: Stefan
 */

#include <sam3x8e/mux_shield.h>
#include "pio.h"
#include "adc.h"

/**
 * Initializes the multiplex shield
 */
void mux_shield_init() {
	// Control(0-3) pins
	pio_conf_pin(PIOC, 25, 0, 0); // S3, Digital pin 5
	pio_conf_pin(PIOC, 26, 0, 0); // S2, Digital pin 4
	pio_conf_pin(PIOC, 28, 0, 0); // S1, Digital pin 3
	pio_conf_pin(PIOB, 25, 0, 0); // S0, Digital pin 2

	// Set to channel 0 as default
	pio_set_pin(PIOC, 25, 0); // S3, Digital pin 5
	pio_set_pin(PIOC, 26, 0); // S2, Digital pin 4
	pio_set_pin(PIOC, 28, 0); // S1, Digital pin 3
	pio_set_pin(PIOB, 25, 0); // S0, Digital pin 2
}

/**
 * Sets a specific channel over all multiplexes(mux0, mux1 & mux2)
 */
void mux_shield_set_channel(uint32_t channel){
	pio_set_pin(PIOC, 25, ((channel & 15) >> 3)); // S3
	pio_set_pin(PIOC, 26, ((channel & 7) >> 2)); // S2
	pio_set_pin(PIOC, 28, ((channel & 3) >> 1)); // S1
	pio_set_pin(PIOB, 25, (channel & 1)); // S0
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
uint32_t mux_shield_set_mode(uint32_t mux, uint32_t mode){
	if(mode == 1){
		pio_conf_pin(muxport, mux, 0, 0); // Set mux chosen as output
		pio_set_pin(muxport, mux, 1); // Set mux data pin as HIGH, for default behavior
		return 1;
	} else if(mode == 2){
		pio_conf_pin(muxport, mux, 1, 1); // Set mux chosen as input, pullup on
		return 2;
	} else if(mode == 3){
			adc_enable_channel(mux);
			return 3;
	} else {
		return 0;
	}
}

/**
 * Returns the level of the chosen multiplex which is set as DIGITAL INPUT.
 */
uint32_t mux_shield_read_datapin(uint32_t mux){
	return pio_read_pin(muxport, mux);
}

/**
 * Sets the level of the chosen multiplex which is set as DIGITAL OUTPUT.
 */
void mux_shield_set_datapin(uint32_t mux, uint32_t level){
	pio_set_pin(muxport, mux, level);
}

/**
 * Returns the level of the chosen multiplex which is set as ANALOG INPUT.
 */
uint32_t mux_shield_read_analog_datapin(uint32_t mux){
	return pio_read_pin(muxport, mux);
}

