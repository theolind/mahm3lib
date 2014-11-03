/*
 * due_pwm.h
 * Pulse Width Modulation on Arduino Due
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 29 October 2014
 */

#include "due_pwm.h"

void due_pwm_init_channel(uint32_t channel) {

	// Channel 6 - 9 is actual hardware (PWM) and has ID's over 21
	if (channel >= 6 && channel <= 9){
		pwm_channel_setting_t channel_settings = {
		.channel = channel,
		.alignment = PWM_CHANNEL_ALIGN_LEFT,
		.polarity = PWM_CHANNEL_POLARITY_LOW,
		.duty_cycle = 0,
		.use_CLKx = 0,
		.frequency = 25000,
		.clock_ID = PWM_CLK_ID_CLKA
		};

		pwm_init_channel(channel_settings);
	}
	// The rest is PWM created with timers (TC)
	else {

	}
}

void due_pwm_set_duty_cycle(uint32_t channel, uint32_t duty) {
	if (channel >= 6 && channel <= 9){
		pwm_set_channel_duty_cycle(channel, duty);
	}
	else {

	}
}

void due_pwm_enable_channel(uint32_t channel) {
	if (channel >= 6 && channel <= 9){
		pwm_enable_channel(channel);
	}
	else {

	}
}

void due_pwm_disable_channel(uint32_t channel) {
	if (channel >= 6 && channel <= 9){
		pwm_disable_channel(channel);
	}
	else {

	}
}
