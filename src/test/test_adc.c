/**
 * \class test_adc
 * \brief Analog-to-digital converter(ADC) tests
 * \details This class is used to test ADC capabilities of this API
 * \author Prince Balabis
 * \version 0.1
 * \date 17 sep 2014
 */

#include "global_definitions.h"
#include "unity.h"
#include "test_adc.h"

/*
 * Checking that ADC channel 0 is enabled
 */
void test_adc_channel_enabled(void) {
	// ADC Channel Status Register
	uint32_t * const p_ADC_CHSR = (uint32_t *) 0x400C0018u;

	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Check if that channel is disabled
	TEST_ASSERT_FALSE(ADC_CHSR & (0x1u << channel));

	// Enable channel
	adc_enable_channel(channel);

	// Check if that channel is enabled
	TEST_ASSERT_TRUE(ADC_CHSR & (0x1u << channel));

}

/*
 * Checking that ADC channel 0 is disabled, requires "test_adc_channel_enabled"
 * to pass it's test
 */
void test_adc_channel_disabled(void) {

	///<ADC Channel Status Register
	uint32_t * const p_ADC_CHSR = (uint32_t *) 0x400C0018u;

	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Enable channel
	adc_enable_channel(channel);

	// Check if that channel is enabled
	TEST_ASSERT_TRUE(ADC_CHSR & (0x1u << channel));

	// Disable channel
	adc_disable_channel(channel);

	// Check if that channel is disabled
	TEST_ASSERT_FALSE(ADC_CHSR & (0x1u << channel));

}


/*
 * Test channel status function, requires "test_adc_channel_enabled" and
 * "test_adc_channel_disabled" to pass it's tests
 */
void test_adc_channel_status(void) {

	// ADC Channel Status Register
	uint32_t * const p_ADC_CHSR = (uint32_t *) 0x400C0018u;

	// Chosen channel to test
	uint32_t channel = ADC_CHANNEL_0;

	// Enable channel
	adc_enable_channel(channel);

	// Check if registry value and function has the same value
	TEST_ASSERT_TRUE(
			(ADC_CHSR & (0x1u << channel)) & adc_get_channel_status(channel));

	// Disable channel
	adc_disable_channel(channel);

	// Check if registry value and function has the same value
	TEST_ASSERT_FALSE(
			(ADC_CHSR & (0x1u << channel)) & adc_get_channel_status(channel));
}

/*
 * Test 12 bit setting
 */
void test_adc_12bit(void) {

	pmc_start_peripheral_clock(ID_ADC);

	// Mode Register
	uint32_t * const p_ADC_MR = (uint32_t *) 0x400C0004u;

	// 12 Bit should be enabled as default
	TEST_ASSERT_FALSE(ADC_MR | (0x0u << 4));

	// Set ADC to 12 bit
	adc_set_resolution(12);

	// Test if ADC is still set as 12 bit
	TEST_ASSERT_FALSE(ADC_MR | (0x0u << 4));
}

/*
 * Test 10 bit setting
 */
void test_adc_10bit(void) {

	pmc_start_peripheral_clock(ID_ADC);

	// Mode Register
	uint32_t * const p_ADC_MR = (uint32_t *) 0x400C0004u;

	// Set ADC to 12 bit
	adc_set_resolution(12);

	// Test if ADC is not set as 10 bit
	TEST_ASSERT_TRUE(ADC_MR ^ (0x1u << 4));

	// Set ADC to 10 bit
	adc_set_resolution(10);

	// Test if ADC is set as 10 bit
	TEST_ASSERT_FALSE(ADC_MR ^ (0x1u << 4));
}

/*
 * Test 12 bit ADC reading on a single channel
 */
void test_adc_12bit_reading_single_channel(void) {

	// Set ADC to 12 bit
	adc_set_resolution(12);

	// Chosen channel to test
	uint8_t channel = ADC_CHANNEL_0;

	// Enable specific channel
	adc_enable_channel(channel);

	// Read ADC-channel
	uint16_t data;
	data = adc_read_channel(channel);

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
	for (int i = 0; i < 10000000; i++)
		;
}

/*
 * Test 10 bit ADC reading on a single channel
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
	for (int i = 0; i < 10000000; i++)
		;

}
