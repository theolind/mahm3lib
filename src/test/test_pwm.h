/*
 * PWM unit tests
 *
 * Author:	Saeed Ghasemi
 *
 * Date:	01 October 2014
 */

#ifndef TEST_PWM_H_
#define TEST_PWM_H_

#include "sam3x8e/pwm.h"

void test_pwm_channel_enabled(void);
void test_pwm_channel_disabled(void);
void test_pwm_channel_prescaler(void);
void test_pwm_channel_duty_cycle(void);
void test_pwm_channel_polarity(void);
void test_pwm_channel_alignment(void);


#endif

