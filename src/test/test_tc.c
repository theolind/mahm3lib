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

void test_tc_conf_channel(void) {
	tc_channel_settings_t tc_settings0 = {
		.wave = 0,
		.tcclks = 0
	};

	tc_channel_settings_t tc_settings1 = {
		.wave = 0,
		.tcclks = 1
	};
	tc_channel_settings_t tc_settings2 = {
		.wave = 0,
		.tcclks = 2
	};
	tc_channel_settings_t tc_settings3 = {
		.wave = 0,
		.tcclks = 3
	};
	pmc_enable_peripheral_clock(ID_TC0);
	pmc_enable_peripheral_clock(ID_TC1);
	pmc_enable_peripheral_clock(ID_TC4);
	pmc_enable_peripheral_clock(ID_TC8);

	tc_conf_channel(&tc_settings0, TC0, TC_CHANNEL_0);
	tc_conf_channel(&tc_settings1, TC0, TC_CHANNEL_1);
	tc_conf_channel(&tc_settings2, TC1, TC_CHANNEL_1);
	tc_conf_channel(&tc_settings3, TC2, TC_CHANNEL_2);

	TEST_ASSERT_TRUE(TC0->TC_CHANNEL[TC_CHANNEL_1].TC_CMR);
	TEST_ASSERT_TRUE(TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CMR);
	TEST_ASSERT_TRUE(TC2->TC_CHANNEL[TC_CHANNEL_2].TC_CMR);
}

void test_tc_conf_block(void) {

}

void test_tc_enable_clock(void) {
	tc_enable_clock(TC0, TC_CHANNEL_0);
	tc_enable_clock(TC0, TC_CHANNEL_1);
	tc_enable_clock(TC1, TC_CHANNEL_1);
	tc_enable_clock(TC2, TC_CHANNEL_2);

	TEST_ASSERT_TRUE( (TC0->TC_CHANNEL[TC_CHANNEL_0].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_TRUE( (TC0->TC_CHANNEL[TC_CHANNEL_1].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_TRUE( (TC1->TC_CHANNEL[TC_CHANNEL_1].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_TRUE( (TC2->TC_CHANNEL[TC_CHANNEL_2].TC_SR) & TC_SR_CLKSTA_ENABLED );
}

void test_tc_disable_clock(void) {
	tc_disable_clock(TC0, TC_CHANNEL_0);
	tc_disable_clock(TC0, TC_CHANNEL_1);
	tc_disable_clock(TC1, TC_CHANNEL_1);
	tc_disable_clock(TC2, TC_CHANNEL_2);

	TEST_ASSERT_FALSE( (TC0->TC_CHANNEL[TC_CHANNEL_0].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_FALSE( (TC0->TC_CHANNEL[TC_CHANNEL_1].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_FALSE( (TC1->TC_CHANNEL[TC_CHANNEL_1].TC_SR) & TC_SR_CLKSTA_ENABLED );
	TEST_ASSERT_FALSE( (TC2->TC_CHANNEL[TC_CHANNEL_2].TC_SR) & TC_SR_CLKSTA_ENABLED );
}

void test_tc_start_clock(void) {
	uint32_t counter0 = 0, counter1 = 0, counter2 = 0, counter3 = 0;

	tc_enable_clock(TC0, TC_CHANNEL_0);
	tc_enable_clock(TC0, TC_CHANNEL_1);
	tc_enable_clock(TC1, TC_CHANNEL_1);
	tc_enable_clock(TC2, TC_CHANNEL_2);

	tc_start_clock(TC0, TC_CHANNEL_0);
	tc_start_clock(TC0, TC_CHANNEL_1);
	tc_start_clock(TC1, TC_CHANNEL_1);
	tc_start_clock(TC2, TC_CHANNEL_2);
	delay_micros(100);

	counter0 = TC0->TC_CHANNEL[TC_CHANNEL_0].TC_CV;
	counter1 = TC0->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter2 = TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter3 = TC2->TC_CHANNEL[TC_CHANNEL_2].TC_CV;
	TEST_ASSERT_TRUE(counter0 > 0);
	TEST_ASSERT_TRUE(counter1 > 0);
	TEST_ASSERT_TRUE(counter2 > 0);
	TEST_ASSERT_TRUE(counter3 > 0);
}

void test_tc_counter_stopped(void) {
	uint32_t counter0 = 0, counter1 = 0, counter2 = 0, counter3 = 0
			, counter_ref0 = 0, counter_ref1 = 0, counter_ref2 = 0,
			counter_ref3 = 0;
	counter0 = TC0->TC_CHANNEL[TC_CHANNEL_0].TC_CV;
	counter1 = TC0->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter2 = TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter3 = TC2->TC_CHANNEL[TC_CHANNEL_2].TC_CV;

	TEST_ASSERT_TRUE(counter0 > counter_ref0);
	TEST_ASSERT_TRUE(counter1 > counter_ref1);
	TEST_ASSERT_TRUE(counter2 > counter_ref2);
	TEST_ASSERT_TRUE(counter3 > counter_ref3);

	tc_disable_clock(TC0, TC_CHANNEL_0);
	tc_disable_clock(TC0, TC_CHANNEL_1);
	tc_disable_clock(TC1, TC_CHANNEL_1);
	tc_disable_clock(TC2, TC_CHANNEL_2);

	delay_micros(100);
	counter0 = TC0->TC_CHANNEL[TC_CHANNEL_0].TC_CV;
	counter1 = TC0->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter2 = TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter3 = TC2->TC_CHANNEL[TC_CHANNEL_2].TC_CV;

	counter_ref0 = counter0;
	counter_ref1 = counter1;
	counter_ref2 = counter2;
	counter_ref3 = counter3;

	delay_micros(100);
	counter0 = TC0->TC_CHANNEL[TC_CHANNEL_0].TC_CV;
	counter1 = TC0->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter2 = TC1->TC_CHANNEL[TC_CHANNEL_1].TC_CV;
	counter3 = TC2->TC_CHANNEL[TC_CHANNEL_2].TC_CV;

	TEST_ASSERT_TRUE(counter0 == counter_ref0);
	TEST_ASSERT_TRUE(counter1 == counter_ref1);
	TEST_ASSERT_TRUE(counter2 == counter_ref2);
	TEST_ASSERT_TRUE(counter3 == counter_ref3);
}

void test_tc_read_counter_value(void) {
	uint32_t counter0 = 0, counter1 = 0, counter2 = 0, counter3 = 0
			, counter_ref0 = 0, counter_ref1 = 0, counter_ref2 = 0,
			counter_ref3 = 0;
	tc_enable_clock(TC0, TC_CHANNEL_0);
	tc_enable_clock(TC0, TC_CHANNEL_1);
	tc_enable_clock(TC1, TC_CHANNEL_1);
	tc_enable_clock(TC2, TC_CHANNEL_2);

	tc_start_clock(TC0, TC_CHANNEL_0);
	tc_start_clock(TC0, TC_CHANNEL_1);
	tc_start_clock(TC1, TC_CHANNEL_1);
	tc_start_clock(TC2, TC_CHANNEL_2);

	delay_micros(100);
	counter0 = tc_read_counter_value(TC0, TC_CHANNEL_0);
	counter1 = tc_read_counter_value(TC0, TC_CHANNEL_1);
	counter2 = tc_read_counter_value(TC1, TC_CHANNEL_1);
	counter3 = tc_read_counter_value(TC2, TC_CHANNEL_2);

	TEST_ASSERT_TRUE(counter0 > counter_ref0);
	TEST_ASSERT_TRUE(counter1 > counter_ref1);
	TEST_ASSERT_TRUE(counter2 > counter_ref2);
	TEST_ASSERT_TRUE(counter3 > counter_ref3);

	counter_ref0 = counter0;
	counter_ref1 = counter1;
	counter_ref2 = counter2;
	counter_ref3 = counter3;

	delay_micros(100);
	counter0 = tc_read_counter_value(TC0, TC_CHANNEL_0);
	counter1 = tc_read_counter_value(TC0, TC_CHANNEL_1);
	counter2 = tc_read_counter_value(TC1, TC_CHANNEL_1);
	counter3 = tc_read_counter_value(TC2, TC_CHANNEL_2);

	TEST_ASSERT_TRUE(counter0 > counter_ref0);
	TEST_ASSERT_TRUE(counter1 > counter_ref1);
	TEST_ASSERT_TRUE(counter2 > counter_ref2);
	TEST_ASSERT_TRUE(counter3 > counter_ref3);
}
