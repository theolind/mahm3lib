/*
 * adc.c
 *
 * Author: Hisham Ramish, Mattias Nilsson, Prince Balabis
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

uint8_t adc_start(void) {

	ADC->ADC_CR = ADC_CR_START;
	return 1;
}

uint8_t adc_reset(void) {

	ADC->ADC_CR = ADC_CR_RESET;
	return 1;
}

uint8_t adc_set_resolution(uint8_t resolution) {

	if(resolution == 12) {
		ADC->ADC_MR = ADC_MR_RES_12;
		return 1;

	} else if(resolution == 10) {
		ADC->ADC_MR = ADC_MR_RES_10;
		return 1;
	}

	return 0;
}

uint8_t adc_enable_channel(uint32_t channel) {

	ADC->ADC_CHER = (0x1u << channel);
	return 1;
}

uint8_t adc_disable_channel(uint32_t channel) {

	ADC->ADC_CHDR = (0x1u << channel);
	return 1;
}

uint8_t adc_channel_enabled(uint32_t channel) {

	if(ADC->ADC_CHSR & (0x1u << channel)) {
			return 1;

	} else {
		return 0;
	}
}

uint32_t adc_read_channel(uint32_t channel) {

	adc_start();

	while(!(ADC->ADC_ISR & ADC_ISR_DRDY));

	uint32_t data = (ADC->ADC_CDR + channel);

	//Original code
	//uint32_t data = *(p_ADC_CDR + ADC_CHANNEL);

	adc_start();

	return data;
}
