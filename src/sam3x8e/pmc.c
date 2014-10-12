/**
 * pmc.c
 *
 * Authors:
 * 		Felix Ruponen
 * 		Mattias Nilsson
 *		Saeed Ghasemi
 *		Mathias Beckius
 *
 * Date: 29 September 2014
 */

#include "pmc.h"

///@cond

// Highest Peripheral Identifier value to be used with register 0.
#define REG_0_ID_MAX			31
// Bit mask for Peripheral Identifier, to be used with register 0.
#define REG_0_BIT_MASK(id)		(0x1u << (id))
// Bit mask for Peripheral Identifier, to be used with register 1.
#define REG_1_BIT_MASK(id)		(0x1u << ((id) - 32))

// ---------------------------------------------------------------------------
// BAD CODE!
// THIS CODE MUST BE REMOVED WHEN THE FUNCTIONS BELOW ARE IN GOOD SHAPE
// ---------------------------------------------------------------------------
//keep this until PMC->PMC_SR is fully working!
#define PMC_SR_ (*((volatile uint32_t *)0x400E0668U))
// ---------------------------------------------------------------------------
// END OF BAD CODE...
// ---------------------------------------------------------------------------

///@endcond

/*
 * Important!
 * PMC->PMC_SR might still be a little unreliable, won't work!
 */
void pmc_init_system_clock(void) {
	/* Config system clock setting - Already running from SYSCLK_SRC_MAINCK_4M_RC */
	//Internal 4MHz RC oscillator as master source clock
	/* Set PMC Clock Generator Main Oscillator Register:
	 * 	- Main Crystal Oscillator Bypass
	 * 	- Enable Main XTAL oscillator
	 * */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~2u) | PMC_CKGR_MOR_KEY | PMC_CKGR_MOR_MOSCXTBY | (62u << 8);
	//(PMC->CKGR_MOR & ~2u) | (0x37u << 16) | 1 | (62u << 8);

	// Wait to the Main XTAL oscillator is stabilized
	while (!(PMC_SR_ & 1u));
	//while (!(PMC->PMC_SR & 0x1u));

	// select the Main Crystal Oscillator
	PMC->CKGR_MOR |= (0x37 << 16) | (1 << 24);

	// oscillator ready? Main Oscillator Selection Status - Selection is in progress
	while ((PMC_SR_ & (1 << 16)) == 0);
	//while (!(PMC->PMC_SR & (1 << 16)));

	// Disable PLLA clock - Always stop PLL first!
	PMC->CKGR_PLLAR = (1 << 29);
	// set PMC clock generator
	PMC->CKGR_PLLAR = (1 << 29) | (13 << 16) | 1 | (0x3fU << 8);

	// wait for PLL to be locked
	while ((PMC_SR_ & 2) == 0);
	//while (!(PMC->PMC_SR & 2));

	// Switch master clock source selection to PLLA clock,
	// selected clock divided by 2
	pmc_switch_mclk_to_pllack(1 << 4);
}

/*
 * Switch master clock source selection to PLLA clock.
 *
 * param: ul_pres Processor clock prescaler.
 *
 * ret 0 Success.
 * ret 1 Timeout error.
 *
 * Important!
 * When everything's working, clean up and move this function to PMC API.
 * PMC->PMC_SR might still be a little unreliable, won't work in
 * systemclock_init().
 */
uint32_t pmc_switch_mclk_to_pllack(uint32_t ul_pres) {
	uint32_t ul_timeout;
	PMC->PMC_MCKR = (PMC->PMC_MCKR & (~(0x7u << 4))) | ul_pres;
	for (ul_timeout = 2048; !(PMC->PMC_SR & (1 << 3)); --ul_timeout) {
	//for (ul_timeout = 2048; (PMC_SR_ & (1 << 3)) == 0; --ul_timeout) {
		if (ul_timeout == 0) {
			return 1;
		}
	}
	PMC->PMC_MCKR = (PMC->PMC_MCKR & (~(0x3u))) | 2;
	for (ul_timeout = 2048; !(PMC->PMC_SR & (1 << 3)); --ul_timeout) {
	//for (ul_timeout = 2048; (PMC_SR_ & (1 << 3)) == 0; --ul_timeout) {
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
