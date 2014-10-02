/*
 * test_delay.c
 *
 *  Created on: 1 October 2014
 *      Author: Mattias Nilsson
 */

#include "sam3x8e/pio.h"
#include "sam3x8e/delay.h"

void test_delay_l_led(uint32_t delay){
	pio_conf_pin(PIOB, 27, 0, 0);
	for(;;){
		//pio_set_pin(PIOB, 27, 1);
		PIOB->PIO_SODR = (0x1u << 27);	//set pin
		delay_us(delay);
		//pio_set_pin(PIOB, 27, 0);
		PIOB->PIO_CODR = (0x1u << 27);	//clear pin
		delay_ms(delay/1000);
	}
}

void test_delay_pin_46(uint32_t delay){
	pio_conf_pin(PIOC, 17,  0, 0);
	for(;;){
		//pio_set_pin(PIOC, 17, 0);
		PIOC->PIO_SODR = (0x1u << 17);	//set pin
		//delay_milliseconds(1);
		delay_us(delay);
		//pio_set_pin(PIOC, 17, 1);
		PIOC->PIO_CODR = (0x1u << 17);	//clear pin
	}

}
