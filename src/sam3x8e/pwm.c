/*
 * pwm.c
 *
 * PWM - Pulse Width Modulation
 * An API for controlling the PWM peripheral inside a SAM3X8E MCU.
 *
 * Author:	Saeed Ghasemi
 *			Andreas Drotth
 *			Mattias Nilsson
 * Date:	02 November 2014
 */

#include "pwm.h"

///\cond
/*
 * Register Channel distance
 * See datasheet page 1019
 */
#define ch_dis		8
///\endcond

/*
 * This initialization function also takes in parameters for the two clocks
 * called CLK_A and CLK_B.
 * Starting these clocks consume more power. It is preferred to use the channel
 * prescalers if possible. All of the 8 channels can use the same clock once it
 * has been initialized. If these clocks are used, the channels prescalers must
 * be set to select the output of theses clocks.
 */
uint8_t pwm_init_peripheral(pwm_clk_setting_t clk_settings) {
	if (clk_settings.clkA_divisor != 0) {
		pwm_set_clkx(PWM_CLK_ID_CLKA, clk_settings.clkA_prescaler,
				clk_settings.clkA_divisor);
	}
	if (clk_settings.clkB_divisor != 0) {
		pwm_set_clkx(PWM_CLK_ID_CLKB, clk_settings.clkB_prescaler,
				clk_settings.clkB_divisor);
	}
	return 1;
}
/*
 * This function initializes a channel of the PWM peripheral.
 */
uint8_t pwm_init_channel(pwm_channel_setting_t settings) {
	uint8_t reenable = 0;
	// Disable the channel and remember the initial state of it
	if (pwm_channel_enabled(settings.channel) == 1) {
		reenable = 1;
		pwm_disable_channel(settings.channel);
	}
	if (settings.use_CLKx == 1) {
		if (pwm_set_channel_frequency(settings.channel, settings.frequency)
				== 0) {
			pwm_set_clkx_frequency(settings.channel, settings.frequency,
					settings.clock_ID);
		}
	} else if (settings.use_CLKx == 0) {
		pwm_set_channel_frequency(settings.channel, settings.frequency);
	}
	pwm_set_channel_alignment(settings.channel, settings.alignment);
	pwm_set_channel_polarity(settings.channel, settings.polarity);
	pwm_set_channel_duty_cycle(settings.channel, settings.duty_cycle);
	if (reenable == 1) {
		pwm_enable_channel(settings.channel);
	}
	return 1;
}
/*
 * This function will enable the selected channel, identified with predefined
 * values, like: PWM_CHANNEL_x_MASK
 *
 * Alternatively use PWM_CHANNEL_ALL_MASK to enable all channel at once.
 */
uint8_t pwm_enable_channel(uint32_t channel) {
	PWM->PWM_ENA = (0x1u << channel);
	return 1;
}

/*
 * This function will disable the selected channel, identified with predefined
 * values, like: PWM_CHANNEL_x_MASK. This function will block till the channel
 * has been disabled. Disabling the channel will be effective at the end of the
 * period as in CPRDx in PWM_CPRDx.
 *
 * Alternatively use PWM_CHANNEL_ALL_MASK to disable all channel at once.
 */
uint8_t pwm_disable_channel(uint32_t channel) {
	if (pwm_channel_enabled(channel)) {
		PWM->PWM_DIS = (0x1u << channel);
		while (pwm_channel_enabled(channel)) {
		}
	}
	return 1;
}
/*
 * This function will read the status of a single channel.
 */
uint8_t pwm_channel_enabled(uint32_t channel) {
	return (uint8_t) (((PWM->PWM_SR >> channel) & 0x01U) == 0x1U);
}

/*
 * Set the channel polarity.
 * This can reverse the duty cycle. Important when using the PWMLx pins.
 */
uint8_t pwm_set_channel_polarity(uint32_t channel, uint32_t pwm_polarity) {
	uint32_t *p_reg;
	p_reg = (&PWM->PWM_CMR0) + (ch_dis * channel);
	*p_reg = ((~PWM_CDTYUPDx_CDTYUPD_MASK) & *p_reg) |
						(pwm_polarity << 9);
	return 1;

}
/*
 * Set the channel alignment
 */
uint8_t pwm_set_channel_alignment(uint32_t channel, uint32_t pwm_alignment) {
	uint32_t *p_reg;
	p_reg = (&PWM->PWM_CMR0) + (ch_dis * channel);
	*p_reg = ((~PWM_CMRx_CALG_MASK) & *p_reg) |
							(pwm_alignment << 8);
	return 1;
}
/*
 * Set the channel prescaler
 */
uint8_t pwm_set_channel_prescaler(uint32_t channel, uint32_t prescaler) {
	uint32_t *p_reg;
	p_reg = (&PWM->PWM_CMR0) + (ch_dis * channel);
	*p_reg = ((~PWM_CMRx_CPRE_MASK) & *p_reg) |
							(prescaler << 0);
	return 1;
}
/*
 * This function will set the period value used by a given PWM channel.
 * Only set the period directly if you know what you are doing, otherwise
 * use pwm_set_channel_frequency() or pwm_set_clkx_frequency(), because they
 * will set the period for you.
 */
uint8_t pwm_set_channel_period(uint32_t channel, uint32_t period) {
	uint32_t *p_reg;
	if (pwm_channel_enabled(channel)) {
		p_reg = (&PWM->PWM_CPRDUPD0) + (ch_dis * channel);
		*p_reg = ((~PWM_CPRDUPDx_CPRDUPD_MASK) & *p_reg) |
								(period << 0);
	} else {
		p_reg = (&PWM->PWM_CPRD0) + (ch_dis * channel);
		*p_reg = ((~PWM_CPRDx_CPRD_MASK) & *p_reg) |
								(period << 0);
	}
	return 1;
}
/*
 * This function will calculate the nessessary prescaler and period to set the
 * channel frequency.
 */
uint8_t pwm_set_channel_frequency(uint32_t channel, uint32_t frequency) {
	uint32_t prescalers[11] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
	//CPRD=MCK/(f*PRE)
	uint32_t CPRD;
	uint32_t i = 0;
	uint8_t reenable = 0;
	uint32_t alignment;
	// Get alignment
	alignment = pwm_get_channel_alignment(channel);

	// check for frequency error
	if (frequency > SYS_CLK_FREQ) {
		return 0; // parameter error
	}
	// Find a prescaler based while aiming at the highest period possible
	// The period of center-alignment must be half of that of left-alignment
	// Initial calculation
	if (alignment == PWM_CHANNEL_ALIGN_CENTER) {
		CPRD = SYS_CLK_FREQ / (frequency * prescalers[i] * 2);
	} else {
		CPRD = SYS_CLK_FREQ / (frequency * prescalers[i]);
	}
	// Test the calculation and continued calculation till values found
	// or out of bounds.
	while ((CPRD > 65535) && (i < 10)) {
		i++;
		if (alignment == PWM_CHANNEL_ALIGN_CENTER) {
			CPRD = SYS_CLK_FREQ / (frequency * prescalers[i] * 2);
		} else {
			CPRD = SYS_CLK_FREQ / (frequency * prescalers[i]);
		}
	}
	// Check result and implement
	if ((CPRD < 65535) && (i < 11)) {
		// Disable the channel and remember the initial state of it
		if (pwm_channel_enabled(channel) == 1) {
			reenable = 1;
			pwm_disable_channel(channel);
		}
		// Implement
		pwm_set_channel_period(channel, CPRD);
		pwm_set_channel_prescaler(channel, i);
		// Reenable if nessessary
		if (reenable == 1) {
			pwm_enable_channel(channel);
		}
	} else {
		return 0;
	}
	return 1;
}
/*
 * This function will calculate a divisor and prescaler for a CLKx clock and
 * set the registers.
 */
uint8_t pwm_set_clkx_frequency(uint32_t channel, uint32_t frequency,
		uint32_t pwm_clk_id) {
	uint32_t prescalers[11] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
	uint8_t prescaler = 0;
	uint32_t divisor;
	uint32_t pwm_channel_pres;
	uint8_t reenable = 0;
	// check for frequency error
	if (frequency > SYS_CLK_FREQ) {
		return 0; // parameter error
	}
	// Find prescaler and divisor values for clk
	divisor = (SYS_CLK_FREQ / prescalers[prescaler]) / frequency;
	while ((divisor > 255) && (prescaler < 11)) {
		prescaler++; // Last prescaler was too low, try a higher one
		divisor = (SYS_CLK_FREQ / prescalers[prescaler]) / frequency;
	}
	// Implement result
	if (prescaler < 11) {
		// Initialize pwm_clk_id with the correct CLKx prescaler
		if (pwm_clk_id == PWM_CLK_ID_CLKA) {
			pwm_channel_pres = PWM_PRES_CLOCKA;
		} else if (pwm_clk_id == PWM_CLK_ID_CLKB) {
			pwm_channel_pres = PWM_PRES_CLOCKB;
		} else {
			return 0; // parameter error
		}
		// Disable the channel and remember the initial state of it
		if (pwm_channel_enabled(channel) == 1) {
			reenable = 1;
			pwm_disable_channel(channel);
		}
		// Initialize the CLKx with the found settings
		pwm_set_clkx(pwm_clk_id, prescaler, divisor);
		// Set the channel prescaler to the chosen CLKx
		pwm_set_channel_prescaler(channel, pwm_channel_pres);
		if (reenable == 1) {
			pwm_enable_channel(channel);
		}
		return 1; // All set (no error)
	} else {
		return 0; // parameter error
	}
}
/*
 * This function will set the indicated clock with prescaler and divisor.
 */
uint8_t pwm_set_clkx(uint32_t clock_id, uint32_t prescaler, uint32_t divisor) {
	uint32_t *p_reg;
	if (clock_id == PWM_CLK_ID_CLKA) {
		p_reg = (&PWM->PWM_CLK);
		*p_reg = ((~PWM_CLK_PREA_MASK) & *p_reg) | (prescaler << 8);
		*p_reg = ((~PWM_CLK_DIVA_MASK) & *p_reg) | (divisor << 0);
		return 1;
	} else if (clock_id == PWM_CLK_ID_CLKB) {
		p_reg = (&PWM->PWM_CLK);
		*p_reg = ((~PWM_CLK_PREB_MASK) & *p_reg) | (prescaler << 24);
		*p_reg = ((~PWM_CLK_DIVB_MASK) & *p_reg) | (divisor << 16);
		return 1;
	}
	return 0;
}
/*
 * This function reads the earlier written duty cycle to the channel.
 */
uint32_t pwm_read_channel(uint32_t channel) {
	return (*((&PWM->PWM_CDTY0) + (ch_dis *channel)) & PWM_CDTYx_CDTY_MASK);
}
/*
 * Writes an output to a given channel by setting the channel duty cycle.
 */
uint8_t pwm_set_channel_duty_cycle(uint32_t channel, uint32_t duty_cycle) {
	uint32_t *p_reg;
	if (pwm_channel_enabled(channel)) {
		p_reg = (&PWM->PWM_CDTYUPD0) + (ch_dis * channel);
		*p_reg = ((~PWM_CDTYUPDx_CDTYUPD_MASK) & *p_reg) |
				(duty_cycle << 0);
	} else {
		p_reg = (&PWM->PWM_CDTY0) + (ch_dis * channel);
		*p_reg = ((~PWM_CDTYx_CDTY_MASK) & *p_reg) |
				(duty_cycle << 0);
	}
	return 1;

}
/*
 * This channel reads the maximum allowed duty cycle for the channel.
 * This is also called channel resolution.
 */
uint32_t pwm_get_channel_period(uint32_t channel) {
	return (*((&PWM->PWM_CPRD0) + (ch_dis *channel)) & PWM_CPRDx_CPRD_MASK);
}
/*
 * This function reads the alignment of the channel.
 */
uint32_t pwm_get_channel_alignment(uint32_t channel) {
	return (*((&PWM->PWM_CMR0) + (ch_dis *channel)) & PWM_CMRx_CALG_MASK);
}
/*
 * This function reads the selected prescaler of the channel.
 */
uint32_t pwm_get_channel_prescaler(uint32_t channel) {
	return (*((&PWM->PWM_CMR0) + (ch_dis *channel)) & PWM_CMRx_CPRE_MASK);
}
/*
 * Turns off clock A or B.
 */
uint8_t pwm_turn_off_clkx(uint8_t clock_id) {
	uint32_t *p_reg;
	if (clock_id == 0) {
		p_reg = (&PWM->PWM_CLK);
		*p_reg = ((~PWM_CLK_DIVA_MASK) & *p_reg) |
				(0 << 0);
		return 1;
	} else if (clock_id == 1) {
		p_reg = (&PWM->PWM_CLK);
		*p_reg = ((~PWM_CLK_DIVB_MASK) & *p_reg) |
				(0 << 16);
		return 1;
	}
	return 0;
}
/*
 * Resets the channel and disables it
 */
uint8_t pwm_reset_channel(uint32_t channel) {
	uint32_t *p_reg;
	pwm_disable_channel(channel);
	p_reg = (&PWM->PWM_CMR0) + (ch_dis * channel);
	*p_reg = ((~0xFFFFFFFFU) & *p_reg) |
			(0 << 0);
	p_reg = (&PWM->PWM_CDTY0) + (ch_dis * channel);
	*p_reg = ((~0xFFFFFFFFU) & *p_reg) |
			(0 << 0);
	p_reg = (&PWM->PWM_CDTYUPD0) + (ch_dis * channel);
	*p_reg = ((~0xFFFFFFFFU) & *p_reg) |
			(0 << 0);
	p_reg = (&PWM->PWM_CPRD0) + (ch_dis * channel);
	*p_reg = ((~0xFFFFFFFFU) & *p_reg) |
			(0 << 0);
	p_reg = (&PWM->PWM_CPRDUPD0) + (ch_dis * channel);
	*p_reg = ((~0xFFFFFFFFU) & *p_reg) |
			(0 << 0);
	p_reg = (&PWM->PWM_DT0) + (ch_dis * channel);
	*p_reg = ((~0xFFFFFFFFU) & *p_reg) |
			(0 << 0);
	p_reg = (&PWM->PWM_DTUPD0) + (ch_dis * channel);
	*p_reg = ((~0xFFFFFFFFU) & *p_reg) |
			(0 << 0);
	return 1;
}
/*
 * Disables and resets all channels and the peripheral
 */
uint8_t pwm_reset_peripheral() {
	uint32_t *p_reg;
	p_reg = (&PWM->PWM_CLK);
	*p_reg = ((~0xFFFFFFFFU) & *p_reg) |
					(0 << 0);
	for (uint32_t channel = 0; channel < 8; channel++) {
		pwm_reset_channel(channel);
	}
	return 1;
}
