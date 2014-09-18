/*!
 * \brief Digital IO controller
 * \details The functions in this file controls the digital input and output of the processor
 *
 * \author Theodor Lindquist
 *
 * \version 0.1
 * \date 18-09-2014
 *
 * \pre First initialize the board, if you want to read inputs, you need to call digital_io_init()
 */

#ifndef PIO_H_
#define PIO_H_

#include <stdint.h>

// To be determined
#define PIO_PORTA 0x01
#define PIO_PORTB 0x02
#define PIO_PORTC 0x03
#define PIO_INPUT 0x01
#define PIO_OUTPUT 0x00

/**
 * Initialize the clocks in the power management controller, neccecary for using digital_io_read_*.
 */
void digital_io_init();

/**
 * Deinitialize the clocks in the power management controller, saves power if you don't need to use digital_io_read_* anymore.
 */
void digital_io_close();

/**
 * Configure a pin to be either an input or an output
 * @param port the port to which the pin belongs
 * @param pin_number the pin number (on the port) to configure
 * @param input (optional) set to 1 to configure pin as an input, 0 to configure as an output (default)
 * @param pullup (optional) set to 1 to configure pin with internal pullup (default), 0 to configure without
 */
void digital_io_conf_pin(uint8_t port, uint8_t pin_number, uint8_t input, uint8_t pullup);

/**
 * Configure a port (multiple pins) to be either inputs or outputs
 * @param port the port to configure
 * @param inputs set a bit to 1 to configure the corresponding pin as an input, 0 to configure as output
 * @param pullups set a bit to 1 to configure the corresponding pin with an internal pullup, 0 to configure without internal pullup
 */
void digital_io_conf_port(uint8_t port, uint32_t inputs, uint32_t pullups);

/**
 * Set a pin to either a high or a low level
 * @param port the port to which the pin belongs
 * @param pin_number the pin number (on the port) to configure
 * @param level 1 is high, 0 is low
 */
void digital_io_set_pin(uint8_t port, uint8_t pin_number, uint8_t level);

/**
 * Set an entire port to either high or low levels
 * @param port the port to set levels on
 * @param levels set a bit to 1 to set a high level for the correspondingpin, 0 to set a low level
 */
void digital_io_set_port(uint8_t port, uint32_t levels);

/**
 * Check if a pin is either high or low
 * @param port the port to which the pin belongs
 * @param pin_number the pin number (on the port) to check
 * @return 1 if high, 0 if low
 */
uint8_t digital_io_read_pin(uint8_t port, uint8_t pin_number);

/**
 * Check the levels of an entire port
 * @param port the port to check
 * @return A bit with value 1 means the corresponding pin is high, bit with 0 means the pin is low
 */
uint32_t digital_io_read_port(uint8_t port);



#endif /* PIO_H_ */
