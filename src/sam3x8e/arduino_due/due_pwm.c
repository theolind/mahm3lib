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
	if (channel >= PWM9 && channel <= PWM6){
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
		// 1015811, 0xF8003
		tc_channel_settings_t tc_settings = {
			.wave = 1,
			.tcclks = 3,
			.wavsel = 0,
			.acpa = 3,
			.acpc = 3
		};

		tc_conf_channel(&tc_settings, TC2, TC_CHANNEL_0);
		tc_write_reg_a(TC2, TC_CHANNEL_0, 16383);
		tc_write_reg_c(TC2, TC_CHANNEL_0, 49149);
	}
}

void due_pwm_set_duty_cycle(uint32_t channel, uint32_t duty) {
	if (channel >= PWM9 && channel <= PWM6){
		pwm_set_channel_duty_cycle(channel, duty);
	}
	else {

	}
}

void due_pwm_enable_channel(uint32_t channel) {
	if (channel >= PWM9 && channel <= PWM6){
		pwm_enable_channel(channel);
	}
	else {
		tc_enable_clock(TC2, 0);
	}
}

void due_pwm_disable_channel(uint32_t channel) {
	if (channel >= PWM9 && channel <= PWM6){
		pwm_disable_channel(channel);
	}
	else {
		tc_disable_clock(TC2, 0);
	}
}
