/**
 * \class pmc
 * \brief Power Managment Class (PMC)
 * \details Header for pmc.h
 * \author Felix Ruponen
 * \author Mattias Nilsson
 * \author Saeed Ghasemi
 * \version 0.1
 * \date 17 sep 2014
 */

#ifndef PMC_H_
#define PMC_H_

#include "global_definitions.h"

#define PMC_WAKE_ON_INTERUPT		(1)
#define PMC_WAKE_ON_EVENT			(0)
/////////////////////////////////////


// MASER CLOCK SETTING //
#define PMC_MCKR_CSS_MASK	(0x03U)	///<Master Clock Source Selection section Mask

#define PMC_CLOCK_SLOW		(0)		///<Master Clock Source Selection SLOW CLK
#define PMC_CLOCK_MAIN		(1)		///<Master Clock Source Selection MAIN CLK
#define PMC_CLOCK_PLLA		(2)		///<Master Clock Source Selection PLLA CLK
#define PMC_CLOCK_UPLL		(3)		///<Master Clock Source Selection UPLL CLK



#define PMC_PROCESSOR_PRES_1	(0)		///<Processor Clock Prescaler - Selected Clock
#define PMC_PROCESSOR_PRES_2	(1)		///<Processor Clock Prescaler - Selected Clock / 2
#define PMC_PROCESSOR_PRES_3	(7)		///<Processor Clock Prescaler - Selected Clock / 3
#define PMC_PROCESSOR_PRES_4	(2)		///<Processor Clock Prescaler - Selected Clock / 4
#define PMC_PROCESSOR_PRES_8	(3)		///<Processor Clock Prescaler - Selected Clock / 8
#define PMC_PROCESSOR_PRES_16	(4)		///<Processor Clock Prescaler - Selected Clock / 16
#define PMC_PROCESSOR_PRES_32	(5)		///<Processor Clock Prescaler - Selected Clock / 32
#define PMC_PROCESSOR_PRES_64	(6)		///<Processor Clock Prescaler - Selected Clock / 64


#define PMC_PRESCALER_MASK		(1 << 4)	///<Processor Clock Prescaler Bit Mask

#define PMC_SR_MCKRDY_MASK		(1 << 3)	///<Master Clock Status	0 = Not Ready 1 = Ready
#define PMC_MCKR_PRES_MASK		(7 << 4)	///<Section Mask for the processor prescaler position


//////////////////////////////////


// Start peripheral clock
uint8_t pmc_start_peripheral_clock(uint8_t ID_);

// Stop peripheral clock
uint8_t pmc_stop_peripheral_clock(uint8_t ID_);

// Get peripheral clock status
uint8_t pmc_status_peripheral_clock(uint8_t ID_);

// Set peripheral prescaler
uint8_t pmc_set_can_prescaler(uint8_t ID_, uint32_t CAN_PRES_);

// Set to sleep mode, provide wakeup method
uint8_t pmc_sleep(uint8_t PMC_WAKE_ON_);

// Sleep for a given amount of milliseconds
uint8_t pmc_sleep_for_ms(uint32_t ms);

// Set master clock
uint8_t pmc_select_master_clock(uint32_t PMC_CLOCK_);

// Set processor clock
uint8_t pmc_set_processor_clk(uint32_t PMC_PROCESSOR_PRES_);

#endif /* PMC_H_ */
