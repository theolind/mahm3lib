/*
 * adc.h
 *
 *  Created on: Sep 17, 2014
 *      Author: Hisham
 */

#include <stdint.h>

#define ADC_CHANNEL_0 	0
#define ADC_CHANNEL_1	1
#define ADC_CHANNEL_2	2
#define ADC_CHANNEL_3	3
#define ADC_CHANNEL_4	4
#define ADC_CHANNEL_5	5
#define ADC_CHANNEL_6	6
#define ADC_CHANNEL_7	7
#define ADC_CHANNEL_8	8
#define ADC_CHANNEL_9	9
#define ADC_CHANNEL_10	10
#define ADC_CHANNEL_11	11
#define ADC_CHANNEL_12	12
#define ADC_CHANNEL_13	13
#define ADC_CHANNEL_14	14

#define ADC_CR		(*p_ADC_CR) 	// Control Register
#define ADC_MR  	(*p_ADC_MR) 	// Mode Register
#define ADC_CHER  	(*p_ADC_CHER) 	// Channel Enable Register
#define ADC_CHDR 	(*p_ADC_CHDR) 	// Channel Disable Register
#define ADC_LCDR  	(*p_ADC_LCDR) 	// Last Converted Data Register
#define ADC_CDR0  	(*p_ADC_CDR0) 	// Channel Data Register 0

uint8_t adc_init(const uint32_t adc_clk);
uint8_t adc_set_resolution(char resolution);
uint8_t adc_enable_channel(char ADC_CHANNEL);
uint8_t adc_disable_channel(char ADC_CHANNEL);
uint8_t adc_read_channel(char ADC_CHANNEL);
