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

// The first register in the Power Management Controller
Reg p_PMC_BASE_ADD = (uint32_t *) 0x400E0600U;

/**
 *  Necessary registers addressed by incrementing the base address by an
 *  register-specific offset.
 */
#define PMC_PCER0 	*(p_PMC_BASE_ADD + 4) // Peripheral Clock Enable Register 0
#define PMC_PCDR0 	*(p_PMC_BASE_ADD + 5) // Peripheral Clock Disable Register 0
#define PMC_PCSR0 	*(p_PMC_BASE_ADD + 6) // Peripheral Clock Status Register 0
#define PMC_PCER1 	*(p_PMC_BASE_ADD + 64) // Peripheral Clock Enable Register 1
#define PMC_PCDR1 	*(p_PMC_BASE_ADD + 65) // Peripheral Clock Disable Register 1
#define PMC_PCSR1 	*(p_PMC_BASE_ADD + 66) // Peripheral Clock Status Register 1

#define PMC_MOR   	*(p_PMC_BASE_ADD + 8)  // Main Oscillator Register

#define PMC_MCFR   	*(p_PMC_BASE_ADD + 9)  // Main Clock Frequency Register

#define PMC_MCKR  	*(p_PMC_BASE_ADD + 12) // Master Clock Register

#define PMC_SR    	*(p_PMC_BASE_ADD + 26) // Status Register

#define PMC_PCR   	*(p_PMC_BASE_ADD + 67) // Peripheral Control register

#define PMC_FSMR   	*(p_PMC_BASE_ADD + 28) // Fast Startup Mode Register
#define PMC_FSPR   	*(p_PMC_BASE_ADD + 29) // Fast Startup polarity Register

#define PMC_WPMR   	*(p_PMC_BASE_ADD + 57) // Write Protect Mode Register
#define PMC_WPSR   	*(p_PMC_BASE_ADD + 58) // Write Protect Status Register

// Remove the following if tests passes

/*   ---- Look up, changed the way registers are accessed in. ----
 // This may even have some memory advantages as well.
 *
 Reg p_PMC_PCER0 = (uint32_t *) 0x400E0610U; ///< PMC Peripheral Clock Enable Register 0
 Reg p_PMC_PCDR0 = (uint32_t *) 0x400E0614U; ///< PMC Peripheral Clock Disable Register 0
 Reg p_PMC_PCSR0 = (uint32_t *) 0x400E0618U; ///< PMC Peripheral Clock Status Register 0

 Reg p_PMC_PCER1 = (uint32_t *) 0x400E0700U; ///< PMC Peripheral Clock Status Register 1
 Reg p_PMC_PCDR1 = (uint32_t *) 0x400E0704U; ///< PMC Peripheral Clock Status Register 1
 Reg p_PMC_PCSR1 = (uint32_t *) 0x400E0708U; ///< PMC Peripheral Clock Status Register 1

 Reg p_PMC_MCKR  = (uint32_t *) 0x400E0630U; ///< PMC Master Clock Register
 Reg p_PMC_SR    = (uint32_t *) 0x400E0668; ///< PMC Status Register
 */

/** Adjusts a specified peripheral (0 - 44) to the correct mask-bit.
 * Static, because it's an internal function to the API.
 *
 * @param ID_ The peripheral clock that get the mask-bit added.
 * @param reg Register 0 containing peripheral 0-31, register 1 containing peripheral 32-44
 */
static uint32_t pmc_get_peripheral_mask(definedInput8 ID_) {
	if (ID_ < 33) {
		return (uint32_t) (0x01U << ID_);
	} else {
		return (uint32_t) (0x01U << (ID_ - 32));	// Adjust to the correct bit
	}
}

/** Start peripheral clock
 * @param ID_ Which peripheral clock that should be started.
 */
error pmc_start_peripheral_clock(definedInput8 ID_) {
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
error pmc_stop_peripheral_clock(definedInput8 ID_) {
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
error pmc_status_peripheral_clock(definedInput8 ID_) {

	error status = FAIL;

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

/** Set peripheral prescaler.
 * This will set a prescaler for the CAN controllers.
 * The CAN controller are the only ones that need their prescalers to be set
 * from the PMC. Every other peripheral has its own internal prescaler settings.
 *
 * 'device' in the parameter-names indicate a peripheral mnemonic like
 * PWM, ADC, DACC ... (All of the peripherals will be ignored by this function
 * except for the CAN controllers.)
 *
 * !! Not yet ready !!
 *
 * @param device_prescaler_ This defines the prescaler to use.
 */
error pmc_set_CAN_prescaler(definedInput8 ID_, definedInput32 device_prescaler_) {
	if (ID_ == ID_CAN0 || ID_ == ID_CAN1) {

		// Code goes here

		return SUCCESS;
	} else {
		return FAIL;
	}
	return FAIL;
}

/** Set to sleep mode, provide wakeup method
 *
 */
error pmc_sleep(definedInput8 wake_on_) {
	if (wake_on_ == wake_on_event) {
		__asm__ ("wfe;"
				: /* output */
				: /* input */
				: /* clobbered register */
		);
	} else if (wake_on_ == wake_on_interupt) {
		__asm__ ("wfi;"
				: /* output */
				: /* input */
				: /* clobbered register */
		);
	} else {
		// Wrong parameter
		return FAIL;
	}
	return SUCCESS;
}

/** This function will make the MCU sleep for the given amount of time using
 * the Real Time Timer.
 *
 * !! Not ready yet !!
 *
 * @param ms
 * @return
 */
error pmc_sleep_for_ms(uint32_t ms) {
	// Set wake up alarm
	pmc_sleep(wake_on_event);
	return SUCCESS;
}

/** Set master clock
 *
 */
error pmc_select_master_clock(uint32_t clock) {

	error status = FAIL;

	if (clock <= 7) {

		PMC_MCKR = clock;

		while ((PMC_SR | PMC_SR_MCKRDY_MASK) == 0)
			;	// Wait for masterclock ready

		status = SUCCESS;
	}

	return status;
}

#define pmc_

/** This function will set the prescaler of the processor clock or master clock
 * to the desired value. For the input one must begin writing
 * pmc_processor_clk_prescaler_ to get to the correct prescalers.
 *
 * @param pmc_processor_clk_prescaler_ Choose amoung predefined prescalers
 * @return
 */
error pmc_set_processor_clk(definedInput8 pmc_processor_clk_prescaler_){
	// 0x00000003 = CSS mask
	if((PMC_MCKR & 0x00000003) < 2){
		while(~PMC_SR_MCKRDY_MASK){} // Wait till the master clock gets ready
		PMC_MCKR |= (~PMC_MCKR_PRES_MASK | (pmc_processor_clk_prescaler_ << 4));

	}

	return SUCCESS;
}
