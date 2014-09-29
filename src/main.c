#include "unity/unity_hw_setup.h"
#include "test_runner.h"

//#include "sam3x8e/pmc.h"
#include "sam3x8e/uart.h"
//#include "sam3x8e/pio.h"

int main() {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	//run_tests();
	uart_write_str("Hello world!\n");
	while (1);
	//uint8_t result = 0;
/*
	const uart_settings_t uart_settings = {
		.baud_rate = 115200,
		.parity = UART_PARITY_NO,
		.ch_mode = UART_CHMODE_LOCAL_LOOPBACK
	};
	uart_init(&uart_settings);


	pmc_enable_peripheral_clock(ID_PIOB);
	pio_conf_pin(PIO_PORTB, 27, 0, 0);
	pio_set_pin(PIO_PORTB, 27, result);

while (1);
*/
	return 0;
}
