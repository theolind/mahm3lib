/**
 * \class pmc
 * \brief Power Managment Class (PMC)
 * \details This class is used to initiate internal clocks on SAM3XAE
 * \author Felix Ruponen
 * \author Mattias Nilsson
 * \author Saeed Ghasemi
 * \version 0.1
 * \date 17 sep 2014
 * \pre First initialize the system. Not all peripheral added yet.
 * \bug May still be bugs
 */

#include "global_definitions.h"
#include "pmc.h"

Reg p_PMC_BASE_ADD = (uint32_t *) 0x400E0610U;

#define PMC_PCER0 (p_PMC_BASE_ADD + 4);
#define PMC_PCDR0 (p_PMC_BASE_ADD + 5);
#define PMC_PCSR0 (p_PMC_BASE_ADD + 6);

Reg p_PMC_PCER0 = (uint32_t *) 0x400E0610U; ///< PMC Peripheral Clock Enable Register 0
Reg p_PMC_PCDR0 = (uint32_t *) 0x400E0614U; ///< PMC Peripheral Clock Disable Register 0
Reg p_PMC_PCSR0 = (uint32_t *) 0x400E0618U; ///< PMC Peripheral Clock Status Register 0

Reg p_PMC_PCER1 = (uint32_t *) 0x400E0700U; ///< PMC Peripheral Clock Status Register 1
Reg p_PMC_PCDR1 = (uint32_t *) 0x400E0704U; ///< PMC Peripheral Clock Status Register 1
Reg p_PMC_PCSR1 = (uint32_t *) 0x400E0708U; ///< PMC Peripheral Clock Status Register 1

Reg p_PMC_MCKR  = (uint32_t *) 0x400E0630U; ///< PMC Master Clock Register
Reg p_PMC_SR    = (uint32_t *) 0x400E0668; ///< PMC Status Register



/** Adjusts a specified peripheral (0 - 44) to the correct mask-bit
 *
 * @param peripheral The peripheral clock that get the mask-bit added.
 * @param reg Register 0 containing peripheral 0-31, register 1 containing peripheral 32-44
 */
uint32_t pmc_get_peripheral_mask(uint32_t peripheral, uint8_t reg){
	if(reg == 0){
		return (uint32_t)(0x01U << peripheral);
	}else{
		return (uint32_t)(0x01U << (peripheral - 32));	// Adjust to the correct bit
	}
}



/** Start peripheral clock
 * @param peripheral Which peripheral clock that should be started.
*/
uint8_t pmc_start_peripheral_clock(uint32_t peripheral){

	if(peripheral < 32){
		PMC_PCER0 = pmc_get_peripheral_mask(peripheral, 0);
	}else{
		PMC_PCER1 = pmc_get_peripheral_mask(peripheral, 1);
	}

	return 1;
}


/** Stop peripheral clock
 *
 * @param peripheral Which peripheral clock that should be stopped.
 */
uint8_t pmc_stop_peripheral_clock(uint32_t peripheral){

	if(peripheral < 32){   // Check if peripheral is register 0
		PMC_PCDR0 = pmc_get_peripheral_mask(peripheral, 0);
	}else if(peripheral > 32 && peripheral < 45){	// Check if peripheral is register 1
		PMC_PCDR1 = pmc_get_peripheral_mask(peripheral, 1);
	}else{	// Out of bounds
		return 0;
	}

	return 1;
}

/** Get peripheral clock status
 *
 * @param peripheral Shows the status of selected peripheral clock.
 */
uint8_t pmc_status_peripheral_clock(uint32_t peripheral){

	uint8_t status = 0;

	if(peripheral < 32){   // Check if peripheral is register 0

		if((PMC_PCSR0 & pmc_get_peripheral_mask(peripheral, 0)) == 0)	// Status Enabled?
			status = 1;

	}else if(peripheral > 32 && peripheral < 45){	// Check if peripheral is register 0

		if((PMC_PCSR1 & pmc_get_peripheral_mask(peripheral, 1)) > 0)	// Is Status Enabled?
			status = 1;

	}else{	// Out of bounds
		status = 0;
	}

	return status;
}

/** Set peripheral prescaler
 *
 */
uint8_t pmc_set_peripheral_prescaler(){

	return 0;
}

/** Set to sleep mode, provide wakeup method
 *
 */
uint8_t pmc_sleep(){

	return 0;
}

/** Set master clock
 *
 */
uint8_t pmc_set_master_clock(uint32_t clock){

	uint8_t status = 0;


	if(clock <= 7) {

			PMC_MCKR = clock;

			while((PMC_SR | PMC_SR_MCKRDY) == 0);	// Wait for masterclock ready

			status = 1;
	}

	return status;
}

