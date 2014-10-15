/*
 * tc.h
 * TC - Timer Counter
 * This API is used to control the three independent hardware timers.
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 15 Oktober 2014
 */

#include "tc.h"

void tc_enable_clock(tc_reg_t *tc, uint32_t channel){
	tc_channel_reg_t *tc_channel;
	if (channel > MAX_CHANNELS){
		return;
	}
	tc_channel = tc->TC_CHANNEL + channel;

	tc_channel->TC_CCR = TC_CCR_CLKEN;
}
