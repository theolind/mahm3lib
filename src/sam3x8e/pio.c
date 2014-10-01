/*
* pio.c
*
* Author: 	Theodor Lindquist
*			Soded Alatia
* 			Felix Ruponen
*
* Date:		29 September 2014
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
		port->PIO_SODR = pins;	//set pins
	} else {
		port->PIO_CODR = pins;	//clear pins
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



/**
 * This function will set the multiplexer inside the PIO peripheral to point
 * one of its pins to an embedded peripheral inside the MCU. The pin will after
 * this configuration no longer be controllable by the PIO.
 *
 * There is only one parameter to this function and that is the pin in question.
 * You can't use any pin for every purpose. Every pin has a digital function (PIO)
 * and a peripheral function. The pin mapping of this API includes all pins and
 * their secondary function. These pins are predefined. Start by writing
 * PIN_[peripheral][additional property and numbering]_[package pin number]
 * example:
 * PIN_PWMH0_60    or    PIN_PWML0_59
 * (These refer to the board independent pin mapping and will be available when
 * the API is included.)
 *
 * @author {Saeed Ghasemi}
 * @param port {This is the pio port of the pin to be multiplexed.}
 * @param periph {Point to your chosen peripheral. PERIPH_A or B}
 * @param pin_number {This is the pin number in the port register.
 * Start with prefix: PIN_[peripheral] to get to predefined pins.}
 * @return error (1  = SUCCESS, 0 = FAIL)
 * @bug {Not yet tested. All ports will be included after initial testing.}
 */
/*
uint8_t pio_conf_pin_to_peripheral(uint32_t port,
		uint32_t periph, uint32_t pin_number){
	uint32_t *p_reg;

	// The pin is now in peripheral mode (not controlled by PIO)
	p_reg = (uint32_t *) (port + PIO_PDR);
	*p_reg = (0x1U << pin_number);
	// The pin is now set to peripheral B
	p_reg = (uint32_t *) (port + PIO_ABSR);
	if(periph){
		*p_reg |= (0x1U << pin_number);
	}else{
		*p_reg &= ~(0x1U << pin_number);
	}
	return SUCCESS;
}

*/
