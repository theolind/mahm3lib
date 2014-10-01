/*
 * Don't refer to a "class, as in: "This class is used to output a pulse width modulated waveform".
 * See more comments in the comment block below
 */
/**
 * @file pwm.c
 * @anchor <pwm>
 * @brief Pulse Width Modulation (PWM)
 * @details {This class is used to output a pulse width modulated waveform
 * using the PWM peripheral on the MCU.
 *
 * ---------IS THIS DESCRIPTION REALLY NECESSARY?
 * This peripheral is an embedded macrocell within the MCU and all of its 44
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * ----------END OF FEEDBACK OF DESCRIPTION
 *
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * This API implements all 8 independent channels and their change of polarity,
 * alignment, PWM frequency and handles the pin multiplexing for all 16 outputs
 * of the peripheral. The API does not stop any clock once it has started them.}
 * @author {Saeed Ghasemi}
 *
 * @version {v0.1}     	DONT USE VERSION NUMBERING!
 * 						This can be handled by Doxygen when compiling/creating documentation,
 * 						according to Felix.
 *
 * @date {28 sep 2014}
 * @pre {The API handles all of its dependencies on other peripherals
 * internally and will start other clocks in order to properly operate.}
 * @bug {Manual and automated testing are being designed.}
 */

#include "global_entities.h"	/* why do you need this file? */


#ifndef PWM_H_
#define PWM_H_
/* DONT USE THESE TYPE OF SUPER-LONG STRINGS OF SLASH-CHARACTERS, TOTALLY UNNECESSARY! */
//////////////////////////////////////////////////////////////////////////
// Externally available typedefs, variables and definitions
/**
 * @typedef
 * This structure is used with pwm_init() to set the settings for the clocks A
 * and B of the PWM peripheral.
 * @param clkA {This is the prescaler for clock A. If the clock is not needed
 * then setting this value to 0 will turn the clock off.
 * Parameter prefix: PWM_CLK_PRES_}
 * @param clkB {This is the prescaler for clock B. If the clock is not needed
 * then setting this value to 0 will turn the clock off.
 * Parameter prefix: PWM_CLK_PRES_}
 */
typedef struct pwm_clk_setting{
	uint32_t clkA_prescaler;
	uint32_t clkB_prescaler;
}; /* how about adding a name for the type? "pwm_clk_setting_t". BTW, the term "settings" is better than "setting" */

/**
 * @def
 * These are parameters used in conjunction with initializing a PWM channel.
 */
#define PWM_POLARITY_HIGH		1
#define PWM_POLARITY_LOW		0
#define PWM_ALIGN_LEFT			0
#define PWM_ALIGN_CENTER		1

/**
 * @typedef
 * This structure is used with pwm_init_channel() to set the settings of a
 * channel.
 * @param polarity {Sets the polarity of the channel.
 * Parameter prefix: PWM_POLARITY_}
 * @param alignment {Sets the alignment of the channel.
 * Parameter prefix: PWM_ALIGN_}
 * @param prescaler {Sets the channel prescaler.
 * This can also select clock A and B.
 * Parameter prefix: PWM_CMRx_SELECTOR_}
 * @param high_polarity_pin {If set HIGH, the high polarity pin of the channel
 * will be multiplexed with the PWM.}
 * @param low_polarity_pin {If set HIGH, the high polarity pin of the channel
 * will be multiplexed with the PWM.}
 */
typedef struct pwm_channel_setting{
	uint32_t polarity;
	uint32_t alignment;
	uint32_t prescaler;
	uint32_t high_polarity_pin;
	uint32_t low_polarity_pin;
}; /* how about adding a name for the type? "pwm_channel_setting_t". BTW, the term "settings" is better than "setting" */


#define PWM_CLK_ID_CLKA			0
#define PWM_CLK_ID_CLKB			1
/* DONT USE THESE TYPE OF SUPER-LONG STRINGS OF SLASH-CHARACTERS, TOTALLY UNNECESSARY! */
//////////////////////////////////////////////////////////////////////////
// Function Prototypes        IT'S VERY REDUNDANT TO ANNOUNCE THAT "Here comes the function prototypes". IT'S QUITE OBVIOUS.

/**
 * Default initialization for the PWM peripheral
 * This leaves clkA and clkB off and starts the peripheral clock.
 *
 * @return error (0 = FAIL, 1 = SUCCESS)
 * @pre {This function requires the PMC API.}
 */
//THE PWM API should not invoke anything from another device's API!
uint8_t	 pwm_init_default(void);
/**
 * Initialize the PWM peripheral with a structure containing clock_settings.
 * This function controls clkA and clkB and starts the peripheral clock.
 * It is recommended to use pwm_set_channel_frequency() to select a clock.
 *
 * @return error (0 = FAIL, 1 = SUCCESS)
 * @pre {This function requires the PMC API.}
 */
uint8_t	 pwm_init(struct pwm_clk_setting);

/**
 * Turns off one of two clocks in PWM that are called clkA and clkB.
 *
 * @return error (0 = FAIL, 1 = SUCCESS)
 */
uint8_t	 pwm_turn_of_clkx(uint8_t clock_id);
//
/**
 * Initializes a single channel in the peripheral out of 8 in total.
 * This function will multiplex the pin to the peripheral channel
 *
 * @return error (0 = FAIL, 1 = SUCCESS)
 */
//AS FAR AS I KNOW, THE PIN IS ONLY NECESSARY TO SPECIFY FOR "PIO OPERATIONS".
//Don't invoke function of other devices API's.
uint8_t  pwm_init_channel(struct pwm_channel_setting, uint8_t pin);

// Set the duty cycle between 0 and resolution
//THIS SHOULD BE DIVIDED INTO TWO FUNCTIONS:
//"pwm_select_channel(uint32_t channel)" and "pwm_write(uint32_t duty_cycle)"
uint32_t pwm_set_channel_duty_cycle(uint32_t channel, uint32_t duty_cycle);

//REGARDING THESE THREE FUNCTIONS, ISN'T ENOUGH TO PROVIDE THESE OPTIONS IN
//THE "pwm_init_channel(..)"
// This can reverse the duty cycle. Important when using the L pins
uint8_t  pwm_set_channel_polarity(uint32_t channel, uint32_t pwm_polarity);
// Choose one of two clocks to be the source
uint8_t  pwm_set_channel_clocksource(uint32_t channel, uint32_t pwm_clock_source);
// Set different alignments for the channel
uint8_t  pwm_set_channel_alignment(uint32_t channel, uint32_t PWM_ALIGN_LEFT_CENTER);

//Shuts down the peripheral but keeps all settings
uint8_t  pwm_shutdown();
//Reset and turns off the peripheral
uint8_t  pwm_close();
//Resets the peripheral and disables all channels
uint8_t  pwm_reset();

//Read what was earlier written to the channel
//CHANGE NAME TO "pwm_read_channel"
uint32_t pwm_read(uint8_t channel);

//Writes an output to a given channel OBS: The same as pwm_set_channel_duty_cycle()
//SEE MY COMMENTS ABOUT "pwm_set_channel_duty_cycle()"
uint8_t pwm_write(uint8_t channel, uint32_t duty_cycle);


/* DONT USE THESE TYPE OF SUPER-LONG STRINGS OF SLASH-CHARACTERS, EVEN MORE UNNECESSARY HERE! */
//////////////////////////////////////////////////////////////////////////


#endif /* PWM_H_ */
