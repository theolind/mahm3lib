/**
 * @file
 * @brief Analog-to-Digital Converter (ADC)
 * @details This class is used to read values from the ADC-channels.
 *
 * Important: Not all functionality of the ADC is implemented in this API yet.
 *
 * @author Hisham Ramish
 * @author Mattias Nilsson
 * @author Prince Balabis
 * @author Andreas Drotth
 * @date 27 September 2014
 *
 * @pre Initiate board and enable peripheral clock for ADC.
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

#define ADC_RESOLUTION_10_BIT	1
#define ADC_RESOLUTION_12_BIT	0

// To check if a provided ID is a valid channel
#define ADC_VALID_CHANNEL(channel) \
	((channel) >= 0 && (channel) <= 14)

/// @cond
// ADC_CR: (ADC Offset: 0x0000) Control Register
#define ADC_CR_START	(0x1u << 1)
#define ADC_CR_RESET	(0x1u << 0)

// ADC_MR: (ADC Offset: 0x0004) Mode Register
#define ADC_MR_RESET	(0)
#define ADC_MR_RES(resolution)	\
	((resolution) << 4)

#define ADC_STARTUP_0	(0 << 16)
#define ADC_PRESCAL_2	(2 << 8)

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
	uint32_t dummy1[2];
	// Channel Enable Register, offset 0x0010
	uint32_t ADC_CHER;
	// Channel Disable Register, offset 0x0014
	uint32_t ADC_CHDR;
	// Channel Status Register, offset 0x0018
	uint32_t ADC_CHSR;
	uint32_t reserved[1];
	// Last Converted Data Register, offset 0x0020
	uint32_t ADC_LCDR;
	uint32_t dummy2[3];
	// Interrupt Status Register, offset 0x0030
	uint32_t ADC_ISR;
	uint32_t dummy3[7];
	// Channel Data Register, offset 0x0050
	uint32_t ADC_CDR;

} adc_reg_t;
/// @endcond

/**
 * Initializes the ADC.
 * @return Returns error code, 0 if everything went okay, 1 means illegal values.
 */
uint8_t adc_init(void);

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
void adc_set_resolution(uint8_t resolution);

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
uint8_t adc_channel_enabled(uint32_t channel);

/**
 * Read the values from a specific channel. Channel 0-15 is available.
 * @param channel The channel (0-15) that is to be read from.
 * @return ADC value of the specific channel.
 */
uint32_t adc_read_channel(uint32_t channel);
#endif
