/*
 * uart.c
 * API for the UART.
 *
 * Author: Mathias Beckius
 * Date: September 21, 2014
 *
 * To do:
 * - Add some control of the parameters in uart_init().
 *   Invalid parameters should make the function return 0.
 */ 

#include "uart.h"

// UART Control Register
//uint32_t *const p_UART_CR = (uint32_t *) 0x400E0800U;
// UART Mode Register
//uint32_t *const p_UART_MR = (uint32_t *) 0x400E0804U;
// UART Status Register
//uint32_t *const p_UART_SR = (uint32_t *) 0x400E0814U;
// UART Receiver Holding Register
//uint32_t *const p_UART_RHR = (uint32_t *) 0x400E0818U;
// UART Transmit Holding Register
//uint32_t *const p_UART_THR = (uint32_t *) 0x400E081CU;
// UART Baud Rate Generator Register
//uint32_t *const p_UART_BRGR = (uint32_t *) 0x400E0820U;

uart_reg_t *const UART = (uart_reg_t *) 0x400E0800U;

/*
 * Important! When a control of input parameters is implemented,
 * write a test for this.
 */
uint8_t uart_init(const uart_settings_t *options) {
	// reset and disable receiver & transmitter
	UART->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX |
					UART_CR_RXDIS | UART_CR_TXDIS;
	// configure baud rate
	UART->UART_BRGR = (84000000UL >> 4) / options->baudrate;
	//(sysclk_get_cpu_hz() >> 4) / options->baudrate;

	// configure mode
	UART->UART_MR = options->paritytype | UART_MR_CHMODE_NORMAL;
	// enable receiver and transmitter
	UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;

	return 1;
}

uint8_t uart_tx_ready(void) {
	return (UART->UART_SR & UART_SR_TXRDY);
}

uint8_t uart_rx_ready(void) {
	return (UART->UART_SR & UART_SR_RXRDY);
}

void uart_write_chr(char chr) {
	//write character to Transmit Holding Register
	UART->UART_THR = (uint32_t) chr;
}

void uart_write_str(char *str) {
	while (*str != '\0') {
		while (!uart_tx_ready());
		uart_write_chr(*str);
		str++;
	}
}

char uart_read_chr(void) {
	//read character from Receiver Holding Register
	char chr = (char) UART->UART_RHR;
	return chr;
}
