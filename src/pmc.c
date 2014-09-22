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
uint32_t *const p_PMC_BASE_ADD = (uint32_t *) 0x400E0600U;

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

/** Adjusts a specified peripheral (0 - 44) to the correct mask-bit.
 * Static, because it's an internal function to the API.
 *
 * @param ID_ The peripheral clock that get the mask-bit added.
 * @param reg Register 0 containing peripheral 0-31, register 1 containing peripheral 32-44
 */

static uint32_t pmc_get_peripheral_mask(uint8_t ID_) {
	if (ID_ < 33) {
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


/** Set to sleep mode, provide wakeup method
 *
 */
uint8_t pmc_sleep(uint8_t wake_on_) {
	if (wake_on_ == PMC_WAKE_ON_EVENT) {
		__asm__ ("wfe;"
				: /* output */
				: /* input */
				: /* clobbered register */
		);
	} else if (wake_on_ == PMC_WAKE_ON_INTERUPT) {
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
uint8_t pmc_sleep_for_ms(uint32_t ms){

	// Set wake up alarm

	return pmc_sleep(PMC_WAKE_ON_EVENT);
}

/** select master clock
 *
 */
uint8_t pmc_select_master_clock(uint32_t PMC_CLOCK_){

	return SUCCESS;
}


/** This function will set the prescaler of the processor clock or master clock
 * to the desired value. For the input one must begin writing
 * pmc_processor_clk_prescaler_ to get to the correct prescalers.
 *
 * This will only work if Slow_clock or Main_clock is selected.
 *
 * @param pmc_processor_clk_prescaler_ Choose amoung predefined prescalers
 * @return error
 */
uint8_t pmc_set_processor_clk(uint8_t PMC_PROCESSOR_PRES_){
	if((PMC_MCKR & PMC_MCKR_CSS_MASK) < 2){
		// Wait till the master clock stabilizes
		while(~is_bit_high(PMC_SR,PMC_SR_MCKRDY_MASK)){}
		// Explanation: Clear the field of the prescaler and add a new prescaler
		// Set PRES with one update of PMC_MCKR
		PMC_MCKR &= ((PMC_MCKR & (~PMC_MCKR_PRES_MASK)) | (PMC_PROCESSOR_PRES_ << 4));
		// Wait till the master clock stabilizes
		while(~is_bit_high(PMC_SR,PMC_SR_MCKRDY_MASK)){}
		return SUCCESS;
	}else{
		return FAIL;
	}

	return SUCCESS;
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
uint8_t pmc_set_can_prescaler(uint8_t ID_, uint32_t CAN_PRES_) {
	if (ID_ == ID_CAN0 || ID_ == ID_CAN1) {

		// Code goes here

		return SUCCESS;
	} else {
		return FAIL;
	}
	return FAIL;
}
