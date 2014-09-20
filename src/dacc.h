/**
 * \brief Digital-to-Analog Conversion Controller
 * \details This file provides basic functionality for usage of the DACC.
 * \author Andreas Drotth
 * \author Jonathan Bjarnason
 *
 * \version 0.1
 * \date 2014-09-19
 * \pre
 */

#ifndef DACC_H
#define DACC_H

#include <stdint.h>

// Addresses to DACC registers
#define DACC_CR 	(*p_DACC_CR)	/// Control register
#define DACC_MR		(*p_DACC_MR)	/// Mode register
#define DACC_CHER 	(*p_DACC_CHER)	/// Channel enable register
#define DACC_CHDR 	(*p_DACC_CHDR)	/// Channel disable register
#define DACC_CHSR 	(*p_DACC_CHSR)	/// Channel status register
#define DACC_CDR	(*p_DACC_CDR)	/// Conversion data register
#define DACC_ISR	(*p_DACC_ISR)	/// Interrupt status register
#define DACC_WRMR	(*p_DACC_WRMR)	/// Write protect mode register
#define DACC_WPSR 	(*p_DACC_WPSR)	/// Write protect status register

// Addresses to PMC registers
#define PMC_PCER1	(*p_PMC_PCER1)	/// Peripheral clock status register 1
#define PMC_WPMR	(*p_PMC_WPMR)	/// Write protect mode Register
#define PMC_WPSR    (*p_PMC_WPSR)	/// Write protect status register

//#define DACC_PID	(38)	/// DACC Peripheral ID

typedef struct dacc_settings_t {
	/**
	 * Trigger Mode
	 * 0: External trigger mode disabled, DACC in free running mode
	 * 1: External trigger mode enabled
	 */
	uint32_t trigger_mode;

	/**
	 * Word transfer
	 * 0: Half-Word transfer
	 * 1: Word transfer
	 */
	uint32_t word_transfer;

	/** Refresh Period = 1024*refresh/DACC Clock */
	uint32_t refresh;

	/**
	 * Max speed mode
	 * 0: Normal mode
	 * 1: Max speed mode enabled
	 */
	uint32_t max_speed_mode;

	/** Startup Time Selection */
	uint32_t startup_time;

} dacc_settings_t;

/**
 * Initiates the DACC
 * @param dacc_settings_t Settings for DACC mode register.
 */
uint8_t dacc_init(const dacc_settings_t *);
uint8_t dacc_enable_channel(uint8_t dacc_channel);
uint8_t dacc_disable_channel(uint8_t dacc_channel);
uint8_t dacc_channel_enabled(uint8_t dacc_channel);
uint8_t dacc_write(uint8_t dacc_channel, uint32_t value);

#endif
