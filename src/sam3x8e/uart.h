/**
* @file uart.h
* @brief UART - Universal Asynchronous Receiver Transceiver
* @details With the UART API you can configure UART communication.
* @details Important! The API is currently limited. Not all features are
* @details implemented!
* @pre Initialize the system clock
*
* Important! Atmel SAM3X8E ARM Cortex-M3 works with 3.3V. To achieve full USB
* speed, Arduino Due has been designed to provide 5V power supply to the 16U2
* chip. There's a level shifter connected to the RX0 to adapt the
* voltage levels between the 16u2 IC and the SAM3X UART.
* To make UART communication working in both directions, you must activate
* the pull-up resistor on the RX0 pin.
*
* @author Mathias Beckius
* @author Felix Ruponen
* @date 29 September 2014
*/

#ifndef UART_H_
#define UART_H_

#include <inttypes.h>

// Pointer to registers of the UART peripheral.
#define UART ((uart_reg_t *) 0x400E0800U)

///@cond
/*
 * CPU Clock frequency - only for temporary usage! Should be replaced by
 * a common function!
 */
#define CPU_HZ	(84000000UL)

// UART Control Register - Reset Receiver
#define UART_CR_RSTRX 					(1u << 2)
// UART Control Register - Reset Transmitter
#define UART_CR_RSTTX 					(1u << 3)
// UART Control Register - Receiver Enable
#define UART_CR_RXEN 					(1u << 4)
// UART Control Register - Receiver Disable
#define UART_CR_RXDIS					(1u << 5)
// UART Control Register - Transmitter Enable
#define UART_CR_TXEN 					(1u << 6)
// UART Control Register - Transmitter Disable
#define UART_CR_TXDIS 					(1u << 7)
// UART Control Register - Reset Status Bits
#define UART_CR_RSTSTA 					(1u << 8)
///@endcond

/*
 * UART Mode Register - Parity setting
 * Macro for setting parity. The value will be filtered with a bit mask,
 * to avoid invalid values.
 */
#define UART_MR_PAR(parity)				((7u & (parity)) << 9)
/// Even Parity
#define UART_PARITY_EVEN 				(0)
/// Odd Parity
#define UART_PARITY_ODD 				(1)
/// Space: parity forced to 0
#define UART_PARITY_SPACE 				(2)
/// Mark: parity forced to 1
#define UART_PARITY_MARK 				(3)
/// No Parity
#define UART_PARITY_NO 					(4)

/*
 * UART Mode Register - Channel Mode
 * Macro for setting channel mode. The value will be filtered with a bit mask,
 * to avoid invalid values.
 */
#define UART_MR_CHMODE(mode)			((3u & (mode)) << 14)
/// Normal Mode
#define UART_CHMODE_NORMAL 				(0)
/// Automatic Echo
#define UART_CHMODE_AUTOMATIC 			(1)
/// Local Loopback
#define UART_CHMODE_LOCAL_LOOPBACK 		(2)
/// Remote Loopback
#define UART_CHMODE_REMOTE_LOOPBACK 	(3)

///@cond
// Defines for the UART Status Register
// Receiver Ready?
#define UART_SR_RXRDY 					(1u << 0)
// Transmitter Ready?
#define UART_SR_TXRDY 					(1u << 1)

/*
 * UART Baud Rate Generator Register - Clock Divisor
 * Macro for setting clock divisor. Value will be filtered with a bit mask,
 * to avoid invalid values. Clock Divisor is calculated according to:
 * 		(MCK / (16 x Baud rate))
 */
#define UART_BRGR_CD(baud)				(0xFFFFu & ((CPU_HZ >> 4) / (baud)))

/*
 * Mapping of UART registers
 * Base address: 0x400E0800
 */
typedef struct uart_reg {
	// Control Register, offset 0x0000
	uint32_t UART_CR;
	// Mode Register, offset 0x0004
	uint32_t UART_MR;
	// Interrupt Enable Register, offset 0x0008
	uint32_t UART_IER;
	// Interrupt Disable Register, offset 0x000C
	uint32_t UART_IDR;
	// Interrupt Mask Register, offset 0x0010
	uint32_t UART_IMR;
	// Status Register, offset 0x0014
	uint32_t UART_SR;
	// Receiver Holding Register, offset 0x0018
	uint32_t UART_RHR;
	// Transmit Holding Register, offset 0x001C
	uint32_t UART_THR;
	// Baud Rate Generator Register, offset 0x0020
	uint32_t UART_BRGR;
} uart_reg_t;

///@endcond

/**
 * Input parameters when initializing RS232 and similar modes.
 */
typedef struct uart_settings {
	/** Set baud rate of the UART. */
	uint32_t baud_rate;
	/**
	 * Parity: UART_PARITY_EVEN, UART_PARITY_ODD,
	 * UART_PARITY_SPACE, UART_PARITY_MARK, UART_PARITY_NO.
	 */
	uint32_t parity;
	/**
	 * Channel Mode: UART_CHMODE_NORMAL, UART_CHMODE_AUTOMATIC,
	 * UART_CHMODE_LOCAL_LOOPBACK, UART_CHMODE_REMOTE_LOOPBACK.
	 */
	uint32_t ch_mode;
} uart_settings_t;

/**
 * Initialization of the UART.
 * @param settings Settings for the initialization (baud rate, parity, etc).
 * @pre Enable PMC Peripheral Clock for UART.
 * @pre Disable the PIO from controlling PA8 (RX-pin) and PA9 (TX-pin).
 * @pre Enable pull-up on PA8 (RX-pin) - only when reading from UART on the
 * Arduino Due!
 */
void uart_init(const uart_settings_t *settings);

/**
 * Checks if a character can be sent by the UART.
 * @return 1 is returned when a character is ready to be sent,
 * otherwise 0 is returned.
 */
uint32_t uart_tx_ready(void);

/**
 * Checks if a character has received to the UART.
 * @return 1 is returned when a character has received,
 * otherwise 0 is returned.
 */
uint32_t uart_rx_ready(void);

/**
 * Sends a character to the UART.
 * @param chr Character (ASCII code) to send.
 * @pre Call uart_tx_ready() to check if a character can be sent.
 */
void uart_write_char(char chr);

/**
 * Sends a string of characters to the UART.
 * @param str String (pointer to character) to send.
 */
void uart_write_str(char *str);

/**
 * Reads a character from the UART.
 * @return Character.
 * @pre Call uart_rx_ready() to check if a character can be read.
 */
char uart_read_char(void);

#endif
