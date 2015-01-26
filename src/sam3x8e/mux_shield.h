/**
 * @file
 * @brief Arduino Multiplex Shield - 3x multiplex
 * @details The functions in this file controls the Arduino multiplex shield
 *
 * @author Prince Balabis
 * @author Stefan Angelov
 *
 * @date 25 October 2014
 *
 */

#ifndef SAM3X8E_MUX_SHIELD_H_
#define SAM3X8E_MUX_SHIELD_H_

#include "pmc.h"
#include "adc.h"
#include "pio.h"
#include "arduino_due.h"

/**
 * These definitions are used when setting multiplex modes on the shields multiplexes
 */
#define DIGITAL_OUTPUT		(0)
#define DIGITAL_INPUT		(1)
#define	ADC_INPUT			(2)

/**
 * Mapped digital pins and port for the common inputs/outputs of the shields multiplexes
 *
 * MUX_DIGITAL_[multiplex]
 *
 */
#define MUX_PORT 			PIOA
#define MUX_DIGITAL_0 		(16)
#define MUX_DIGITAL_1 		(24)
#define MUX_DIGITAL_2 		(23)

/**
 * Mapped ADC channels for the common inputs/outputs of the shields multiplexes
 *
 * MUX_ADC_[multiplex]
 *
 */
#define MUX_ADC_0 			A0
#define MUX_ADC_1			A1
#define MUX_ADC_2			A2

///@cond
/**
 * Mapped pins for the four address inputs of the shields multiplexes
 *
 * MUX_S[multiplex]
 * MUX_S_PORT_[multiplex port]
 *
 */
#define MUX_S_PORT_0 		PIOC
#define MUX_S_PORT_1 		PIOB
#define MUX_S0 				(25)
#define MUX_S1 				(28)
#define MUX_S2 				(26)
#define MUX_S3 				(25)
///@endcond

/**
 * Initializes the multiplex shield
 */
void mux_shield_init(void);

/**
 * Sets a specific channel over all multiplexes(mux0, mux1 & mux2)
 *
 * @param channel the channel you want to select, which is between 0-15
 */
void mux_shield_set_channel(uint32_t channel);

/**
 * This function sets the chosen multiplex Common Input/output as digital input,
 * digital output or analog input. When set as analog input the ADC clock is
 * automatically initalized with ".startup_time = 0, .prescaler = 0" and
 * ADC resolution to 12 bit
 *
 * @param mux the multiplex you want to configure
 * @param mode the mode you want to set the multiplex as Expects: DIGITAL_OUTPUT, DIGITAL_INPUT or ADC_INPUT. Defined in mux_shield.h
 *
 */
void mux_shield_set_mode(uint32_t mux, uint32_t mode);

/**
 * Sets the level of the chosen multiplex which is set as DIGITAL OUTPUT.
 *
 * @param mux the multiplex you want to configure
 * @param level 1 is high, 0 is low
 */
void mux_shield_set_datapin(uint32_t mux, uint32_t level);

/**
 * Returns the level of the chosen multiplex which is set as DIGITAL INPUT.
 *
 * @param mux the multiplex you want to get the digital value from
 */
uint32_t mux_shield_read_datapin(uint32_t mux);

/**
 * Returns the level of the chosen multiplex which is set as ANALOG INPUT.
 *
 * @param mux the multiplex you want to get the analog value from
 *
 */
uint32_t mux_shield_read_analog_datapin(uint32_t mux);

#endif /* SAM3X8E_MUX_SHIELD_H_ */
