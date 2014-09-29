#include "pmc.h"
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

uint8_t dacc_init(const dacc_settings_t *settings){

	// Check for illegal values
	if(settings->trigger_mode>1||
			settings->word_transfer>1||
			settings->speed_mode>1||
			settings->startup_time>63){
		return 0;
	}

	// Software reset
	DACC_CR = (0x1u << 0);

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

void dacc_enable_channel(uint32_t channel) {
	if (channel <= DACC_CHANNEL_MAX) {
		DACC->DACC_CHER |= (0x1u << channel);
	}
}

void dacc_disable_channel(uint32_t channel) {
	if (channel <= DACC_CHANNEL_MAX) {
		DACC->DACC_CHDR |= (0x1u << channel);
	}
}

uint32_t dacc_channel_enabled(uint32_t channel) {
	if (channel <= DACC_CHANNEL_MAX) {
		return (DACC->DACC_CHSR & (0x1u << channel));
	} else {
		return 0;
	}
}

void dacc_select_channel(uint32_t channel) {
	if (channel <= DACC_CHANNEL_MAX) {
		DACC->DACC_MR |= (channel << DACC_MR_USER_SEL_POS);
	}
}

void dacc_write(uint32_t value){

	if (dacc_channel > 1 || value > DACC_MAX_RESOLUTION) {
		return 0;
	}

	//Check if converter is ready before sending new data
	while ( !( DACC_ISR & 0x1u << 0) );

	DACC_CDR = value;

	return 1;
}
