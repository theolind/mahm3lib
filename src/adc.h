/**
 * \class adc
 * \brief Analog to Digital Converter (ADC)
 * \details Header for adc.c
 * \author Hisham Ramish
 * \author Mattias Nilsson
 * \author Prince Balabis
 * \version 0.2
 * \date 17 sep 2014
 */

#include <stdint.h>

#define ADC_CHANNEL_0 	0	///<Channel 0
#define ADC_CHANNEL_1	1	///<Channel 1
#define ADC_CHANNEL_2	2	///<Channel 2
#define ADC_CHANNEL_3	3	///<Channel 3
#define ADC_CHANNEL_4	4	///<Channel 4
#define ADC_CHANNEL_5	5	///<Channel 5
#define ADC_CHANNEL_6	6	///<Channel 6
#define ADC_CHANNEL_7	7	///<Channel 7
#define ADC_CHANNEL_8	8	///<Channel 8
#define ADC_CHANNEL_9	9	///<Channel 9
#define ADC_CHANNEL_10	10	///<Channel 10
#define ADC_CHANNEL_11	11	///<Channel 11
#define ADC_CHANNEL_12	12	///<Channel 12
#define ADC_CHANNEL_13	13	///<Channel 13
#define ADC_CHANNEL_14	14	///<Channel 14

#define ADC_CR		(*p_ADC_CR) 	///< Control Register
#define ADC_MR  	(*p_ADC_MR) 	///< Mode Register
#define ADC_CHER  	(*p_ADC_CHER) 	///< Channel Enable Register
#define ADC_CHDR 	(*p_ADC_CHDR) 	///< Channel Disable Register
#define ADC_CHSR 	(*p_ADC_CHSR) 	///< Channel Status Register
#define ADC_LCDR  	(*p_ADC_LCDR) 	///< Last Converted Data Register
#define ADC_CDR0  	(*p_ADC_CDR0) 	///< Channel Data Register 0

#define PMC_PCER1	(*p_PMC_PCER1)  ///< pmc peripheral

#define ADC_PTCR	(*p_ADC_PTCR)	///< Transfer Control Register

#define ADC_WPMR	(*p_ADC_WPMR)	///< Write Protect Mode Register

uint8_t adc_init(const uint32_t adc_clk);
uint8_t adc_start();
uint8_t adc_stop();
uint8_t adc_set_resolution(char resolution);
uint8_t adc_enable_channel(char ADC_CHANNEL);
uint8_t adc_disable_channel(char ADC_CHANNEL);
uint8_t adc_get_channel_status(char ADC_CHANNEL);
uint16_t adc_read_channel(char ADC_CHANNEL);
