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
	uint8_t PULLUP_OK = 0;
	uint32_t *p_PUSR = PIO_PORTB + PIO_PUSR; //Pullup status Register B
	pio_conf_pin(PIO_PORTB, (1<<32), 1, 1); //PIO_PUSR
	if(*p_PUSR == (1<<32)) {
		PULLUP_OK = 1;
	} else {
		PULLUP_OK = 0;
	}
	return PULLUP_OK;
}

uint8_t test_pio_output() {
	uint8_t OUTPUT_OK = 0;
	uint32_t *p_OSR = PIO_PORTB + PIO_OSR; //Output status Register B
	pio_conf_pin(PIO_PORTB, (1<<32), 1, 1); //PIO_PUSR
	if(*p_OSR == 1) {
		OUTPUT_OK = 1;
	} else {
		OUTPUT_OK = 0;
	}
	return OUTPUT_OK;
}

