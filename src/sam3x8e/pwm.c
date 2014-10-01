/**
 * @file pwm.c
 * @anchor <pwm>
 * @brief Pulse Width Modulation (PWM)
 * @details {This class is used to output a pulse width modulated waveform
 * using the PWM peripheral on the MCU.
 * This peripheral is an embedded macrocell within the MCU and all of its 44
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * This API implements all 8 independent channels and their change of polarity,
 * alignment, PWM frequency and handles the pin multiplexing for all 16 outputs
 * of the peripheral. The API does not stop any clock once it has started them.}
 * @author {Saeed Ghasemi}
 * @version {v0.1}
 * @date {28 sep 2014}
 * @pre {The API handles all of its dependencies on other peripherals
 * internally and will start other clocks in order to properly operate.}
 * @bug {Manual and automated testing are being designed.}
 */


#include "global_entities.h"
#include "pwm.h"

/////////////////////////////////////////////////////////////////////////////
///\cond
/*
 *  Necessary registers addressed by incrementing the base address by an
 *  register-specific offset.
 */
// The first register in the Power Management Controller
#define p_PWM_BASE_ADD			0x40094000U

#define PWM_CLK 	*((uint32_t*)(p_PWM_BASE_ADD + 0x000)) // PWM Clock Register
#define PWM_ENA 	*((uint32_t*)(p_PWM_BASE_ADD + 0x004)) // PWM Enable Register
#define PWM_DIS 	*((uint32_t*)(p_PWM_BASE_ADD + 0x008)) // PWM Disable Register
#define PWM_SR 		*((uint32_t*)(p_PWM_BASE_ADD + 0x00C)) // PWM Status Register
#define PWM_CMR1 	*((uint32_t*)(p_PWM_BASE_ADD + 0x200)) // PWM Channel Mode Register
#define PWM_CDTY 	*((uint32_t*)(p_PWM_BASE_ADD + 0x204)) // PWM Channel Duty Cycle Register
#define PWM_CDTYUPD *((uint32_t*)(p_PWM_BASE_ADD + 0x208)) // PWM Channel Duty Cycle Update Register
#define PWM_CPRD 	*((uint32_t*)(p_PWM_BASE_ADD + 0x20C)) // PWM Channel Period Register
#define PWM_CPRDUPD *((uint32_t*)(p_PWM_BASE_ADD + 0x210)) // PWM Channel Period Update Register
///\endcond
/////////////////////////////////////////////////////////////////////////////
/**
 * MASKs are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_MASK
 */
#define PWM_CLK_PREA_MASK				(0x00000F00)
#define PWM_CLK_PREB_MASK				(0x0F000000)
#define PWM_CLK_DIVA_MASK				(0x000000FF)
#define PWM_CLK_DIVB_MASK				(0x00FF0000)

// Enable disable bit masts for the individual channels
/**
 * @def <defines>
 * These defines are masks for the PWM channels and can be used on
 * PWM_ENA, PWM_DIS and PWM_SR.
 */
#define PWM_CHANNEL_0_MASK				(1<<0)
#define PWM_CHANNEL_1_MASK				(1<<1)
#define PWM_CHANNEL_2_MASK				(1<<2)
#define PWM_CHANNEL_3_MASK				(1<<3)
#define PWM_CHANNEL_4_MASK				(1<<4)
#define PWM_CHANNEL_5_MASK				(1<<5)
#define PWM_CHANNEL_6_MASK				(1<<6)
#define PWM_CHANNEL_7_MASK				(1<<7)

#define PWM_CMRx_CPRE_MASK				(0x0000000F)
#define PWM_CMRx_CALG_MASK				(1 << 8)
#define PWM_CMRx_CPOL_MASK				(1 << 9)
#define PWM_CMRx_CES_MASK				(1 << 10)
#define PWM_CMRx_DTE_MASK				(1 << 16)
#define PWM_CMRx_DTHI_MASK				(1 << 17)
#define PWM_CMRx_DTLI_MASK				(1 << 18)

#define PWM_CDTYx_CDTY__MASK			(0x0000FFFF)
#define PWM_CDTYUPDx_CDTYUPD_MASK		(0x0000FFFF)

#define PWM_CPRDx_CPRD_MASK				(0x0000FFFF)
#define PWM_CPRDUPDx_CPRDUPD_MASK		(0x0000FFFF)
/////////////////////////////////////////////////////////////////////////////
/**
 * Parameters are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_VALUE    (IF ANY NUMBER)
 */
//PESCALLERS FOR CLOCK REGISTER
#define PWM_CLK_PRES_1					(0b0000)
#define PWM_CLK_PRES_2					(0b0001)
#define PWM_CLK_PRES_4					(0b0010)
#define PWM_CLK_PRES_8					(0b0011)
#define PWM_CLK_PRES_16					(0b0100)
#define PWM_CLK_PRES_32					(0b0101)
#define PWM_CLK_PRES_64					(0b0110)
#define PWM_CLK_PRES_128				(0b0111)
#define PWM_CLK_PRES_256				(0b1000)
#define PWM_CLK_PRES_512				(0b1001)
#define PWM_CLK_PRES_1024				(0b1010)

// Parameters for easy selecting of clocks within each channel
#define PWM_CMRx_SELECTOR_MCK/1			(0b0000)
#define PWM_CMRx_SELECTOR_MCK/2			(0b0001)
#define PWM_CMRx_SELECTOR_MCK/4			(0b0010)
#define PWM_CMRx_SELECTOR_MCK/8			(0b0011)
#define PWM_CMRx_SELECTOR_MCK/16		(0b0100)
#define PWM_CMRx_SELECTOR_MCK/32		(0b0101)
#define PWM_CMRx_SELECTOR_MCK/64		(0b0110)
#define PWM_CMRx_SELECTOR_MCK/128		(0b0111)
#define PWM_CMRx_SELECTOR_MCK/256		(0b1000)
#define PWM_CMRx_SELECTOR_MCK/512		(0b1001)
#define PWM_CMRx_SELECTOR_MCK/1024		(0b1010)
#define PWM_CMRx_SELECTOR_CLOCK_A		(0b1011)
#define PWM_CMRx_SELECTOR_CLOCK_B		(0b1111)

//DIVIDERS FOR CLKA AND CLKB
#define PWM_CLK_DIVx_TURNOFF			0
#define PWM_CLK_DIVx_PREx				1
//PESCALLERS FOR CHANNEL MODE REGISTER
#define PWM_CMRx_PRES_1					(0b0000)
#define PWM_CMRx_PRES_2					(0b0001)
#define PWM_CMRx_PRES_4					(0b0010)
#define PWM_CMRx_PRES_8					(0b0011)
#define PWM_CMRx_PRES_16				(0b0100)
#define PWM_CMRx_PRES_32				(0b0101)
#define PWM_CMRx_PRES_64				(0b0110)
#define PWM_CMRx_PRES_128				(0b0111)
#define PWM_CMRx_PRES_256				(0b1000)
#define PWM_CMRx_PRES_512				(0b1001)
#define PWM_CMRx_PRES_1024				(0b1010)
#define PWM_CMRx_PRES_CLOCKA			(0b1011)
#define PWM_CMRx_PRES_CLOCKB			(0b1100)
// PARAMETERS FOR THE ALIGNMENT
#define PWM_CMRx_ALIGN_LEFT				0
#define PWM_CMRx_ALIGN_CENTER			1
// PARAMETERS FOR THE POLARITY
#define PWM_CMRx_POLARITY_HIGH			1
#define PWM_CMRx_POLARITY_LOW			0
//////////////////////////////////

/**
 * Start pmc clock
 *
 * @return
 */
uint8_t pwm_init_default(){
	pmc_start_peripheral_clock(ID_PWM);
}

/**
 * disable channel
 * set parameters
 * enable channel
 * @return
 */
uint8_t  pwm_init_channel(struct pwm_channel_setting instance, uint8_t pin){

	return SUCCESS;
}

/**
 * Set the channel prescaler
 * @return
 */
uint8_t pwm_set_channel_prescaler(uint32_t channel, uint32_t prescaler){

	return SUCCESS;
}

/**
 * Set the channel polarity
 * @return
 */
uint8_t  pwm_set_channel_polarity(uint32_t channel, uint32_t pwm_polarity){

	return SUCCESS;
}

/**
 * Set the channel alignment
 * @return
 */
uint8_t  pwm_set_channel_alignment(uint32_t channel, uint32_t PWM_ALIGN_){

	return SUCCESS;
}

/**
 * Turns off clock A or B.
 *
 *
 * @param clock_id {Must be 0 for clkA and 1 for clkB}
 * @return
 */
uint8_t	 pwm_turn_of_clkx(uint8_t clock_id){
	if(clock_id == 0){
		set_section_in_register(&PWM_CLK, PWM_CLK_PREA_MASK, 0);
		return SUCCESS;
	}else if(clock_id == 1){
		set_section_in_register(&PWM_CLK, PWM_CLK_PREB_MASK, 0);
		return SUCCESS;
	}

	return FAIL;
}

/**
 * Set the channel duty cycle
 * @param channel
 * @param duty_cycle
 * @return
 */
uint32_t pwm_set_channel_duty_cycle(uint32_t channel, uint32_t duty_cycle){

	return SUCCESS;
}

/**
 * Shuts down the peripheral but keeps all settings
 * @return
 */
uint8_t  pwm_shutdown(){
	pmc_stop_peripheral_clock(ID_PWM);
}


/**
 * Resets the peripheral and disables all channels
 * @return error
 */
uint8_t  pwm_reset(){
	clear_register(&PWM_CLK);
	set_register(&PWM_DIS);
	clear_register(&PWM_CMR1);
	clear_register(&PWM_CDTY);
	clear_register(&PWM_CDTYUPD);
	clear_register(&PWM_CPRD);
	clear_register(&PWM_CPRDUPD);
	return SUCCESS;
}

/**
 * Reset and turns off the peripheral
 * @return
 */
uint8_t  pwm_close(){
	pwm_reset();
	pwm_shutdown();
	return SUCCESS;
}

/**
 * Read what was earlier written to the channel
 * @param channel
 * @return
 */
uint32_t pwm_read(uint8_t channel){
	&PWM_CMR1
	return SUCCESS;
}

void function(){
	/**
	 * enable the PWM clock in PMC
	 * See status for channel
	 * if enabled then disable channel
	 ** initialize peripheral by selecting a prescaler of clk register with PREA
	 * Select a clock for channel_0
	 * Select alignment for channel_0
	 * Select polarity for channel_0
	 *
	 *
	 */


}




