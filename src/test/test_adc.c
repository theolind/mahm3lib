/*
 * Analog-to-Digital Converter (ADC) unit tests
 *
 * Author: Prince Balabis, Andreas Drotth
 * Date: 28 September 2014
 */

#include "unity/unity.h"
#include "test/test_adc.h"

/*
 * Checking that an ADC channel is enabled.
 */
void test_adc_channel_enabled(void) {
	uint8_t channel = ADC_CHANNEL_0;

	// Check if that channel is disabled
	TEST_ASSERT_FALSE(ADC->ADC_CHSR & (0x1u << channel));

	adc_enable_channel(channel);

	// Check if that channel is enabled
	TEST_ASSERT_TRUE(ADC->ADC_CHSR & (0x1u << channel));
}

/*
 * Checking that an ADC channel is disabled.
 * Requires "test_adc_channel_enabled"
 * to pass it's test
 */
void test_adc_channel_disabled(void) {
	uint8_t channel = ADC_CHANNEL_0;
	adc_enable_channel(channel);

	// Check if that channel is enabled
	TEST_ASSERT_TRUE(ADC->ADC_CHSR & (0x1u << channel));

	adc_disable_channel(channel);

	// Check if that channel is disabled
	TEST_ASSERT_FALSE(ADC->ADC_CHSR & (0x1u << channel));
}


/*
 * Test getting the state of a channel (enabled or not).
 * Requires "test_adc_channel_enabled" and
 * "test_adc_channel_disabled" to pass it's tests
 */
void test_adc_channel_status(void) {
	uint32_t channel = ADC_CHANNEL_0;
	adc_enable_channel(channel);

	// Check if registry value and function has the same value
	TEST_ASSERT_TRUE(ADC->ADC_CHSR & (0x1u << channel));
	TEST_ASSERT_TRUE(adc_channel_enabled(channel));

	adc_disable_channel(channel);

	// Check if registry value and function has the same value
	TEST_ASSERT_FALSE(ADC->ADC_CHSR & (0x1u << channel));
	TEST_ASSERT_FALSE(adc_channel_enabled(channel));
}

/*
 * Test setting the ADC to use 10 bit resolution.
 */
void test_adc_set_resolution_10_bit(void) {
	// Test if ADC is not set as 10 bit
	TEST_ASSERT_FALSE(ADC->ADC_MR | (0x0u << 4));

	adc_set_resolution(ADC_RESOLUTION_10_BIT);

	// Test if ADC is set as 10 bit
	TEST_ASSERT_TRUE(ADC->ADC_MR & (0x1u << 4));
}

/*
 * Test setting the ADC to use 12 bit resolution.
 */
void test_adc_set_resolution_12_bit(void) {
	// Test if ADC is not set as 12 bit
	TEST_ASSERT_TRUE(ADC->ADC_MR & (0x1u << 4));

	adc_set_resolution(ADC_RESOLUTION_12_BIT);

	// Test if ADC is set as 12 bit
	TEST_ASSERT_FALSE(ADC->ADC_MR | (0x0u << 4));
}
