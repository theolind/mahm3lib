/*
 * Timer Counter (TC) unit tests
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 20 Oktober 2014
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/delay.h"
#include "test/test_tc.h"

// TODO: Why does the test fail if timerclk1 (0) is used?
void test_tc_conf_channel(void) {
	const tc_channel_settings_t tc_settings_tc0 = {
		.wave = 0,
		.tcclks = 1
	};

	const tc_channel_settings_t tc_settings_tc1 = {
		.wave = 0,
		.tcclks = 2
	};
	const tc_channel_settings_t tc_settings_tc2 = {
		.wave = 0,
		.tcclks = 3
	};
	pmc_enable_peripheral_clock(ID_TC2);
	pmc_enable_peripheral_clock(ID_TC4);
	pmc_enable_peripheral_clock(ID_TC6);

	tc_conf_channel(&tc_settings_tc0, TC0, TC_CHANNEL_2);
	tc_conf_channel(&tc_settings_tc1, TC1, TC_CHANNEL_1);
	tc_conf_channel(&tc_settings_tc2, TC2, TC_CHANNEL_0);

	TEST_ASSERT_TRUE(TC0->TC_CHANNEL[TC_CHANNEL_2].TC_CMR);
	TEST_ASSERT_TRUE(TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CMR);
	TEST_ASSERT_TRUE(TC2->TC_CHANNEL[TC_CHANNEL_0].TC_CMR);
}

void test_tc_conf_block(void) {

}

void test_tc_enable_clock(void) {
	tc_enable_clock(TC0, TC_CHANNEL_2);
	tc_enable_clock(TC1, TC_CHANNEL_1);
	tc_enable_clock(TC2, TC_CHANNEL_0);

	TEST_ASSERT_TRUE( (TC0->TC_CHANNEL[TC_CHANNEL_2].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_TRUE( (TC1->TC_CHANNEL[TC_CHANNEL_1].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_TRUE( (TC2->TC_CHANNEL[TC_CHANNEL_0].TC_SR) & TC_SR_CLKSTA_ENABLED );
}

void test_tc_disable_clock(void) {
	tc_disable_clock(TC0, TC_CHANNEL_2);
	tc_disable_clock(TC1, TC_CHANNEL_1);
	tc_disable_clock(TC2, TC_CHANNEL_0);

	TEST_ASSERT_FALSE( (TC0->TC_CHANNEL[TC_CHANNEL_2].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_FALSE( (TC1->TC_CHANNEL[TC_CHANNEL_1].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_FALSE( (TC2->TC_CHANNEL[TC_CHANNEL_0].TC_SR) & TC_SR_CLKSTA_ENABLED );
}

void test_tc_start_clock(void) {
	uint32_t counter_tc0 = 0, counter_tc1 = 0, counter_tc2 = 0;

	tc_enable_clock(TC0, TC_CHANNEL_2);
	tc_enable_clock(TC1, TC_CHANNEL_1);
	tc_enable_clock(TC2, TC_CHANNEL_0);

	tc_start_clock(TC0, TC_CHANNEL_2);
	tc_start_clock(TC1, TC_CHANNEL_1);
	tc_start_clock(TC2, TC_CHANNEL_0);
	delay_micros(100);

	counter_tc0 = TC0->TC_CHANNEL[TC_CHANNEL_2].TC_CV;
	counter_tc1 = TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter_tc2 = TC2->TC_CHANNEL[TC_CHANNEL_0].TC_CV;
	TEST_ASSERT_TRUE(counter_tc0 > 0);
	TEST_ASSERT_TRUE(counter_tc1 > 0);
	TEST_ASSERT_TRUE(counter_tc2 > 0);
}

void test_tc_counter_stopped(void) {
	uint32_t counter_tc0 = 0, counter_tc1 = 0, counter_tc2 = 0
			, counter_ref_tc0 = 0, counter_ref_tc1 = 0, counter_ref_tc2 = 0;
	counter_tc0 = TC0->TC_CHANNEL[TC_CHANNEL_2].TC_CV;
	counter_tc1 = TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter_tc2 = TC2->TC_CHANNEL[TC_CHANNEL_0].TC_CV;

	TEST_ASSERT_TRUE(counter_tc0 > counter_ref_tc0);
	TEST_ASSERT_TRUE(counter_tc1 > counter_ref_tc1);
	TEST_ASSERT_TRUE(counter_tc2 > counter_ref_tc2);

	tc_disable_clock(TC0, TC_CHANNEL_2);
	tc_disable_clock(TC1, TC_CHANNEL_1);
	tc_disable_clock(TC2, TC_CHANNEL_0);

	delay_micros(100);
	counter_tc0 = TC0->TC_CHANNEL[TC_CHANNEL_2].TC_CV;
	counter_tc1 = TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter_tc2 = TC2->TC_CHANNEL[TC_CHANNEL_0].TC_CV;

	counter_ref_tc0 = counter_tc0;
	counter_ref_tc1 = counter_tc1;
	counter_ref_tc2 = counter_tc2;

	delay_micros(100);
	counter_tc0 = TC0->TC_CHANNEL[TC_CHANNEL_2].TC_CV;
	counter_tc1 = TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter_tc2 = TC2->TC_CHANNEL[TC_CHANNEL_0].TC_CV;

	TEST_ASSERT_TRUE(counter_tc0 == counter_ref_tc0);
	TEST_ASSERT_TRUE(counter_tc1 == counter_ref_tc1);
	TEST_ASSERT_TRUE(counter_tc2 == counter_ref_tc2);
}

void test_tc_read_counter_value(void) {
	uint32_t counter_tc0 = 0, counter_tc1 = 0, counter_tc2 = 0
			, counter_ref_tc0 = 0, counter_ref_tc1 = 0, counter_ref_tc2 = 0;
	tc_enable_clock(TC0, TC_CHANNEL_2);
	tc_enable_clock(TC1, TC_CHANNEL_1);
	tc_enable_clock(TC2, TC_CHANNEL_0);

	tc_start_clock(TC0, TC_CHANNEL_2);
	tc_start_clock(TC1, TC_CHANNEL_1);
	tc_start_clock(TC2, TC_CHANNEL_0);

	counter_tc0 = tc_read_counter_value(TC0, TC_CHANNEL_2);
	counter_tc1 = tc_read_counter_value(TC1, TC_CHANNEL_1);
	counter_tc2 = tc_read_counter_value(TC2, TC_CHANNEL_0);

	TEST_ASSERT_TRUE(counter_tc0 > counter_ref_tc0);
	TEST_ASSERT_TRUE(counter_tc1 > counter_ref_tc1);
	TEST_ASSERT_TRUE(counter_tc2 > counter_ref_tc2);

	counter_ref_tc0 = counter_tc0;
	counter_ref_tc1 = counter_tc1;
	counter_ref_tc2 = counter_tc2;

	//Must use a quite long delay due to TC2 running on a quite slow clock
	delay_micros(200000);
	counter_tc0 = tc_read_counter_value(TC0, TC_CHANNEL_2);
	counter_tc1 = tc_read_counter_value(TC1, TC_CHANNEL_1);
	counter_tc2 = tc_read_counter_value(TC2, TC_CHANNEL_0);

	TEST_ASSERT_TRUE(counter_tc0 > counter_ref_tc0);
	TEST_ASSERT_TRUE(counter_tc1 > counter_ref_tc1);
	TEST_ASSERT_TRUE(counter_tc2 > counter_ref_tc2);
}
