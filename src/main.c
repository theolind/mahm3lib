#include "unity/unity_hw_setup.h"
#include "test_runner.h"

//#include "sam3x8e/pmc.h"
#include "sam3x8e/pio.h"


int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	//run_tests();

	uint8_t result = 0;
/*
	const uart_settings_t uart_settings = {
		.baud_rate = 115200,
		.parity = UART_PARITY_NO,
		.ch_mode = UART_CHMODE_LOCAL_LOOPBACK
	};
	uart_init(&uart_settings);
*/

	pio_conf_pin(PIO_PORTB, 27, result, 0); // Turn LED on if success

while (1);
	return 0;
}
