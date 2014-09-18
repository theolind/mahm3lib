/* test_pio.c
*
*  Created on: Sep 18, 2014
*      Author: Theodor Lindquist
*      Author: Soded Alatia
*/

#include "pio.h"
#include "test_pio.h"

void pio_setUp() {
 
}

void pio_tearDown() {

}

void pio_resetTest() {
	tearDown();
}
 
uint8_t test_pio_pullup() {
	uint8_t ret = 0;
	uint32_t *p_pusr = PIO_PORTB + PIO_PUSR; //Pullup status Register B
	pio_conf_pin(PIO_PORTB, (1<<32), 1, 1); //PIO_PUSR
	if(*p_pusr == (1<<32)) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}

uint8_t test_pio_output() {
	uint8_t ret = 0;
	uint32_t *p_osr = PIO_PORTB + PIO_OSR; //Output status Register B
	pio_conf_pin(PIO_PORTB, (1<<32), 1, 1); //PIO_PUSR
	if(*p_osr == (1<<32)) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}

uint8_t test_pio_read_pin() {
	uint8_t ret = 0;
	uint8_t value = pio_read_pin(PIO_PORTB, 17);
	if(value == 0) {
		ret = 1;
	} else {
		ret = 0;
	}

	return ret;
}

uint8_t test_pio_set_output() {
	uint8_t ret = 0;
	uint32_t *p_odsr = PIO_PORTB + PIO_ODSR;

	pio_set_pin(PIO_PORTB, (1<<17), 1);
	if(*p_odsr == (1<<17)) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}
