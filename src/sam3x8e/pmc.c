/**
 * pmc.c
 *
 * Authors:
 * 		Felix Ruponen
 * 		Mattias Nilsson
 *		Saeed Ghasemi
 *		Mathias Beckius
 *
 * Date: 16 October 2014
 */

#include "pmc.h"

///@cond

// Highest Peripheral Identifier value to be used with register 0.
#define REG_0_ID_MAX			31
// Bit mask for Peripheral Identifier, to be used with register 0.
#define REG_0_BIT_MASK(id)		(0x1u << (id))
// Bit mask for Peripheral Identifier, to be used with register 1.
#define REG_1_BIT_MASK(id)		(0x1u << ((id) - 32))

static uint32_t pmc_switch_mclk_to_pllack(uint32_t);

///@endcond

void pmc_init_system_clock(void) {
	// Enable Main XTAL oscillator
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~2u) | PMC_CKGR_MOR_KEY |
					PMC_CKGR_MOR_MOSCXTEN |	PMC_CKGR_MOR_MOSCXTST;

	// Wait to the Main XTAL oscillator is stabilized
	while (!(PMC->PMC_SR & PMC_SR_MOSCXTS));

	// select the Main Crystal Oscillator
	PMC->CKGR_MOR |= PMC_CKGR_MOR_KEY | PMC_CKGR_MOR_MOSCSEL;

	// check Main Oscillator Selection Status - Selection is in progress
	while (!(PMC->PMC_SR & PMC_SR_MOSCSELS));

	// Disable PLLA clock - Always stop PLL first!
	PMC->CKGR_PLLAR = CKGR_PLLAR_ONE;
	// set PMC clock generator
	PMC->CKGR_PLLAR = 	CKGR_PLLAR_ONE | CKGR_PLLAR_MULA |
						CKGR_PLLAR_DIVA_BYPASS | CKGR_PLLAR_PLLACOUNT;

	// wait for PLL to be locked
	while (!(PMC->PMC_SR & PMC_SR_LOCKA));

	/*
	 * Switch master clock source selection to PLLA clock,
	 * selected clock divided by 2.
	 */
	pmc_switch_mclk_to_pllack(1u << 4);
}

/*
 * Switch master clock source selection to PLLA clock.
 *
 * param: ul_pres Processor clock prescaler.
 *
 * ret 0 Success.
 * ret 1 Timeout error.
 */
static uint32_t pmc_switch_mclk_to_pllack(uint32_t ul_pres) {
	uint32_t ul_timeout;
	PMC->PMC_MCKR = PMC_MCKR_PRES(ul_pres);
	for (ul_timeout = 2048; !(PMC->PMC_SR & PMC_SR_MCKRDY); --ul_timeout) {
		if (ul_timeout == 0) {
			return 1;
		}
	}
	PMC->PMC_MCKR = PMC_MCKR_CSS(PMC_MCKR_CSS_PLLA_CLK);
	for (ul_timeout = 2048; !(PMC->PMC_SR & PMC_SR_MCKRDY); --ul_timeout) {
		if (ul_timeout == 0) {
			return 1;
		}
	}
	return 0;
}

/*
 * These registers can only be written if the WPEN bit is cleared in
 * “PMC Write Protect Mode Register”.
 */
void pmc_enable_peripheral_clock(uint32_t id) {
	if (id <= REG_0_ID_MAX) {
		PMC->PMC_PCER0 = REG_0_BIT_MASK(id);
	} else if (id <= ID_MAX) {
		PMC->PMC_PCER1 = REG_1_BIT_MASK(id);
	}
}

/*
 * These registers can only be written if the WPEN bit is cleared in
 * “PMC Write Protect Mode Register”.
 */
void pmc_disable_peripheral_clock(uint32_t id) {
	if (id <= REG_0_ID_MAX) {
		PMC->PMC_PCDR0 = REG_0_BIT_MASK(id);
	} else if (id <= ID_MAX) {
		PMC->PMC_PCDR1 = REG_1_BIT_MASK(id);
	}
}

uint32_t pmc_peripheral_clock_enabled(uint32_t id) {
	if (id <= REG_0_ID_MAX) {
		return (PMC->PMC_PCSR0 & REG_0_BIT_MASK(id));
	} else if (id <= ID_MAX) {
		return (PMC->PMC_PCSR1 & REG_1_BIT_MASK(id));
	} else {
		return 0;
	}
}
