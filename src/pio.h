/*
 * pio.h
 *
 *  Created on: Sep 18, 2014
 *      Author: Theodor Lindquist
 */

#ifndef PIO_H_
#define PIO_H_

#include <stdint.h>

#define PIO_PORTA 0x01
#define PIO_PORTB 0x02
#define PIO_PORTC 0x03
#define PIO_INPUT 0x01
#define PIO_OUTPUT 0x00

/**
 * Start and stop Power Management Controller (PMC)
 */
void digital_io_init();
void digital_io_close();

/**
 * Configure a pin to be either an input or an output
 */
void digital_io_conf_pin(uint8_t port, uint8_t pin_number, uint8_t input, uint8_t pullup);
void digital_io_conf_port(uint8_t port, uint32_t inputs, uint8_t pullup);

/**
 * Set a pin to either a high or a low level
 */
void digital_io_set_pin(uint8_t port, uint8_t pin_number, char level);
void digital_io_set_port(uint8_t port, uint32_t levels);

/**
 * Check if a pin is either high or low
 */
char digital_io_read_pin(uint8_t port, uint8_t pin_number);
uint32_t digital_io_read_port(uint8_t port);



#endif /* PIO_H_ */
