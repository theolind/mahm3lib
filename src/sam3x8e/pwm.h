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
// Initialize with a struct
uint8_t	 pwm_init(struct clock_settings);
// Initializes the a single channel in the peripheral of 8 in total
uint8_t  PWM_init_channel(uint32_t channel, uint32_t pin_PWMHx_or_PWMLx);
// Set the duty cycle between 0 and resolution
uint32_t pwm_set_duty_cycle(uint32_t channel, uint32_t duty_cycle);
// This can reverse the duty cycle. Important when using the L pins
uint8_t  PWM_set_channel_polarity(uint32_t channel, uint32_t pwm_polarity);
// Choose one of two clocks to be the source
uint8_t  PWM_set_channel_clocksource(uint32_t channel, uint32_t pwm_clock_source);
// Set different alignments for the channel
uint8_t  PWM_set_channel_alignment(uint32_t channel, uint32_t PWM_ALIGN_LEFT_CENTER);

//////////////////////////////////////////////////////////////////////////


#endif /* PWM_H_ */
