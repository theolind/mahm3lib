#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/tc.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/pio.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	run_tests();
	const tc_channel_settings_t tc_settings = {
		.wave = 0,
		.tcclks = 0
	};

	pmc_enable_peripheral_clock(ID_TC2);
	pmc_enable_peripheral_clock(ID_PIOB);
	pio_conf_pin(PIOB, 27, 0, 0);
	tc_conf_channel(&tc_settings, TC2, 0);
	tc_enable_clock(TC2, TC_CHANNEL_0);
	uint32_t delay_us = 5000000;
	while(1){
		PIOB->PIO_CODR = (0x1u << 27);	//clear pin
		delay(delay_us);
		PIOB->PIO_SODR = (0x1u << 27);	//set pin
		delay(delay_us);
	}

	return 0;
}

void delay(uint32_t us)
{
	tc_start_clock(TC2, TC_CHANNEL_0);
	while (tc_read_counter_value(TC2, TC_CHANNEL_0) < us*42);
	tc_stop_clock(TC2, TC_CHANNEL_0);
}
