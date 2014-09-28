/**
 * @file pmc.h
 * @brief Power Management Controller
 * @details The PMC API is used to handle internal clocks on the SAM3XAE.
 * @author Felix Ruponen
 * @author Mattias Nilsson
 * @author Saeed Ghasemi
 * @author Mathias Beckius
 * @date 27 September 2014
 * @pre Initialize the system clock.
 */

#ifndef PMC_H_
#define PMC_H_

#include <inttypes.h>
#include "id.h"			// Definitions of Peripheral Identifiers

// pointer to registers of the PMC, base address: 0x400E0600
#define PMC ((pmc_reg_t *) 0x400E0600U)

/*
 * Mapping of PMC registers
 * Base address: 0x400E0600
 */
typedef struct {
	uint32_t PMC_SCER;
	uint32_t PMC_SCDR;
	uint32_t PMC_SCSR;
	uint32_t reserved1;
	uint32_t PMC_PCER0;
	uint32_t PMC_PCDR0;
	uint32_t PMC_PCSR0;
	uint32_t CKGR_UCKR;
	uint32_t CKGR_MOR;
	uint32_t CKGR_MCFR;
	uint32_t CKGR_PLLAR;
	uint32_t reserved2;
	uint32_t PMC_MCKR;
	uint32_t reserved3;
	uint32_t PMC_USB;
	uint32_t reserved4;
	uint32_t PMC_PCK[3];
	// Reserved, offset 0x004C-0x005C
	uint32_t reserved5[5];
	uint32_t PMC_IER;
	uint32_t PMC_IDR;
	uint32_t PMC_SR;
	uint32_t PMC_IMR;
	uint32_t PMC_FSMR;
	uint32_t PMC_FSPR;
	uint32_t PMC_FOCR;
	// Reserved, offset 0x007C-0x00E0
	uint32_t reserved6[30];
	uint32_t PMC_WPMR;
	uint32_t PMC_WPSR;
	// Reserved, offset 0x00EC-0x00FC
	uint32_t reserved7[5];
	uint32_t PMC_PCER1;
	uint32_t PMC_PCDR1;
	uint32_t PMC_PCSR1;
	uint32_t PMC_PCR;
} pmc_reg_t;

/**
 * Enable peripheral clock.
 * @param id Peripheral Identifier
 */
void pmc_enable_peripheral_clock(uint32_t id);

/**
 * Disable peripheral clock.
 * @param id Peripheral Identifier
 */
void pmc_disable_peripheral_clock(uint32_t id);

/**
 * Is peripheral clock enabled?
 * @param id Peripheral Identifier
 * @return If the peripheral clock is enabled, return 1, otherwise 0.
 */
uint8_t pmc_peripheral_clock_enabled(uint32_t id);

#endif
