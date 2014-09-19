/**
 * @author Andreas Drotth
 * @author Jonathan Bjarnason
 */

#include "dacc.h"

uint32_t *const p_DACC_CR   = 	(uint32_t *)	0x400C8000U;
uint32_t *const p_DACC_MR   = 	(uint32_t *)	0x400C8004U;
uint32_t *const p_DACC_CHER = 	(uint32_t *) 	0x400C8010U;
uint32_t *const p_DACC_CHDR = 	(uint32_t *) 	0x400C8014U;
uint32_t *const p_DACC_CHSR = 	(uint32_t *) 	0x400C8018U;
uint32_t *const p_DACC_CDR  = 	(uint32_t *)	0x400C8020U;
uint32_t *const p_DACC_ISR  = 	(uint32_t *) 	0x400C8030U;
uint32_t *const p_DACC_WRMR = 	(uint32_t *)	0x400C80E4U;

uint8_t dacc_init(dacc_settings_t *){
	//Configure write protect to be able to actually configure settings
	//Configure startup time, sleep mode and possible fast wakeup?

	//Software reset
	*p_DACC_CR = (0x1u << 0);
}

uint8_t dacc_enable_channel(uint8_t dacc_channel){
	*p_DACC_CHER = (0x1u << dacc_channel);

	if (*p_DACC_CHSR & (0x1u << dacc_channel)){
		return 1;
	}
	else return 0;
}

uint8_t dacc_disable_channel(uint8_t dacc_channel){
	*p_DACC_CHER = (0x1u << dacc_channel);

	if (!(*p_DACC_CHSR & (0x1u << dacc_channel))){
		return 1;
	}
	else return 0;
}

uint8_t dacc_write(uint8_t dacc_channel, unit16_t value){
	//Check status flag, TXRDY
	while (!(*p_DACC_ISR & 0x1u << 0));
	//TODO: Write to conversion data register
}

uint8_t dacc_channel_enabled(uint8_t dacc_channel){
	if (*p_DACC_CHSR & (0x1u << dacc_channel)){
		return 1;
	}
	else return 0;
}
