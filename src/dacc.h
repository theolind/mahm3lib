/**
 * @brief Digital-to-Analog Conversion Controller
 * @details This file provides basic functionality for usage of the DACC.
 * @author Andreas Drotth
 * @author Jonathan Bjarnason
 *
 * @version 0.1
 * @date 2014-09-19
 * @pre
 */

#ifndef DACC_H
#define DACC_H

#include <stdint.h>

// Addresses to different DACC registers
#define DACC_CR 	(*p_DACC_CR)	// Control Register
#define DACC_MR		(*p_DACC_MR)	// Mode register
#define DACC_CHER 	(*p_DACC_CER)	// Channel enable register
#define DACC_CHDR 	(*p_DACC_CHDR)	// Channel disable register
#define DACC_CHSR 	(*p_DACC_CSR)	// Channel status register
#define DACC_WRMR	(*p_DACC_WRMR)	// Write protect mode register
#define DACC_CDR	(*p_DACC_CDR)	// Conversion data register
#define DACC_ISR	(*p_DACC_ISR)	// Interrupt status register

typedef struct dacc_settings_t {
	//Write struct parameters, your move Jonathan
} dacc_settings_t;

/*
 * Initialize the  settings necessary for the DACC.
 * @param dacc_settings_t Settings for the DACC initialization.
 */
uint8_t dacc_init(dacc_settings_t *);

/*
 * Enables a specified DACC channel.
 * @param dacc_channel The channel to enable.
 */
uint8_t dacc_enable_channel(uint8_t dacc_channel);

/*
 * Disables a specified DACC channel.
 * @param dacc_channel The channel to disable.
 */
uint8_t dacc_disable_channel(uint8_t dacc_channel);

/*
 * Converts a 12-bit digital value to corresponding analog
 * value on a specified channel.
 * @param dacc_channel The channel to output the value
 * @param value The value to output.
 */
uint8_t dacc_write(uint8_t dacc_channel, unit16_t value);

/*
 * Checks if the specified channel is enabled.
 * @param dacc_channel The channel which is checked for.
 */
uint8_t dacc_channel_enabled(uint8_t dacc_channel);

#endif
