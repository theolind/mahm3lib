/*
 * pio.c
 *
 *  Created on: Sep 18, 2014
 *      Author: Theodor Lindquist
 */

#include "pio.h"

void pio_init() {
	/**
	 * TODO
	 * Periphial IDs for PIO*
	 * PIO  PID   BIT #pins
	 * PIOA PID11 11  30
	 * PIOB PID12 12  32
	 * PIOC PID13 13  31
	 * PIOD PID14 14  10
	 * PIOE PID15 15  -
	 * PIOF PID16 16  -
	 *
	 * Set bits 11 to 16 in PMC_PCER0 (0x400E0610) to enable clocks for a port
	 * To do this, first clear WPEN bit (bit 0) in PMC_WPMR (0x400E06E4)
	 */
}

void pio_close() {
	//TODO undo what has been done in digital_io_init
}

void pio_conf_pin(uint8_t port, uint8_t pin_number, uint8_t input, uint8_t pullup) {
	//use the port function to set a single pin
	pio_conf_port(port, (1<<pin_number), (input<<pin_number), (pullup<<pin_number));
}

void pio_conf_port(uint8_t port, uint32_t inputs, uint32_t pullups) {
	uint32_t *p_reg;	//register pointer points to the register currently used

	//TODO move this to init ?
	//enable the pins of the port
	p_reg = port+PIO_PER;	//point to PIO enable register
	**p_reg = ~(0);

	//set output/input
	p_reg = port+PIO_OER;	//point to Output enable register
	**p_reg = inputs;		//if a bit is 1, enable input for that pin
	p_reg = port+PIO_ODR;	//point to output disable register
	**p_reg = ~inputs;		//if a bit is 0, disable input for that pin

	//set pullups
	p_reg = port+PIO_PUER;	//point to pull-up enable register
	**p_reg = pullups;		//enable pull-ups
	p_reg = port+PIO_PUDR;	//point to pull-up disable register
	**p_reg = ~pullups;		//disable pull-ups
}

//TODO void pio_set_pin(uint8_t port, uint8_t pin_number, uint8_t level);
//TODO void pio_set_port(uint8_t port, uint32_t levels);

uint8_t pio_read_pin(uint8_t port, uint8_t pin_number) {
	//return (digital_io_read_port(port) & (1<<pin_number)) >> pin_number; ?
}

uint32_t pio_read_port(uint8_t port) {
	/**
	 * TODO
	 * Read input from PIO_PDSR
	 */
}
