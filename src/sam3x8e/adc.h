/**
 * @file adc.h
 * @brief ADC - Analog-to-Digital Converter
 * @details This API is used to read values from the ADC-channels.
 * @pre Initiate board and enable peripheral clock for ADC.
 *
 * Important: Not all functionality of the ADC is implemented in this API yet.
 *
 * @author Hisham Ramish
 * @author Mattias Nilsson
 * @author Prince Balabis
 * @author Andreas Drotth
 * @date 16 October 2014
 */

#ifndef ADC_H_
#define ADC_H_

#include <inttypes.h>

///@cond
// pointer to registers of ADC, base address: 0x400C0000
#define ADC ((adc_reg_t *) 0x400C0000U)
///@endcond

// Valid DACC channels
#define ADC_CHANNEL_0 	0	///< ADC Channel 0
#define ADC_CHANNEL_1	1	///< ADC Channel 1
#define ADC_CHANNEL_2	2	///< ADC Channel 2
#define ADC_CHANNEL_3	3	///< ADC Channel 3
#define ADC_CHANNEL_4	4	///< ADC Channel 4
#define ADC_CHANNEL_5	5	///< ADC Channel 5
#define ADC_CHANNEL_6	6	///< ADC Channel 6
#define ADC_CHANNEL_7	7	///< ADC Channel 7
#define ADC_CHANNEL_8	8	///< ADC Channel 8
#define ADC_CHANNEL_9	9	///< ADC Channel 9
#define ADC_CHANNEL_10	10	///< ADC Channel 10
#define ADC_CHANNEL_11	11	///< ADC Channel 11
#define ADC_CHANNEL_12	12	///< ADC Channel 12
#define ADC_CHANNEL_13	13	///< ADC Channel 13
#define ADC_CHANNEL_14	14	///< ADC Channel 14
#define ADC_CHANNEL_15	15	///< ADC Channel 15

// Resolution values
#define ADC_RESOLUTION_10_BIT	1	///< ADC 10 bit resolution
#define ADC_RESOLUTION_12_BIT	0	///< ADC 12 bit resolution

///@cond
/*
 * Set specified bit levels in a register at specified position.
 * The bit mask should consist of a number of high bits.
 * This macro function could be of common use.....
 */
#define _SET_BIT_LEVELS(reg, levels, bit_mask, pos)	\
	((reg & ~((bit_mask) << (pos))) | ((levels) << (pos)))

#define ADC_MR_SET_RESOLUTION(reg, bits)			\
	_SET_BIT_LEVELS(reg, bits, 0x1u, 4)

// Highest channel ID
#define ADC_CHANNEL_MAX	(15)

// ADC_CR: (ADC Offset: 0x0000) Control Register
#define ADC_CR_START	(0x1u << 1)
#define ADC_CR_RESET	(0x1u << 0)

// ADC_MR: (ADC Offset: 0x0004) Mode Register
#define ADC_MR_RESET	(0)
#define ADC_MR_PRES_POS (8)
#define ADC_MR_SUT0		(0x0u << 16)
#define ADC_MR_SUT8		(0x1u << 16)
#define ADC_MR_SUT16	(0x2u << 16)
#define ADC_MR_SUT24	(0x3u << 16)
#define ADC_MR_SUT64	(0x4u << 16)
#define ADC_MR_SUT80	(0x5u << 16)
#define ADC_MR_SUT96	(0x6u << 16)
#define ADC_MR_SUT112	(0x7u << 16)
#define ADC_MR_SUT512	(0x8u << 16)
#define ADC_MR_SUT576	(0x9u << 16)
#define ADC_MR_SUT640	(0xAu << 16)
#define ADC_MR_SUT704	(0xBu << 16)
#define ADC_MR_SUT768	(0xCu << 16)
#define ADC_MR_SUT832	(0xDu << 16)
#define ADC_MR_SUT896	(0xEu << 16)
#define ADC_MR_SUT960	(0xFu << 16)
#define ADC_MR_RES(resolution) \
	((resolution) << 4)

// ADC_ISR: (ADC Offset: 0x0030) Interrupt Status Register
#define ADC_ISR_DRDY	(0x01 << 24)

/*
 * Mapping of ADC registers
 * Base address: 0x400E0800
 */
typedef struct {
	// Control Register, offset 0x0000
	uint32_t ADC_CR;
	// Mode Register, offset 0x0004
	uint32_t ADC_MR;
	// Channel Sequence Register 1, offset 0x0008
	uint32_t ADC_SEQR1;
	// Channel Sequence Register 2, offset 0x00C
	uint32_t ADC_SEQR2;
	// Channel Enable Register, offset 0x0010
	uint32_t ADC_CHER;
	// Channel Disable Register, offset 0x0014
	uint32_t ADC_CHDR;
	// Channel Status Register, offset 0x0018
	uint32_t ADC_CHSR;
	// Reserved, offset 0x001C
	uint32_t reserved1[1];
	// Last Converted Data Register, offset 0x0020
	uint32_t ADC_LCDR;
	// Interrupt Enable Register, offset 0x0024
	uint32_t ADC_IER;
	// Interrupt Disable Register, offset 0x0028
	uint32_t ADC_IDR;
	// Interrupt Mask Register, offset 0x002C
	uint32_t ADC_IMR;
	// Interrupt Status Register, offset 0x0030
	uint32_t ADC_ISR;
	// Reserved, offset 0x0034 and 0x0038
	uint32_t reserved2[2];
	// Overrun Status Register, offset 0x003C
	uint32_t ADC_OVER;
	// Extended Mode Register, offset 0x0040
	uint32_t ADC_EMR;
	// Compare Window Register, offset 0x0044
	uint32_t ADC_CWR;
	// Channel Gain Register, offset 0x0048
	uint32_t ADC_CGR;
	// Channel Offset Register, offset 0x004C
	uint32_t ADC_COR;
	// Channel Data Register, offset 0x0050 to 0x008C
	uint32_t ADC_CDR[16];
	// Reserved, offset 0x90
	uint32_t reserved3;
	// Analog Control Register, offset 0x0094
	uint32_t ADC_ACR;
	// Reserved, offset 0x0098 to 0x00E0
	uint32_t reserved4[19];
	// Write Protect Mode Register, offset 0x00E4
	uint32_t ADC_WPMR;
	// Write Protect Status Register, offset 0x00E8
	uint32_t ADC_WPSR;
	// Reserved, offset 0x00EC to 0x00FC
	uint32_t reserved5[5];

} adc_reg_t;

///@endcond

/**
 * Input parameters when initializing the ADC.
 */
typedef struct {
	/**
	 * Set the startup time of the ADC.
	 */
	uint32_t startup_time;

	/**
	 * Set the preferred prescaler.
	 * Valid values are between 0-255.
	 * ADCClock = MCK / ((PRESCAL+1) * 2)
	 */
	uint32_t prescaler;

} adc_settings_t;

/**
 * Initializes the ADC.
 * @param adc_settings Pointer to settings for the initlization (startuptime, precaler).
 */
void adc_init(adc_settings_t * adc_settings);

/**
 * Starts the ADC.
 */
void adc_start(void);

/**
 * Resets the ADC.
 */
void adc_reset(void);

/**
 * Sets ADC resolution to 10 bits or 12 bits. 12 bits is default after initiation.
 * @param resolution The resolution of the ADC.
 */
void adc_set_resolution(uint32_t resolution);

/**
 * Enables a specific channel.
 * Channel 15 is used for temperature-reader.
 * @param channel The channel (0-15) that is to be enabled.
 * Nothing will happen if the specified channel is out of bounds.
 */
void adc_enable_channel(uint32_t channel);

/**
 * Disables a specific channel.
 * @param channel The channel (0-15) that is to be disabled.
 * Nothing will happen if the specified channel is out of bounds.
 */
void adc_disable_channel(uint32_t channel);

/**
 * Reads the status for a specific channel. Channel 0-15 is available for readout.
 * @param channel The channel (0-15) that the status is asked for.
 * @return If the channel is enabled, returns 1. Otherwise returns 0.
 * @return 0 is also returned if the specified channel is out of bounds.
 */
uint32_t adc_channel_enabled(uint32_t channel);

/**
 * Read the values from a specific channel. Channel 0-15 is available.
 * @param channel The channel (0-15) that is to be read from.
 * @return ADC value of the specific channel.
 */
uint32_t adc_read_channel(uint32_t channel);
#endif
