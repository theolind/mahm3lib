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
uint8_t uart_init(uart_reg_t *uart, const uart_settings_t *options) {
	// reset and disable receiver & transmitter
	uart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX |
					UART_CR_RXDIS | UART_CR_TXDIS;
	// configure baud rate
	uart->UART_BRGR = (84000000UL >> 4) / options->baudrate;
	//(sysclk_get_cpu_hz() >> 4) / options->baudrate;

	// configure mode
	uart->UART_MR = options->paritytype | UART_MR_CHMODE_NORMAL;
	// enable receiver and transmitter
	uart->UART_CR = UART_CR_RXEN | UART_CR_TXEN;

	return 1;
}

uint8_t uart_tx_ready(uart_reg_t *uart) {
	return (uart->UART_SR & UART_SR_TXRDY);
}

uint8_t uart_rx_ready(uart_reg_t *uart) {
	return (uart->UART_SR & UART_SR_RXRDY);
}

void uart_write_chr(uart_reg_t *uart, char chr) {
	//write character to Transmit Holding Register
	uart->UART_THR = (uint32_t) chr;
}

void uart_write_str(uart_reg_t *uart, char *str) {
	while (*str != '\0') {
		while (!uart_tx_ready(uart));
		uart_write_chr(uart, *str);
		str++;
	}
}

char uart_read_chr(uart_reg_t *uart) {
	//read character from Receiver Holding Register
	char chr = (char) uart->UART_RHR;
	return chr;
}
