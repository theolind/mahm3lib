/*
 * adc.c
 *
 * Author:	Hisham Ramish,
 * 			Mattias Nilsson,
 * 			Prince Balabis,
 * 			Andreas Drotth
 * 			Mathias Beckius
 *
 * Date: 	30 September 2014
 */

#include "adc.h"

void adc_init(adc_settings_t * adc_settings) {
	// Software reset
	adc_reset();

	// Reset Mode Register
	ADC->ADC_MR = ADC_MR_RESET;

	// Configure prescaler
	ADC->ADC_MR |= (adc_settings->prescaler << ADC_MR_PRES_POS);

	// Configure startup time
	ADC->ADC_MR |= adc_settings->startup_time;
}

void adc_start(void) {
	ADC->ADC_CR = ADC_CR_START;
}

void adc_reset(void) {
	ADC->ADC_CR = ADC_CR_RESET;
}

void adc_set_resolution(uint32_t resolution) {
	if (resolution == ADC_RESOLUTION_10_BIT ||
		resolution == ADC_RESOLUTION_12_BIT) {
		ADC->ADC_MR = ADC_MR_SET_RESOLUTION(ADC->ADC_MR, resolution);
	}
}

void adc_enable_channel(uint32_t channel) {
	if (channel <= ADC_CHANNEL_MAX) {
		ADC->ADC_CHER = (0x1u << channel);
	}
}

void adc_disable_channel(uint32_t channel) {
	if (channel <= ADC_CHANNEL_MAX) {
		ADC->ADC_CHDR = (0x1u << channel);
	}
}

uint32_t adc_channel_enabled(uint32_t channel) {
	if (channel <= ADC_CHANNEL_MAX) {
		return (ADC->ADC_CHSR & (0x1u << channel));
	} else {
		return 0;
	}
}

uint32_t adc_read_channel(uint32_t channel) {
	return (ADC->ADC_CDR[channel]);
}
