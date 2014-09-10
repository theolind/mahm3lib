/*
 * io_uart.c
 *
 * This file contains functions for UART communication.
 * 
 * Created by: Mathias Beckius, 2014-03-18
 *
 * Modified: 2014-03-20
 * Added explanation of why activation of internal pull-up is
 * necessary. Did also change input parameter type for 'uart_config()'.
 *
 * Modified: 2014-09-07
 * Made the UART library 100% free from ASF!
 */ 

#include "io_uart.h"

/* UART Control Register (pointer) */
uint32_t *const p_UART_CR = (uint32_t *) 0x400E0800U;
/* UART Mode Register (pointer) */
uint32_t *const p_UART_MR = (uint32_t *) 0x400E0804U;
/* UART Status Register (pointer) */
uint32_t *const p_UART_SR = (uint32_t *) 0x400E0814U;
/* UART Receiver Holding Register (pointer) */
uint32_t *const p_UART_RHR = (uint32_t *) 0x400E0818U;
/* UART Transmit Holding Register (pointer) */
uint32_t *const p_UART_THR = (uint32_t *) 0x400E081CU;
/* UART Baud Rate Generator Register (pointer) */
uint32_t *const p_UART_BRGR = (uint32_t *) 0x400E0820U;

/*
 * UART Configuration
 * Configures UART communication with a certain baud rate and parity setting.
 *
 * Important! Atmel SAM3X8E ARM Cortex-M3 works with 3.3V. To achieve full USB
 * speed, Arduino Due has been designed to provide 5V power supply to the 16U2
 * chip. There's a level shifter connected to the RX0 to adapt the
 * voltage levels between the 16u2 IC and the SAM3X UART.
 * To make UART communication working in both directions, you must activate
 * the pull-up resistor on the RX0 pin.
 */
void uart_config(const uart_options_t *options)
{
	// Peripheral Clock Enable Register 0
	uint32_t *const p_PMC_PCER0 = (uint32_t *) 0x400E0610U;
	// PIO Controller PIO Disable Register - PIOA
	uint32_t *const p_PIO_PDR = (uint32_t *) 0x400E0E04U;
	// PIO Controller Output Enable Register - PIOA
	uint32_t *const p_PIO_OER = (uint32_t *) 0x400E0E10U;
	// PIO Pull Up Enable Register (PIOA)
	uint32_t *const p_PIO_PUER = (uint32_t *) 0x400E0E64U;
	
	// Enable Peripheral Clock for UART.
	// This register can only be written if the WPEN bit is cleared in “PMC Write Protect Mode Register” .
	*p_PMC_PCER0 = 1 << 8;
	// reset and disable receiver & transmitter
	UART_CR = UART_CR_RSTRX | UART_CR_RSTTX	| UART_CR_RXDIS | UART_CR_TXDIS;
	// configure baud rate
	UART_BRGR = (84000000UL >> 4) / options->baudrate; //(sysclk_get_cpu_hz() >> 4) / options->baudrate;
	// configure mode
	UART_MR = options->paritytype | UART_MR_CHMODE_NORMAL;
	// enable receiver and transmitter
	UART_CR = UART_CR_RXEN | UART_CR_TXEN;
	
	/* Configure UART pins */
	// Remove the pins from under the control of PIO
	// This register can only be written if the WPEN bit is cleared in “PIO Write Protect Mode Register” .
	*p_PIO_PDR = (1 << 8) | (1 << 9);
	// configure TX0 as output
	*p_PIO_OER = (1 << 9);
	// configure RX0 pin as pull-up
	*p_PIO_PUER = (1 << 8);
}

/*
 * Transmitter Ready?
 * Return 1 if "Transmitter Ready" flag is set, otherwise 0.
 */
int uart_transmitter_ready(void)
{
	return (UART_SR & UART_SR_TXRDY);
}

/*
 * Receiver Ready?
 * Return 1 if "Receiver Ready" flag is set, otherwise 0.
 */
int uart_receiver_ready(void)
{
	return (UART_SR & UART_SR_RXRDY);
}

/*
 * Send character
 * Write character to Transmit Holding Register.
 */
void uart_send_char(uint8_t chr)
{
	UART_THR = chr;
}

/*
 * Receive character
 * Read character from Receiver Holding Register.
 */
char uart_receive_char(void)
{
	char chr = UART_RHR;
	return chr;
}