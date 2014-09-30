/*
 * pio.c
 *
 *  Created on: Sep 18, 2014
 *      Author: Theodor Lindquist
 *      Author: Soded Alatia
 *      Author: Saeed Ghasemi
 */

#include "global_entities.h"
#include "pio.h"

void pio_init(pio_init_param *param) {
	/**
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
	uint32_t clk_config = 0;

	if(param->porta == ON) {
		clk_config |= (1<<11);
	}

	if(param->portb == ON) {
		clk_config |= (1<<12);
	}

	if(param->portc == ON) {
		clk_config |= (1<<13);
	}

	if(param->portd == ON) {
		clk_config |= (1<<14);
	}

	if(param->porte == ON) {
		clk_config |= (1<<15);
	}

	if(param->portf == ON) {
		clk_config |= (1<<16);
	}

	uint32_t *p_pmc_pcer0 = (uint32_t *)0x400E0610;
	*p_pmc_pcer0 |= clk_config;
}

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
		//use the output enable register to enable outputs
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
	if(level == 1) {
		p_reg = (uint32_t *)(port+PIO_SODR);
		//set pins high
		*p_reg |= pin_numbers;
	} else {
		p_reg = (uint32_t *)(port+PIO_CODR);
		//set pins low
		*p_reg |= pin_numbers;
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


////////////////////////////////////////////////////////
// Internal (not for user)
#define PERIPH_A			0
#define PERIPH_B			1

////////////////////////////////////////////////////////
// External (to be used by the user)
//Physical pin mapping
//PIO_PIN_[package pin number]_[port and bit number]
#define PIN_PIO_1_PB26			(26)
#define PIN_PIO_42_PA19			(19)
#define PIN_PIO_59_PC2			(2)
#define PIN_PIO_60_PC3			(3)
#define PIN_PIO_63_PC5			(5)
#define PIN_PIO_64_PC6			(6)
#define PIN_PIO_65_PC7			(7)
#define PIN_PIO_66_PC8			(8)
#define PIN_PIO_67_PC9			(9)
#define PIN_PIO_72_PA20			(20)
#define PIN_PIO_95_PC13			(13)
#define PIN_PIO_97_PC15			(15)
#define PIN_PIO_99_PC17			(17)
#define PIN_PIO_100_PC18		(18)
#define PIN_PIO_101_PBC19		(19)
#define PIN_PIO_116_PC4			(4)
#define PIN_PIO_140_PB14		(14)

////////////////////////////////////////////////////////
// External (to be used by the user)
#define PIN_PWMH0_60			PIN_PIO_60_PC3
#define PIN_PWML0_59			PIN_PIO_59_PC2

////////////////////////////////////////////////////////



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
 * @param pin_number {This is the pin number in the port register.
 * Start with prefix: PIN_[peripheral] to get to predefined pins.}
 * @return error (1  = SUCCESS, 0 = FAIL)
 * @bug {not yet tested. All ports will be included after initial testing.}
 */
uint8_t pio_conf_pin_to_peripheral(uint32_t port,
		uint32_t periph, uint32_t pin_number){
	uint32_t *p_reg;

	// The pin is now in peripheral mode (not controlled by PIO)
	p_reg = (uint32_t *) (port + PIO_PDR);
	*p_reg = (1 << pin_number);
	// The pin is now set to peripheral B
	p_reg = (uint32_t *) (port + PIO_ABSR);
	if(periph){
		*p_reg |= (1 << pin_number);
	}else{
		*p_reg &= ~(1 << pin_number);
	}
	return SUCCESS;
}


