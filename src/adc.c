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

uint32_t *const p_PMC_PCER1	= (uint32_t *) 0x400E0700u;

uint32_t *const p_ADC_RCR 	= (uint32_t *) 0x400C0104u;
uint32_t *const p_ADC_RNCR 	= (uint32_t *) 0x400C0114u;
uint32_t *const p_ADC_PTCR 	= (uint32_t *) 0x400C0120u;

uint32_t *const p_ADC_ISR 	= (uint32_t *) 0x400C0030u;


uint8_t adc_init(const uint32_t adc_clk){


	// Enable Peripheral clock
	*p_PMC_PCER1 = (1 << 5);

	// Software reset
	*p_ADC_CR = (0x1u << 0);

	// Reset Mode Register
	*p_ADC_MR = (0);

	// PDC Transfer Reset
	*p_ADC_PTCR = (0x1u << 1) | (0x1u << 9);
	*p_ADC_RCR = (0);
	*p_ADC_RNCR = (0);

	// Set ADC clock (prescaler set to 2)
	*p_ADC_MR |= ((0xFFu << 8) & (2 << 8)) | ((0 << 16) & (0xFu << 8));

	if (0x400C00E8 & 0x0u){
		return 1;
	}else{
		return 0;
	}

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

	if(*p_ADC_CHSR & 0x1u){
		return 0;
	} else{
		return 1;
	}

}

uint8_t adc_get_channel_status(char ADC_CHANNEL){

	if(*p_ADC_CHSR & 0x1u){
			return 1;
		} else{
			return 0;
		}

}

uint16_t adc_read_channel(char ADC_CHANNEL){


	*p_ADC_CR = (0x1u << 1);

	while(!(*p_ADC_ISR & 0x01000000));

	uint16_t data = (uint16_t)(*p_ADC_LCDR & 0x00000FFFu);

	*p_ADC_CR = (0x1u << 1);

	return data;
}
