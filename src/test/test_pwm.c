/*
 * PWM unit tests
 *
 * Author:	Saeed Ghasemi
 *
 * Date:	01 October 2014
 */

#include "unity/unity.h"
#include "test_pwm.h"

//TODO define registers
#define p_PWM_BASE_ADD			0x40094000U

#define PWM_SR 		*((uint32_t*)(p_PWM_BASE_ADD + 0x00C)) // PWM Status Register


/*
 * Checking that an PWM channel is enabled.
 */
void test_pwm_channel_enabled(void) {
	pwm_reset_peripheral();
	pwm_channel_enable(PWM_CHANNEL_3);
	TEST_ASSERT_BITS_HIGH(PWM_CHANNEL_3, PWM_SR);
}

void test_pwm_channel_disabled(void){
	pwm_reset_peripheral();
	pwm_channel_enable(PWM_CHANNEL_3);
	TEST_ASSERT_BITS_HIGH(PWM_CHANNEL_3, PWM_SR);
	pwm_channel_disable(PWM_CHANNEL_3);
	TEST_ASSERT_BITS_LOW(PWM_CHANNEL_3, PWM_SR);
}
