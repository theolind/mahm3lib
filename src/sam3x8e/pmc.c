/**
 * pmc.c
 *
 * Authors:
 * 		Felix Ruponen
 * 		Mattias Nilsson
 *		Saeed Ghasemi
 *		Mathias Beckius
 *
 * Date: 27 September 2014
 */

#include "pmc.h"

///@cond

// Highest Peripheral Identifier value to be used with register 0.
#define REG_0_ID_MAX	31

// Bit mask for Peripheral Identifier, to be used with register 0.
#define REG_0_BIT_MASK(id) 	\
	(0x1u << (id))

// Bit mask for Peripheral Identifier, to be used with register 1.
#define REG_1_BIT_MASK(id) 	\
	(0x1u << ((id) - 32))

///@endcond

/*
 * These registers can only be written if the WPEN bit is cleared in
 * “PMC Write Protect Mode Register”.
 */
void pmc_enable_peripheral_clock(uint32_t id) {
	if (id <= REG_0_ID_MAX) {
		PMC->PMC_PCER0 = REG_0_BIT_MASK(id);
	} else {
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
	} else {
		PMC->PMC_PCDR1 = REG_1_BIT_MASK(id);
	}
}

uint8_t pmc_peripheral_clock_enabled(uint32_t id) {
	if (id <= REG_0_ID_MAX) {
		return (uint8_t)(PMC->PMC_PCSR0 & REG_0_BIT_MASK(id));
	} else {
		return (uint8_t)(PMC->PMC_PCSR1 & REG_1_BIT_MASK(id));
	}
}
