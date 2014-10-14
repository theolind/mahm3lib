/**
 * @file tc.h
 * @brief TC - Timer Counter
 * @details This API is used to control the three independent hardware timers.
 * @pre Timer clocks must be enabled through PMC and their appropriate
 * channels must be configured to peripheral use with PIO.
 *
 * @author Andreas Drotth
 * @author Mattias Nilsson
 * @date 14 Oktober 2014
 */

#ifndef TC_H_
#define TC_H_

#include <inttypes.h>

// Pointer to base addresses of the three Timer Counters.
#define TC0 ((tc_reg_t *) 0x40080000U) ///< Instance of TC0
#define TC1 ((tc_reg_t *) 0x40084000U) ///< Instance of TC1
#define TC2 ((tc_reg_t *) 0x40088000U) ///< Instance of TC2

// Valid channels for each TC instance
#define CHANNEL_0	(0x00) ///< TCx channel 0
#define CHANNEL_1	(0x40) ///< TCx channel 1
#define CHANNEL_2	(0x80) ///< TCx channel 2

// Valid clock selections
#define TCLK1 		(0)	///< Timer clock 1 (MCK/2)
#define TCLK2 		(1)	///< Timer clock 2 (MCK/8)
#define TCLK3 		(2)	///< Timer clock 3 (MCK/32)
#define TCLK4 		(3)	///< Timer clock 4 (MCK/128)
#define TCLK5		(4) ///< Timer clock 5 (SLCK, equivalent to MCK in SCLK mode)
#define XC0			(5) ///< Extern clock 0
#define XC1			(6) ///< Extern clock 1
#define XC2			(7) ///< Extern clock 2

typedef struct {
	// Channel Control Register, offset 0x0000
	uint32_t TC_CCR;
	// Channel Mode Register, offset 0x0004
	uint32_t TC_CMR;
	// Stepper Motor Mode Register, offset 0x0008
	uint32_t TC_SMMR;
	// Reserved, offset 0x000C
	uint32_t reserved1;
	// Counter Value, offset 0x0010
	uint32_t TC_CV;
	// Register A, offset 0x0014
	uint32_t TC_RA;
	// Register B, offset 0x0018
	uint32_t TC_RB;
	// Register C, offset 0x001C
	uint32_t TC_RC;
	// Status Register, offset 0x0020
	uint32_t TC_SR;
	// Interrupt Enable Register, offset 0x0024
	uint32_t TC_IER;
	// Interrupt Disable Register, offset 0x0028
	uint32_t TC_IDR;
	// Interrupt Mask Register, offset 0x002C
	uint32_t TC_IMR;
	// Skip, offset 0x0030 - 0x00BC
	uint32_t skip[35];
	// Block Control Register, offset 0x00C0
	uint32_t TC_BCR;
	// Block Mode Register, offset 0x00C4
	uint32_t TC_BMR;
	// QDEC Interrupt Enable Register, offset 0x00C8
	uint32_t TC_QIER;
	// QDEC Interrupt Disable Register, offset 0x00CC
	uint32_t TC_QIDR;
	// QDEC Interrupt Mask Register, offset 0x00D0
	uint32_t TC_QIMR;
	// QDEC Interrupt Status Register, offset 0x00D4
	uint32_t TC_QISR;
	// Fault Mode Register, offset 0x00D8
	uint32_t TC_FM;
	// Reserved, offset 0x00DC - 0x00E0
	uint32_t reserved2[2];
	// Write Protection Mode Register, offset 0x00E4
	uint32_t TC_WPMR;
} tc_reg_t;

typedef struct {
	/**
	 * Mode selection.
	 * 0 = Capture Mode
	 * 1 = Waveform Mode
	 */
	uint32_t mode;
	/**
	 * Clock selection.
	 * Either an internal timer clock or external clock.
	 */
	uint32_t clock;
} tc_settings_t;

/**
 * Configures a specified counter with provided settings.
 * @param settings Settings for timer counter.
 * Should be a struct of type tc_settings_t.
 * @param tc Timer counter instance.
 * @param channel Channel to configure.
 */
void tc_conf(tc_settings_t* settings, tc_reg_t *tc, uint32_t channel);

/**
 * Enables the clock for a channel.
 * @param tc Timer counter instance.
 * @param channel Channel to configure.
 */
void tc_enable_clock(tc_reg_t *tc, uint32_t channel);

/**
 * Disables the clock for a channel.
 * @param tc Timer counter instance.
 * @param channel Channel to configure.
 */
void tc_disable_clock(tc_reg_t *tc, uint32_t channel);

/**
 * Starts the clock for a channel.
 * @param tc Timer counter instance.
 * @param channel Channel to configure.
 */
void tc_start_clock(tc_reg_t *tc, uint32_t channel);

/**
 * Stops the clock for a channel.
 * @param tc Timer counter instance.
 * @param channel Channel to configure.
 */
void tc_stop_clock(tc_reg_t *tc, uint32_t channel);

/**
 * Read the counter value from a channel.
 * @param tc Timer counter instance.
 * @param channel Channel to configure.
 */
uint32_t tc_read_counter_value(tc_reg_t * tc, uint32_t channel);

#endif
