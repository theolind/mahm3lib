/*
 * adc.c
 *
 *  Created on: Sep 17, 2014
 *      Author: Hisham
 */

#include "adc.h"
#include <stdint.h>


uint32_t *const p_ADC_CR 	= (uint32_t *) 0x400C0000u;
uint32_t *const p_ADC_MR 	= (uint32_t *) 0x400C0004u;
uint32_t *const p_ADC_CHER 	= (uint32_t *) 0x400C0010u;
uint32_t *const p_ADC_CHDR 	= (uint32_t *) 0x400C0014u;
uint32_t *const p_ADC_CHSR 	= (uint32_t *) 0x400C0018u;
uint32_t *const p_ADC_LCDR 	= (uint32_t *) 0x400C0020u;
uint32_t *const p_ADC_CDR0 	= (uint32_t *) 0x400C0050u;

uint8_t adc_init(const uint32_t prescal_pos){

	// Software reset
	*p_ADC_CR = (0x1u << 0);

	// Reset Mode Register
	*p_ADC_CR = (0);

	// Set ADC clock (prescaler from 1-41)
	*p_ADC_MR = (0xFFu << 8) & (prescal_pos << 8);

	return 0;
}

uint8_t adc_set_resolution(char resolution){

	if(resolution == 12){
		*p_ADC_MR = (0x0u << 4);
	} else if(resolution == 10){
		*p_ADC_MR = (0x1u << 4);
	}
	return 0;
}

uint8_t adc_enable_channel(char ADC_CHANNEL){


	*p_ADC_CHER = (0x1u << ADC_CHANNEL);

	if(*p_ADC_CHSR & 0x1u){
		return 1;
	} else{
		return 0;
	}



}

uint8_t adc_disable_channel(char ADC_CHANNEL){

	*p_ADC_CHDR = (uint32_t)(1 << ADC_CHANNEL);

	return 0;
}

uint8_t adc_read_channel(char ADC_CHANNEL){

	return 0;
}
