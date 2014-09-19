/**
 * \class adc
 * \brief Analog to Digital Converter (ADC)
 * \details This class is used to read values from the ADC-channels
 * \author Hisham Ramish
 * \author Mattias Nilsson
 * \author Prince Balabis
 * \version 0.2
 * \date 17 sep 2014
 * \pre As it is now, the ADC is very much stripped down. All functions not included.
 * \bug Not working currently
 */


#include "adc.h"
#include <stdint.h>

///< Pointers to ADC-registers
uint32_t *const p_ADC_CR 	= (uint32_t *) 0x400C0000u;	///<ADC Control Register
uint32_t *const p_ADC_MR 	= (uint32_t *) 0x400C0004u;	///<ADC Mode Register
uint32_t *const p_ADC_CHER 	= (uint32_t *) 0x400C0010u;	///<ADC Channel Enable Register
uint32_t *const p_ADC_CHDR 	= (uint32_t *) 0x400C0014u;	///<ADC Channel Disable Register
uint32_t *const p_ADC_CHSR 	= (uint32_t *) 0x400C0018u;	///<ADC Channel Status Register
uint32_t *const p_ADC_LCDR 	= (uint32_t *) 0x400C0020u;	///<ADC Last Converted Data Register
uint32_t *const p_ADC_CDR0 	= (uint32_t *) 0x400C0050u;	///<ADC Channel Data Register 0

uint32_t *const p_PMC_PCER1	= (uint32_t *) 0x400E0700u;	///<PMC Peripheral Clock Status Register 1

uint32_t *const p_ADC_RCR 	= (uint32_t *) 0x400C0104u;	///<ADC Receive Counter Register
uint32_t *const p_ADC_RNCR 	= (uint32_t *) 0x400C0114u;	///<ADC Receive Next Pointer Register
uint32_t *const p_ADC_PTCR 	= (uint32_t *) 0x400C0120u;	///<ADC Transfer Control Register

uint32_t *const p_ADC_ISR 	= (uint32_t *) 0x400C0030u;	///<ADC Interrupts Status Register

uint32_t *const p_ADC_WPMR	= (uint32_t *) 0x400C00E4;	///<ADC Write Protect Mode Register

/**
 * Initializes the ADC.
 * @param adc_clk The frequency of the ADC-clock
 */
uint8_t adc_init(const uint32_t adc_clk){

	 //Unlocks ADC Mode Register
	//*p_ADC_WPMR = 0x41444300; //Disables the Write Protect if content corresponds to "ADC" in ASCII
	//*p_ADC_WPMR = (0x0 << 0);

	// Enable Peripheral clock
	*p_PMC_PCER1 = (1 << 5);

	// Software reset
	*p_ADC_CR = (0x1u << 0);

	// Reset Mode Register
	*p_ADC_MR = (0);

	// PDC Transfer Reset
	*p_ADC_PTCR = (0x1u << 1) | (0x1u << 9);
	*p_ADC_RCR = (0);
	*p_ADC_RNCR = (0);

	// Set ADC clock (prescaler set to 2)
	*p_ADC_MR |= ((0xFFu << 8) & (2 << 8)) | ((0 << 16) & (0xFu << 8));

	//*p_ADC_MR = (0x0 << 0); 	//Disables hardware triggers
	if (0x400C00E8 & 0x0u){
		return 1;
	}else{
		return 0;
	}

}

/**
 * Starts the ADC.
 */
uint8_t adc_start(){
	*p_ADC_CR = (0x1u << 1);
	return 1;
}

/**
 * Stops the ADC.
 */
uint8_t adc_stop(){
	*p_ADC_CR = (0x1u << 0);
	return 1;
}

/**
 * Sets ADC resolution to 10 bits or 12 bits. 12 bits is default after reset.(adc_init();)
 * @param resolution The resolution of the ADC.
 */
uint8_t adc_set_resolution(char resolution){

	if(resolution == 12){
		*p_ADC_MR = (0x0u << 4);
	} else if(resolution == 10){
		*p_ADC_MR = (0x1u << 4);
	}
	return 0;
}

/**
 * Enables a specific channel.
 * @param ADC_CHANNEL The channel that is to be enabled.
 */
uint8_t adc_enable_channel(char ADC_CHANNEL){

	*p_ADC_CHER = (0x1u << ADC_CHANNEL);

	if(*p_ADC_CHSR & (0x1u << ADC_CHANNEL)){
		return 1;
	} else{
		return 0;
	}
}

/**
 * Disables a specific channel.
 * @param ADC_CHANNEL The channel that is to be disabled.
 */
uint8_t adc_disable_channel(char ADC_CHANNEL){

	*p_ADC_CHDR = (uint32_t)(1 << ADC_CHANNEL);

	if(*p_ADC_CHSR & (0x1u << ADC_CHANNEL)){
		return 0;
	} else{
		return 1;
	}

}

/**
 * Reads the status for a specific channel.
 * @param ADC_CHANNEL The channel that the status is asked for.
 */
uint8_t adc_get_channel_status(char ADC_CHANNEL){

	if(*p_ADC_CHSR & (0x1u << ADC_CHANNEL)){
			return 1;
		} else{
			return 0;
		}

}

/**
 * Read the values from a specific channel.
 * @param ADC_CHANNEL The channel that is to be read from.
 * @return ADC value of the specific channel.
 */
uint16_t adc_read_channel(char ADC_CHANNEL){

	*p_ADC_CR = (0x1u << 1);

	while(!(*p_ADC_ISR & 0x01000000));

	uint16_t data = (uint16_t)(*p_ADC_LCDR & 0x00000FFFu);

	*p_ADC_CR = (0x1u << 1);

	return data;
}

/***
 * Read the last ADC result data.
 * @return ADC latest value.
 */
uint16_t adc_get_latest_value(){

	adc_start();
	//while((*p_ADC_ISR & 0x1u << 24) == 0);
	while(!(*p_ADC_ISR & 0x01000000));
	uint16_t data = *p_ADC_LCDR;
	return data;
}
