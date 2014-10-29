/*
 * due_pwm.h
 * Pulse Width Modulation on Arduino Due
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 29 October 2014
 */

#include "due_pwm.h"

void init_channel(uint32_t channel) {

	//TODO: Can't use 1-13 as channels. Need to use the ones defined in PWM etc.
	//TODO: Add arduino PWM in pin mapping
	// Channel 6 - 9 is actual hardware (PWM)
	if (channel >= 6 && channel <= 9){
		// 1000 Hz
		// low
		// left
		// etc..
	}
	// The rest is PWM created with timers (TC)
	else {

	}
}

void set_duty_cycle(uint32_t channel, uint32_t duty) {
	if (channel >= 6 && channel <= 9){

	}
	else {

	}
}

void enable_channel(uint32_t channel) {
	if (channel >= 6 && channel <= 9){

	}
	else {

	}
}

void disable_channel(uint32_t channel) {
	if (channel >= 6 && channel <= 9){

	}
	else {

	}
}
