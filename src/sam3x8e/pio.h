/**
 * @file
 * @brief Digital IO controller
 * @details {The functions in this file controls the digital input and output
 * of the processor.}
 *
 * @author Theodor Lindquist
 * @author Soded Alatia
 * @author Saeed Ghasemi
 *
 * @version 0.3
 * @since {The peripheral multiplexing is added since version 0.3}
 * @date 18-09-2014
 *
 * @pre First initialize the board, if you want to read inputs, you need to call digital_io_init()
 */

#ifndef PIO_H_
#define PIO_H_

#include <stdint.h>

// addresses to ports
#define PIO_PORTA 0x400E0E00
#define PIO_PORTB 0x400E1000
#define PIO_PORTC 0x400E1200
#define PIO_PORTD 0x400E1400
#define PIO_PORTE 0x400E1600
#define PIO_PORTF 0x400E1800

// port register offsets
#define PIO_PER 0x0000	//PIO enable register
#define PIO_PDR 0x0004	//PIO disable register
#define PIO_PSR 0x0008  //PIO status register

#define PIO_OER 0x0010	//output enable register
#define PIO_ODR 0x0014	//output disable register
#define PIO_OSR 0x0018 	//output status register

#define PIO_SODR 0x0030	//set output data register
#define PIO_CODR 0x0034	//clear output data register
#define PIO_ODSR 0x0038 //output data status register
#define PIO_PDSR 0x003C	//pin data status register

#define PIO_PUDR 0x0060	//pull-up disable register
#define PIO_PUER 0x0064	//pull-up enable register
#define PIO_PUSR 0x0068	//pull-up status register

#define PIO_ABSR 0x0070	//Peripheral AB Select Register

#define PIO_OWER 0x00A0	//Output Write Enable
#define PIO_OWDR 0x00A4	//Output Write Disable
#define PIO_OWSR 0x00A8	//Output Write Status Register


typedef enum {OFF, ON} pio_init_setting;
typedef struct pio_init_param {
	pio_init_setting porta;
	pio_init_setting portb;
	pio_init_setting portc;
	pio_init_setting portd;
	pio_init_setting porte;
	pio_init_setting portf;
} pio_init_param;

/**
 * Initialize the clocks in the power management controller, necessary for
 * using digital_io_read_*.
 */
void pio_init(pio_init_param *param);

/**
 * Deinitialize the clocks in the power management controller, saves power if
 * you don't need to use digital_io_read_* anymore.
 */
void pio_close(void);

/**
 * Configure a pin to be either an input or an output
 * @param port the port to which the pin belong
 * @param pin_number the pin number (on the port) to configure
 * @param input {set to 1 to configure pin as an input, 0 to configure as an
 * output (default)}
 * @param pullup {set to 1 to configure pin with internal pullup (default),
 * 0 to configure without}
 */
void pio_conf_pin(uint32_t port, uint8_t pin_number, uint8_t input, uint8_t pullup);

/**
 * Configure multiple pins to be either inputs or outputs
 * @param port the port to which the pins belong
 * @param pin_numbers the pin numbers (on the port) to configure (1 means, will
 * be configured, 0 = will not be configured)}
 * @param input {set to 1 to configure pin as an input, 0 to configure as an
 * output (default)}
 * @param pullup {set to 1 to configure pin with internal pullup (default),
 * 0 to configure without}
 */
void pio_conf_pins(uint32_t port, uint32_t pin_numbers, uint8_t input, uint8_t pullup);

/**
 * Configure a whole to be either inputs or outputs, this will reset the whole port
 * @param port the port to configure
 * @param inputs {set a bit to 1 to configure the corresponding pin as an input,
 * 0 to configure as output}
 * @param pullups {set a bit to 1 to configure the corresponding pin with an
 * internal pullup, 0 to configure without internal pullup}
 */
void pio_conf_port(uint32_t port, uint32_t inputs, uint32_t pullups);

/**
 * Set a pin to either a high or a low level
 * @param port the port to which the pin belongs
 * @param pin_number the pin number (on the port) to configure
 * @param level 1 is high, 0 is low
 */
void pio_set_pin(uint32_t port, uint8_t pin_number, uint8_t level);

/**
 * Set multiple pins to either a high or a low level
 * @param port the port to which the pin belongs
 * @param pin_numbers the pin numbers (on the port) to configure (1= configure the pin, 0= do not configure the pin)
 * @param level 1 is high, 0 is low
 */
void pio_set_pins(uint32_t port, uint32_t pin_numbers, uint8_t level);

/**
 * Set an entire port to either high or low levels
 * @param port the port to set levels on
 * @param levels set a bit to 1 to set a high level for the corresponding pin, 0 to set a low level
 */
void pio_set_port(uint32_t port, uint32_t levels);

/**
 * Check if a pin is either high or low
 * @param port the port to which the pin belongs
 * @param pin_number the pin number (on the port) to check
 * @return 1 if high, 0 if low
 */
uint8_t pio_read_pin(uint32_t port, uint8_t pin_number);

/**
 * Check the levels of an entire port
 * @param port the port to check
 * @return A bit with value 1 means the corresponding pin is high, bit with 0 means the pin is low
 */
uint32_t pio_read_port(uint32_t port);

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
		uint32_t periph, uint32_t pin_number);

#endif /* PIO_H_ */
