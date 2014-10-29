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

#define MUXPORT 		PIOA

#define MUX0 			(16)
#define MUX1 			(24)
#define MUX2 			(23)

#define MUXSPORT0 			PIOC
#define MUXSPORT1 			PIOB

#define MUXS0 			(25)
#define MUXS1 			(28)
#define MUXS2 			(26)
#define MUXS3 			(25)

void mux_shield_init(void);
void mux_shield_set_channel(uint32_t channel);
uint32_t mux_shield_set_mode(uint32_t mux, uint32_t mode);
void mux_shield_set_channel(uint32_t channel);
void mux_shield_set_datapin(uint32_t mux, uint32_t level);
uint32_t mux_shield_read_datapin(uint32_t mux);
uint32_t mux_shield_read_analog_datapin(uint32_t mux);

#endif /* SAM3X8E_MUX_SHIELD_H_ */
