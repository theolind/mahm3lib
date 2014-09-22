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

/**
 * No idea as to why these should be defined here as these should not be
 * accessed outside the API, or should they?
 * @author Saeed Ghasemi
 * @param peripheral
 * @return
 */
/*
// REGISTERS //
#define PMC_PCER0	(*p_PMC_PCER0)	///< PMC Peripheral Clock Enable Register 0
#define PMC_PCDR0	(*p_PMC_PCDR0)	///< PMC Peripheral Clock Disable Register 0
#define PMC_PCSR0	(*p_PMC_PCSR0)	///< PMC Peripheral Clock Status Register 0

#define PMC_PCER1	(*p_PMC_PCER1)	///< PMC Peripheral Clock Enable Register 1
#define PMC_PCDR1	(*p_PMC_PCDR1)	///< PMC Peripheral Clock Disable Register 1
#define PMC_PCSR1	(*p_PMC_PCSR1)	///< PMC Peripheral Clock Status Register 1

#define PMC_MCKR	(*p_PMC_MCKR)	///<PMC Set Master Clock Register

#define PMC_SR		(*p_PMC_SR)		///<PMC Status Register
*/

/*    --     MOVED TO GLOBAL DEFINITIONS    ----
 * Can't call them PMC_ since they are global identifiers in the MCU
// PHERIPHERAL IDENTIFIERS //
#define PMC_PERIPHERAL_PIOA (11) ///<Peripheral PIOA
#define PMC_PERIPHERAL_PIOB (12) ///<Peripheral PIOB
#define PMC_PERIPHERAL_PIOC (13) ///<Peripheral PIOC
#define PMC_PERIPHERAL_PIOD (14) ///<Peripheral PIOD
#define PMC_PERIPHERAL_PIOE (15) ///<Peripheral PIOE
#define PMC_PERIPHERAL_PIOF (16) ///<Peripheral PIOF

#define PMC_PERIPHERAL_PWM (36) ///<Peripheral PWM
#define PMC_PERIPHERAL_ADC (37) ///<Peripheral ADC
#define PMC_PERIPHERAL_DACC	(38) ///<Peripheral DACC
*/


#define PMC_WAKE_ON_INTERUPT		(1)
#define PMC_WAKE_ON_EVENT			(0)
/////////////////////////////////////

// MASER CLOCK SETTING //
#define PMC_CSS					(0x01U)		///<Master Clock Source Selection Bit Mask

#define PMC_CLOCK_SLOW		(0)		///<Master Clock Source Selection SLOW CLK
#define PMC_CLOCK_MAIN		(1)		///<Master Clock Source Selection MAIN CLK
#define PMC_CLOCK_PLLA		(2)		///<Master Clock Source Selection PLLA CLK
#define PMC_CLOCK_UPLL		(3)		///<Master Clock Source Selection UPLL CLK

#define PMC_PRESCALER			(0x01U << 4)	///<Processor Clock Prescaler Bit Mask

#define PMC_PRES_0			(0)		///<Processor Clock Prescaler - Selected Clock
#define PMC_PRES_2			(1)		///<Processor Clock Prescaler - Selected Clock / 2
#define PMC_PRES_3			(7)		///<Processor Clock Prescaler - Selected Clock / 3
#define PMC_PRES_4			(2)		///<Processor Clock Prescaler - Selected Clock / 4
#define PMC_PRES_8			(3)		///<Processor Clock Prescaler - Selected Clock / 8
#define PMC_PRES_16			(4)		///<Processor Clock Prescaler - Selected Clock / 16
#define PMC_PRES_32			(5)		///<Processor Clock Prescaler - Selected Clock / 32
#define PMC_PRES_64			(6)		///<Processor Clock Prescaler - Selected Clock / 64


#define PMC_SR_MCKRDY_MASK		(0x01U << 3)	///<Master Clock Status	0 = Not Ready 1 = Ready
#define PMC_MCKR_PRES_MASK		(0x07U << 4)	///<Mask for the processor prescaler


//////////////////////////////////

// Start peripheral clock
uint8_t pmc_start_peripheral_clock(uint8_t ID_);

// Stop peripheral clock
uint8_t pmc_stop_peripheral_clock(uint8_t ID_);

// Get peripheral clock status
uint8_t pmc_status_peripheral_clock(uint8_t ID_);

// Set peripheral prescaler
uint8_t pmc_set_can_prescaler(uint8_t ID_, uint32_t device_prescaler_);

// Set to sleep mode, provide wakeup method
uint8_t pmc_sleep(uint8_t wake_on_);

// Sleep for a given amount of milliseconds
uint8_t pmc_sleep_for_ms(uint32_t ms);

// Set master clock
uint8_t pmc_set_master_clock(uint32_t clock);

uint8_t pmc_set_processor_clk(uint8_t pmc_processor_clk_prescaler_);

#endif /* PMC_H_ */
