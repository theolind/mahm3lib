/*
 * pio.c
 *
 *  Created on: Sep 18, 2014
 *      Author: Theodor Lindquist
 */

void digital_io_init() {
	/**
	 * Periphial IDs for PIO*
	 * PIO  PID   BIT
	 * PIOA PID11 11
	 * PIOB PID12 12
	 * PIOC PID13 13
	 * PIOD PID14 14
	 * PIOE PID15 15
	 * PIOF PID16 16
	 *
	 * Set bits 11 to 16 in PMC_PCER0 (0x400E0610) to enable clocks for a port
	 * To do this, first clear WPEN bit (bit 0) in PMC_WPMR (0x400E06E4)
	 */
}

void digital_io_close() {

}

//TODO void digital_io_conf_pin(uint8_t port, uint8_t pin_number, uint8_t input, uint8_t pullup);
//TODO void digital_io_conf_port(uint8_t port, uint32_t inputs, uint32_t pullups);
//TODO void digital_io_set_pin(uint8_t port, uint8_t pin_number, uint8_t level);
//TODO void digital_io_set_port(uint8_t port, uint32_t levels);
//TODO uint8_t digital_io_read_pin(uint8_t port, uint8_t pin_number);
//TODO uint32_t digital_io_read_port(uint8_t port);
