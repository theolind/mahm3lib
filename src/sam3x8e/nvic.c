/**
 * @file
 * @brief NVIC - Nested Vectored Interrupt Controller
 * @details This is a simplistic implementation of NVIC just to be able to
 * enable and disable interrupts-lines for the peripheral controllers.
 * There may be many interrupts for a given peripheral, but only one line to
 * the NVIC and the handler must take care of reading which interrupt of the
 * peripheral has interrupted the process and handle it.
 * @author Saeed Ghasemi
 * @date 29 September 2014
 * @bug
 */

#include "nvic.h"

uint8_t nvic_enable_interrupt(uint8_t peripheral_id){
	if(peripheral_id > 31){
		set_bit_in_register(&NVIC->NVIC_ISER1, peripheral_id);
	}else if(peripheral_id < 32){
		set_bit_in_register(&NVIC->NVIC_ISER0, peripheral_id);
	}
	return 1;
}

uint8_t nvic_disable_interrupt(uint8_t peripheral_id){
	if(peripheral_id > 31){
		set_bit_in_register(&NVIC->NVIC_ICER1, peripheral_id);
	}else if(peripheral_id < 32){
		set_bit_in_register(&NVIC->NVIC_ICER0, peripheral_id);
	}
	return 1;
}
