/*
 * pmc.c
 *
 *  Created on: 17 sep 2014
 *      Author: felix
 */

#include "pmc.h"
#include<stdint.h>

/*
uint32_t *const p_PCM_SCER = (uint32_t *) 0x400E0600U;  // PMC System Clock Enable Register
uint32_t *const p_PMC_SCDR = (uint32_t *) 0x400E0604U;  // PMC System Clock Disable Register
uint32_t *const p_PMC_SCSR = (uint32_t *) 0x400E0608U;  // PMC System Clock Status Register
uint32_t *const p_PMC_PCER0 = (uint32_t *) 0x400E0610U; // PMC Peripheral Clock Enable Register 0
uint32_t *const p_PMC_PCDR0 = (uint32_t *) 0x400E0614U; // PMC Peripheral Clock Disable Register 0
uint32_t *const p_PMC_PCSR0 = (uint32_t *) 0x400E0618U; // PMC Peripheral Clock Status Register 0
uint32_t *const p_CKGR_UCKR = (uint32_t *) 0x400E061CU; // PMC UTMI Clock Configuration Register

uint32_t *const p_CKGR_MOR = (uint32_t *) 0x400E0620U;  // PMC Clock Generator Main Oscillator Register

// Main On-Chip Oscillator Frequency
#define MOSCRCF			(0x01 << 4)

#define MOSCRCF_4MHZ 	(0x0U)
#define MOSCRCF_8MHZ 	(0x1)
#define MOSCRCF_12MHZ 	(0x2)


uint32_t *const p_PMC_MCKR = (uint32_t *) 0x400E0630;  // PMC Master Clock Register

// Master Clock Source Selection
#define MCKR_CSS	(0x01U)

#define MCKR_SLOW_CLK	(0x0U)
#define MCKR_MAIN_CLK	(0x01U)
#define MCKR_PLLA_CLK	(0x02U)
#define MCKR_UPLL_CLK	(0x03U)


uint32_t *const p_PMC_WPMR = (uint32_t *) 0x400E06E4;  // PMC Write Protect Mode Register

// Write Protect Mode Bit Enable/Disable
#define PCM_WPMR_WPEN	(0x01U)

// Write Protect Mode Key
*/































