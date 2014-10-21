/*
 * tc.h
 * TC - Timer Counter
 * This API is used to control the three independent hardware timers.
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 20 Oktober 2014
 */

#include "tc.h"

// TODO: make macro mask function, works for now but mask is better
void tc_conf_channel(tc_channel_settings_t* set, tc_reg_t *tc, uint32_t channel) {
	if (channel > MAX_CHANNELS){
		return;
	}
	tc_channel_reg_t *tc_ch = tc->TC_CHANNEL + channel;

	// Common parameters
	tc_ch->TC_CMR = (set->tcclks << TC_CMR_TCCLKS_POS);
	tc_ch->TC_CMR |= (set->wave << TC_CMR_WAVE_POS);
	tc_ch->TC_CMR |= (set->clki << TC_CMR_CLKI_POS);
	tc_ch->TC_CMR |= (set->burst << TC_CMR_BURST_POS);

	if (set->wave == TC_CMR_CAPTURE_MODE){
		tc_ch->TC_CMR |= (set->ldbstop << TC_CMR_LDBSTOP_POS);
		tc_ch->TC_CMR |= (set->ldbdis << TC_CMR_LDBDIS_POS);
		tc_ch->TC_CMR |= (set->etrgedg << TC_CMR_ETRGEDG_POS);
		tc_ch->TC_CMR |= (set->abetrg << TC_CMR_ABETRG_POS);
		tc_ch->TC_CMR |= (set->cpctrg << TC_CMR_CPCTRG_POS);
		tc_ch->TC_CMR |= (set->ldra << TC_CMR_LDRA_POS);
		tc_ch->TC_CMR |= (set->ldrb << TC_CMR_LDRB_POS);
	}
	else if (set->wave == TC_CMR_WAVEFORM_MODE){
		tc_ch->TC_CMR |= (set->cpcstop << TC_CMR_CPCSTOP_POS);
		tc_ch->TC_CMR |= (set->cpcdis << TC_CMR_CPCDIS_POS);
		tc_ch->TC_CMR |= (set->eevtedg << TC_CMR_EEVTEDG_POS);
		tc_ch->TC_CMR |= (set->eevt << TC_CMR_EEVT_POS);
		tc_ch->TC_CMR |= (set->enetrg << TC_CMR_ENETRG_POS);
		tc_ch->TC_CMR |= (set->wavsel << TC_CMR_WAVSEL_POS);
		tc_ch->TC_CMR |= (set->acpa << TC_CMR_ACPA_POS);
		tc_ch->TC_CMR |= (set->acpc << TC_CMR_ACPC_POS);
		tc_ch->TC_CMR |= (set->aeevt << TC_CMR_AEEVT_POS);
		tc_ch->TC_CMR |= (set->aswtrg << TC_CMR_ASWTRG_POS);
		tc_ch->TC_CMR |= (set->bcpb << TC_CMR_BCPB_POS);
		tc_ch->TC_CMR |= (set->bcpc << TC_CMR_BCPC_POS);
		tc_ch->TC_CMR |= (set->beevt << TC_CMR_BEEVT_POS);
		tc_ch->TC_CMR |= (set->bswtrg << TC_CMR_BSWTRG_POS);
	}
}

void tc_conf_block(tc_block_settings_t* set, tc_reg_t *tc){
	tc->TC_BMR = (set->tc0xc0s << TC_BMR_TC0XC0S_POS);
	tc->TC_BMR |= (set->tc1xc1s << TC_BMR_TC1XC1S_POS);
	tc->TC_BMR |= (set->tc2xc2s << TC_BMR_TC2XCS2_POS);
	tc->TC_BMR |= (set->qden << TC_BMR_QDEN_POS);
	tc->TC_BMR |= (set->posen << TC_BMR_POSEN_POS);
	tc->TC_BMR |= (set->speeden << TC_BMR_SPEEDEN_POS);
	tc->TC_BMR |= (set->qdtrans << TC_BMR_QDTRANS_POS);
	tc->TC_BMR |= (set->edgpha << TC_BMR_EDGPHA_POS);
	tc->TC_BMR |= (set->inva << TC_BMR_INVA_POS);
	tc->TC_BMR |= (set->invb << TC_BMR_INVB_POS);
	tc->TC_BMR |= (set->invidx << TC_BMR_INVIDX_POS);
	tc->TC_BMR |= (set->swap << TC_BMR_SWAP_POS);
	tc->TC_BMR |= (set->idxphb << TC_BMR_IDXPHB_POS);
	tc->TC_BMR |= (set->filter << TC_BMR_FILTER_POS);
	tc->TC_BMR |= (set->maxfilt << TC_BMR_MAXFILT_POS);
}

void tc_enable_clock(tc_reg_t *tc, uint32_t channel) {
	if (channel < MAX_CHANNELS){
		tc->TC_CHANNEL[channel].TC_CCR = TC_CCR_CLKEN;
	}
}

void tc_disable_clock(tc_reg_t *tc, uint32_t channel){
	if (channel < MAX_CHANNELS){
		tc->TC_CHANNEL[channel].TC_CCR = TC_CCR_CLKDIS;
	}
}

void tc_start_clock(tc_reg_t *tc, uint32_t channel){
	if (channel < MAX_CHANNELS){
		tc->TC_CHANNEL[channel].TC_CCR |= TC_CCR_SWTRG;
	}
}

void tc_sync_block(tc_reg_t *tc){
	tc->TC_BCR = TC_BCR_SYNC;
}

uint32_t tc_read_counter_value(tc_reg_t * tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return 0;
	}
	return tc->TC_CHANNEL[channel].TC_CV;
}

uint32_t tc_read_reg_a(tc_reg_t * tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return 0;
	}
	return tc->TC_CHANNEL[channel].TC_RA;
}

uint32_t tc_read_reg_b(tc_reg_t * tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return 0;
	}
	return tc->TC_CHANNEL[channel].TC_RB;
}

uint32_t tc_read_reg_c(tc_reg_t * tc, uint32_t channel){
	if (channel > MAX_CHANNELS){
		return 0;
	}
	return tc->TC_CHANNEL[channel].TC_RC;
}

void tc_write_reg_a(tc_reg_t * tc, uint32_t channel, uint32_t value){
	if (channel < MAX_CHANNELS){
		tc->TC_CHANNEL[channel].TC_RA = value;
	}
}

void tc_write_reg_b(tc_reg_t * tc, uint32_t channel, uint32_t value){
	if (channel < MAX_CHANNELS){
		tc->TC_CHANNEL[channel].TC_RB = value;
	}
}

void tc_write_reg_c(tc_reg_t * tc, uint32_t channel, uint32_t value){
	if (channel < MAX_CHANNELS){
		tc->TC_CHANNEL[channel].TC_RC = value;
	}
}
