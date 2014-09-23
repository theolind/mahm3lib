/**
 * @file
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

// The first register in the Power Management Controller
uint32_t *const p_pmc_base_add = (uint32_t *) 0x400E0600U;

/**
 *  Necessary registers addressed by incrementing the base address by an
 *  register-specific offset.
 */
#define PMC_PCER0 	*(p_pmc_base_add + 4) // Peripheral Clock Enable Register 0
#define PMC_PCDR0 	*(p_pmc_base_add + 5) // Peripheral Clock Disable Register 0
#define PMC_PCSR0 	*(p_pmc_base_add + 6) // Peripheral Clock Status Register 0
#define PMC_PCER1 	*(p_pmc_base_add + 64) // Peripheral Clock Enable Register 1
#define PMC_PCDR1 	*(p_pmc_base_add + 65) // Peripheral Clock Disable Register 1
#define PMC_PCSR1 	*(p_pmc_base_add + 66) // Peripheral Clock Status Register 1



// Remove the following if tests passes

/** Adjusts a specified peripheral (0 - 44) to the correct mask-bit.
 * Static, because it's an internal function to the API.
 *
 * @param ID_ The peripheral clock that get the mask-bit added.
 * @param reg Register 0 containing peripheral 0-31, register 1 containing peripheral 32-44
 */

static uint32_t pmc_get_peripheral_mask(uint8_t ID_) {
	if (ID_ < 32) {
		return (uint32_t) (0x01U << ID_);
	} else {
		return (uint32_t) (0x01U << (ID_ - 32));	// Adjust to the correct bit
	}
}

/** Start peripheral clock
 * @param ID_ Which peripheral clock that should be started.
 */
uint8_t pmc_start_peripheral_clock(uint8_t ID_) {
	if (ID_ < 32) {
		PMC_PCER0 |= pmc_get_peripheral_mask(ID_);
	} else {
		PMC_PCER1 |= pmc_get_peripheral_mask(ID_);
	}
	return SUCCESS;
}

/** Stop peripheral clock
 *
 * @param ID_ Which peripheral clock that should be stopped.
 */
uint8_t pmc_stop_peripheral_clock(uint8_t ID_) {
	if (ID_ < 32) {   // Check if peripheral is register 0
		PMC_PCDR0 = pmc_get_peripheral_mask(ID_);
	} else if (ID_ > 32 && ID_ < 45) {	// Check if peripheral is register 1
		PMC_PCDR1 = pmc_get_peripheral_mask(ID_);
	} else {	// Out of bounds
		return FAIL;
	}
	return SUCCESS;
}

/** Get peripheral clock status
 *
 * @param ID_ Shows the status of selected peripheral clock.
 */
uint8_t pmc_status_peripheral_clock(uint8_t ID_) {

	uint8_t status = FAIL;

	if (ID_ < 32) {   // Check if ID_ is register 0

		if ((PMC_PCSR0 & pmc_get_peripheral_mask(ID_)) == 0)  // Status Enabled?
			status = SUCCESS;

	} else if (ID_ > 32 && ID_ < 45) {	// Check if ID_ is register 0

		if ((PMC_PCSR1 & pmc_get_peripheral_mask(ID_)) > 0)	// Is Status Enabled?
			status = SUCCESS;

	} else {	// Out of bounds
		status = FAIL;
	}

	return status;
}
