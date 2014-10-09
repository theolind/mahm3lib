/*
 * PWM unit tests
 *
 * Author:	Saeed Ghasemi
 *
 * Date:	01 October 2014
 */

#include "unity/unity.h"
#include "test_pwm.h"
#include "sam3x8e/pwm.h"
#include "sam3x8e/pmc.h"


/*
 * Checking that an PWM channel is enabled.
 */
void test_pwm_channel_enabled(void) {
	pmc_enable_peripheral_clock(ID_PWM);
	pwm_reset_peripheral();
	pwm_channel_enable(PWM_CHANNEL_3);
	TEST_ASSERT_EQUAL_HEX32(0x00000008, 0x000000FF & PWM->PWM_SR);
	pwm_channel_enable(PWM_CHANNEL_4);
	//TEST_ASSERT_EQUAL_HEX32(0x00000018, 0x000000FF & PWM->PWM_SR);
}

void test_pwm_channel_disabled(void) {
	pwm_reset_peripheral();
	pwm_channel_enable(PWM_CHANNEL_3);
	TEST_ASSERT_BITS_HIGH((1<<PWM_CHANNEL_3), 0x000000FF & PWM->PWM_SR);
	pwm_channel_disable(PWM_CHANNEL_3);
	TEST_ASSERT_BITS_LOW((1<<PWM_CHANNEL_3), 0x000000FF & PWM->PWM_SR);
}

void test_pwm_channel_prescaler(void) {
	pwm_reset_peripheral();
	pwm_set_channel_prescaler(PWM_CHANNEL_3, PWM_PRES_MCK_DIV_1024);
	TEST_ASSERT_EQUAL_UINT32(PWM_PRES_MCK_DIV_1024,
			get_section_in_register(PWM->PWM_CMR3,PWM_CMRx_CPRE_MASK));
	pwm_set_channel_prescaler(PWM_CHANNEL_3, PWM_PRES_MCK_DIV_32);
	TEST_ASSERT_EQUAL_UINT32(PWM_PRES_MCK_DIV_32,
			get_section_in_register(PWM->PWM_CMR3,PWM_CMRx_CPRE_MASK));
}
void test_pwm_channel_duty_cycle(void) {
	pwm_reset_peripheral();
	pwm_set_channel_duty_cycle(PWM_CHANNEL_3, 50);
	TEST_ASSERT_EQUAL_UINT32(50,
			get_section_in_register(PWM->PWM_CDTY3,PWM_CDTYx_CDTY_MASK));
	// change duty cycle when channel is enabled
	pwm_channel_enable(PWM_CHANNEL_3);
	pwm_set_channel_duty_cycle(PWM_CHANNEL_3, 50);
	TEST_ASSERT_EQUAL_UINT32(50,
			get_section_in_register(PWM->PWM_CDTYUPD3, PWM_CDTYUPDx_CDTYUPD_MASK));
}
void test_pwm_channel_polarity(void) {
	pwm_reset_peripheral();

}
void test_pwm_channel_alignment(void) {
	pwm_reset_peripheral();

}

