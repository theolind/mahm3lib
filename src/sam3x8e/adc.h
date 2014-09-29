/**
 * @file adc.h
 * @brief Analog-to-Digital Converter (ADC)
 * @details This class is used to read values from the ADC-channels.
 * @pre Initiate board and enable peripheral clock for ADC.
 *
 * Important: Not all functionality of the ADC is implemented in this API yet.
 *
 * @author Hisham Ramish
 * @author Mattias Nilsson
 * @author Prince Balabis
 * @author Andreas Drotth
 * @date 28 September 2014
 *
 */

#ifndef ADC_H_
#define ADC_H_

#include <inttypes.h>

// pointer to registers of ADC, base address: 0x400C0000
#define ADC ((adc_reg_t *) 0x400C0000U)

// Valid DACC channels
#define ADC_CHANNEL_0 	0
#define ADC_CHANNEL_1	1
#define ADC_CHANNEL_2	2
#define ADC_CHANNEL_3	3
#define ADC_CHANNEL_4	4
#define ADC_CHANNEL_5	5
#define ADC_CHANNEL_6	6
#define ADC_CHANNEL_7	7
#define ADC_CHANNEL_8	8
#define ADC_CHANNEL_9	9
#define ADC_CHANNEL_10	10
#define ADC_CHANNEL_11	11
#define ADC_CHANNEL_12	12
#define ADC_CHANNEL_13	13
#define ADC_CHANNEL_14	14

// Resolution values
#define ADC_RESOLUTION_10_BIT	1
#define ADC_RESOLUTION_12_BIT	0

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
	uint32_t unused1[2];
	// Channel Enable Register, offset 0x0010
	uint32_t ADC_CHER;
	// Channel Disable Register, offset 0x0014
	uint32_t ADC_CHDR;
	// Channel Status Register, offset 0x0018
	uint32_t ADC_CHSR;
	uint32_t reserved[1];
	// Last Converted Data Register, offset 0x0020
	uint32_t ADC_LCDR;
	uint32_t unused2[3];
	// Interrupt Status Register, offset 0x0030
	uint32_t ADC_ISR;
	uint32_t unused3[7];
	// Channel Data Register, offset 0x0050
	uint32_t ADC_CDR[0];

} adc_reg_t;

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
 * @return Returns error code, 0 if everything went okay, 1 means illegal values.
 */
uint8_t adc_init(adc_settings_t * adc_settings);

/**
 * Starts the ADC.
 * @return Return 1 if started.
 */
void adc_start(void);

/**
 * Resets the ADC.
 * @return Return 1 if stopped.
 */
void adc_reset(void);

/**
 * Sets ADC resolution to 10 bits or 12 bits. 12 bits is default after initiation.
 * @param resolution The resolution of the ADC.
 * @return Returns 1 if correctly set or 0 if not correct set (10 or 12-bit not used as input).
 */
void adc_set_resolution(uint32_t resolution);

/**
 * Enables a specific channel. Channel 0 - 15 is available.
 * Channel 15 is used for temperature-reader.
 * @param channel The channel (0-15) that is to be enabled.
 * @return If not in the range 0-15 or channel does not become enabled, 0 is returned. Otherwise 1.
 */
void adc_enable_channel(uint32_t channel);

/**
 * Disables a specific channel. Channel 0-15 is available.
 * @param channel The channel (0-15) that is to be disabled.
 * @return If not in the range 0-15 or channel does not become disabled, 0 is returned. Otherwise 1.
 */
void adc_disable_channel(uint32_t channel);

/**
 * Reads the status for a specific channel. Channel 0-15 is available for readout.
 * @param channel The channel (0-15) that the status is asked for.
 * @return If the channel is enabled, returns 1. Otherwise returns 0.
 */
uint32_t adc_channel_enabled(uint32_t channel);

/**
 * Read the values from a specific channel. Channel 0-15 is available.
 * @param channel The channel (0-15) that is to be read from.
 * @return ADC value of the specific channel.
 */
uint32_t adc_read_channel(uint32_t channel);
#endif
