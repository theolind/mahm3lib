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
	(tc->TC_CCR + channel) = TC_CCR_CLKEN;
}
