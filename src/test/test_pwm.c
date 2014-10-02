/*
 * PWM unit tests
 *
 * Author:	Saeed Ghasemi
 *
 * Date:	01 October 2014
 */

#include "unity/unity.h"
#include "test_pwm.h"


/*
 * Checking that an ADC channel is enabled.
 */
void test_pwm_channel_enabled(void) {
	pwm_reset();
	pwm_channel_enable(PWM_CHANNEL_3_MASK);
	TEST_ASSERT_BITS_HIGH(PWM_CHANNEL_3_MASK, PWM_SR);
}

void test_pwm_channel_disabled(void){
	pwm_reset();
	pwm_channel_disable(PWM_CHANNEL_3_MASK);
	TEST_ASSERT_BITS_LOW(PWM_CHANNEL_3_MASK, PWM_SR);
}
