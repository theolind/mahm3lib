#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/tc.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/pio.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	//run_tests();
	const tc_channel_settings_t tc_settings = {
		.wave = 0,
		.tcclks = 0
	};

	pmc_enable_peripheral_clock(ID_TC0);
	pmc_enable_peripheral_clock(ID_PIOB);
	pio_conf_pin(PIOB, 27, 0, 0);
	tc_conf_channel(&tc_settings, TC0, 0);
	tc_enable_clock(TC0, TC_CHANNEL_0);

	tc_enable_clock(TC0, TC_CHANNEL_1);

	tc_enable_clock(TC0, TC_CHANNEL_2);
	uint32_t delay_us = 1000000;
	while(1){
		PIOB->PIO_CODR = (0x1u << 27);	//clear pin
		delay_TC_CHANNEL_0(delay_us);
		PIOB->PIO_SODR = (0x1u << 27);	//set pin
		delay_TC_CHANNEL_0(delay_us);

		PIOB->PIO_CODR = (0x1u << 27);	//clear pin
		delay_TC_CHANNEL_1(delay_us*2);
		PIOB->PIO_SODR = (0x1u << 27);	//set pin
		delay_TC_CHANNEL_1(delay_us*2);

		PIOB->PIO_CODR = (0x1u << 27);	//clear pin
		delay_TC_CHANNEL_2(delay_us*4);
		PIOB->PIO_SODR = (0x1u << 27);	//set pin
		delay_TC_CHANNEL_2(delay_us*4);
	}

	return 0;
}

void delay_TC_CHANNEL_0(uint32_t us)
{
	tc_start_clock(TC0, TC_CHANNEL_0);
	while (tc_read_counter_value(TC0, TC_CHANNEL_0) < us*42);
	tc_stop_clock(TC0, TC_CHANNEL_0);
}

void delay_TC_CHANNEL_1(uint32_t us)
{
	tc_start_clock(TC0, TC_CHANNEL_1);
	while (tc_read_counter_value(TC0, TC_CHANNEL_1) < us*42);
	tc_stop_clock(TC0, TC_CHANNEL_1);
}

void delay_TC_CHANNEL_2(uint32_t us)
{
	tc_start_clock(TC0, TC_CHANNEL_2);
	while (tc_read_counter_value(TC0, TC_CHANNEL_2) < us*42);
	tc_stop_clock(TC0, TC_CHANNEL_2);
}
