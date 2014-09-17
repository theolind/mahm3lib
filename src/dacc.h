#ifndef DACC_H
#define DACC_H

#define DACC_CR 	(*p_DACC_CR)	// Control Register
#define DACC_MR		(*p_DACC_MR)	// Mode register, set triggers and such
#define DACC_CHER 	(*p_DACC_CER)	// Channel enable register
#define DACC_CHDR 	(*p_DACC_CHDR)	// Channel disable register
#define DACC_CHSR 	(*p_DACC_CSR)	// Channel status register
#define DACC_WRMR	(*p_DACC_WRMR)	// Write protect mode register, used to set write permissions
#define DACC_CDR	(*p_DACC_CDR)	// Conversion data register, where data is stored for write
#define DACC_ISR	(*p_DACC_ISR)	// Interrupt status register, only used for TXRDY to identify
					// when the DACC is ready to accept new conversion requests

//Initialize basic settings
uint8_t dacc_init(dacc_settings_t *);

//Enable a DACC channel
uint8_t dacc_enable_channel(uint8_t dacc_channel);

//Disable a DACC channel
uint8_t dacc_disable_channel(uint8_t dacc_channel);

//Write a value to a channel
uint8_t dacc_write(uint8_t pin, unit16_t value);

//Check if a channel is enabled
uint8_t dacc_channel_enabled(uint8_t dacc_channel);

#endif