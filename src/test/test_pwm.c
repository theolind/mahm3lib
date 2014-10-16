/*
 * PWM unit tests
 *
 * Author:	Saeed Ghasemi
 *
 * Date:	01 October 2014
 */

#include <sam3x8e/bitwise_operations.h>
#include <sam3x8e/id.h>
#include <sam3x8e/pmc.h>
#include <sam3x8e/pwm.h>
#include <unity/unity.h>
#include <unity/unity_internals.h>
#include "test_pwm.h"

//#include "sam3x8e/id.h"

/*
 * Checking that an PWM channel is enabled.
 */
void test_pwm_channel_enabled() {
	pmc_enable_peripheral_clock(ID_PWM);
	pwm_reset_peripheral();
	pwm_channel_enable(PWM_CHANNEL_3);
	TEST_ASSERT_EQUAL_HEX32(0x00000008, PWM->PWM_SR);
	pwm_channel_enable(PWM_CHANNEL_4);
	TEST_ASSERT_EQUAL_HEX32(0x00000018, PWM->PWM_SR);
}

void test_pwm_channel_disabled() {
	pwm_reset_peripheral();
	pwm_channel_enable(PWM_CHANNEL_3);
	TEST_ASSERT_BITS_HIGH((1<<PWM_CHANNEL_3), PWM->PWM_SR);
	pwm_channel_disable(PWM_CHANNEL_3);
	TEST_ASSERT_BITS_LOW((1<<PWM_CHANNEL_3), PWM->PWM_SR);
}

void test_pwm_channel_prescaler() {
	pwm_reset_peripheral();
	pwm_set_channel_prescaler(PWM_CHANNEL_3, PWM_PRES_MCK_DIV_1024);
	TEST_ASSERT_EQUAL_UINT32(PWM_PRES_MCK_DIV_1024,
			get_section_in_register(&PWM->PWM_CMR3,PWM_CMRx_CPRE_MASK));
	TEST_ASSERT_EQUAL_UINT32(PWM_PRES_MCK_DIV_1024,
			pwm_get_channel_prescaler(PWM_CHANNEL_3)); //TODO
	pwm_set_channel_prescaler(PWM_CHANNEL_3, PWM_PRES_MCK_DIV_32);
	TEST_ASSERT_EQUAL_UINT32(PWM_PRES_MCK_DIV_32,
			get_section_in_register(&PWM->PWM_CMR3,PWM_CMRx_CPRE_MASK));
	TEST_ASSERT_EQUAL_UINT32(PWM_PRES_MCK_DIV_32,
			pwm_get_channel_prescaler(PWM_CHANNEL_3)); //TODO
}
void test_pwm_channel_duty_cycle() {
	pwm_reset_peripheral();
	pwm_set_channel_duty_cycle(PWM_CHANNEL_3, 50);
	TEST_ASSERT_EQUAL_UINT32(50,
			get_section_in_register(&PWM->PWM_CDTY3,PWM_CDTYx_CDTY_MASK));
	TEST_ASSERT_EQUAL_UINT32(50, pwm_channel_read(PWM_CHANNEL_3)); //TODO
	// change duty cycle when channel is enabled
	pwm_channel_enable(PWM_CHANNEL_3);
	pwm_set_channel_duty_cycle(PWM_CHANNEL_3, 60);
	TEST_ASSERT_EQUAL_UINT32(60,
			get_section_in_register(&PWM->PWM_CDTY3, PWM_CDTYx_CDTY_MASK));
	TEST_ASSERT_EQUAL_UINT32(60, pwm_channel_read(PWM_CHANNEL_3));	//TODO
}
void test_pwm_channel_polarity() {
	pwm_reset_peripheral();
	pwm_set_channel_polarity(PWM_CHANNEL_3, PWM_CHANNEL_POLARITY_HIGH);
	TEST_ASSERT_EQUAL_UINT32(1,
			get_section_in_register(&PWM->PWM_CMR3,PWM_CMRx_CPOL_MASK));
	pwm_set_channel_polarity(PWM_CHANNEL_3, PWM_CHANNEL_POLARITY_LOW);
	TEST_ASSERT_EQUAL_HEX32(0x0,
			get_section_in_register(&PWM->PWM_CMR3,PWM_CMRx_CPOL_MASK));
}
void test_pwm_channel_alignment() {
	pwm_reset_peripheral();
	pwm_set_channel_alignment(PWM_CHANNEL_3, PWM_CHANNEL_ALIGN_CENTER);
	TEST_ASSERT_EQUAL_HEX32(0x1,
			get_section_in_register(&PWM->PWM_CMR3,PWM_CMRx_CALG_MASK));
	TEST_ASSERT_EQUAL_HEX32(0x1, pwm_get_channel_alignment(PWM_CHANNEL_3));
	pwm_set_channel_alignment(PWM_CHANNEL_3, PWM_CHANNEL_ALIGN_LEFT);
	TEST_ASSERT_EQUAL_HEX32(0x0,
			get_section_in_register(&PWM->PWM_CMR3,PWM_CMRx_CALG_MASK));
	TEST_ASSERT_EQUAL_HEX32(0x0, pwm_get_channel_alignment(PWM_CHANNEL_3));
}

void test_pwm_channel_period() {
	pwm_reset_peripheral();
	pwm_set_channel_period(PWM_CHANNEL_3, 1000);
	TEST_ASSERT_EQUAL_UINT32(1000,
			get_section_in_register(&PWM->PWM_CPRD3,PWM_CPRDx_CPRD_MASK));
	TEST_ASSERT_EQUAL_UINT32(1000, pwm_get_channel_period(PWM_CHANNEL_3));
	pwm_set_channel_period(PWM_CHANNEL_3, 65535);
	TEST_ASSERT_EQUAL_UINT32(65535,
			get_section_in_register(&PWM->PWM_CPRD3,PWM_CPRDx_CPRD_MASK));
	TEST_ASSERT_EQUAL_UINT32(65535, pwm_get_channel_period(PWM_CHANNEL_3));
}

void test_pwm_set_clkx() {
	pwm_reset_peripheral();
	// For CLKA
	pwm_set_clkx(PWM_CLK_ID_CLKA, PWM_PRES_MCK_DIV_1024, 255);
	TEST_ASSERT_EQUAL_UINT32(PWM_PRES_MCK_DIV_1024,
			get_section_in_register(&PWM->PWM_CLK,PWM_CLK_PREA_MASK));
	TEST_ASSERT_EQUAL_UINT32(255,
			get_section_in_register(&PWM->PWM_CLK,PWM_CLK_DIVA_MASK));
	// For CLKB
	pwm_set_clkx(PWM_CLK_ID_CLKB, PWM_PRES_MCK_DIV_32, 128);
	TEST_ASSERT_EQUAL_UINT32(PWM_PRES_MCK_DIV_32,
			get_section_in_register(&PWM->PWM_CLK,PWM_CLK_PREB_MASK));
	TEST_ASSERT_EQUAL_UINT32(128,
			get_section_in_register(&PWM->PWM_CLK,PWM_CLK_DIVB_MASK));
}

void test_set_frequency(){
	pwm_reset_peripheral();
	pwm_set_channel_alignment(PWM_CHANNEL_3, PWM_CHANNEL_ALIGN_LEFT);
	pwm_set_channel_frequency(PWM_CHANNEL_3, 25000);
	TEST_ASSERT_EQUAL_UINT32(0,
					pwm_get_channel_prescaler(PWM_CHANNEL_3));
	TEST_ASSERT_EQUAL_UINT32(3360,
					pwm_get_channel_period(PWM_CHANNEL_3));

}
