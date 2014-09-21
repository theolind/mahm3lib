/*
 * adc.c
 *
 *  Created on: Sep 17, 2014
 *      Author: Prince
 */

#include "unity.h"
#include "test_adc.h"


/*
 * Checking that ADC channel 0 is enabled
 */
void test_adc_channel_enabled(void) {
	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Enable channel and check if that channel is enabled
	TEST_ASSERT_TRUE(adc_enable_channel(channel));
}

/*
 * Test 12 bit conversion with ADC channel 0
 */
void test_adc_12bit(void) {
	pmc_start_peripheral_clock(PMC_PERIPHERAL_ADC);

	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Enable specific channel
	adc_enable_channel(channel);

	// Read the specific channel and test if a 12 bit value comes through
	TEST_ASSERT_UINT_WITHIN(2048, 2048, adc_read_channel(channel));

}

/*
 * Test 10 bit conversion with ADC channel 0
 */
void test_adc_10bit(void) {

	pmc_start_peripheral_clock(PMC_PERIPHERAL_ADC);

	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Set ADC to 10 bit
	adc_set_resolution(10);

	// Enable specific channel
	adc_enable_channel(channel);

	// Read the specific channel and test if a 10 bit value comes through
	TEST_ASSERT_UINT_WITHIN(512, 512, adc_read_channel(channel));

}

/*
 * Switch channel
 */

