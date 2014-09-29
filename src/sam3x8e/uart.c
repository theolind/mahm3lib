/*
 * uart.c
 *
 * Authors:	Mathias Beckius
 * 			Felix Ruponen
 *
 * Date:	28 September, 2014
 */ 

#include "uart.h"

void uart_init(const uart_settings_t *settings) {
	// reset and disable receiver & transmitter, reset status bits
	UART->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX |// UART_CR_RSTSTA |
					UART_CR_RXDIS | UART_CR_TXDIS;
	// configure baud rate
	UART->UART_BRGR = (84000000UL >> 4) / settings->baud_rate;//45;//UART_BRGR_CD(settings->baud_rate);
	// configure mode
	UART->UART_MR = settings->parity;// | UART_MR_CHMODE_NORMAL;//0;/*UART_MR_PAR(settings->parity) |
					//UART_MR_CHMODE(settings->ch_mode);*/
	// enable receiver and transmitter
	UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;
}

uint8_t uart_tx_ready(void) {
	return (UART->UART_SR & UART_SR_TXRDY);
}

uint8_t uart_rx_ready(void) {
	return (UART->UART_SR & UART_SR_RXRDY);
}

void uart_write_char(char chr) {
	UART->UART_THR = (uint32_t) chr;
}

void uart_write_str(char *str) {
	while (*str != '\0') {
		while (!uart_tx_ready());
		uart_write_char(*str);
		str++;
	}
}

char uart_read_char(void) {
	char chr = (char) UART->UART_RHR;
	return chr;
}
