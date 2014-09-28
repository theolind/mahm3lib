/*
 * pio.c
 *
 *  Created on: Sep 18, 2014
 *      Author: Theodor Lindquist
 *      Author: Soded Alatia
 */

#include "pio.h"


void pio_close(void) {
	uint32_t *p_pmc_pcer0 = (uint32_t *)0x400E0610;
	*p_pmc_pcer0 &= ~(0b111111<<11);	//clear bit 11 to 16 in PMC_PCER0
}

void pio_conf_pin(uint32_t port, uint8_t pin_number, uint8_t input, uint8_t pullup) {
	//use the port function to set a single pin
	pio_conf_pins(port, (uint32_t)(1<<pin_number), input, pullup);
}

void pio_conf_pins(uint32_t port, uint32_t pin_numbers, uint8_t input, uint8_t pullup) {
	uint32_t *p_reg;	//register pointer points to the register currently used

	//set output/input
	if(input == 1) {
		//use the output disable register to enable inputs
		p_reg = (uint32_t *)(port+PIO_ODR);
		*p_reg = pin_numbers;
	} else {
		//use the output enable register to enalbe outputs
		p_reg = (uint32_t *)(port+PIO_OER);
		*p_reg = pin_numbers;
	}

	//set pullupts
	if(pullup == 1) {
		//use the pull up enable register
		p_reg = (uint32_t *)(port+PIO_PUER);
		*p_reg = pin_numbers;
	} else {
		//use the pull up disable register
		p_reg = (uint32_t *)(port+PIO_PUDR);
		*p_reg = pin_numbers;
	}
}

void pio_conf_port(uint32_t port, uint32_t inputs, uint32_t pullups) {
	uint32_t *p_reg;	//register pointer points to the register currently used

	//TODO move this to init ?
	//enable the pins of the port
	p_reg = (uint32_t *)(port+PIO_PER);	//point to PIO enable register
	*p_reg = ~(0);

	//set output/input
	p_reg = (uint32_t *)(port+PIO_ODR);	//point to Output enable register
	*p_reg = inputs;		//if a bit is 1, disable output for that pin
	p_reg = (uint32_t *)(port+PIO_OER);	//point to output disable register
	*p_reg = ~inputs;		//if a bit is 0, enable output for that pin

	//set pullups
	p_reg = (uint32_t *)(port+PIO_PUER);	//point to pull-up enable register
	*p_reg = pullups;		//enable pull-ups
	p_reg = (uint32_t *)(port+PIO_PUDR);	//point to pull-up disable register
	*p_reg = ~pullups;		//disable pull-ups
}

void pio_set_pin(uint32_t port, uint8_t pin_number, uint8_t level) {
	pio_set_pins(port, (uint32_t)(1<<pin_number), level);
}

void pio_set_pins(uint32_t port, uint32_t pin_numbers, uint8_t level) {
	uint32_t *p_reg;
	p_reg = (uint32_t *)(port+PIO_SODR);
	if(level == 1) {
		//set pins high
		*p_reg |= pin_numbers;
	} else {
		//set pins low
		*p_reg &= ~pin_numbers;
	}
}

void pio_set_port(uint32_t port, uint32_t levels) {
	uint32_t *p_reg;

	p_reg = (uint32_t *)(port+PIO_SODR);
	*p_reg = levels;
}

uint8_t pio_read_pin(uint32_t port, uint8_t pin_number) {
	uint8_t ret = ((pio_read_port(port) & (1<<pin_number)) >> pin_number);
	return ret;
}

uint32_t pio_read_port(uint32_t port) {
	uint32_t *p_reg;	//register pointer points to the register currently used

	p_reg = (uint32_t *)(port+PIO_PDSR);
	return *p_reg;
}
