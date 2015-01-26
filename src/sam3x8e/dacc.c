/*
 * dacc.c
 *
 * Author:	Jonathan Bjarnason,
 * 			Andreas Drotth,
 * 			Mathias Beckius
 *
 * Date: 30 September 2014
 */

#include "pmc.h"
#include "dacc.h"

void dacc_init(const dacc_settings_t *settings) {
	// Software reset
	DACC->DACC_CR = (0x1u << 0);
	// Word transfer
	DACC->DACC_MR |= (settings->word_transfer << DACC_MR_WORD_POS);
	// Refresh period
	DACC->DACC_MR |= (settings->refresh << DACC_MR_REFRESH_POS);
	// Max speed mode
	DACC->DACC_MR |= (settings->speed_mode << DACC_MR_MAXS_POS);
	// Startup time selection
	DACC->DACC_MR |= (settings->startup_time << DACC_MR_STARTUP_POS);
}

void dacc_enable_channel(uint32_t channel) {
	if (channel <= DACC_CHANNEL_MAX) {
		DACC->DACC_CHER = (0x1u << channel);
	}
}

void dacc_disable_channel(uint32_t channel) {
	if (channel <= DACC_CHANNEL_MAX) {
		DACC->DACC_CHDR = (0x1u << channel);
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

uint32_t dacc_tx_ready(void) {
	return (DACC->DACC_ISR & DACC_ISR_TXRDY_MSK);
}

/*
* If transfer mode is set to HALF-WORD then only DACC_CHR[15:0]
* is used whereby [11:0] make up the actual output data.
* If transfer mode is set to WORD then all bits are used whereby
* [15:0] is converted first and afterwards the [31:16] bits.
*/
void dacc_write(uint32_t value) {
	if (value <= DACC_MAX_RESOLUTION) {
		DACC->DACC_CDR = value;
	}
}
