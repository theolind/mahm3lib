/*
 * tc.h
 * TC - Timer Counter
 * This API is used to control the three independent hardware timers.
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 20 Oktober 2014
 */

#include "tc.h"

// TODO: const really necessary?
// TODO: function header exceeds 80 width limit
// TODO: make macro mask function, works for now but mask is better
void tc_conf_channel(const tc_channel_settings_t* settings, tc_reg_t *tc, uint32_t channel) {
	tc->TC_CHANNEL[channel].TC_CMR |= (settings->wave << TC_CMR_WAVE_POS);
	tc->TC_CHANNEL[channel].TC_CMR |= (settings->tcclks << TC_CMR_TCCLKS_POS);
}

void tc_enable_clock(tc_reg_t *tc, uint32_t channel) {
	if (channel > MAX_CHANNELS){
		return;
	}

	tc->TC_CHANNEL[channel].TC_CCR = TC_CCR_CLKEN;
}

void tc_disable_clock(tc_reg_t *tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return;
	}
	tc->TC_CHANNEL[channel].TC_CCR = TC_CCR_CLKDIS;
}

void tc_start_clock(tc_reg_t *tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return;
	}
	tc->TC_CHANNEL[channel].TC_CCR |= TC_CCR_SWTRG;
}

uint32_t tc_read_counter_value(tc_reg_t * tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return 0;
	}
	return tc->TC_CHANNEL[channel].TC_CV;
}
