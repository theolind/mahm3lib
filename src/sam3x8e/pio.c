/*
 * pio.c
 *
 * Author: 	Theodor Lindquist
 *			Soded Alatia
 * 			Felix Ruponen
 * 			Mathias Beckius
 *
 * Date:		12 October 2014
 */

#include "pio.h"
#include "sam3x8e/bitwise_operations.h"

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
	if (level == 1) {
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
	set_bit_in_register(&port->PIO_IDR, pin_number);

	// The pin will be set to peripheral B
	if (periph == PIO_PERIPH_B) { // 0 is peripheral A and 1 is B
		// Set to peripheral B
		set_bit_in_register(&port->PIO_ABSR, pin_number);
	} else if (periph == PIO_PERIPH_A) {
		// Clear for peripheral A
		clear_bit_in_register(&port->PIO_ABSR, pin_number);
	}
	// The pin will be set in peripheral mode (not controllable by PIO)
	set_bit_in_register(&port->PIO_PDR, pin_number);
	return 1;
}
////////////////////////////////////////////////////////////////

/*
 * This function will enable the interrupt on a given pin.
 * The interrupt can be configured in all conditions as they can always detect
 * changes, even when in peripheral mode.
 *
 * This function is the primary function for using interrupts. There are
 * however, additional interrupt functions that can be used.
 *
 *
 * @param port The PIO-port to operate on
 * @param pin The pin-number of the pio-port.
 * @param detection The detection method to be used for the interrupt.
 * Use one of the predefines for this input with prefix: PIO_INT_
 * @return
 */
uint8_t pio_conf_interrupt(pio_reg_t *port, uint32_t pin, uint32_t detection) {
	if(detection == PIO_INT_DISABLE){
		// disable interrupt and additional interrupts mode
		port->PIO_IDR = (0x1u << pin);
		port->PIO_AIMDR = (0x1u << pin);
	}else if(detection == PIO_INT_EDGE_CHANGE){
		// Enable interrupt but disable additional modes
		port->PIO_IER = (0x1u << pin);
		port->PIO_AIMDR = (0x1u << pin);
	}else if(detection == PIO_INT_EDGE_RISING){
		// Enable interrupt and enable additional modes
		port->PIO_IER = (0x1u << pin);
		port->PIO_AIMER = (0x1u << pin);
		// Set to edge detection
		port->PIO_ESR = (0x1u << pin);
		// set to detect rising edge
		port->PIO_REHLSR = (0x1u << pin);
	}else if(detection == PIO_INT_EDGE_FALLING){
		// Enable interrupt and enable additional modes
		port->PIO_IER = (0x1u << pin);
		port->PIO_AIMER = (0x1u << pin);
		// Set to edge detection
		port->PIO_ESR = (0x1u << pin);
		// set to detect falling edge
		port->PIO_FELLSR = (0x1u << pin);
	}else if(detection == PIO_INT_LEVEL_HIGH){
		// Enable interrupt and enable additional modes
		port->PIO_IER = (0x1u << pin);
		port->PIO_AIMER = (0x1u << pin);
		// Set to level detection
		port->PIO_LSR = (0x1u << pin);
		// set to detect high level
		port->PIO_REHLSR = (0x1u << pin);
	}else if(detection == PIO_INT_LEVEL_LOW){
		// Enable interrupt and enable additional modes
		port->PIO_IER = (0x1u << pin);
		port->PIO_AIMER = (0x1u << pin);
		// Set to level detection
		port->PIO_LSR = (0x1u << pin);
		// set to detect low level
		port->PIO_FELLSR = (0x1u << pin);
	}
	return 1;
}

uint8_t pio_interrupt_enable(pio_reg_t *port, uint32_t pin) {
	port->PIO_IER = (0x1u << pin);
	return 1;
}

uint8_t pio_interrupt_disable(pio_reg_t *port, uint32_t pin) {
	port->PIO_IDR = (0x1u << pin);
	return 1;
}
/*
 * This function checks to see if an interrupt has occurred on a certain pin.
 *
 * @param port The PIO-port to operate on
 * @param pin The pin-number of the pio-port.
 * @return Returns 1 if an interrupt has occurred since last read of PIO_ISR.
 */
uint8_t pio_get_interrupt_status(pio_reg_t *port, uint32_t pin) {
	return (port->PIO_ISR & (0x1u << pin)) > 0;
}

/*
 * This function checks to see if interrupt is enabled for a certain pin.
 *
 * @param port The PIO-port to operate on.
 * @param pin The pin-number of the pio-port.
 * @return Returns high if interrupt is enabled, otherwise zero.
 */
uint8_t pio_get_interrupt_mask(pio_reg_t *port, uint32_t pin) {
	return (port->PIO_IMR & (0x1u << pin)) > 0;
}

/*
 * This function will enable additional modes for the interrupt of a given pin.
 * If additional modes are disabled the interrupt mode will be the basic one
 * which is to fire at both rising and falling edge. If level detection or just
 * falling edge is wanted then additional modes are needed.
 *
 * @param port The PIO-port to operate on.
 * @param pin The pin-number of the pio-port.
 * @return error, 1 = SUCCESS and 0 = FAIL
 */
uint8_t pio_interrupt_additional_modes_enable(pio_reg_t *port,
		uint32_t pin) {
	port->PIO_AIMER = (0x1u << pin);
	return 1;
}
/*
 * This function will disable additional modes for the interrupt of a given pin.
 * If additional modes are disabled the interrupt mode will be the basic one
 * which is to fire at both rising and falling edge. If level detection or just
 * falling edge is wanted then additional modes are needed.
 *
 * @param port The PIO-port to operate on.
 * @param pin The pin-number of the pio-port.
 * @return error, 1 = SUCCESS and 0 = FAIL
 */
uint8_t pio_interrupt_additional_modes_disable(pio_reg_t *port,
		uint32_t pin) {
	port->PIO_AIMDR = (0x1u << pin);
	return 1;
}

/**
 * This function will return 1 if additional modes ar enabled for the given
 * pin.
 *
 * @param port
 * @param pin
 * @return
 */
uint8_t pio_get_interrupt_additional_modes_mask(pio_reg_t *port,
		uint32_t pin) {
	return (port->PIO_AIMMR & (0x1u << pin)) > 0;
}

/**
 * This function will set the additional interrupt mode to edge detection.
 *
 * @param port
 * @param pin
 * @return
 */
uint8_t pio_set_interrupt_to_edge_detection(pio_reg_t *port, uint32_t pin) {
	port->PIO_ESR = (0x1u << pin);
	return 1;
}

/**
 * This function will set the additional interrupt mode to level detection.
 *
 * @param port
 * @param pin
 * @return
 */
uint8_t pio_set_interrupt_to_level_detection(pio_reg_t *port, uint32_t pin) {
	port->PIO_LSR = (0x1u << pin);
	return 1;
}

/**
 * This function will return the detection method for a given pin interrupt.
 *
 * @param port
 * @param pin
 * @return if high then detection method is ...
 */
uint8_t pio_get_interrupt_detection_method(pio_reg_t *port, uint32_t pin) {
	return (port->PIO_ELSR & (0x1u << pin)) > 0;
}



/**
 * This function will set the final step in defining an interrupt for a pin.
 * If additional modes are enabled, then this function can let you choose
 * between rising/high edge/level detection or falling/low edge/level detection.
 *
 * @param port
 * @param pin
 * @param detection
 * @return
 */
uint8_t pio_set_interrupt_method(pio_reg_t *port, uint32_t pin,
		uint32_t detection) {
	if (detection == PIO_INT_EDGE_FALLING || detection == PIO_INT_LEVEL_LOW) {
		port->PIO_FELLSR = (1U << pin);
	} else if (detection == PIO_INT_EDGE_RISING || detection == PIO_INT_LEVEL_HIGH) {
		port->PIO_REHLSR = (0x1u << pin);
	}
	return 1;
}




/*
Interrupt Enable Register
PIO_IER Write-only –
Interrupt Disable Register
PIO_IDR Write-only –
Interrupt Mask Register
PIO_IMR 		Read-only 0x00000000
Interrupt Status Register(4)
PIO_ISR 		Read-only 0x00000000

Additional Interrupt Modes Enable Register
PIO_AIMER Write-Only –
Additional Interrupt Modes Disables Register
PIO_AIMDR Write-Only –
Additional Interrupt Modes Mask Register
PIO_AIMMR 		Read-Only 0x00000000

Edge Select Register
PIO_ESR Write-Only –
Level Select Register
PIO_LSR Write-Only –
Edge/Level Status Register
PIO_ELSR 		Read-Only 0x00000000

Falling Edge/Low Level Select Register
PIO_FELLSR Write-Only –
Rising Edge/ High Level Select Register
PIO_REHLSR Write-Only –
Fall/Rise - Low/High Status Register
PIO_FRLHSR 		Read-Only 0x00000000

*/
