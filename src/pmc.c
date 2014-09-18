/*
 * pmc.c
 *
 *  Created on: 17 sep 2014
 *      Author: Felix (Modified by Saeed)
 */


#include <stdint.h>
#include "pmc.h"

uint32_t *const p_PMC_PCER0 = (uint32_t *) 0x400E0610U; // PMC Peripheral Clock Enable Register 0
uint32_t *const p_PMC_PCDR0 = (uint32_t *) 0x400E0614U; // PMC Peripheral Clock Disable Register 0
uint32_t *const p_PMC_PCSR0 = (uint32_t *) 0x400E0618U; // PMC Peripheral Clock Status Register 0

uint32_t *const p_PMC_PCER1 = (uint32_t *) 0x400E0700U; // PMC Peripheral Clock Status Register 1
uint32_t *const p_PMC_PCDR1 = (uint32_t *) 0x400E0704U; // PMC Peripheral Clock Status Register 1
uint32_t *const p_PMC_PCSR1 = (uint32_t *) 0x400E0708U; // PMC Peripheral Clock Status Register 1


// Adjusts a specified peripheral (0 - 44) to the correct mask-bit
uint32_t pmc_get_peripheral_mask(uint32_t peripheral, uint8_t reg){

	if(reg == 0){
		return (uint32_t)(0x01 << peripheral);
	}else{
		return (uint32_t)(0x01 << (peripheral - 32));	// Adjust to the correct bit
	}
}



// Start peripheral clock
uint8_t pmc_start_peripheral_clock(uint32_t peripheral){

	if(peripheral < 32){
		*p_PMC_PCER0 = pmc_get_peripheral_mask(peripheral, 0);
	}else{
		*p_PMC_PCER1 = pmc_get_peripheral_mask(peripheral, 1);
	}

	return 1;
}


// Stop peripheral clock
uint8_t pmc_stop_peripheral_clock(uint32_t peripheral){

	if(peripheral < 32){   // Check if peripheral is register 0
		*p_PMC_PCDR0 = pmc_get_peripheral_mask(peripheral, 0);
	}else if(peripheral > 32 && peripheral < 45){	// Check if peripheral is register 1
		*p_PMC_PCDR1 = pmc_get_peripheral_mask(peripheral, 1);
	}else{	// Out of bounds
		return 0;
	}

	return 1;
}

// Get peripheral clock status
uint8_t pmc_status_peripheral_clock(uint32_t peripheral){

	uint8_t status = 0;

	if(peripheral < 32){   // Check if peripheral is register 0

		if((*p_PMC_PCSR0 & pmc_get_peripheral_mask(peripheral, 0)) == 0)	// Status Enabled?
			status = 1;

	}else if(peripheral > 32 && peripheral < 45){	// Check if peripheral is register 0

		if((*p_PMC_PCSR1 & pmc_get_peripheral_mask(peripheral, 1)) > 0)	// Is Status Enabled?
			status = 1;

	}else{	// Out of bounds
		status = 0;
	}

	return status;
}

// Set peripheral prescaler
uint8_t pmc_set_peripheral_prescaler(defInput peripheral, defInput prescaler){

	return 0;
}

// Set to sleep mode, provide wakeup method
uint8_t pmc_sleep(){

	return 0;
}

// Set master clock
uint8_t pmc_set_master_clock(defInput clock){

	return 0;
}

