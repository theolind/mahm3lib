#include "dacc.h"

uint32_t *const p_DACC_CR   = (uint32_t *) 0x400C8000U;
uint32_t *const p_DACC_MR   = (uint32_t *) 0x400C8004U;
uint32_t *const p_DACC_CHER = (uint32_t *) 0x400C8010U;
uint32_t *const p_DACC_CHDR = (uint32_t *) 0x400C8014U;
uint32_t *const p_DACC_CHSR = (uint32_t *) 0x400C8018U;
uint32_t *const p_DACC_CDR  = (uint32_t *) 0x400C8020U;
uint32_t *const p_DACC_ISR  = (uint32_t *) 0x400C8030U;
uint32_t *const p_DACC_WRMR = (uint32_t *) 0x400C80E4U;
uint32_t *const p_DACC_WPSR = (uint32_t *) 0x400C80E8U;

// TODO: should be unnecessary after PMC API is done
uint32_t *const p_PMC_PCER1	= (uint32_t *) 0x400E0700U;

uint8_t dacc_init(dacc_settings_t *settings){

	// Check for illegal values
	if(settings->trigger_mode>1||
			settings->word_transfer>1||
			settings->speed_mode>1||
			settings->startup_time>63){
		return 0;
	}

	// TODO: change to PMC API when that's done
	// Enable Peripheral clock for DACC
	PMC_PCER1 |= (1 << 6);

	// Software reset
	DACC_CR = (0x1u << 0);

	// TODO: Fix five warnings below
	// Trigger mode
	DACC_MR |= (settings->trigger_mode << 0);

	// Word transfer
	DACC_MR |= (settings->word_transfer << 4);

	// Refresh period
	DACC_MR |= (settings->refresh << 8);

	// Max speed mode
	DACC_MR |= (settings->speed_mode << 21);

	// Startup time selection
	DACC_MR |= (settings->startup_time << 24);

	return 1;
}

uint8_t dacc_enable_channel(uint8_t dacc_channel) {

	if (dacc_channel > 1) {
		return 0;
	}

	DACC_CHER |= (0x1u << dacc_channel);

	if ( *p_DACC_CHSR & (0x1u << dacc_channel) ) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t dacc_disable_channel(uint8_t dacc_channel){

	if (dacc_channel > 1) {
		return 0;
	}

	DACC_CHER |= (0x1u << dacc_channel);

	if ( !(*p_DACC_CHSR & (0x1u << dacc_channel)) ) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t dacc_channel_enabled(uint8_t dacc_channel){

	if (dacc_channel > 1) {
		return 0;
	}

	if ( *p_DACC_CHSR & (0x1u << dacc_channel) ) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t dacc_write(uint8_t dacc_channel, uint32_t value){

	if (dacc_channel > 1 || value > 4095) {
		return 0;
	}

	//TODO: Fix conversion warning
	DACC_MR |= (dacc_channel << 16);

	//Check if converter is ready before sending new data
	while ( !(*p_DACC_ISR & 0x1u << 0) );

	DACC_CDR = value;

	return 1;
}
