/*
 * adc.c
 *
 * Author: Hisham Ramish, Mattias Nilsson, Prince Balabis, Andreas Drotth
 * Date: 17 September 2014
 */

#include "adc.h"

uint8_t adc_init(void) {

	// Software reset
	adc_reset();

	// Reset Mode Register
	ADC->ADC_MR = ADC_MR_RESET;

	// Set ADC clock (prescaler set to 2)
	// Set start-up time to zero
	ADC->ADC_MR |= ((0xFFu << 8) & ADC_PRESCAL_2) | (ADC_STARTUP_0 & (0xFu << 8));

	//ADC->ADC_MR |= (ADC_PRESCAL_2) | (ADC_STARTUP_0);

	// Original code
	//ADC->ADC_MR |= ((0xFFu << 8) & (2 << 8)) | ((0 << 16) & (0xFu << 8));

	return 0;
}

void adc_start(void) {
	ADC->ADC_CR = ADC_CR_START;
}

void adc_reset(void) {
	ADC->ADC_CR = ADC_CR_RESET;
}

void adc_set_resolution(uint32_t resolution) {
	ADC->ADC_MR |= ADC_MR_RES(resolution);
}

void adc_enable_channel(uint32_t channel) {
	ADC->ADC_CHER = (0x1u << channel);
}

void adc_disable_channel(uint32_t channel) {
	ADC->ADC_CHDR = (0x1u << channel);
}

uint32_t adc_channel_enabled(uint32_t channel) {
	return (ADC->ADC_CHSR & (0x1u << channel));
}

uint32_t adc_read_channel(uint32_t channel) {
	return (ADC->ADC_CDR[channel]);
}
