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

// MASER CLOCK SETTING //
#define PMC_CSS					(0x01U)		///<Master Clock Source Selection Bit Mask

#define PMC_CSS_SLOW_CLK		(0x0)		///<Master Clock Source Selection SLOW CLK
#define PMC_CSS_MAIN_CLK		(0x01)		///<Master Clock Source Selection MAIN CLK
#define PMC_CSS_PLLA_CLK		(0x02)		///<Master Clock Source Selection PLLA CLK
#define PMC_CSS_UPLL_CLK		(0x03)		///<Master Clock Source Selection UPLL CLK

#define PMC_PRESCALER			(0x01U << 4)	///<Processor Clock Prescaler Bit Mask

#define PMC_PRES_CLK_0			(0x0U)		///<Processor Clock Prescaler - Selected Clock
#define PMC_PRES_CLK_2			(0x1U)		///<Processor Clock Prescaler - Selected Clock / 2
#define PMC_PRES_CLK_4			(0x2U)		///<Processor Clock Prescaler - Selected Clock / 4
#define PMC_PRES_CLK_8			(0x3U)		///<Processor Clock Prescaler - Selected Clock / 8
#define PMC_PRES_CLK_16			(0x4U)		///<Processor Clock Prescaler - Selected Clock / 16
#define PMC_PRES_CLK_32			(0x5U)		///<Processor Clock Prescaler - Selected Clock / 32
#define PMC_PRES_CLK_64			(0x6U)		///<Processor Clock Prescaler - Selected Clock / 64
#define PMC_PRES_CLK_3			(0x7U)		///<Processor Clock Prescaler - Selected Clock / 3


#define PMC_SR_MCKRDY			(0x01U << 3)	///<Master Clock Status	0 = Not Ready 1 = Ready



//////////////////////////////////

// Start peripheral clock
uint8_t pmc_start_peripheral_clock(uint32_t peripheral);

// Stop peripheral clock
uint8_t pmc_stop_peripheral_clock(uint32_t peripheral);

// Get peripheral clock status
uint8_t pmc_status_peripheral_clock(uint32_t peripheral);

// Set peripheral prescaler
uint8_t pmc_set_peripheral_prescaler(void);

// Set to sleep mode, provide wakeup method
uint8_t pmc_sleep(void);

// Set master clock
uint8_t pmc_set_master_clock(uint32_t clock);


#endif /* PMC_H_ */
