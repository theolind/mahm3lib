/*
 * mux.h
 *
 *  Created on: 25 okt 2014
 *      Author: Stefan
 */

#ifndef SAM3X8E_MUX_H_
#define SAM3X8E_MUX_H_

#include "adc.h"
#include "pmc.h"

#define mux0 			(6)
#define mux1 			(5)
#define mux2 			(3)



//	pio_conf_pin(PIOA, 23, ((mux&7)>>2), 0);		// A2
//	pio_conf_pin(PIOA, 24,((mux&3)>>1) , 0); 		// A1
//	pio_conf_pin(PIOA, 16, (mux&1), 0); 			// A0

void mux_digital_in();
void mux_digital_out();
void mux_analog_in();

public void enable_mux_pin(S);
void disable_mux_pin(uint32_t mux, uint32_t pin);


#endif /* SAM3X8E_MUX_H_ */
