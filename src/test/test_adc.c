/*
 * Analog-to-Digital Converter (ADC) unit tests
 *
 * Author: Prince Balabis, Andreas Drotth
 * Date: 28 September 2014
 */

#include "unity/unity.h"
#include "test/test_adc.h"

// ADC Channel Status Register
uint32_t * const p_ADC_CHSR = (uint32_t *) 0x400C0018u;

// ADC Mode Register
uint32_t * const p_ADC_MR = (uint32_t *) 0x400C0004u;


/*
 * Checking that the init function doesn't accept illegal values.
 */
void test_adc_init() {
	adc_settings_t adc_settings;
	adc_settings.startup_time = 256;
	adc_settings.prescaler = 16;

	TEST_ASSERT_TRUE(adc_init(&adc_settings));

	adc_settings.startup_time = 2;
	adc_settings.prescaler = 2;

	TEST_ASSERT_FALSE(adc_init(&adc_settings));
}

/*
 * Checking that an ADC channel is enabled.
 */
void test_adc_channel_enabled(void) {
	uint8_t channel = ADC_CHANNEL_0;

	// Check if that channel is disabled
	TEST_ASSERT_FALSE(*p_ADC_CHSR & (0x1u << channel));

	adc_enable_channel(channel);

	// Check if that channel is enabled
	TEST_ASSERT_TRUE(*p_ADC_CHSR & (0x1u << channel));
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
	TEST_ASSERT_TRUE(*p_ADC_CHSR & (0x1u << channel));

	adc_disable_channel(channel);

	// Check if that channel is disabled
	TEST_ASSERT_FALSE(*p_ADC_CHSR & (0x1u << channel));
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
	TEST_ASSERT_TRUE(
			(*p_ADC_CHSR & (0x1u << channel)) & adc_channel_enabled(channel));

	adc_disable_channel(channel);

	// Check if registry value and function has the same value
	TEST_ASSERT_FALSE(*p_ADC_CHSR & (0x1u << channel));
	TEST_ASSERT_FALSE(adc_channel_enabled(channel));
}

/*
 * Test setting the ADC to use 10 bit resolution.
 */
void test_adc_set_resolution_10_bit(void) {
	adc_set_resolution(ADC_RESOLUTION_10_BIT);

	// Test if ADC is set as 10 bit
	TEST_ASSERT_TRUE(*p_ADC_MR & (0x1u << 4));
}

/*
 * Test setting the ADC to use 12 bit resolution.
 */
void test_adc_set_resolution_12_bit(void) {
	adc_set_resolution(ADC_RESOLUTION_12_BIT);

	// Test if ADC is set as 12 bit
	TEST_ASSERT_FALSE(*p_ADC_MR | (0x0u << 4));
}
