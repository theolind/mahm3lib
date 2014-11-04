/*
* pio.c
*
* Author: 	Theodor Lindquist
*			Soded Alatia
* 			Felix Ruponen
* 			Mathias Beckius
* 			Saeed Ghasemi
*
* Date:		12 October 2014
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

void pio_conf_pin(pio_reg_t *port, uint32_t pin, uint32_t input,
		uint32_t pullup) {
	pio_conf_pins(port, (0x1u << pin), input, pullup);
}

void pio_conf_pins(pio_reg_t *port, uint32_t pins, uint32_t input,
		uint32_t pullup) {
	//set output/input
	if (input == 1) {
		//use the output disable register to enable inputs
		port->PIO_ODR = pins;
	} else {
		//use the output enable register to enable outputs
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
	if (level != 0) {
		port->PIO_SODR = pins;	//set pins
	} else {
		port->PIO_CODR = pins;	//clear pins
	}
}

void pio_set_port(pio_reg_t *port, uint32_t levels) {
	port->PIO_SODR = levels;
	port->PIO_CODR = ~levels;
}

uint32_t pio_read_pin(pio_reg_t *port, uint32_t pin) {
	return ((pio_read_port(port) & (1U << pin)) != 0);
}

uint32_t pio_read_port(pio_reg_t *port) {
	return port->PIO_PDSR;
}

uint8_t pio_conf_pin_to_peripheral(pio_reg_t *port, uint32_t periph,
		uint8_t pin_number) {
	// Disable interrupts on the pin
	port->PIO_IDR |= (0x1U << pin_number);

	// The pin will be set to peripheral B
	if (periph == PIO_PERIPH_B) { // 0 is peripheral A and 1 is B
		// Set to peripheral B
		port->PIO_ABSR |= (0x1U << pin_number);
	} else if (periph == PIO_PERIPH_A) {
		// Clear for peripheral A
		port->PIO_ABSR &= ~(0x1U << pin_number);
	}
	// The pin will be set in peripheral mode (not controllable by PIO)
	port->PIO_PDR |= (0x1U << pin_number);
	return 1;
}
