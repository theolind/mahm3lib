/*
 * uart.c
 * API for the UART.
 *
 * Author: Mathias Beckius
 * Date: September 22, 2014
 *
 * To do:
 * - Add some control of the parameters in uart_init().
 *   Invalid parameters should make the function return 0.
 */ 

#include "uart.h"

/*
 * Important! When a control of input parameters is implemented,
 * write a test for this.
 */
uint8_t uart_init (const uart_settings_t *settings) {

	// (MCK / 16) / baudrate
	uint32_t baudrate_clock = ((CPU_HZ >> 4) / settings->baudrate);

	// If baudrate is less than max value allow init
	if (baudrate_clock > UART_BSGR_MIN && baudrate_clock < UART_BSGR_MAX) {
		// reset and disable receiver & transmitter
		UART->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX |
						UART_CR_RXDIS | UART_CR_TXDIS;
		// configure baud rate
		UART->UART_BRGR = baudrate_clock;	// MCK / Baudrate

		// configure mode
		UART->UART_MR = settings->paritytype | UART_MR_CHMODE_NORMAL;
		// enable receiver and transmitter
		UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;

		return 0;
	} else {
		return 1;
	}
}

uint8_t uart_tx_ready(void) {
	return (UART->UART_SR & UART_SR_TXRDY);
}

uint8_t uart_rx_ready(void) {
	return (UART->UART_SR & UART_SR_RXRDY);
}

void uart_write_chr(char chr) {
	//Write character to Transmit Holding Register
	UART->UART_THR = (uint32_t) chr;
}

void uart_write_str(char *str) {
	while (*str != '\0') {
		while (!uart_tx_ready());	// Wait for tx ready
		uart_write_chr(*str);
		str++;
	}
}

char uart_read_chr(void) {
	//Read character from Receiver Holding Register
	char chr = (char) UART->UART_RHR;
	return chr;
}
