/**
 * \class PWM
 * \brief Pulse Width Modulation (PWM)
 * \details This class is used to output a pulse width modulated waveform using
 * \details the PWM peripheral on the MCU.
 * \author Saeed Ghasemi
 * \version 0.1
 * \date 25 sep 2014
 * \pre
 * \bug
 */

#include "global_entities.h"


#ifndef PWM_H_
#define PWM_H_

//////////////////////////////////////////////////////////////////////////
// Function Prototypes

// Default initialization
uint8_t	 pwm_init(void);

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
