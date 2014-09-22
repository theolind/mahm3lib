/**
 * \class test_adc
 * \brief Analog-to-digital converter(ADC) tests
 * \details This class is used to test ADC capabilities of this API
 * \author Prince Balabis
 * \version 0.1
 * \date 17 sep 2014
 */


#include "unity.h"
#include "test_adc.h"


/*
 * Checking that ADC channel 0 is enabled
 */
void test_adc_channel_enabled(void) {

	///<ADC Channel Status Register
    uint32_t *const p_ADC_CHSR      = (uint32_t *) 0x400C0018u;

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
 * Checking that ADC channel 0 is disabled
 */
void test_adc_channel_disabled(void) {

	///<ADC Channel Status Register
    uint32_t *const p_ADC_CHSR      = (uint32_t *) 0x400C0018u;

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
 * Test 12 bit setting
 */
void test_adc_12bit(void) {

	pmc_start_peripheral_clock(PMC_PERIPHERAL_ADC);

	///< Mode Register
    uint32_t *const p_ADC_MR        = (uint32_t *) 0x400C0004u;

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

	pmc_start_peripheral_clock(PMC_PERIPHERAL_ADC);

	///< Mode Register
    uint32_t *const p_ADC_MR        = (uint32_t *) 0x400C0004u;

	// Set ADC to 12 bit
	adc_set_resolution(12);

	// Test if ADC is not set as 10 bit
	TEST_ASSERT_TRUE(ADC_MR ^ (0x1u << 4));

	// Set ADC to 10 bit
	adc_set_resolution(10);

	// Test if ADC is set as 10 bit
	TEST_ASSERT_FALSE(ADC_MR ^ (0x1u << 4));
}

