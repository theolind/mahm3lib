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

#define DACC_CHANNEL_0 0			///<DACC Channel 0
#define DACC_CHANNEL_1 1			///<DACC Channel 1

// Addresses to DACC registers
#define DACC_CR 	(*p_DACC_CR)	///<Control Register
#define DACC_MR		(*p_DACC_MR)	///<Mode Register
#define DACC_CHER 	(*p_DACC_CHER)	///<Channel Enable Register
#define DACC_CHDR 	(*p_DACC_CHDR)	///<Channel Disable Register
#define DACC_CHSR 	(*p_DACC_CHSR)	///<Channel Status Register
#define DACC_CDR	(*p_DACC_CDR)	///<Conversion Data Register
#define DACC_ISR	(*p_DACC_ISR)	///<Interrupt Status Register
#define DACC_WPMR	(*p_DACC_WPMR)	///<Write Protect Mode Register
#define DACC_WPSR 	(*p_DACC_WPSR)	///<Write Protect Status Register

// TODO: should be unnecessary after PMC API is done
// Addresses to PMC registers
#define PMC_PCER1	(*p_PMC_PCER1)	///<Peripheral clock status register 1

typedef struct dacc_settings {
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

} dacc_settings;

/**
 * Initiates the DACC with provided settings.
 * @param settings Settings for DACC mode register
 * @return Return 0 if settings contain illegal values.
 * Otherwise return 1.
 */
uint8_t dacc_init(dacc_settings *settings);

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
