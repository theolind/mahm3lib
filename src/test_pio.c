/* test_pio.c
*
*  Created on: Sep 18, 2014
*      Author: Theodor Lindquist
*      Author: Soded Alatia
*/

#include "pio.h"
#include "test_pio.h"

uint8_t test_pio_pullup(void) {
	uint8_t ret = 0;
	uint32_t *p_pusr = (uint32_t *)(PIO_PORTB + PIO_PUSR); //Pullup status Register B
	pio_conf_pin(PIO_PORTB, 31, 1, 1); //PIO_PUSR
	if(*p_pusr == (uint32_t)(1<<31)) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}

uint8_t test_pio_output(void) {
	uint8_t ret = 0;
	uint32_t *p_osr = PIO_PORTB + PIO_OSR; //Output status Register B
	pio_conf_pin(PIO_PORTB, 31, 1, 1); //PIO_PUSR
	if(*p_osr == (uint32_t)(1<<31)) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}

uint8_t test_pio_read_pin(void) {
	uint8_t ret = 0;
	uint8_t value = pio_read_pin(PIO_PORTB, 17);
	if(value == 0) {
		ret = 1;
	} else {
		ret = 0;
	}

	return ret;
}

uint8_t test_pio_set_output(void) {
	uint8_t ret = 0;
	uint32_t *p_odsr = (uint32_t *)(PIO_PORTB + PIO_ODSR);

	pio_set_pin(PIO_PORTB, 17, 1);
	if(*p_odsr == (1<<17)) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}
