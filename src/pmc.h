/*
 * pmc.h
 *
 *  Created on: 17 sep 2014
 *      Author: felix
 */

#ifndef PMC_H_
#define PMC_H_

#include <stdint.h>

#define PMC_PERIPHERAL_ADC (37)
#define PMC_PERIPHERAL_DACC	(38)
#define PMC_PERIPHERAL_PIOB (12)


extern uint32_t *const p_PMC_PCER1;
extern uint32_t *const p_PMC_PCER0;
extern uint32_t *const p_PMC_PCDR0;
extern uint32_t *const p_PMC_PCSR0;

extern uint32_t *const p_PMC_PCDR1;
extern uint32_t *const p_PMC_PCSR1;



// Start peripheral clock
uint8_t pmc_start_peripheral_clock(uint32_t peripheral);

// Stop peripheral clock
uint8_t pmc_stop_peripheral_clock(uint32_t peripheral);

// Get peripheral clock status
uint8_t pmc_status_peripheral_clock(uint32_t peripheral);

// Set peripheral prescaler
uint8_t pmc_set_peripheral_prescaler();

// Set to sleep mode, provide wakeup method
uint8_t pmc_sleep();

// Set master clock
uint8_t pmc_set_master_clock();

#endif /* PMC_H_ */
