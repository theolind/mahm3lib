/*
 * Timer Counter (TC) unit tests
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 17 Oktober 2014
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/delay.h"
#include "test/test_tc.h"

void test_tc_conf_channel(void) {
	const tc_channel_settings_t tc_settings = {
		.wave = 0,
		.tcclks = 1
	};

	pmc_enable_peripheral_clock(ID_TC1);

	tc_conf_channel(&tc_settings, TC1, 0);

	TEST_ASSERT_TRUE(TC1->TC_CHANNEL[0].TC_CMR);
}

void test_tc_conf_block(void) {

}

void test_tc_enable_clock(void) {
	tc_enable_clock(TC1, TC_CHANNEL_0);

	TEST_ASSERT_TRUE( (TC1->TC_CHANNEL[0].TC_SR) & TC_SR_CLKSTA_ENABLED );
}

void test_tc_disable_clock(void) {
	tc_disable_clock(TC1, TC_CHANNEL_0);
	TEST_ASSERT_FALSE( (TC1->TC_CHANNEL[0].TC_SR) & TC_SR_CLKSTA_ENABLED );
}

void test_tc_start_clock(void) {
	uint32_t counter = 0;
	TEST_ASSERT_FALSE(counter);
	tc_enable_clock(TC1, TC_CHANNEL_0);
	tc_start_clock(TC1, TC_CHANNEL_0);
	delay_micros(100);
	counter = TC1->TC_CHANNEL[0].TC_CV;
	TEST_ASSERT_TRUE(counter > 0);
}

void test_tc_stop_clock(void) {
	uint32_t counter = 0, counter_ref = 0;
	counter = TC1->TC_CHANNEL[0].TC_CV;
	TEST_ASSERT_TRUE(counter > counter_ref);
	tc_stop_clock(TC1, TC_CHANNEL_0);
	counter = TC1->TC_CHANNEL[0].TC_CV;
	counter_ref = counter;
	delay_micros(100);
	counter = TC1->TC_CHANNEL[0].TC_CV;
}

void test_tc_read_counter_value(void) {
	uint32_t counter = 0, counter_ref = 0;
	counter = tc_read_counter_value(TC1, TC_CHANNEL_0);
	TEST_ASSERT_TRUE(counter > counter_ref);
	counter_ref = counter;
	delay_micros(100);
	counter = tc_read_counter_value(TC1, TC_CHANNEL_0);
	TEST_ASSERT_TRUE(counter > counter_ref);
}
