/*
 * pmc.h
 *
 *  Created on: 17 sep 2014
 *      Author: felix (Modified by Saeed)
 */

#ifndef PMC_H_
#define PMC_H_

#include <stdint.h>
/////////////////////////////////////
typedef uint8_t error;
typedef uint32_t defInput;
/////////////////////////////////////
#define PMC_PERIPHERAL_PIOA (11)
#define PMC_PERIPHERAL_PIOB (12)
#define PMC_PERIPHERAL_PIOC (13)
#define PMC_PERIPHERAL_PIOD (14)
#define PMC_PERIPHERAL_PIOE (15)
#define PMC_PERIPHERAL_PIOF (16)

#define PMC_PERIPHERAL_PWM (36)
#define PMC_PERIPHERAL_ADC (37)
#define PMC_PERIPHERAL_DACC	(38)
/////////////////////////////////////
#define pmc_clock_Main			0
#define pmc_clock_slow_clock	0
#define pmc_clock_PLL			0
#define pmc_clock_ULLD //? look it up
/////////////////////////////////////
#define wake_on_interupt		1
#define wake_on_event			0
/////////////////////////////////////
// We do not want to use global variables!!!!!
// No need to do this at all!!
extern uint32_t *const p_PMC_PCER1;
extern uint32_t *const p_PMC_PCER0;
extern uint32_t *const p_PMC_PCDR0;
extern uint32_t *const p_PMC_PCSR0;

extern uint32_t *const p_PMC_PCDR1;
extern uint32_t *const p_PMC_PCSR1;

/////////////////////////////////////

// Start peripheral clock
error pmc_start_peripheral_clock(defInput peripheral);

// Stop peripheral clock
error pmc_stop_peripheral_clock(defInput peripheral);

// Get peripheral clock status
error pmc_status_peripheral_clock(defInput peripheral);

// Set peripheral prescaler
error pmc_set_peripheral_prescaler(defInput peripheral,
		defInput prescaler);

// Set to sleep mode, provide wakeup method
error pmc_sleep(void);

// Set master clock
error pmc_set_master_clock(defInput clock);



// Put processor to sleep
error api_pmc_sleep(defInput wake_on);
error api_pmc_choose_master_CLK(defInput clock);


#endif /* PMC_H_ */
