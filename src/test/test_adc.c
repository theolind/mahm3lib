/*
 * Analog-to-Digital Converter (ADC) unit tests
 *
 * Author: Prince Balabis
 * Date: 17 September 2014
 */

#include "unity/unity.h"
#include "test/test_adc.h"

// ADC Channel Status Register
uint32_t * const p_ADC_CHSR = (uint32_t *) 0x400C0018u;

// ADC Mode Register
uint32_t * const p_ADC_MR = (uint32_t *) 0x400C0004u;

/*
 * Checking that an ADC channel is enabled.
 */
void test_adc_channel_enabled(void) {
	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Check if that channel is disabled
	TEST_ASSERT_FALSE(*p_ADC_CHSR & (0x1u << channel));

	// Enable channel
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
	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Enable channel
	adc_enable_channel(channel);

	// Check if that channel is enabled
	TEST_ASSERT_TRUE(*p_ADC_CHSR & (0x1u << channel));

	// Disable channel
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
	// Chosen channel to test
	uint32_t channel = ADC_CHANNEL_0;

	// Enable channel
	adc_enable_channel(channel);

	// Check if registry value and function has the same value
	TEST_ASSERT_TRUE(
			(*p_ADC_CHSR & (0x1u << channel)) & adc_channel_enabled(channel));

	// Disable channel
	adc_disable_channel(channel);

	// Check if registry value and function has the same value
	TEST_ASSERT_FALSE(*p_ADC_CHSR & (0x1u << channel));
	TEST_ASSERT_FALSE(adc_channel_enabled(channel));
}

/*
 * Test setting the ADC to use 10 bit resolution.
 */
void test_adc_set_resolution_10_bit(void) {
	// Set ADC resolution to 10 bit
	adc_set_resolution(ADC_RESOLUTION_10_BIT);

	// Test if ADC is set as 10 bit
	TEST_ASSERT_TRUE(*p_ADC_MR & (0x1u << 4));
}

/*
 * Test setting the ADC to use 12 bit resolution.
 */
void test_adc_set_resolution_12_bit(void) {
	// Set ADC resolution to 12 bit
	adc_set_resolution(ADC_RESOLUTION_12_BIT);

	// Test if ADC is set as 12 bit
	TEST_ASSERT_FALSE(*p_ADC_MR | (0x0u << 4));
}

/*
 * Test reading from a single ADC channel using 12 bit resolution.
 */
void test_adc_12bit_reading_single_channel(void) {

	// Set ADC resolution to 12 bit
	adc_set_resolution(12);

	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Enable that channel
	adc_enable_channel(channel);

	// Read channel
	uint16_t data;
	data = (uint16_t) adc_read_channel(channel);

	// Test if a 12 bit value comes through (0-4095)
	//TEST_ASSERT_UINT_WITHIN(2048, 2047, data);

	// Print value through serial communicatin
	uint16_t first, second, third, fourth;

	first = (data - (data % 1000)) / 1000;
	data = (data - first * 1000);
	second = (data - (data % 100)) / 100;
	data = (data - second * 100);
	third = (data - (data % 10)) / 10;
	data = (data - second * 10);
	fourth = data % 10;

	char dataprint[4];
	dataprint[0] = (char) first;
	dataprint[1] = (char) second;
	dataprint[2] = (char) third;
	dataprint[3] = (char) fourth;

	for (int i = 0; i < 4; i++) {
		UNITY_OUTPUT_CHAR(dataprint[i] + 48);
	}

	UNITY_OUTPUT_CHAR('\r');
	UNITY_OUTPUT_CHAR('\n');

	// Delay
	for (int i = 0; i < 10000000; i++);
}

/*
 * Test reading from a single ADC channel using 10 bit resolution.
 */
void test_adc_10bit_reading_single_channel(void) {

	// Set ADC to 10 bit
	adc_set_resolution(10);

	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Enable specific channel
	adc_enable_channel(channel);

	// Read ADC-channel
	uint16_t data;
	data = adc_read_channel(channel);

	// Test if a 12 bit value comes through (0-4095)
	//TEST_ASSERT_UINT_WITHIN(512, 511, data);

	// Print value through serial communicating
	uint16_t first, second, third, fourth;

	first = (data - (data % 1000)) / 1000;
	data = (data - first * 1000);
	second = (data - (data % 100)) / 100;
	data = (data - second * 100);
	third = (data - (data % 10)) / 10;
	data = (data - second * 10);
	fourth = data % 10;

	char dataprint[4];
	dataprint[0] = (char) first;
	dataprint[1] = (char) second;
	dataprint[2] = (char) third;
	dataprint[3] = (char) fourth;

	for (int i = 0; i < 4; i++) {
		UNITY_OUTPUT_CHAR(dataprint[i] + 48);
	}

	UNITY_OUTPUT_CHAR('\r');
	UNITY_OUTPUT_CHAR('\n');

	// Delay
	for (int i = 0; i < 10000000; i++);

}
