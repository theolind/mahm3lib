/**
 * @file pwm.c
 * @brief Pulse Width Modulation (PWM)
 * @details An API for controlling the PWM peripheral inside a SAM3X8E MCU.
 * This peripheral is an embedded macrocell within the MCU and all of its 44
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * This API implements all 8 independent channels and their change of polarity,
 * alignment, PWM frequency and handles the pin multiplexing for all 16 outputs
 * of the peripheral. The API does not stop any clock once it has started them.
 * @author Saeed Ghasemi
 * @date 28 sep 2014
 * @pre The API handles all of its dependencies on other peripherals
 * internally and will start other clocks in order to properly operate.
 * @bug Manually tested all functions to comply with all demands.
 * The only problem is that the register set defined below is not working when
 * implemented. The register mapping currently working is non conventional.
 */

#include "sam3x8e/bitwise_operations.h"
#include "sam3x8e/pwm.h"

///\cond
/*
 * Register Channel distance
 * See datasheet page 1019
 */
#define ch_dis		0x20
///\endcond


/*
 * This initialization function also takes in parameters for the two clocks
 * called CLK_A and CLK_B.
 * Starting these clocks consume more power. It is preferred to use the channel
 * prescalers if possible. All of the 8 channels can use the same clock once it
 * has been initialized. If these clocks are used, the channels prescalers must
 * be set to select the output of theses clocks.
 */
uint8_t pwm_init_peripheral(struct pwm_clk_setting clk_settings) {
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
uint8_t pwm_init_channel(struct pwm_channel_setting settings) {
	uint8_t reenable = 0;
	// Disable the channel and remember the initial state of it
	if (pwm_channel_status(settings.channel) == 1) {
		reenable = 1;
		pwm_channel_disable(settings.channel);
	}
	if (settings.use_CLKx == 1) {
		if (pwm_set_channel_frequency(settings.channel,
				settings.frequency) == 0) {
			pwm_set_clkx_frequency(settings.channel, settings.frequency,
					settings.clock_ID);
		}
	} else if (settings.use_CLKx == 0) {
		pwm_set_channel_frequency(settings.channel, settings.frequency);
	}
	pwm_channel_disable(settings.channel);
	pwm_set_channel_alignment(settings.channel, settings.alignment);
	pwm_set_channel_polarity(settings.channel, settings.polarity);
	pwm_set_channel_duty_cycle(settings.channel, settings.duty_cycle);
	if (reenable == 1) {
		pwm_channel_enable(settings.channel);
	}
	return 1;
}
/*
 * This function will enable the selected channel, identified with predefined
 * values, like: PWM_CHANNEL_x_MASK
 *
 * Alternatively use PWM_CHANNEL_ALL_MASK to enable all channel at once.
 */
uint8_t pwm_channel_enable(uint32_t channel) {
	set_section_in_register(&PWM->PWM_ENA, (1u<<channel), 1);
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
uint8_t pwm_channel_disable(uint32_t channel) {
	if (pwm_channel_status(channel)) {
		set_section_in_register(&PWM->PWM_DIS, (1u<<channel), 1);
		while (pwm_channel_status(channel)) {
		}
	}
	return (uint8_t) 0x01;
}
/*
 * This function will read the status of a single channel.
 */
uint8_t pwm_channel_status(uint32_t channel) {
	return get_bit(&PWM->PWM_SR, (uint8_t)channel);
}
/*
 * Set the channel polarity.
 * This can reverse the duty cycle. Important when using the PWMLx pins.
 */
uint8_t pwm_set_channel_polarity(uint32_t channel, uint32_t pwm_polarity) {
	switch (channel) {
	case PWM_CHANNEL_0:
		set_section_in_register(&PWM->PWM_CMR0, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_1:
		set_section_in_register(&PWM->PWM_CMR1, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_2:
		set_section_in_register(&PWM->PWM_CMR2, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_3:
		set_section_in_register(&PWM->PWM_CMR3, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_4:
		set_section_in_register(&PWM->PWM_CMR4, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_5:
		set_section_in_register(&PWM->PWM_CMR5, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_6:
		set_section_in_register(&PWM->PWM_CMR6, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_7:
		set_section_in_register(&PWM->PWM_CMR7, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	default:
		return 0;
		break;
	}
	return 1;
}
/*
 * Set the channel alignment
 */
uint8_t pwm_set_channel_alignment(uint32_t channel, uint32_t pwm_alignment) {
	switch (channel) {
	case PWM_CHANNEL_0:
		set_section_in_register(&PWM->PWM_CMR0, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_1:
		set_section_in_register(&PWM->PWM_CMR1, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_2:
		set_section_in_register(&PWM->PWM_CMR2, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_3:
		set_section_in_register(&PWM->PWM_CMR3, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_4:
		set_section_in_register(&PWM->PWM_CMR4, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_5:
		set_section_in_register(&PWM->PWM_CMR5, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_6:
		set_section_in_register(&PWM->PWM_CMR6, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_7:
		set_section_in_register(&PWM->PWM_CMR7, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	default:
		return 0;
		break;
	}
	return 1;
}
/*
 * Set the channel prescaler
 */
uint8_t pwm_set_channel_prescaler(uint32_t channel, uint32_t prescaler) {
	uint8_t error = 0;
	switch (channel) {
	case PWM_CHANNEL_0:
		error = set_section_in_register(&PWM->PWM_CMR0, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_1:
		error = set_section_in_register(&PWM->PWM_CMR1, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_2:
		error = set_section_in_register(&PWM->PWM_CMR2, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_3:
		error = set_section_in_register(&PWM->PWM_CMR3, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_4:
		error = set_section_in_register(&PWM->PWM_CMR4, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_5:
		error = set_section_in_register(&PWM->PWM_CMR5, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_6:
		error = set_section_in_register(&PWM->PWM_CMR6, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_7:
		error = set_section_in_register(&PWM->PWM_CMR7, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	default:
		return 0;
		break;
	}
	return error;
}
/*
 * This function will set the period value used by a given PWM channel.
 * Only set the period directly if you know what you are doing, otherwise
 * use pwm_set_channel_frequency() or pwm_set_clkx_frequency(), because they
 * will set the period for you.
 */
uint8_t pwm_set_channel_period(uint32_t channel, uint32_t period) {
	switch (channel) {
	case PWM_CHANNEL_0:
		if (pwm_channel_status(PWM_CHANNEL_0)) {
			set_section_in_register(&PWM->PWM_CPRDUPD0, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM->PWM_CPRD0, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_1:
		if (pwm_channel_status(PWM_CHANNEL_1)) {
			set_section_in_register(&PWM->PWM_CPRDUPD1, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM->PWM_CPRD1, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_2:
		if (pwm_channel_status(PWM_CHANNEL_2)) {
			set_section_in_register(&PWM->PWM_CPRDUPD2, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM->PWM_CPRD2, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_3:
		if (pwm_channel_status(PWM_CHANNEL_3)) {
			set_section_in_register(&PWM->PWM_CPRDUPD3, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM->PWM_CPRD3, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_4:
		if (pwm_channel_status(PWM_CHANNEL_4)) {
			set_section_in_register(&PWM->PWM_CPRDUPD4, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM->PWM_CPRD4, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_5:
		if (pwm_channel_status(PWM_CHANNEL_5)) {
			set_section_in_register(&PWM->PWM_CPRDUPD5, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM->PWM_CPRD5, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_6:
		if (pwm_channel_status(PWM_CHANNEL_6)) {
			set_section_in_register(&PWM->PWM_CPRDUPD6, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM->PWM_CPRD6, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_7:
		if (pwm_channel_status(PWM_CHANNEL_7)) {
			set_section_in_register(&PWM->PWM_CPRDUPD7, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM->PWM_CPRD7, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	default:
		return 0;
		break;
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
		if (pwm_channel_status(channel) == 1) {
			reenable = 1;
			pwm_channel_disable(channel);
		}
		// Implement
		pwm_set_channel_period(channel, CPRD);
		pwm_set_channel_prescaler(channel, i);
		// Reenable if nessessary
		if (reenable == 1) {
			pwm_channel_enable(channel);
		}
	}else{
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
		if (pwm_channel_status(channel) == 1) {
			reenable = 1;
			pwm_channel_disable(channel);
		}
		// Initialize the CLKx with the found settings
		pwm_set_clkx(pwm_clk_id, prescaler, divisor);
		// Set the channel prescaler to the chosen CLKx
		pwm_set_channel_prescaler(channel, pwm_channel_pres);
		if (reenable == 1) {
			pwm_channel_enable(channel);
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
	if (clock_id == PWM_CLK_ID_CLKA) {
		set_section_in_register(&PWM->PWM_CLK, PWM_CLK_PREA_MASK, prescaler);
		set_section_in_register(&PWM->PWM_CLK, PWM_CLK_DIVA_MASK, divisor);
		return 1;
	} else if (clock_id == PWM_CLK_ID_CLKB) {
		set_section_in_register(&PWM->PWM_CLK, PWM_CLK_PREB_MASK, prescaler);
		set_section_in_register(&PWM->PWM_CLK, PWM_CLK_DIVB_MASK, divisor);
		return 1;
	}
	return 0;
}
/*
 * This function reads the earlier written duty cycle to the channel.
 */
uint32_t pwm_channel_read(uint32_t channel) {
	switch (channel) {
	case PWM_CHANNEL_0:
		return get_section_in_register(&PWM->PWM_CDTY0, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_1:
		return get_section_in_register(&PWM->PWM_CDTY1, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_2:
		return get_section_in_register(&PWM->PWM_CDTY2, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_3:
		return get_section_in_register(&PWM->PWM_CDTY3, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_4:
		return get_section_in_register(&PWM->PWM_CDTY4, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_5:
		return get_section_in_register(&PWM->PWM_CDTY5, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_6:
		return get_section_in_register(&PWM->PWM_CDTY6, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_7:
		return get_section_in_register(&PWM->PWM_CDTY7, PWM_CDTYx_CDTY_MASK);
		break;
	default:
		return 0;
		break;
	}
	return 1;
}
/*
 * Writes an output to a given channel by setting the channel duty cycle.
 */
uint8_t pwm_set_channel_duty_cycle(uint32_t channel, uint32_t duty_cycle) {

	//return set_section_in_register((&PWM->PWM_CDTYUPD0)+ch_dis*channel,
	//		PWM_CDTYUPDx_CDTYUPD_MASK, duty_cycle);

	switch (channel) {
	case PWM_CHANNEL_0:
		if (pwm_channel_status(PWM_CHANNEL_0)) {
			set_section_in_register(&PWM->PWM_CDTYUPD0, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM->PWM_CDTY0, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_1:
		if (pwm_channel_status(PWM_CHANNEL_1)) {
			set_section_in_register(&PWM->PWM_CDTYUPD1, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM->PWM_CDTY1, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_2:
		if (pwm_channel_status(PWM_CHANNEL_2)) {
			set_section_in_register(&PWM->PWM_CDTYUPD2, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM->PWM_CDTY2, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_3:
		if (pwm_channel_status(PWM_CHANNEL_3)) {
			set_section_in_register(&PWM->PWM_CDTYUPD3, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM->PWM_CDTY3, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_4:
		if (pwm_channel_status(PWM_CHANNEL_4)) {
			set_section_in_register(&PWM->PWM_CDTYUPD4, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM->PWM_CDTY4, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_5:
		if (pwm_channel_status(PWM_CHANNEL_5)) {
			set_section_in_register(&PWM->PWM_CDTYUPD5, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM->PWM_CDTY5, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_6:
		if (pwm_channel_status(PWM_CHANNEL_6)) {
			set_section_in_register(&PWM->PWM_CDTYUPD6, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM->PWM_CDTY6, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_7:
		if (pwm_channel_status(PWM_CHANNEL_7)) {
			set_section_in_register(&PWM->PWM_CDTYUPD7, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM->PWM_CDTY7, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	default:
		return 0;
		break;
	}
	return 1;

}
/*
 * This channel reads the maximum allowed duty cycle for the channel.
 * This is also called channel resolution.
 */
uint32_t pwm_get_channel_period(uint32_t channel) {
	switch (channel) {
	case PWM_CHANNEL_0:
		return get_section_in_register(&PWM->PWM_CPRD0, PWM_CPRDx_CPRD_MASK);
		break;
	case PWM_CHANNEL_1:
		return get_section_in_register(&PWM->PWM_CPRD1, PWM_CPRDx_CPRD_MASK);
		break;
	case PWM_CHANNEL_2:
		return get_section_in_register(&PWM->PWM_CPRD2, PWM_CPRDx_CPRD_MASK);
		break;
	case PWM_CHANNEL_3:
		return get_section_in_register(&PWM->PWM_CPRD3, PWM_CPRDx_CPRD_MASK);
		break;
	case PWM_CHANNEL_4:
		return get_section_in_register(&PWM->PWM_CPRD4, PWM_CPRDx_CPRD_MASK);
		break;
	case PWM_CHANNEL_5:
		return get_section_in_register(&PWM->PWM_CPRD5, PWM_CPRDx_CPRD_MASK);
		break;
	case PWM_CHANNEL_6:
		return get_section_in_register(&PWM->PWM_CPRD6, PWM_CPRDx_CPRD_MASK);
		break;
	case PWM_CHANNEL_7:
		return get_section_in_register(&PWM->PWM_CPRD7, PWM_CPRDx_CPRD_MASK);
		break;
	default:
		return 0;
		break;
	}
	return 0;
}
/*
 * This function reads the alignment og the channel.
 */
uint32_t pwm_get_channel_alignment(uint32_t channel) {
	switch (channel) {
	case PWM_CHANNEL_0:
		return get_section_in_register(&PWM->PWM_CMR0, PWM_CMRx_CALG_MASK);
		break;
	case PWM_CHANNEL_1:
		return get_section_in_register(&PWM->PWM_CMR1, PWM_CMRx_CALG_MASK);
		break;
	case PWM_CHANNEL_2:
		return get_section_in_register(&PWM->PWM_CMR2, PWM_CMRx_CALG_MASK);
		break;
	case PWM_CHANNEL_3:
		return get_section_in_register(&PWM->PWM_CMR3, PWM_CMRx_CALG_MASK);
		break;
	case PWM_CHANNEL_4:
		return get_section_in_register(&PWM->PWM_CMR4, PWM_CMRx_CALG_MASK);
		break;
	case PWM_CHANNEL_5:
		return get_section_in_register(&PWM->PWM_CMR5, PWM_CMRx_CALG_MASK);
		break;
	case PWM_CHANNEL_6:
		return get_section_in_register(&PWM->PWM_CMR6, PWM_CMRx_CALG_MASK);
		break;
	case PWM_CHANNEL_7:
		return get_section_in_register(&PWM->PWM_CMR7, PWM_CMRx_CALG_MASK);
		break;
	default:
		return 0;
		break;
	}
	return 0;
}
/*
 * Turns off clock A or B.
 */
uint8_t pwm_turn_off_clkx(uint8_t clock_id) {
	if (clock_id == 0) {
		set_section_in_register(&PWM->PWM_CLK, PWM_CLK_DIVA_MASK,
		PWM_CLK_DIVx_TURNOFF);
		return 1;
	} else if (clock_id == 1) {
		set_section_in_register(&PWM->PWM_CLK, PWM_CLK_DIVB_MASK,
		PWM_CLK_DIVx_TURNOFF);
		return 1;
	}
	return 0;
}
/*
 * Resets the channel and disables it
 */
uint8_t pwm_reset_channel(){
	// works only for channel 1 right now
	pwm_channel_disable(PWM_CHANNEL_0);
	clear_register(&PWM->PWM_CMR0);
	clear_register(&PWM->PWM_CDTY0);
	clear_register(&PWM->PWM_CPRD0);
	return 1;
}
/*
 * Resets the peripheral and disables all channels
 */
uint8_t pwm_reset_peripheral() {
	clear_register(&PWM->PWM_CLK);

	clear_register(&PWM->PWM_CMR1);
	clear_register(&PWM->PWM_CMR2);
	clear_register(&PWM->PWM_CMR3);
	clear_register(&PWM->PWM_CMR4);
	clear_register(&PWM->PWM_CMR5);
	clear_register(&PWM->PWM_CMR6);
	clear_register(&PWM->PWM_CMR7);


	clear_register(&PWM->PWM_CDTY1);
	clear_register(&PWM->PWM_CDTY2);
	clear_register(&PWM->PWM_CDTY3);
	clear_register(&PWM->PWM_CDTY4);
	clear_register(&PWM->PWM_CDTY5);
	clear_register(&PWM->PWM_CDTY6);
	clear_register(&PWM->PWM_CDTY7);


	clear_register(&PWM->PWM_CPRD1);
	clear_register(&PWM->PWM_CPRD2);
	clear_register(&PWM->PWM_CPRD3);
	clear_register(&PWM->PWM_CPRD4);
	clear_register(&PWM->PWM_CPRD5);
	clear_register(&PWM->PWM_CPRD6);
	clear_register(&PWM->PWM_CPRD7);
	return 1;
}


