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


#ifndef PWM_H_
#define PWM_H_

//////////////////////////////////////////////////////////////////////////
// Externally available typedefs, variables and definitions
typedef struct pwm_clk_setting{
	uint32_t clkA;
	uint32_t clkB;
};

#define PWM_CLK_ID_CLKA			0
#define PWM_CLK_ID_CLKB			1

//////////////////////////////////////////////////////////////////////////
// Function Prototypes

/**
 * Default initialization for the PWM peripheral
 * This leaves clkA and clkB off and starts the peripheral clock.
 *
 * @return error (0 = FAIL, 1 = SUCCESS)
 * @pre {This function requires the PMC API.}
 */
uint8_t	 pwm_init(void);
// Initialize with a structure
uint8_t	 pwm_init(struct clock_settings);
// Calculates necessary parameters automatically for the given frequency and
// returnes actual frequency
uint8_t	 pwm_set_channel_frequency(uint8_t channel, uint32_t frequency);
// Turns of one of two clocks in PWM that are called clkA and clkB.
uint8_t	 pwm_turn_of_clkx(uint8_t clock_id);
// Initializes the a single channel in the peripheral of 8 in total
uint8_t  pwm_init_channel(uint32_t channel, uint32_t pin_PWMHx_or_PWMLx);
// Set the duty cycle between 0 and resolution
uint32_t pwm_set_channel_duty_cycle(uint32_t channel, uint32_t duty_cycle);
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
uint32_t pwm_read(uint8_t channel);
//Writes an output to a given channel
uint8_t pwm_write(uint8_t channel, uint32_t duty_cycle);

//Turns write protection on or off
uint8_t  pwm_set_writ_protection(uint8_t state);




//////////////////////////////////////////////////////////////////////////


#endif /* PWM_H_ */
