/**
 * @file dacc.h
 * @brief DACC - Digital-to-Analog Conversion Controller
 * @details This API provides basic functionality for usage of the DACC.
 * @pre First Initialize the board.
 *
 * @author Andreas Drotth
 * @author Jonathan Bjarnason
 * @author Mathias Beckius
 *
 * @date 29 September 2014
 */

#ifndef DACC_H
#define DACC_H

#include <inttypes.h>

///@cond
// Pointer to registers of the DACC peripheral.
#define DACC ((dacc_reg_t *) 0x40094000U)
///@endcond

#define DACC_CHANNEL_0		(0)			///<DACC Channel 0
#define DACC_CHANNEL_1		(1)			///<DACC Channel 1
#define DACC_CHANNEL_MAX	(1)

///@cond

#define DACC_MAX_RESOLUTION 4095	///<The DACC has a 12 bit resolution

#define DACC_MR_WORD_POS		(4)
#define DACC_MR_REFRESH_POS		(8)
#define DACC_MR_USER_SEL_POS	(16)
#define DACC_MR_MAXS_POS		(21)
#define DACC_MR_STARTUP_POS		(24)

#define DACC_ISR_TXRDY_MSK		(1u)

/*
 * Mapping of DACC registers
 * Base address: 0x400C8000
 */
typedef struct {
	// Control Register, offset 0x0000
	uint32_t DACC_CR;
	// Mode Register, offset 0x0004
	uint32_t DACC_MR;
	// reserved, offset 0x0008-0x000C
	uint32_t reserved1[2];
	// Channel Enable Register, offset 0x0010
	uint32_t DACC_CHER;
	// Channel Disable Register, offset 0x0014
	uint32_t DACC_CHDR;
	// Channel Status Register, offset 0x0018
	uint32_t DACC_CHSR;
	// reserved, offset 0x001C
	uint32_t reserved2;
	// Conversion Data Register, offset 0x0020
	uint32_t DACC_CDR;
	// Interrupt Enable Register, offset 0x0024
	uint32_t DACC_IER;
	// Interrupt Disable Register, offset 0x0028
	uint32_t DACC_IDR;
	// Interrupt Mask Register, offset 0x002C
	uint32_t DACC_IMR;
	// Interrupt Status Register, offset 0x0030
	uint32_t DACC_ISR;
	// reserved, offset 0x0034-0x0090
	uint32_t reserved3[25];
	// Analog Current Register, offset 0x0094
	uint32_t DACC_ACR;
	// reserved, 0x0098-0x00E0
	uint32_t reserved4[19];
	// Write Protect Mode register, offset 0x00E4
	uint32_t DACC_WPMR;
	// Write Protect Status register, offset 0x00E8
	uint32_t DACC_WPSR;
} dacc_reg_t;

///@endcond

/**
 * Input parameters when initializing the DAC Controller.
 */
typedef struct dacc_settings {
	/**
	 * 0: Half-Word transfer
	 * 1: Word transfer
	 */
	uint32_t word_transfer;
	/** Refresh Period = 1024*refresh/DACC Clock */
	uint32_t refresh;
	/**
	 * 0: Normal mode
	 * 1: Max speed mode
	 */
	uint32_t speed_mode;
	/**
	 * A value in the range of 0-63 that describes the length of the startup time.
	 * The length for each corresponding value can be found in the datasheet.
	 */
	uint32_t startup_time;
} dacc_settings_t;

/**
 * Initiates the DACC with provided settings.
 * @param settings Settings for DACC mode register,
 * should be a struct of type dacc_settings_t.
 */
void dacc_init(const dacc_settings_t *settings);

/**
 * Enables a specified DACC channel.
 * @param channel The channel to enable (DACC_CHANNEL_0 or DACC_CHANNEl_1).
 * Nothing will happen if the specified channel is out of bounds.
 */
void dacc_enable_channel(uint32_t channel);

/**
 * Disables a specified DACC channel.
 * @param channel The channel to disable (DACC_CHANNEL_0 or DACC_CHANNEl_1).
 * Nothing will happen if the specified channel is out of bounds.
 */
void dacc_disable_channel(uint32_t channel);

/**
 * Checks if the specified channel is enabled.
 * @param channel Channel (DACC_CHANNEL_0 or DACC_CHANNEl_1).
 * @return If the channel is enabled, return 1, otherwise 0.
 * @return 0 is also returned if the specified channel is out of bounds.
 */
uint32_t dacc_channel_enabled(uint32_t channel);

/**
 * Select DACC channel.
 * @param channel Channel (DACC_CHANNEL_0 or DACC_CHANNEl_1).
 * Nothing will happen if the specified channel is out of bounds.
 */
void dacc_select_channel(uint32_t channel);

/**
 * Checks if a new value can be converted by the DACC.
 * @return 1 is returned when new a value can be converted,
 * otherwise 0 is returned.
 */
uint32_t dacc_tx_ready(void);

/**
 * Converts a 12-bit digital value to corresponding analog
 * value on a specified channel.
 * If transfer mode is set to HALF-WORD, then only bits 0-11 is used for
 * output data. If transfer mode is set to WORD, then bits 16-31 will also
 * be used.
 * The least significant bits are converted first in WORD transfer mode.
 * @param value The value to convert.
 * @pre Call dacc_tx_ready() to check if a new value can be converted.
 */
void dacc_write(uint32_t value);

#endif
