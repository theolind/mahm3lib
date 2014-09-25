#include "global_entities.h"
#include "dacc.h"

uint32_t *const p_dacc_cr   = (uint32_t *) 0x400C8000U;
uint32_t *const p_dacc_mr   = (uint32_t *) 0x400C8004U;
uint32_t *const p_dacc_cher = (uint32_t *) 0x400C8010U;
uint32_t *const p_dacc_chdr = (uint32_t *) 0x400C8014U;
uint32_t *const p_dacc_chsr = (uint32_t *) 0x400C8018U;
uint32_t *const p_dacc_cdr  = (uint32_t *) 0x400C8020U;
uint32_t *const p_dacc_isr  = (uint32_t *) 0x400C8030U;
uint32_t *const p_dacc_wrmr = (uint32_t *) 0x400C80E4U;
uint32_t *const p_dacc_wpsr = (uint32_t *) 0x400C80E8U;

uint8_t dacc_init(dacc_settings_t *settings){

	// Check for illegal values
	if(settings->trigger_mode>1||
			settings->word_transfer>1||
			settings->speed_mode>1||
			settings->startup_time>63){
		return 0;
	}

	// Enable Peripheral clock for DACC
	pmc_start_peripheral_clock(ID_DACC);

	// Software reset
	DACC_CR = (0x1u << 0);

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

	if ( DACC_CHSR & (0x1u << dacc_channel) ) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t dacc_disable_channel(uint8_t dacc_channel){

	if (dacc_channel > 1) {
		return 0;
	}

	DACC_CHDR |= (0x1u << dacc_channel);

	if ( !( DACC_CHSR & (0x1u << dacc_channel)) ) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t dacc_get_channel_status(uint8_t dacc_channel){

	if (dacc_channel > 1) {
		return 0;
	}

	if ( DACC_CHSR & (0x1u << dacc_channel) ) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t dacc_write(uint8_t dacc_channel, uint32_t value){

	if (dacc_channel > 1 || value > DACC_MAX_RESOLUTION) {
		return 0;
	}

	//TODO: Fix conversion warning
	DACC_MR |= (dacc_channel << 16);

	//Check if converter is ready before sending new data
	while ( !( DACC_ISR & 0x1u << 0) );

	DACC_CDR = value;

	return 1;
}
