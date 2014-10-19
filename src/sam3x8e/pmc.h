/**
 * @file pmc.h
 * @brief PMC - Power Management Controller
 * @details The PMC API is used to handle internal clocks on the SAM3XAE.
 *
 * @author Felix Ruponen
 * @author Mattias Nilsson
 * @author Saeed Ghasemi
 * @author Mathias Beckius
 * @author Andreas Drotth
 * @date 16 October 2014
 */

#ifndef PMC_H_
#define PMC_H_

#include <inttypes.h>
#include "id.h"				// Definitions of Peripheral Identifiers

///@cond
// Pointer to registers of the PMC peripheral.
#define PMC ((pmc_reg_t *) 0x400E0600U)

// Main Crystal Oscillator Enable
#define PMC_CKGR_MOR_MOSCXTEN 		(1u)
// Main Crystal Oscillator Start-up Time
#define PMC_CKGR_MOR_MOSCXTST 		(62u << 8)
// Password
#define PMC_CKGR_MOR_KEY 			(0x37u << 16)
// Main Oscillator Selection
#define PMC_CKGR_MOR_MOSCSEL		(1u << 24)

// Main XTAL Oscillator Status
#define PMC_SR_MOSCXTS				(1u)
// PLLA Lock Status
#define PMC_SR_LOCKA				(2u)
// Master Clock Status
#define PMC_SR_MCKRDY				(1 << 3)
// Main Oscillator Selection Status
#define PMC_SR_MOSCSELS				(1u << 16)

// Divider is bypassed
#define CKGR_PLLAR_DIVA_BYPASS		(1u)
// PLLA Counter
#define CKGR_PLLAR_PLLACOUNT		(0x3fU << 8)
// PLLA Multiplier
#define CKGR_PLLAR_MULA				(13u << 16)
// ONE: Must Be Set to 1 (when programming the CKGR_PLLAR register)
#define CKGR_PLLAR_ONE				(1u << 29)

// Master Clock Source Selection: PLLA Clock is selected
#define PMC_MCKR_CSS_PLLA_CLK		(2)
// Master Clock Source Selection
#define PMC_MCKR_CSS(selection)	\
	((PMC->PMC_MCKR & (~(0x3u))) | (selection))
// Processor Clock Prescaler
#define PMC_MCKR_PRES(prescaler) \
	((PMC->PMC_MCKR & (~(0x7u << 4))) | prescaler)

/*
 * Mapping of PMC registers
 * Base address: 0x400E0600
 */
typedef struct {
	// System Clock Enable Register, offset 0x0000
	uint32_t PMC_SCER;
	// System Clock Disable Register, offset 0x0004
	uint32_t PMC_SCDR;
	// System Clock Status Register, offset 0x0008
	uint32_t PMC_SCSR;
	// reserved, offset 0x000C
	uint32_t reserved1[1];
	// Peripheral Clock Enable Register 0, offset 0x0010
	uint32_t PMC_PCER0;
	// Peripheral Clock Disable Register 0, offset 0x0014
	uint32_t PMC_PCDR0;
	// Peripheral Clock Status Register 0, offset 0x0018
	uint32_t PMC_PCSR0;
	// UTMI Clock Register, offset 0x001C
	uint32_t CKGR_UCKR;
	// Main Oscillator Register, offset 0x0020
	uint32_t CKGR_MOR;
	// Main Clock Frequency Register, offset 0x0024
	uint32_t CKGR_MCFR;
	// PLLA Register, offset 0x0028
	uint32_t CKGR_PLLAR;
	// reserved, offset 0x002C
	uint32_t reserved2[1];
	// Master Clock Register, offset 0x0030
	uint32_t PMC_MCKR;
	// reserved, offset 0x0034
	uint32_t reserved3[1];
	// USB Clock Register, offset 0x0038
	uint32_t PMC_USB;
	// reserved, 0x003C
	uint32_t reserved4[1];
	// Programmable Clock 0-2 Register, offset 0x0040-0x0048
	uint32_t PMC_PCK[3];
	// reserved, offset 0x004C-0x005C
	uint32_t reserved5[5];
	// Interrupt Enable Register, offset 0x0060
	uint32_t PMC_IER;
	// Interrupt Disable Register, offset 0x0064
	uint32_t PMC_IDR;
	// Status Register, offset 0x0068
	uint32_t PMC_SR;
	// Interrupt Mask Register, offset 0x006C
	uint32_t PMC_IMR;
	// Fast Startup Mode Register, offset 0x0070
	uint32_t PMC_FSMR;
	// Fast Startup Polarity Register, offset 0x0074
	uint32_t PMC_FSPR;
	// Fault Output Clear Register, offset 0x0078
	uint32_t PMC_FOCR;
	// reserved, offset 0x007C-0x00E0
	uint32_t reserved6[26];
	// Write Protect Mode Register, offset 0x00E4
	uint32_t PMC_WPMR;
	// Write Protect Status Register, offset 0x00E8
	uint32_t PMC_WPSR;
	// Reserved, offset 0x00EC-0x00FC
	uint32_t reserved7[5];
	// Peripheral Clock Enable Register 1, offset 0x0100
	uint32_t PMC_PCER1;
	// Peripheral Clock Disable Register 1, offset 0x0104
	uint32_t PMC_PCDR1;
	// Peripheral Clock Status Register 1, offset 0x0108
	uint32_t PMC_PCSR1;
	// Peripheral Control Register, offset 0x010C
	uint32_t PMC_PCR;
} pmc_reg_t;
///@endcond

/**
 * Initializes the system clock, must be performed during system initialization.
 * @pre Set Flash Wait State.
 */
void pmc_init_system_clock(void);

/**
 * Enable peripheral clock.
 * @param id Peripheral Identifier
 * Nothing will happen if the specified Peripheral Identifier is out of bounds.
 */
void pmc_enable_peripheral_clock(uint32_t id);

/**
 * Disable peripheral clock.
 * @param id Peripheral Identifier
 * Nothing will happen if the specified Peripheral Identifier is out of bounds.
 */
void pmc_disable_peripheral_clock(uint32_t id);

/**
 * Is peripheral clock enabled?
 * @param id Peripheral Identifier
 * @return If the peripheral clock is enabled, return 1, otherwise 0.
 * @return 0 is also returned if the specified Peripheral Identifier
 * is out of bounds.
 */
uint32_t pmc_peripheral_clock_enabled(uint32_t id);

#endif
