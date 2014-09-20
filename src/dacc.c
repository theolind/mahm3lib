/**
 * @author Andreas Drotth
 * @author Jonathan Bjarnason
 */

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

uint32_t *const p_PMC_PCER1	= (uint32_t *) 0x400E0700U;
uint32_t *const p_PMC_WPMR  = (uint32_t *) 0x400E06E4U;
uint32_t *const p_PMC_WPSR  = (uint32_t *) 0x400E06E8U;

/**
 * Initiates the DACC
 * @param settings Settings for DACC mode register
 * @return Return 1 if settings contain illegal values.
 * Return 2 if DACC encounters write protection errors.
 * Return 3 if PMC encounters write protection errors.
 * Otherwise return 0.
 */
uint8_t dacc_init(const dacc_settings_t *settings){

	// Check for illegal values
	if(settings->trigger_mode>1||
			settings->word_transfer>1||
			settings->max_speed_mode>1||
			settings->startup_time>64){
		return 1;
	}

	// Software reset
	DACC_CR = (0x1u << 0);

	// Disable write protect for DACC registers
	DACC_WRMR = 0x44414300;
	DACC_WRMR = (0x0 << 0);

	// Disable write protect for PMC registers
	PMC_WPMR = 0x504D4300;
	PMC_WPMR = (0x0 << 0);

	// Enable Peripheral clock for DACC
	PMC_PCER1 = (1 << 6);

	// Trigger mode
	DACC_MR = (settings->trigger_mode << 0);

	// Word transfer
	DACC_MR = (settings->word_transfer << 4);

	// Refresh period
	/* Not to sure if this will be assigned the right position. */
	DACC_MR = (settings->refresh << 8);

	// Max speed mode
	DACC_MR = (settings->max_speed_mode << 21);

	// Startup time selection
	DACC_MR = (settings->startup_time << 24);

	// Check for write protection errors
	if (DACC_WPSR & 0x0u){
		return 2;
		/*
		 * For future improvement:
		 * Alternatively return the address were the write protection error
		 * occurred
		 *
		 * return (DACC_WPSR & 0xFF00 >> 8);
		 */
	}

	if (PMC_WPSR & 0x0u){
		return 3;
		/*
		 * For future improvement:
		 * Alternatively return the address were the write protection error
		 * occurred
		 *
		 * return (PMC_WPSR & 0xFF00 >> 8);
		 */
	}

	return 0;
}

uint8_t dacc_enable_channel(uint8_t dacc_channel){
	//TODO: Check for parameters > 2

	*p_DACC_CHER = (0x1u << dacc_channel);

	if (*p_DACC_CHSR & (0x1u << dacc_channel)){
		return 1;
	}
	else return 0;
}

uint8_t dacc_disable_channel(uint8_t dacc_channel){
	//TODO: Check for parameters > 2

	*p_DACC_CHER = (0x1u << dacc_channel);

	if (!(*p_DACC_CHSR & (0x1u << dacc_channel))){
		return 1;
	}
	else return 0;
}

uint8_t dacc_write(uint8_t dacc_channel, uint16_t value){
	//Check status flag, TXRDY
	while (!(*p_DACC_ISR & 0x1u << 0));
	//TODO: Write to conversion data register
	return 1;
}

uint8_t dacc_channel_enabled(uint8_t dacc_channel){
	if (*p_DACC_CHSR & (0x1u << dacc_channel)){
		return 1;
	}
	else return 0;
}
