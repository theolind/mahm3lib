/*
 * UART unit tests
 *
 * Author:	Mathias Beckius
 *
 * Date:	29 September 2014
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/uart.h"
#include "test/test_uart.h"

/*
 * Send and receive a character in Local Loopback mode.
 * If these two conditions are satisfied, then the test is successful:
 *		1) Send 'A', receive 'A'
 *		2) Send 'A', don't receive 'B'
 */
void test_uart_send_receive_char_local_loopback_mode(void) {
	uint8_t result_true;
	uint8_t result_false;

	// UART settings
	uart_settings_t uart_settings = {
		.baud_rate = 115200,
		.parity = UART_PARITY_NO,
		.ch_mode = UART_CHMODE_LOCAL_LOOPBACK
	};
	// initialize UART
	uart_init(&uart_settings);

	// perform test
	while (!(uart_tx_ready()));		// wait until character can be sent
	uart_write_char('A');			// send character
	while (!(uart_rx_ready()));		// wait until character can be read

	// result should be true!
	result_true = (uint8_t) (uart_read_char() == 'A');

	while (!(uart_tx_ready()));		// wait until character can be sent
	uart_write_char('A');			// send character
	while (!(uart_rx_ready()));		// wait until character can be read

	// result should be false!
	result_false = (uint8_t) (uart_read_char() == 'B');

	// change channel mode, back to Normal Mode (otherwise Unity won't work!)
	uart_settings.ch_mode = UART_CHMODE_NORMAL;
	// reinitialize UART
	uart_init(&uart_settings);

	TEST_ASSERT_TRUE(result_true);
	TEST_ASSERT_FALSE(result_false);
}
