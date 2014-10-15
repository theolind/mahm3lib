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

// Clock selections
#define TCLK1 		(0)	///< Timer clock 1 (MCK/2)
#define TCLK2 		(1)	///< Timer clock 2 (MCK/8)
#define TCLK3 		(2)	///< Timer clock 3 (MCK/32)
#define TCLK4 		(3)	///< Timer clock 4 (MCK/128)
#define TCLK5		(4) ///< Timer clock 5 (SLCK, equivalent to MCK in SCLK mode)
#define TCLK_XC0	(5) ///< Extern clock 0
#define TCLK_XC1	(6) ///< Extern clock 1
#define TCLK_XC2	(7) ///< Extern clock 2

// Burst selections
#define BURST_NONE	(0) ///< The clock is not gated by an external signal.
#define BURST_XC0 	(1) ///< XC0 is ANDed with the selected clock.
#define BURST_XC1 	(2) ///< XC1 is ANDed with the selected clock.
#define BURST_XC2 	(3) ///< XC2 is ANDed with the selected clock.



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

/**
 * Settings for the individual channels.
 */
typedef struct tc_channel_settings {
	// Common parameters
	/**
	 * Clock selection.
	 * Either an internal timer clock or external clock.
	 */
	uint32_t tcclcks;
	/**
	 * Clock invertion.
	 * 0: counter is incremented on rising edge of the clock.
	 * 1: counter is incremented on falling edge of the clock.
	 */
	uint32_t clki;
	/**
	 * Burst Signal Selection
	 * 0: The clock is not gated by an external signal.
	 * 1-3: ANDed with the selected clock.
	 */
	uint32_t burst;
	/**
	 * Mode selection.
	 * 0: Capture Mode
	 * 1: Waveform Mode
	 */
	uint32_t wave;

	// Capture mode parameters
	uint32_t ldbstop;
	uint32_t ldbdis;
	uint32_t etrgedg;
	uint32_t abetrg;
	uint32_t cpctrg;
	uint32_t ldra;
	uint32_t ldrb;

	// Waveform mode parameters
	uint32_t cpcstop;
	uint32_t cpcdis;
	uint32_t eevtedg;
	uint32_t eevt;
	uint32_t enetrg;
	uint32_t wavesel;
	uint32_t acpa;
	uint32_t acpc;
	uint32_t aeevt;
	uint32_t aswtrg;
	uint32_t bcpb;
	uint32_t bcpc;
	uint32_t beevt;
	uint32_t bswtrg;
} tc_channel_settings_t;

/**
 * Configures a specified counter with provided settings.
 * @param settings Settings for timer counter.
 * Should be a struct of type tc_settings_t.
 * @param tc Timer counter instance.
 * @param channel Channel to configure.
 */
void tc_conf(tc_channel_settings_t* settings, tc_reg_t *tc, uint32_t channel);

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
 * @return The read counter value.
 */
uint32_t tc_read_counter_value(tc_reg_t * tc, uint32_t channel);

#endif
