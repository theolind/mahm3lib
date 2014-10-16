/*
 * tc.h
 * TC - Timer Counter
 * This API is used to control the three independent hardware timers.
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 15 Oktober 2014
 */

#include "tc.h"

void tc_conf_channel(tc_channel_settings_t* settings, tc_reg_t *tc, uint32_t channel) {
		tc->TC_CHANNEL[channel].TC_CMR |= (settings->wave << TC_CMR_WAVE_POS);
		tc->TC_CHANNEL[channel].TC_CMR |= (settings->tcclks << TC_CMR_TCCLKS_POS);
}

void tc_enable_clock(tc_reg_t *tc, uint32_t channel) {
	if (channel > MAX_CHANNELS){
		return;
	}

	// This is basiclly ASF way of doing it
//	tc_channel_reg_t *tc_channel;
//	tc_channel = tc->TC_CHANNEL + channel;
//	tc_channel->TC_CCR = TC_CCR_CLKEN;

	// Our alternative way
	tc->TC_CHANNEL[channel].TC_CCR = TC_CCR_CLKEN;
}
