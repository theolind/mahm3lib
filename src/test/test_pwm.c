/*
 * PWM unit tests
 *
 * Author:	Saeed Ghasemi
 *
 * Date:	01 October 2014
 */

#include "unity/unity.h"
#include "test_pwm.h"
#include "pwm.c"


/*
 * Checking that an ADC channel is enabled.
 */
void test_pwm_channel_enabled(void) {
	pwm_reset();
	pwm_channel_enable(PWM_CHANNEL_3_MASK);
	TEST_ASSERT_BITS_HIGH(PWM_CHANNEL_3_MASK, PWM_ENA);
}

void test_pwm_channel_enabled(void) {
	pwm_reset();
	pwm_channel_enable(PWM_CHANNEL_3_MASK);
	TEST_ASSERT_BITS_HIGH(PWM_CHANNEL_3_MASK, PWM_ENA);
}
