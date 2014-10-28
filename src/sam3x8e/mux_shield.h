/*
 * mux.h
 *
 *  Created on: 25 okt 2014
 *      Author: Stefan
 */

#ifndef SAM3X8E_MUX_SHIELD_H_
#define SAM3X8E_MUX_SHIELD_H_

#include "pmc.h"
#include "adc.h"
#include "pio.h"

//PIOA
#define muxport 		((pio_reg_t *) 0x400E0E00)

#define mux0 			(16)
#define mux1 			(24)
#define mux2 			(23)

void mux_shield_init();
void mux_shield_set_channel(uint32_t channel);
uint32_t mux_shield_set_mode(uint32_t mux, uint32_t mode);
void mux_shield_set_channel(uint32_t channel);
uint32_t mux_shield_read_datapin(uint32_t mux);
void mux_shield_set_datapin(uint32_t mux, uint32_t level);
uint32_t mux_shield_read_analog_datapin(uint32_t mux);

#endif /* SAM3X8E_MUX_SHIELD_H_ */
