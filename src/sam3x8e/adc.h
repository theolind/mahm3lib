/**
 * @file
 *
 * @author Hisham Ramish
 * @author Mattias Nilsson
 * @author Prince Balabis
 * @version 0.4
 * \date 17 sep 2014
 */

#include <inttypes.h>
#include "pmc.h"

///\cond
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
#define ADC_CHSR 	(*p_ADC_CHSR) 	// Channel Status Register
#define ADC_LCDR  	(*p_ADC_LCDR) 	// Last Converted Data Register
#define ADC_CDR  	(*p_ADC_CDR) 	// Channel Data Register 0
#define ADC_ISR		(*p_ADC_ISR)	// Interrupt Status Register

///\endcond

void adc_init(void);
uint8_t adc_start(void);
uint8_t adc_stop(void);
uint8_t adc_set_resolution(uint8_t resolution);
uint8_t adc_enable_channel(uint8_t ADC_CHANNEL);
uint8_t adc_disable_channel(uint8_t ADC_CHANNEL);
uint8_t adc_get_channel_status(uint8_t ADC_CHANNEL);
uint32_t adc_read_channel(uint32_t ADC_CHANNEL);
