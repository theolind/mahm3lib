/*
* mux.c
*
* Author: 	Prince Balabis
*			Stefan Angelov
*
* Date:		25 October 2014
*
*
*/

#include <sam3x8e/mux_shield.h>

void mux_shield_init(void) {
	// Configure bit/channel select pins
	pio_conf_pin(MUX_S_PORT_0, MUX_S3, 0, 0); // S3, Digital pin 5
	pio_conf_pin(MUX_S_PORT_0, MUX_S2, 0, 0); // S2, Digital pin 4
	pio_conf_pin(MUX_S_PORT_0, MUX_S1, 0, 0); // S1, Digital pin 3
	pio_conf_pin(MUX_S_PORT_1, MUX_S0, 0, 0); // S0, Digital pin 2

	// Set multiplexes to channel 0 as default
	pio_set_pin(MUX_S_PORT_0, MUX_S3, 0); // S3, Digital pin 5
	pio_set_pin(MUX_S_PORT_0, MUX_S2, 0); // S2, Digital pin 4
	pio_set_pin(MUX_S_PORT_0, MUX_S1, 0); // S1, Digital pin 3
	pio_set_pin(MUX_S_PORT_1, MUX_S0, 0); // S0, Digital pin 2
}

void mux_shield_set_channel(uint32_t channel) {
	if (channel > 0 && channel < 15) {
		pio_set_pin(MUX_S_PORT_0, MUX_S3, (channel & 8)); // S3, Digital pin 5
		pio_set_pin(MUX_S_PORT_0, MUX_S2, (channel & 4)); // S2, Digital pin 4
		pio_set_pin(MUX_S_PORT_0, MUX_S1, (channel & 2)); // S1, Digital pin 3
		pio_set_pin(MUX_S_PORT_1, MUX_S0, (channel & 1)); // S0, Digital pin 2
	}
}

void mux_shield_set_mode(uint32_t mux, uint32_t mode) {
	if (mode == 1) {
		pio_conf_pin(MUX_PORT, mux, 0, 0); // Set multiplex chosen as output
		pio_set_pin(MUX_PORT, mux, 1); // Set multiplex data pin as HIGH, for default behavior
	} else if (mode == 2) {
		pio_conf_pin(MUX_PORT, mux, 1, 1); // Set multiplex chosen as input, pullup on
	} else if (mode == 3) {
		// Enable Peripheral clock for ADC
		pmc_enable_peripheral_clock(37);

		// Initialize the ADC
		adc_settings_t adc_settings = { .startup_time = 0, .prescaler = 0 };
		adc_init(&adc_settings);

		// Enable multiplex channel and start reading
		if (mux == MUX_DIGITAL_0) {
			adc_enable_channel(MUX_ADC_0);
		} else if (mux == MUX_DIGITAL_1) {
			adc_enable_channel(MUX_ADC_1);
		} else if (mux == MUX_DIGITAL_2) {
			adc_enable_channel(MUX_ADC_2);
		} else if (mux == MUX_ADC_0 || mux == MUX_ADC_1
				|| mux == MUX_ADC_2) {
			adc_enable_channel(mux);
		}

		// The resolution you want to test
		adc_set_resolution(ADC_RESOLUTION_12_BIT);
		adc_start();
	}
}

void mux_shield_set_datapin(uint32_t mux, uint32_t level) {
	return pio_set_pin(MUX_PORT, mux, level);
}

uint32_t mux_shield_read_datapin(uint32_t mux) {
	return pio_read_pin(MUX_PORT, mux);
}

uint32_t mux_shield_read_analog_datapin(uint32_t mux) {
	if (mux == MUX_ADC_0) {
		return adc_read_channel(MUX_ADC_0);
	} else if (mux == MUX_ADC_1) {
		return adc_read_channel(MUX_ADC_1);
	} else if (mux == MUX_ADC_2) {
		return adc_read_channel(MUX_ADC_2);
	} else if (mux == MUX_ADC_0 || mux == MUX_ADC_1
			|| mux == MUX_ADC_2) {
		return adc_read_channel(mux);
	} else {
		return 0;
	}
}

