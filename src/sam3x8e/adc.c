/*
 * adc.c
 *
 * Author: Hisham Ramish, Mattias Nilsson, Prince Balabis, Andreas Drotth
 * Date: 28 September 2014
 */

#include "adc.h"

uint8_t adc_init(adc_settings_t * adc_settings) {
	if (adc_settings->prescaler > 255 || adc_settings->startup_time > 15){
		return 1;
	}
	else {
		// Software reset
		adc_reset();

		// Reset Mode Register
		ADC->ADC_MR = ADC_MR_RESET;

		// Configure prescaler
		ADC->ADC_MR |= (adc_settings->prescaler << ADC_MR_PRES_POS);

		// Configure startup time
		ADC->ADC_MR |= adc_settings->startup_time;

		return 0;
	}
}

void adc_start(void) {
	ADC->ADC_CR = ADC_CR_START;
}

void adc_reset(void) {
	ADC->ADC_CR = ADC_CR_RESET;
}

void adc_set_resolution(uint32_t resolution) {
	//ADC->ADC_MR |= ADC_MR_RES(resolution);

	if(resolution == 0){
		ADC->ADC_MR &= ADC_MR_RES(resolution);
	}
	else if (resolution == 1){
		ADC->ADC_MR |= ADC_MR_RES(resolution);
	}
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
