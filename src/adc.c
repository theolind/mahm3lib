/*
 * adc.c
 *
 *  Created on: Sep 17, 2014
 *      Author: Prince
 *      Author: Hisham
 */


uint32_t *const p_ADC_CR 	= (uint32_t *) 0x400C0000u;
uint32_t *const p_ADC_MR 	= (uint32_t *) 0x400C0004u;
uint32_t *const p_ADC_CHER 	= (uint32_t *) 0x400C0010u;
uint32_t *const p_ADC_CHDR 	= (uint32_t *) 0x400C0014u;
uint32_t *const p_ADC_LCDR 	= (uint32_t *) 0x400C0020u;
uint32_t *const p_ADC_CDR0 	= (uint32_t *) 0x400C0050u;

uint8_t adc_init(const uint32_t adc_clk, char resolution){

	return 0;
}
uint8_t adc_enable_channel(char ADC_CHANNEL){

	return 0;
}
uint8_t adc_disable_channel(char ADC_CHANNEL){

	return 0;
}
uint8_t adc_read_channel(char ADC_CHANNEL){

	return 0;
}
