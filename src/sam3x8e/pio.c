/*
* pio.c
*
* Created on: Sep 18, 2014
* Author: Theodor Lindquist
* Author: Soded Alatia
* Author: Felix Ruponen
*/

#include "pio.h"

/*
 * This register can only be written if the WPEN bit is cleared in
 * "PIO Write Protect Mode Register".
 */
void pio_enable_pin(pio_reg_t *port, uint32_t pin) {
	port->PIO_PER = (1u << pin);
}

/*
 * This register can only be written if the WPEN bit is cleared in
 * "PIO Write Protect Mode Register".
 */
void pio_disable_pin(pio_reg_t *port, uint32_t pin) {
	port->PIO_PDR = (1u << pin);
}

void pio_conf_pin(pio_reg_t *port, uint32_t pin, uint32_t input, uint32_t pullup) {
	pio_conf_pins(port, (0x1u << pin), input, pullup);
}

void pio_conf_pins(pio_reg_t *port, uint32_t pins, uint32_t input, uint32_t pullup) {
	//set output/input
	if (input == 1) {
		//use the output disable register to enable inputs
		port->PIO_ODR = pins;
	} else {
		//use the output enable register to enalbe outputs
		port->PIO_OER = pins;
}
	//set pullups
	if (pullup == 1) {
		//use the pull up enable register
		port->PIO_PUER = pins;
	} else {
		//use the pull up disable register
		port->PIO_PUDR = pins;
	}
}

void pio_conf_port(pio_reg_t *port, uint32_t inputs, uint32_t pullups) {
	//enable the pins of the port
	port->PIO_PER = ~(0U);
	//set output/input
	port->PIO_ODR = inputs;	//if a bit is 1, disable output for that pin
	port->PIO_OER = ~inputs;	//if a bit is 0, enable output for that pin
	//set pullups
	//point to pull-up enable register
	port->PIO_PUER = pullups;	//enable pull-ups
	//point to pull-up disable register
	port->PIO_PUDR = ~pullups;	//disable pull-ups
}

void pio_set_pin(pio_reg_t *port, uint32_t pin, uint32_t level) {
	pio_set_pins(port, (0x1u << pin), level);
}

void pio_set_pins(pio_reg_t *port, uint32_t pins, uint32_t level) {
	if (level == 1) {
		//set pins high
		port->PIO_SODR |= pins;
	} else {
		//set pins low
		port->PIO_SODR &= ~pins;
	}
}

void pio_set_port(pio_reg_t *port, uint32_t levels) {
	port->PIO_SODR = levels;
}

uint32_t pio_read_pin(pio_reg_t *port, uint32_t pin) {
	return ((pio_read_port(port) & (1U << pin)) >> pin);
}

uint32_t pio_read_port(pio_reg_t *port) {
	return port->PIO_PDSR;
}
