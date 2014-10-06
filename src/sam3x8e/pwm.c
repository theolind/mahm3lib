/**
 * @file pwm.c
 * @anchor <pwm>
 * @brief Pulse Width Modulation (PWM)
 * @details {This class is used to output a pulse width modulated waveform
 * using the PWM peripheral on the MCU.
 * This peripheral is an embedded macrocell within the MCU and all of its 44
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * This API implements all 8 independent channels and their change of polarity,
 * alignment, PWM frequency and handles the pin multiplexing for all 16 outputs
 * of the peripheral. The API does not stop any clock once it has started them.}
 * @author {Saeed Ghasemi}
 * @version {v0.1}
 * @date {28 sep 2014}
 * @pre {The API handles all of its dependencies on other peripherals
 * internally and will start other clocks in order to properly operate.}
 * @bug {Manual and automated testing are being designed.}
 */

#include "sam3x8e/bitwise_operations.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/pwm.h"

/////////////////////////////////////////////////////////////////////////////
///\cond
/*
 *  Necessary registers addressed by incrementing the base address by an
 *  register-specific offset.
 */
// The first register in the PWM peripheral
#define p_PWM_BASE_ADD			0x40094000U

#define PWM_CLK 	*((uint32_t*)(p_PWM_BASE_ADD + 0x000)) // PWM Clock Register
#define PWM_ENA 	*((uint32_t*)(p_PWM_BASE_ADD + 0x004)) // PWM Enable Register
#define PWM_DIS 	*((uint32_t*)(p_PWM_BASE_ADD + 0x008)) // PWM Disable Register
#define PWM_SR 		*((uint32_t*)(p_PWM_BASE_ADD + 0x00C)) // PWM Status Register

#define PWM_CMR0 	*((uint32_t*)(p_PWM_BASE_ADD + 0x200 + 0x020*0)) // PWM Channel Mode Register
#define PWM_CMR1 	*((uint32_t*)(p_PWM_BASE_ADD + 0x200 + 0x020*1)) // PWM Channel Mode Register
#define PWM_CMR2 	*((uint32_t*)(p_PWM_BASE_ADD + 0x200 + 0x020*2)) // PWM Channel Mode Register
#define PWM_CMR3 	*((uint32_t*)(p_PWM_BASE_ADD + 0x200 + 0x020*3)) // PWM Channel Mode Register
#define PWM_CMR4 	*((uint32_t*)(p_PWM_BASE_ADD + 0x200 + 0x020*4)) // PWM Channel Mode Register
#define PWM_CMR5 	*((uint32_t*)(p_PWM_BASE_ADD + 0x200 + 0x020*5)) // PWM Channel Mode Register
#define PWM_CMR6 	*((uint32_t*)(p_PWM_BASE_ADD + 0x200 + 0x020*6)) // PWM Channel Mode Register
#define PWM_CMR7 	*((uint32_t*)(p_PWM_BASE_ADD + 0x200 + 0x020*7)) // PWM Channel Mode Register

#define PWM_CDTY0 	*((uint32_t*)(p_PWM_BASE_ADD + 0x204 + 0x020*0)) // PWM Channel Duty Cycle Register
#define PWM_CDTY1 	*((uint32_t*)(p_PWM_BASE_ADD + 0x204 + 0x020*1)) // PWM Channel Duty Cycle Register
#define PWM_CDTY2 	*((uint32_t*)(p_PWM_BASE_ADD + 0x204 + 0x020*2)) // PWM Channel Duty Cycle Register
#define PWM_CDTY3 	*((uint32_t*)(p_PWM_BASE_ADD + 0x204 + 0x020*3)) // PWM Channel Duty Cycle Register
#define PWM_CDTY4 	*((uint32_t*)(p_PWM_BASE_ADD + 0x204 + 0x020*4)) // PWM Channel Duty Cycle Register
#define PWM_CDTY5 	*((uint32_t*)(p_PWM_BASE_ADD + 0x204 + 0x020*5)) // PWM Channel Duty Cycle Register
#define PWM_CDTY6 	*((uint32_t*)(p_PWM_BASE_ADD + 0x204 + 0x020*6)) // PWM Channel Duty Cycle Register
#define PWM_CDTY7 	*((uint32_t*)(p_PWM_BASE_ADD + 0x204 + 0x020*7)) // PWM Channel Duty Cycle Register

#define PWM_CDTYUPD0 *((uint32_t*)(p_PWM_BASE_ADD + 0x208 + 0x020*0)) // PWM Channel Duty Cycle Update Register
#define PWM_CDTYUPD1 *((uint32_t*)(p_PWM_BASE_ADD + 0x208 + 0x020*1)) // PWM Channel Duty Cycle Update Register
#define PWM_CDTYUPD2 *((uint32_t*)(p_PWM_BASE_ADD + 0x208 + 0x020*2)) // PWM Channel Duty Cycle Update Register
#define PWM_CDTYUPD3 *((uint32_t*)(p_PWM_BASE_ADD + 0x208 + 0x020*3)) // PWM Channel Duty Cycle Update Register
#define PWM_CDTYUPD4 *((uint32_t*)(p_PWM_BASE_ADD + 0x208 + 0x020*4)) // PWM Channel Duty Cycle Update Register
#define PWM_CDTYUPD5 *((uint32_t*)(p_PWM_BASE_ADD + 0x208 + 0x020*5)) // PWM Channel Duty Cycle Update Register
#define PWM_CDTYUPD6 *((uint32_t*)(p_PWM_BASE_ADD + 0x208 + 0x020*6)) // PWM Channel Duty Cycle Update Register
#define PWM_CDTYUPD7 *((uint32_t*)(p_PWM_BASE_ADD + 0x208 + 0x020*7)) // PWM Channel Duty Cycle Update Register

#define PWM_CPRD0 	*((uint32_t*)(p_PWM_BASE_ADD + 0x20C + 0x020*0)) // PWM Channel Period Register
#define PWM_CPRD1 	*((uint32_t*)(p_PWM_BASE_ADD + 0x20C + 0x020*1)) // PWM Channel Period Register
#define PWM_CPRD2 	*((uint32_t*)(p_PWM_BASE_ADD + 0x20C + 0x020*2)) // PWM Channel Period Register
#define PWM_CPRD3 	*((uint32_t*)(p_PWM_BASE_ADD + 0x20C + 0x020*3)) // PWM Channel Period Register
#define PWM_CPRD4 	*((uint32_t*)(p_PWM_BASE_ADD + 0x20C + 0x020*4)) // PWM Channel Period Register
#define PWM_CPRD5 	*((uint32_t*)(p_PWM_BASE_ADD + 0x20C + 0x020*5)) // PWM Channel Period Register
#define PWM_CPRD6 	*((uint32_t*)(p_PWM_BASE_ADD + 0x20C + 0x020*6)) // PWM Channel Period Register
#define PWM_CPRD7 	*((uint32_t*)(p_PWM_BASE_ADD + 0x20C + 0x020*7)) // PWM Channel Period Register

#define PWM_CPRDUPD0 *((uint32_t*)(p_PWM_BASE_ADD + 0x210 + 0x020*0)) // PWM Channel Period Update Register
#define PWM_CPRDUPD1 *((uint32_t*)(p_PWM_BASE_ADD + 0x210 + 0x020*1)) // PWM Channel Period Update Register
#define PWM_CPRDUPD2 *((uint32_t*)(p_PWM_BASE_ADD + 0x210 + 0x020*2)) // PWM Channel Period Update Register
#define PWM_CPRDUPD3 *((uint32_t*)(p_PWM_BASE_ADD + 0x210 + 0x020*3)) // PWM Channel Period Update Register
#define PWM_CPRDUPD4 *((uint32_t*)(p_PWM_BASE_ADD + 0x210 + 0x020*4)) // PWM Channel Period Update Register
#define PWM_CPRDUPD5 *((uint32_t*)(p_PWM_BASE_ADD + 0x210 + 0x020*5)) // PWM Channel Period Update Register
#define PWM_CPRDUPD6 *((uint32_t*)(p_PWM_BASE_ADD + 0x210 + 0x020*6)) // PWM Channel Period Update Register
#define PWM_CPRDUPD7 *((uint32_t*)(p_PWM_BASE_ADD + 0x210 + 0x020*7)) // PWM Channel Period Update Register

///\endcond
////////////////////////////////////////////////////////////////////////

/**
 * Initialize the PWM peripheral with minimum requirements.
 *
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_init_peripheral_default() {
	pmc_enable_peripheral_clock(ID_PWM);
	pwm_reset();
	return 1;
}
/**
 * This initialization function also takes in parameters for the two clocks
 * called CLK_A and CLK_B.
 * Starting these clocks consume more power. It is preferred to use the channel
 * prescalers if possible. All of the 8 channels can use the same clock once it
 * has been initialized. If these clocks are used, the channels prescalers must
 * be set to select the output of theses clocks.
 *
 * @param clk_settings {A structure of type pwm_clk_setting to initialize the
 * clocks A and B. For more details see description of typedef pwm_clk_setting.}
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_init_peripheral(struct pwm_clk_setting clk_settings) {
	uint8_t error = 0;
	pmc_enable_peripheral_clock(ID_PWM);
	pwm_reset();
	if (clk_settings.clkA_divisor != 0) {
		error += pwm_set_clkx(PWM_CLK_ID_CLKA, clk_settings.clkA_prescaler,
				clk_settings.clkA_divisor);
	}
	if (clk_settings.clkB_divisor != 0) {
		error += pwm_set_clkx(PWM_CLK_ID_CLKB, clk_settings.clkB_prescaler,
				clk_settings.clkB_divisor);
	}
	// output no_error if no error occurred in any of the functions
	return (error == 2) ? 1 : 0;
}
/**
 * Initialize the PWM peripheral with channel- polarity, alignment, prescaler
 * and initial duty cycle. If prescaler is chosen then use_prescaler must be
 * set to 1, and if a specific frequency is needed, then use_prescaler must be
 * set to 0. Using the prescaler should be considered first, cause setting the
 * frequency will occupy a CLKx and consume more power.
 * This function will disable the channel but not enable it.
 *
 * The frequency must be set between 322 and 84 MHz.
 *
 * @param channel {The channel-instance of type pwm_channel_setting,
 * (See typedef pwm_channel_setting for more details.)}
 * @return {error, 1 = SUCCESS and 0 = FAIL}
 */
uint8_t pwm_init_channel(struct pwm_channel_setting channel) {
	uint8_t error = 0;
	if (channel.use_prescaler == 1) {
		error += pwm_set_channel_prescaler(channel.channel, channel.prescaler);
	} else {
		error += pwm_set_clkx_frequency(channel.channel, channel.frequency,
				channel.clock_ID);
	}
	error += pwm_channel_disable(channel.channel);
	error += pwm_set_channel_alignment(channel.channel, channel.alignment);
	error += pwm_set_channel_polarity(channel.channel, channel.polarity);
	error += pwm_set_channel_duty_cycle(channel.channel, channel.duty_cycle);
	// output no_error if no error occurred in any of the functions
	return (error == 6) ? 1 : 0;
}

/**
 * This function will enable the selected channel, identified with predefined
 * values, like: PWM_CHANNEL_x_MASK
 *
 * Alternatively use PWM_CHANNEL_ALL_MASK to enable all channel at once.
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @return error Will always return 1 = SUCCESS
 */
uint8_t pwm_channel_enable(uint32_t channel) {
	set_section_in_register(&PWM_ENA, channel, 1);
	return 1;
}

/**
 * This function will disable the selected channel, identified with predefined
 * values, like: PWM_CHANNEL_x_MASK. This function will block till the channel
 * has been disabled. Disabling the channel will be effective at the end of the
 * period as in CPRDx in PWM_CPRDx.
 *
 * Alternatively use PWM_CHANNEL_ALL_MASK to disable all channel at once.
 *
 * @param channel {The channel to be disabled, use prefix: PWM_CHANNEL_}
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t pwm_channel_disable(uint32_t channel) {
	if (pwm_channel_status(channel)) {
		set_section_in_register(&PWM_DIS, channel, 1);
		while (pwm_channel_status(channel)) {
		}
	}
	return (uint8_t) 0x01;
}

/**
 * Set the channel prescaler
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @param prescaler {This is the prescaler to be set.
 * Use one of the predefined. prefix: PWM_CMRx_PRES_}
 * @return error
 */
uint8_t pwm_set_channel_prescaler(uint32_t channel, uint32_t prescaler) {
	uint8_t error = 0;
	switch (channel) {
	case PWM_CHANNEL_0_MASK:
		error = set_section_in_register(&PWM_CMR0, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_1_MASK:
		error = set_section_in_register(&PWM_CMR1, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_2_MASK:
		error = set_section_in_register(&PWM_CMR2, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_3_MASK:
		error = set_section_in_register(&PWM_CMR3, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_4_MASK:
		error = set_section_in_register(&PWM_CMR4, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_5_MASK:
		error = set_section_in_register(&PWM_CMR5, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_6_MASK:
		error = set_section_in_register(&PWM_CMR6, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	case PWM_CHANNEL_7_MASK:
		error = set_section_in_register(&PWM_CMR7, PWM_CMRx_CPRE_MASK,
				prescaler);
		break;
	default:
		return 0;
		break;
	}
	return error;
}

/**
 * Set the channel polarity.
 * This can reverse the duty cycle. Important when using the PWMLx pins.
 *
 * @param channel {The channel to set the polarity for. ex PWM_CHANNEL_0_MASK}
 * @return
 */
uint8_t pwm_set_channel_polarity(uint32_t channel, uint32_t pwm_polarity) {
	switch (channel) {
	case PWM_CHANNEL_0_MASK:
		set_section_in_register(&PWM_CMR0, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_1_MASK:
		set_section_in_register(&PWM_CMR1, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_2_MASK:
		set_section_in_register(&PWM_CMR2, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_3_MASK:
		set_section_in_register(&PWM_CMR3, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_4_MASK:
		set_section_in_register(&PWM_CMR4, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_5_MASK:
		set_section_in_register(&PWM_CMR5, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_6_MASK:
		set_section_in_register(&PWM_CMR6, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	case PWM_CHANNEL_7_MASK:
		set_section_in_register(&PWM_CMR7, PWM_CMRx_CPOL_MASK, pwm_polarity);
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

/**
 * Set the channel alignment
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @return
 */
uint8_t pwm_set_channel_alignment(uint32_t channel, uint32_t pwm_alignment) {
	switch (channel) {
	case PWM_CHANNEL_0_MASK:
		set_section_in_register(&PWM_CMR0, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_1_MASK:
		set_section_in_register(&PWM_CMR1, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_2_MASK:
		set_section_in_register(&PWM_CMR2, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_3_MASK:
		set_section_in_register(&PWM_CMR3, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_4_MASK:
		set_section_in_register(&PWM_CMR4, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_5_MASK:
		set_section_in_register(&PWM_CMR5, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_6_MASK:
		set_section_in_register(&PWM_CMR6, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	case PWM_CHANNEL_7_MASK:
		set_section_in_register(&PWM_CMR7, PWM_CMRx_CALG_MASK, pwm_alignment);
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

/**
 * Turns off clock A or B.
 *
 * @param clock_id {Must be 0 for clkA and 1 for clkB}
 * @return
 */
uint8_t pwm_turn_off_clkx(uint8_t clock_id) {
	if (clock_id == 0) {
		set_section_in_register(&PWM_CLK, PWM_CLK_DIVA_MASK,
		PWM_CLK_DIVx_TURNOFF);
		return 1;
	} else if (clock_id == 1) {
		set_section_in_register(&PWM_CLK, PWM_CLK_DIVB_MASK,
		PWM_CLK_DIVx_TURNOFF);
		return 1;
	}
	return 0;
}

uint8_t pwm_set_clkx(uint32_t clock_id, uint32_t prescaler, uint32_t divisor) {
	if (clock_id == PWM_CLK_ID_CLKA) {
		set_section_in_register(&PWM_CLK, PWM_CLK_PREA_MASK, prescaler);
		set_section_in_register(&PWM_CLK, PWM_CLK_DIVA_MASK, divisor);
		return 1;
	} else if (clock_id == PWM_CLK_ID_CLKB) {
		set_section_in_register(&PWM_CLK, PWM_CLK_PREB_MASK, prescaler);
		set_section_in_register(&PWM_CLK, PWM_CLK_DIVB_MASK, divisor);
		return 1;
	}
	return 0;
}

/**
 * Writes an output to a given channel by setting the channel duty cycle.
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @param duty_cycle {must be between 0 and period as in CPRD in the register PWM_CPRDx.}
 * @return error (1 = SCCESS and 0 = FAIL)
 */
uint8_t pwm_set_channel_duty_cycle(uint32_t channel, uint32_t duty_cycle) {
	switch (channel) {
	case PWM_CHANNEL_0_MASK:
		if (pwm_channel_status(PWM_CHANNEL_0_MASK)) {
			set_section_in_register(&PWM_CDTYUPD0, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM_CDTY0, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_1_MASK:
		if (pwm_channel_status(PWM_CHANNEL_1_MASK)) {
			set_section_in_register(&PWM_CDTYUPD1, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM_CDTY1, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_2_MASK:
		if (pwm_channel_status(PWM_CHANNEL_2_MASK)) {
			set_section_in_register(&PWM_CDTYUPD2, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM_CDTY2, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_3_MASK:
		if (pwm_channel_status(PWM_CHANNEL_3_MASK)) {
			set_section_in_register(&PWM_CDTYUPD3, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM_CDTY3, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_4_MASK:
		if (pwm_channel_status(PWM_CHANNEL_4_MASK)) {
			set_section_in_register(&PWM_CDTYUPD4, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM_CDTY4, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_5_MASK:
		if (pwm_channel_status(PWM_CHANNEL_5_MASK)) {
			set_section_in_register(&PWM_CDTYUPD5, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM_CDTY5, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_6_MASK:
		if (pwm_channel_status(PWM_CHANNEL_6_MASK)) {
			set_section_in_register(&PWM_CDTYUPD6, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM_CDTY6, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	case PWM_CHANNEL_7_MASK:
		if (pwm_channel_status(PWM_CHANNEL_7_MASK)) {
			set_section_in_register(&PWM_CDTYUPD7, PWM_CDTYUPDx_CDTYUPD_MASK,
					duty_cycle);
		} else {
			set_section_in_register(&PWM_CDTY7, PWM_CDTYx_CDTY_MASK,
					duty_cycle);
		}
		break;
	default:
		return 0;
		break;
	}
	return 1;
}
/**
 * Shuts down the peripheral but keeps all settings
 * @return
 */
uint8_t pwm_shutdown() {
	pmc_disable_peripheral_clock(ID_PWM);
	return 1;
}
/**
 * Resets the peripheral and disables all channels
 * @return error
 */
uint8_t pwm_reset() {
	pwm_channel_disable(PWM_CHANNEL_ALL_MASK);

	clear_register(&PWM_CLK);

	clear_register(&PWM_CMR0);
	clear_register(&PWM_CMR1);
	clear_register(&PWM_CMR2);
	clear_register(&PWM_CMR3);
	clear_register(&PWM_CMR4);
	clear_register(&PWM_CMR5);
	clear_register(&PWM_CMR6);
	clear_register(&PWM_CMR7);

	clear_register(&PWM_CDTYUPD0);
	clear_register(&PWM_CDTYUPD1);
	clear_register(&PWM_CDTYUPD2);
	clear_register(&PWM_CDTYUPD3);
	clear_register(&PWM_CDTYUPD4);
	clear_register(&PWM_CDTYUPD5);
	clear_register(&PWM_CDTYUPD6);
	clear_register(&PWM_CDTYUPD7);

	clear_register(&PWM_CPRDUPD0);
	clear_register(&PWM_CPRDUPD1);
	clear_register(&PWM_CPRDUPD2);
	clear_register(&PWM_CPRDUPD3);
	clear_register(&PWM_CPRDUPD4);
	clear_register(&PWM_CPRDUPD5);
	clear_register(&PWM_CPRDUPD6);
	clear_register(&PWM_CPRDUPD7);
	return 1;
}
/**
 * Reset and turns off the peripheral
 * @return
 */
uint8_t pwm_close() {
	pwm_reset();
	pwm_shutdown();
	return 1;
}

uint32_t pwm_read(uint32_t channel) {
	switch (channel) {
	case PWM_CHANNEL_0_MASK:
		return get_section_in_register(&PWM_CDTY0, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_1_MASK:
		return get_section_in_register(&PWM_CDTY1, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_2_MASK:
		return get_section_in_register(&PWM_CDTY2, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_3_MASK:
		return get_section_in_register(&PWM_CDTY3, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_4_MASK:
		return get_section_in_register(&PWM_CDTY4, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_5_MASK:
		return get_section_in_register(&PWM_CDTY5, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_6_MASK:
		return get_section_in_register(&PWM_CDTY6, PWM_CDTYx_CDTY_MASK);
		break;
	case PWM_CHANNEL_7_MASK:
		return get_section_in_register(&PWM_CDTY7, PWM_CDTYx_CDTY_MASK);
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

uint8_t pwm_channel_status(uint32_t channel) {
	return is_bit_high(&PWM_SR, get_position_of_first_highbit(channel));
}


/**
 * This function will set the period value used by a given PWM channel.
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @param period {The period of the channel. t must be between 0 and 65535.}
 * @return error (1 = SCCESS and 0 = FAIL)
 */
uint8_t pwm_set_channel_period(uint32_t channel, uint32_t period) {
	switch (channel) {
	case PWM_CHANNEL_0_MASK:
		if (pwm_channel_status(PWM_CHANNEL_0_MASK)) {
			set_section_in_register(&PWM_CPRDUPD0, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM_CPRD0, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_1_MASK:
		if (pwm_channel_status(PWM_CHANNEL_1_MASK)) {
			set_section_in_register(&PWM_CPRDUPD1, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM_CPRD1, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_2_MASK:
		if (pwm_channel_status(PWM_CHANNEL_2_MASK)) {
			set_section_in_register(&PWM_CPRDUPD2, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM_CPRD2, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_3_MASK:
		if (pwm_channel_status(PWM_CHANNEL_3_MASK)) {
			set_section_in_register(&PWM_CPRDUPD3, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM_CPRD3, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_4_MASK:
		if (pwm_channel_status(PWM_CHANNEL_4_MASK)) {
			set_section_in_register(&PWM_CPRDUPD4, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM_CPRD4, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_5_MASK:
		if (pwm_channel_status(PWM_CHANNEL_5_MASK)) {
			set_section_in_register(&PWM_CPRDUPD5, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM_CPRD5, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_6_MASK:
		if (pwm_channel_status(PWM_CHANNEL_6_MASK)) {
			set_section_in_register(&PWM_CPRDUPD6, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM_CPRD6, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	case PWM_CHANNEL_7_MASK:
		if (pwm_channel_status(PWM_CHANNEL_7_MASK)) {
			set_section_in_register(&PWM_CPRDUPD7, PWM_CPRDUPDx_CPRDUPD_MASK,
					period);
		} else {
			set_section_in_register(&PWM_CPRD7, PWM_CPRDx_CPRD_MASK, period);
		}
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

uint8_t pwm_set_clkx_frequency(uint32_t channel, uint32_t frequency,
		uint32_t pwm_clk_id) {
	uint32_t prescalers[11] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
	uint8_t prescaler = 0;
	uint32_t divisor;
	uint32_t pwm_channel_pres;

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
		// Initialize the CLKx with the found settings
		pwm_set_clkx(pwm_clk_id, prescaler, divisor);
		// Set the channel prescaler to the chosen CLKx
		pwm_set_channel_prescaler(channel, pwm_channel_pres);
		return 1; // All set (no error)
	} else {
		return 0; // parameter error
	}
}

uint32_t pwm_get_max_duty_cycle(){
	return get_section_in_register(PWM_CPRD0, PWM_CPRDx_CPRD_MASK);
}


//TODO write a function to set the period based on a given frequency

//uint8_t pwm_set_channel_frequency(uint32_t channel, uint32_t min_resolution,
	//	uint32_t ) {

//}
