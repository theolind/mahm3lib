/**
 * @file tc.h
 * @brief TC - Timer Counter
 * @details This API is used to control the three independent hardware timers.
 * @pre Timer clocks must be enabled through PMC and their appropriate
 * channels must be configured to peripheral use with PIO.
 *
 * @author Andreas Drotth
 * @author Mattias Nilsson
 * @date 20 Oktober 2014
 */

#ifndef TC_H_
#define TC_H_

#include <inttypes.h>

// Pointer to base addresses of the three Timer Counters.
#define TC0 ((tc_reg_t *) 0x40080000U) ///< Instance of TC0
#define TC1 ((tc_reg_t *) 0x40084000U) ///< Instance of TC1
#define TC2 ((tc_reg_t *) 0x40088000U) ///< Instance of TC2

// Valid channels for each TC instance
#define TC_CHANNEL_0	(0) ///< TC channel 0
#define TC_CHANNEL_1	(1) ///< TC channel 1
#define TC_CHANNEL_2	(2) ///< TC channel 2

// TC Channel Mode Register
#define TC_CMR_TCCLKS_TCLK1 	(0)	///< Timer clock 1 (MCK/2)
#define TC_CMR_TCCLKS_TCLK2 	(1)	///< Timer clock 2 (MCK/8)
#define TC_CMR_TCCLKS_TCLK3 	(2)	///< Timer clock 3 (MCK/32)
#define TC_CMR_TCCLKS_TCLK4 	(3)	///< Timer clock 4 (MCK/128)
#define TC_CMR_TCCLKS_TCLK5		(4) ///< Timer clock 5 (SLCK, equivalent to MCK in SCLK mode)
#define TC_CMR_TCCLKS_XC0		(5) ///< Extern clock 0
#define TC_CMR_TCCLKS_XC1		(6) ///< Extern clock 1
#define TC_CMR_TCCLKS_XC2		(7) ///< Extern clock 2
#define TC_CMR_BURST_NONE		(0) ///< The clock is not gated by an external signal
#define TC_CMR_BURST_XC0 		(1) ///< XC0 is ANDed with the selected clock
#define TC_CMR_BURST_XC1 		(2) ///< XC1 is ANDed with the selected clock
#define TC_CMR_BURST_XC2 		(3) ///< XC2 is ANDed with the selected clock
#define TC_CMR_ETREDG_NONE		(0) ///< The clock is not gated by an external signal
#define TC_CMR_ETREDG_RISING	(1) ///< Rising edge
#define TC_CMR_ETREDG_FALLING	(2) ///< Falling edge
#define TC_CMR_ETREDG_EDGE		(3) ///< Each edge
#define TC_CMR_LDRA_NONE		(0) ///< None
#define TC_CMR_LDRA_RISING		(1) ///< Rising edge of TIOA
#define TC_CMR_LDRA_FALLING		(2) ///< Falling edge of TIOA
#define TC_CMR_LDRA_EDGE		(3) ///< Each edge of TIOA
#define TC_CMR_LDRB_NONE		(0) ///< None
#define TC_CMR_LDRB_RISING		(1) ///< Rising edge of TIOB
#define TC_CMR_LDRB_FALLING		(2) ///< Falling edge of TIOB
#define TC_CMR_LDRB_EDGE		(3) ///< Each edge of TIOB
#define TC_CMR_EEVTEDG_NONE		(0) ///< None
#define TC_CMR_EEVTEDG_RISING	(1) ///< Rising edge
#define TC_CMR_EEVTEDG_FALLING	(2) ///< Falling edge
#define TC_CMR_EEVTEDG_EDGE		(3) ///< Each edge
#define TC_CMR_EEVT_TIOB		(0) ///< Input
#define TC_CMR_EEVT_XC0			(1) ///< Output
#define TC_CMR_EEVT_XC1			(2) ///< Output
#define TC_CMR_EEVT_XC2			(3) ///< Output
#define TC_CMR_WAVESEL_UP		(0) ///< UP mode without automatic trigger on RC Compare
#define TC_CMR_WAVESEL_UPDOWN	(1) ///< UPDOWN mode without automatic trigger on RC Compare
#define TC_CMR_WAVESEL_UP_RC	(2) ///< UP mode with automatic trigger on RC Compare
#define TC_CMR_WAVESEL_UPDOWN_RC (3) ///< UPDOWN mode with automatic trigger on RC Compare

// TC Block Mode Register
#define TC_BMR_TC0XC0S_TCLK0	(0) ///< Signal connected to XC0: TCLK0
#define TC_BMR_TC0XC0S_TIOA1	(2) ///< Signal connected to XC0: TIOA1
#define TC_BMR_TC0XC0S_TIOA2	(3) ///< Signal connected to XC0: TIOA2
#define TC_BMR_TC1XC1S_TCLK1	(0) ///< Signal connected to XC1: TCLK1
#define TC_BMR_TC1XC1S_TIOA0	(2) ///< Signal connected to XC1: TIOA0
#define TC_BMR_TC1XC1S_TIOA2	(3) ///< Signal connected to XC1: TIOA2
#define TC_BMR_TC2XC2S_TCLK2	(0) ///< Signal connected to XC2: TCLK2
#define TC_BMR_TC2XC2S_TIOA1	(2) ///< Signal connected to XC2: TIOA1
#define TC_BMR_TC2XC2S_TIOA2	(3) ///< Signal connected to XC2: TIOA2

///@cond
// Used by functions
#define MAX_CHANNELS			(3)
#define TC_CCR_CLKEN			(0x1u << 0)
#define TC_CCR_CLKDIS			(0x1u << 1)
#define TC_CCR_SWTRG			(0x1u << 2)
#define TC_SR_CLKSTA_ENABLED	(0x1u << 16)
#define TC_CMR_WAVEFORM_MODE	(1)
#define TC_CMR_CAPTURE_MODE		(0)
#define TC_BCR_SYNC				(1)

// Parameter positions
#define TC_CMR_WAVE_POS			(15)
#define TC_CMR_TCCLKS_POS		(0)
#define TC_CMR_CLKI_POS			(3)
#define TC_CMR_BURST_POS		(4)
#define TC_CMR_LDBSTOP_POS		(6)
#define TC_CMR_LDBDIS_POS		(7)
#define TC_CMR_ETRGEDG_POS		(8)
#define TC_CMR_ABETRG_POS		(10)
#define TC_CMR_CPCTRG_POS		(14)
#define TC_CMR_LDRA_POS			(16)
#define TC_CMR_LDRB_POS			(18)
#define TC_CMR_CPCSTOP_POS		(6)
#define TC_CMR_CPCDIS_POS		(7)
#define TC_CMR_EEVTEDG_POS		(8)
#define TC_CMR_EEVT_POS			(10)
#define TC_CMR_ENETRG_POS		(12)
#define TC_CMR_WAVSEL_POS		(13)
#define TC_CMR_ACPA_POS			(16)
#define TC_CMR_ACPC_POS			(18)
#define TC_CMR_AEEVT_POS		(20)
#define TC_CMR_ASWTRG_POS		(22)
#define TC_CMR_BCPB_POS			(24)
#define TC_CMR_BCPC_POS			(26)
#define TC_CMR_BEEVT_POS		(28)
#define TC_CMR_BSWTRG_POS		(30)

#define TC_BMR_TC0XC0S_POS		(0)
#define TC_BMR_TC1XC1S_POS		(2)
#define TC_BMR_TC2XCS2_POS		(3)
#define TC_BMR_QDEN_POS			(8)
#define TC_BMR_POSEN_POS		(9)
#define TC_BMR_SPEEDEN_POS		(10)
#define TC_BMR_QDTRANS_POS		(11)
#define TC_BMR_EDGPHA_POS		(12)
#define TC_BMR_INVA_POS			(13)
#define TC_BMR_INVB_POS			(14)
#define TC_BMR_INVIDX_POS		(15)
#define TC_BMR_SWAP_POS			(16)
#define TC_BMR_IDXPHB_POS		(17)
#define TC_BMR_FILTER_POS		(19)
#define TC_BMR_MAXFILT_POS		(20)


/*
 * Mapping of TC channel registers
 */
typedef struct tc_channel_reg {
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
	// Reserved, offset 0x0030 - 0x003C
	uint32_t reserved2[4];
} tc_channel_reg_t;

/*
 * Mapping of TC block registers
 */
typedef struct tc_reg {
	// Channel 0-2 registers, offset 0x0000 - 0x00BC
	tc_channel_reg_t TC_CHANNEL[3];
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
	uint32_t TC_FMR;
	// Reserved, offset 0x00DC - 0x00E0
	uint32_t reserved[2];
	// Write Protection Mode Register, offset 0x00E4
	uint32_t TC_WPMR;
} tc_reg_t;
///@endcond

/**
 * Settings for the individual TC channels.
 */
typedef struct tc_channel_settings {
	// Common parameters
	/**
	 * Clock selection.
	 * Either an internal timer clock or external clock.
	 */
	uint32_t tcclks;
	/**
	 * Clock invertion.
	 * 0: counter is incremented on rising edge of the clock.
	 * 1: counter is incremented on falling edge of the clock.
	 */
	uint32_t clki;
	/**
	 * Burst Signal Selection.
	 */
	uint32_t burst;
	/**
	 * Mode selection.
	 * 0: Capture Mode
	 * 1: Waveform Mode
	 */
	uint32_t wave;

	// Capture mode parameters
	/**
	 * Counter Clock Stopped with RB Loading.
	 * 0: counter clock is not stopped when RB loading occurs.
	 * 1: counter clock is stopped when RB loading occurs.
	 */
	uint32_t ldbstop;
	/**
	 * Counter Clock Disable with RB Loading.
	 * 0: counter clock is not disabled when RB loading occurs.
	 * 1: counter clock is disabled when RB loading occurs.
	 */
	uint32_t ldbdis;
	/**
	 * External Trigger Edge Selection.
	 */
	uint32_t etrgedg;
	/**
	 * TIOA or TIOB External Trigger Selection.
	 * 0: TIOB is used as an external trigger.
	 * 1: TIOA is used as an external trigger.
	 */
	uint32_t abetrg;
	/**
	 * RC Compare Trigger Enable.
	 * 0: RC Compare has no effect on the counter and its clock.
	 * 1: RC Compare resets the counter and starts the counter clock.
	 */
	uint32_t cpctrg;
	/**
	 * RA Loading Selection
	 */
	uint32_t ldra;
	/**
	 * RB Loading Selection
	 */
	uint32_t ldrb;

	// Waveform mode parameters
	/**
	 * Counter Clock Stopped with RC Compare.
	 * 0: counter clock is not stopped when counter reaches RC.
	 * 1: counter clock is stopped when counter reaches RC.
	 */
	uint32_t cpcstop;
	/**
	 * Counter Clock Disable with RC Compare.
	 * 0: counter clock is not disabled when counter reaches RC.
	 * 1: counter clock is disabled when counter reaches RC.
	 */
	uint32_t cpcdis;
	/**
	 * External Event Edge Selection.
	 */
	uint32_t eevtedg;
	/**
	 * External Event Selection.
	 */
	uint32_t eevt;
	/**
	 * External Event Trigger Enable.
	 * 0: the external event has no effect on the counter and its clock.
	 * 1: the external event resets the counter and starts the counter clock.
	 */
	uint32_t enetrg;
	/**
	 * Waveform Selection.
	 */
	uint32_t wavsel;
	/**
	 * RA Compare Effect on TIOA.
	 * 0: NONE, 1: SET
	 * 2: CLEAR, 3: TOGGLE
	 */
	uint32_t acpa;
	/**
	 * RC Compare Effect on TIOA.
	 * 0: NONE, 1: SET
	 * 2: CLEAR, 3: TOGGLE
	 */
	uint32_t acpc;
	/**
	 * External Event Effect on TIOA.
	 * 0: NONE, 1: SET
	 * 2: CLEAR, 3: TOGGLE
	 */
	uint32_t aeevt;
	/**
	 * Software Trigger Effect on TIOA.
	 * 0: NONE, 1: SET
	 * 2: CLEAR, 3: TOGGLE
	 */
	uint32_t aswtrg;
	/**
	 * RB Compare Effect on TIOB.
	 * 0: NONE, 1: SET
	 * 2: CLEAR, 3: TOGGLE
	 */
	uint32_t bcpb;
	/**
	 * RC Compare Effect on TIOB.
	 * 0: NONE, 1: SET
	 * 2: CLEAR, 3: TOGGLE
	 */
	uint32_t bcpc;
	/**
	 * External Event Effect on TIOB.
	 * 0: NONE, 1: SET
	 * 2: CLEAR, 3: TOGGLE
	 */
	uint32_t beevt;
	/**
	 * Software Trigger Effect on TIOB.
	 * 0: NONE, 1: SET
	 * 2: CLEAR, 3: TOGGLE
	 */
	uint32_t bswtrg;
} tc_channel_settings_t;

/**
 * Settings for the TC instance block.
 */
typedef struct tc_block_settings {
	/**
	 * External Clock Signal 0 Selection.
	 */
	uint32_t tc0xc0s;
	/**
	 * External Clock Signal 1 Selection.
	 */
	uint32_t tc1xc1s;
	/**
	 * External Clock Signal 2 Selection.
	 */
	uint32_t tc2xc2s;
	/**
	 * Quadrature Decoder Enabled.
	 * 0: disabled.
	 * 1: enables the quadrature decoder logic.
	 */
	uint32_t qden;
	/**
	 * Position Enabled.
	 * 0: disabled.
	 * 1: enables the position measure on channel 0 and 1.
	 */
	uint32_t posen;
	/**
	 * Speed Enabled.
	 * 0: disabled.
	 * 1: enables the speed measure on channel 0, the time base being provided by channel 2.
	 */
	uint32_t speeden;
	/**
	 * Quadrature Decoding Transparent.
	 * 0: full quadrature decoding logic is active (direction change detected).
	 * 1: quadrature decoding logic (direction change) is inactive.
	 */
	uint32_t qdtrans;
	/**
	 * Edge on phA count mode.
	 * 0: edges are detected on both PHA and PHB.
	 * 1: edges are detected on PHA only.
	 */
	uint32_t edgpha;
	/**
	 * Inverted phA.
	 * 0: PHA (TIOA0) is directly driving quadrature decoder logic.
	 * 1: PHA is inverted before driving quadrature decoder logic.
	 */
	uint32_t inva;
	/**
	 * Inverted phB.
	 * 0: PHB (TIOB0) is directly driving quadrature decoder logic.
	 * 1: PHB is inverted before driving quadrature decoder logic.
	 */
	uint32_t invb;
	/**
	 * Swap phA and phB.
	 * 0: no swap between PHA and PHB.
	 * 1: swap PHA and PHB internally, prior to driving quadrature decoder logic.
	 */
	uint32_t swap;
	/**
	 * Inverted index.
	 * 0: IDX (TIOA1) is directly driving quadrature logic.
	 * 1: IDX is inverted before driving quadrature logic.
	 */
	uint32_t invidx;
	/**
	 * Index pin is phB pin.
	 * 0: IDX pin of the rotary sensor must drive TIOA1.
	 * 1: IDX pin of the rotary sensor must drive TIOB0.
	 */
	uint32_t idxphb;
	/**
	 * Filter.
	 * 0: IDX,PHA, PHB input pins are not filtered.
	 * 1: IDX,PHA, PHB input pins are filtered using MAXFILT value.
	 */
	uint32_t filter;
	/**
	 * Maximum filter.
	 * 1..63: defines the filtering capabilities.
	 * Pulses with a period shorter than MAXFILT+1 MCK clock cycles are discarded.
	 */
	uint32_t maxfilt;
} tc_block_settings_t;

/**
 * Configures a specified counter channel with provided settings.
 * @param set Settings for timer counter channel.
 * Should be a struct of type tc_channel_settings_t.
 * @param tc Timer counter instance.
 * @param channel Channel to configure.
 */
void tc_conf_channel(tc_channel_settings_t* set, tc_reg_t *tc, uint32_t channel);

/**
 * Configures a specified timer instance with provided settings.
 * @param set Settings for timer counter block.
 * Should be a struct of type tc_block_settings_t.
 * @param tc Timer counter instance.
 */
void tc_conf_block(tc_block_settings_t* set, tc_reg_t *tc);

/**
 * Enables the clock for a channel.
 * @param tc Timer counter instance.
 * @param channel Channel to configure.
 */
void tc_enable_clock(tc_reg_t *tc, uint32_t channel);

/**
 * Disables the clock for a channel. Is also used for stopping the counter.
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
 * Generates a software trigger simultaneously for each of the channels.
 * @param tc Timer counter instance.
 */
void tc_sync_block(tc_reg_t *tc);

/**
 * Read the counter value from a channel.
 * @param tc Timer counter instance.
 * @param channel Channel to read value from.
 * @return The read counter value.
 */
uint32_t tc_read_counter_value(tc_reg_t * tc, uint32_t channel);

/**
 * Reads from register A from the specified channel.
 * @param tc Timer counter instance.
 * @param channel Channel to read from.
 * @return The read register value.
 */
uint32_t tc_read_reg_a(tc_reg_t * tc, uint32_t channel);

/**
 * Reads from register B from the specified channel.
 * @param tc Timer counter instance.
 * @param channel Channel to read from.
 * @return The read register value.
 */
uint32_t tc_read_reg_b(tc_reg_t * tc, uint32_t channel);

/**
 * Reads from register C from the specified channel.
 * @param tc Timer counter instance.
 * @param channel Channel to read from.
 * @return The read register value.
 */
uint32_t tc_read_reg_c(tc_reg_t * tc, uint32_t channel);

/**
 * Writes to register A from the specified channel.
 * @param tc Timer counter instance.
 * @param channel Channel to write to.
 * @param value The value to be written to the register.
 */
void tc_write_reg_a(tc_reg_t * tc, uint32_t channel, uint32_t value);

/**
 * Writes to register B from the specified channel.
 * @param tc Timer counter instance.
 * @param channel Channel to write to.
 * @param value The value to be written to the register.
 */
void tc_write_reg_b(tc_reg_t * tc, uint32_t channel, uint32_t value);

/**
 * Writes to register C from the specified channel.
 * @param tc Timer counter instance.
 * @param channel Channel to write to.
 * @param value The value to be written to the register.
 */
void tc_write_reg_c(tc_reg_t * tc, uint32_t channel, uint32_t value);

#endif
