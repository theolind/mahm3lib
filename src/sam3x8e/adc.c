/**
 * @file
 * @brief Analog to Digital Converter (ADC)
 * @details This class is used to read values from the ADC-channels
 * @author Hisham Ramish
 * @author Mattias Nilsson
 * @author Prince Balabis
 * @version 0.4
 * @date 17 sep 2014
 * @pre As it is now, the ADC is very much stripped down. All functions not included.
 * @bug No known bugs.
 */

///\cond
#include "global_definitions.h"
#include <inttypes.h>
#include "adc.h"

// Pointers to ADC-registers
uint32_t *const p_ADC_CR 	= (uint32_t *) 0x400C0000u;	// ADC Control Register
uint32_t *const p_ADC_MR 	= (uint32_t *) 0x400C0004u;	// ADC Mode Register
uint32_t *const p_ADC_CHER 	= (uint32_t *) 0x400C0010u;	// ADC Channel Enable Register
uint32_t *const p_ADC_CHDR 	= (uint32_t *) 0x400C0014u;	// ADC Channel Disable Register
uint32_t *const p_ADC_CHSR 	= (uint32_t *) 0x400C0018u;	// ADC Channel Status Register
uint32_t *const p_ADC_LCDR 	= (uint32_t *) 0x400C0020u;	// ADC Last Converted Data Register
uint32_t *const p_ADC_CDR 	= (uint32_t *) 0x400C0050u;	// ADC Channel Data Register 0
uint32_t *const p_ADC_ISR 	= (uint32_t *) 0x400C0030u;	// ADC Interrupts Status Register

///\endcond


/**
 * Initializes the ADC.
 */
void adc_init(void) {

	// Enable Peripheral clock
	 pmc_start_peripheral_clock(ID_ADC);

	// Software reset
	ADC_CR = (0x1u << 0);

	// Reset Mode Register
	ADC_MR = (0);

	// Set ADC clock (prescaler set to 2)
	// Set start-up time to zero
	ADC_MR |= ((0xFFu << 8) & (2 << 8)) | ((0 << 16) & (0xFu << 8));

}

/**
 * Starts the ADC.
 * @return Return 1 if started.
 */
uint8_t adc_start(void) {
	ADC_CR = (0x1u << 1);
	return 1;
}

/**
 * Stops the ADC.
 * @return Return 1 if stopped.
 */
uint8_t adc_stop(void) {
	ADC_CR = (0x1u << 0);
	return 1;
}

/**
 * Sets ADC resolution to 10 bits or 12 bits. 12 bits is default after initiation.
 * @param resolution The resolution of the ADC.
 * @return Returns 1 if correctly set or 0 if not correct set (10 or 12-bit not used as input).
 */
uint8_t adc_set_resolution(uint8_t resolution){

	if(resolution == 12) {
		ADC_MR = (0x0u << 4);
		return 1;
	} else if(resolution == 10) {
		ADC_MR = (0x1u << 4);
		return 1;
	}
	return 0;
}

/**
 * Enables a specific channel. Channel 0 - 15 is available.
 * Channel 15 is used for temperature-reader.
 * @param ADC_CHANNEL The channel (0-15) that is to be enabled.
 * @return If not in the range 0-15 or channel does not become enabled, 0 is returned. Otherwise 1.
 */
uint8_t adc_enable_channel(uint8_t ADC_CHANNEL) {
	if(ADC_CHANNEL <0 || ADC_CHANNEL > 15){
		return 0;
	}
	else {
	ADC_CHER = (0x1u << ADC_CHANNEL);

	if(ADC_CHSR & (0x1u << ADC_CHANNEL)) {
		return 1;
	} else {
		return 0;
	}
	}
}

/**
 * Disables a specific channel. Channel 0-15 is available.
 * @param ADC_CHANNEL The channel (0-15) that is to be disabled.
 * @return If not in the range 0-15 or channel does not become disabled, 0 is returned. Otherwise 1.
 */
uint8_t adc_disable_channel(uint8_t ADC_CHANNEL) {

	ADC_CHDR = (uint32_t)(1 << ADC_CHANNEL);

	if(ADC_CHSR & (0x1u << ADC_CHANNEL)) {
		return 0;
	} else {
		return 1;
	}

}

/**
 * Reads the status for a specific channel. Channel 0-15 is available for readout.
 * @param ADC_CHANNEL The channel (0-15) that the status is asked for.
 * @return If the channel is enabled, returns 1. Otherwise returns 0.
 */
uint8_t adc_get_channel_status(uint8_t ADC_CHANNEL) {

	if(ADC_CHSR & (0x1u << ADC_CHANNEL)) {
			return 1;
		} else {
			return 0;
		}

}

/**
 * Read the values from a specific channel. Channel 0-15 is available.
 * @param ADC_CHANNEL The channel (0-15) that is to be read from.
 * @return ADC value of the specific channel.
 */
uint32_t adc_read_channel(uint32_t ADC_CHANNEL) {

	ADC_CR = (0x1u << 1);

	while(!(ADC_ISR & 0x01000000));

	uint32_t data = *(p_ADC_CDR + ADC_CHANNEL);

	ADC_CR = (0x1u << 1);

	return data;
}
