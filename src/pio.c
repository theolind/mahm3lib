/*
 * pio.c
 *
 *  Created on: Sep 18, 2014
 *      Author: Theodor Lindquist
 */

void digital_io_init() {
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

void digital_io_close() {
	//TODO undo what has been done in digital_io_init
}

void digital_io_conf_pin(uint8_t port, uint8_t pin_number, uint8_t input, uint8_t pullup) {
	//use the port function to set a single pin
	digital_io_conf_port(port, (1<<pin_number), (input<<pin_number), (pullup<<pin_number));
}

void digital_io_conf_port(uint8_t port, uint32_t inputs, uint32_t pullups) {
	uint32_t *p_reg;	//register pointer points to the register currently used

	//enable the pins
	p_reg = port+PIO_PER;	//point to PIO enable register

	/**
	 * TODO
	 * Enable pullup in PIO_PUER
	 * Disable pullup in PIO_PUDR
	 *
	 * Enable pin in PIO_PER
	 * Disable pin in PIO_PDR
	 *
	 * Enable output in PIO_OER
	 * Disable output in PIO_ODR
	 */
}

//TODO void digital_io_set_pin(uint8_t port, uint8_t pin_number, uint8_t level);
//TODO void digital_io_set_port(uint8_t port, uint32_t levels);

uint8_t digital_io_read_pin(uint8_t port, uint8_t pin_number) {
	//return (digital_io_read_port(port) & (1<<pin_number)) >> pin_number; ?
}

uint32_t digital_io_read_port(uint8_t port) {
	/**
	 * TODO
	 * Read input from PIO_PDSR
	 */
}
