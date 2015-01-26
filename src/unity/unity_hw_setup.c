/*
 * unity_hw_setup.c
 *
 * Author:	Mathias Beckius
 *
 * Date:	12 October 2014
 */

#include "unity_hw_setup.h"
#include "sam3x8e/eefc.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/uart.h"
#include "sam3x8e/wdt.h"

static void configure_uart(void) {
	const uart_settings_t uart_settings = {
		.baud_rate = 115200,
		.parity = UART_PARITY_NO,
		.ch_mode = UART_CHMODE_NORMAL
	};

	// enable Peripheral Clock for UART.
	pmc_enable_peripheral_clock(ID_UART);

	// remove the pins from under the control of PIO
	pio_disable_pin(PIOA, 8);	//RX0
	pio_disable_pin(PIOA, 9);	//TX0

	// initialize UART
	uart_init(&uart_settings);
}

void unity_hw_setup(void) {
	/*
	 * Set Flash Wait State, by defining the number of cycles
	 * for read and write operations: FWS + 1
	 */
	eefc_set_flash_wait_state(EEFC0, 4);
	eefc_set_flash_wait_state(EEFC1, 4);

	// initialize system clock
	pmc_init_system_clock();

	// disable the watchdog timer
	wdt_disable();

	// configure UART so Unity can use USB/RS-232 as output
	configure_uart();
}
