/**
 * @file
 * @brief Digital-to-Analog Conversion Controller
 * @details This file provides basic functionality for usage of the DACC.
 * @author Andreas Drotth
 * @author Jonathan Bjarnason
 *
 * @version 1.0
 * @date 2014-09-21
 * @pre First Initialize the board.
 */

#ifndef DACC_H
#define DACC_H

#include <inttypes.h>
#include "pmc.h"

#define DACC_CHANNEL_0 0			///<DACC Channel 0
#define DACC_CHANNEL_1 1			///<DACC Channel 1

// Addresses to DACC registers
#define DACC_CR 	(*p_dacc_cr)	///<Control Register
#define DACC_MR		(*p_dacc_mr)	///<Mode Register
#define DACC_CHER 	(*p_dacc_cher)	///<Channel Enable Register
#define DACC_CHDR 	(*p_dacc_chdr)	///<Channel Disable Register
#define DACC_CHSR 	(*p_dacc_chsr)	///<Channel Status Register
#define DACC_CDR	(*p_dacc_cdr)	///<Conversion Data Register
#define DACC_ISR	(*p_dacc_isr)	///<Interrupt Status Register
#define DACC_WPMR	(*p_dacc_wpmr)	///<Write Protect Mode Register
#define DACC_WPSR 	(*p_dacc_wpsr)	///<Write Protect Status Register

typedef struct dacc_settings_t {
	/**
	 * 0: External trigger mode disabled, DACC in free running mode
	 * 1: External trigger mode enabled
	 */
	uint8_t trigger_mode;

	/**
	 * 0: Half-Word transfer
	 * 1: Word transfer
	 */
	uint8_t word_transfer;

	/** Refresh Period = 1024*refresh/DACC Clock */
	uint8_t refresh;

	/**
	 * 0: Normal mode
	 * 1: Max speed mode
	 */
	uint8_t speed_mode;

	/** Value can be 0-63 */
	uint8_t startup_time;

} dacc_settings_t;

/**
 * Initiates the DACC with provided settings.
 * @param settings Settings for DACC mode register
 * @return Return 0 if settings contain illegal values.
 * Otherwise return 1.
 */
uint8_t dacc_init(dacc_settings_t *settings);

/**
 * Enables a specified DACC channel.
 * @param dacc_channel The channel to enable.
 * @return Return 1 if the function executed correctly, otherwise 0.
 */
uint8_t dacc_enable_channel(uint8_t dacc_channel);

/**
 * Disables a specified DACC channel.
 * @param dacc_channel The channel to disable.
 * @return Return 1 if the function executed correctly.
 */
uint8_t dacc_disable_channel(uint8_t dacc_channel);

/**
 * Checks if the specified channel is enabled.
 * @param dacc_channel The channel which is checked for.
 * @return Return 1 if the function executed correctly, otherwise 0.
 */
uint8_t dacc_channel_enabled(uint8_t dacc_channel);

/**
 * Converts a 12-bit digital value to corresponding analog
 * value on a specified channel.
 * If transfer mode is set to HALF-WORD then only DACC_CHR[15:0]
 * is used whereby [11:0] make up the actual output data.
 * If transfer mode is set to WORD then all bits are used whereby
 * [15:0] is converted first and afterwards the [31:16] bits.
 * @param dacc_channel The channel to output the converted value.
 * @param value The value to convert.
 * @return Return 1 if the function executed correctly, otherwise 0.
 */
uint8_t dacc_write(uint8_t dacc_channel, uint32_t value);

#endif