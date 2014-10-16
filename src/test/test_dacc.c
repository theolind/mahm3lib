/*
 * DACC unit tests
 *
 * Author:	Mathias Beckius
 *
 * Date:	29 September 2014
 */

#include "test/test_dacc.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/dacc.h"
#include "unity/unity.h"

static void init_dacc(void) {
	const dacc_settings_t dacc_settings = {
		.speed_mode = 0,
		.refresh = 1,
		.startup_time = 0,
		.word_transfer = 0
	};
	// Enable Peripheral clock for DACC
	pmc_enable_peripheral_clock(ID_DACC);
	// initialize the DACC
	dacc_init(&dacc_settings);
}

/*
 * Tests if channel 0 is disabled, which it should be if no one has
 * been tinkering with it.
 * Checking value by direct register operation and by using the API.
 */
void test_dacc_channel_0_disabled1(void) {
	init_dacc();
	TEST_ASSERT_FALSE(DACC->DACC_CHSR & (0x1u << DACC_CHANNEL_0));
	TEST_ASSERT_FALSE(dacc_channel_enabled(DACC_CHANNEL_0));
}

/*
 * Tests if channel 1 is disabled, which it should be if no one has
 * been tinkering with it.
 * Checking value by direct register operation and by using the API.
 */
void test_dacc_channel_1_disabled1(void) {
	TEST_ASSERT_FALSE(DACC->DACC_CHSR & (0x1u << DACC_CHANNEL_1));
	TEST_ASSERT_FALSE(dacc_channel_enabled(DACC_CHANNEL_1));
}

/*
 * Enable channel 0.
 * Verification is done by direct register operation.
 */
void test_dacc_enable_channel_0(void) {
	dacc_enable_channel(DACC_CHANNEL_0);
	TEST_ASSERT_TRUE(DACC->DACC_CHSR & (0x1u << DACC_CHANNEL_0));
}

/*
 * Enable channel 1.
 * Verification is done by direct register operation.
 */
void test_dacc_enable_channel_1(void) {
	dacc_enable_channel(DACC_CHANNEL_1);
	TEST_ASSERT_TRUE(DACC->DACC_CHSR & (0x1u << DACC_CHANNEL_1));
}

/*
 * Disable channel 0.
 * Verification is done by direct register operation.
 */
void test_dacc_disable_channel_0(void) {
	dacc_disable_channel(DACC_CHANNEL_0);
	TEST_ASSERT_FALSE(DACC->DACC_CHSR & (0x1u << DACC_CHANNEL_0));
}

/*
 * Disable channel 1.
 * Verification is done by direct register operation.
 */
void test_dacc_disable_channel_1(void) {
	dacc_disable_channel(DACC_CHANNEL_1);
	TEST_ASSERT_FALSE(DACC->DACC_CHSR & (0x1u << DACC_CHANNEL_1));
}

/*
 * Tests if channel 0 is disabled, once again.
 * Verification is done by using API.
 */
void test_dacc_channel_0_disabled2(void) {
	TEST_ASSERT_FALSE(dacc_channel_enabled(DACC_CHANNEL_0));
}

/*
 * Tests if channel 1 is disabled, once again.
 * Verification is done by using API.
 */
void test_dacc_channel_1_disabled2(void) {
	TEST_ASSERT_FALSE(dacc_channel_enabled(DACC_CHANNEL_1));
	// disable Peripheral clock for DACC
	pmc_disable_peripheral_clock(ID_DACC);
}
