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

	config();
	run();

	return 0;
}

void config(){
	const tc_channel_settings_t tc_settings_0 = {
		.wave = 0,
		.tcclks = 0
	};
	const tc_channel_settings_t tc_settings_1 = {
		.wave = 0,
		.tcclks = 1
	};
	const tc_channel_settings_t tc_settings_2 = {
		.wave = 0,
		.tcclks = 2
	};

	pmc_enable_peripheral_clock(ID_TC0);
	pmc_enable_peripheral_clock(ID_TC1);
	pmc_enable_peripheral_clock(ID_TC2);
	pmc_enable_peripheral_clock(ID_PIOB);
	pio_conf_pin(PIOB, 27, 0, 0);

	tc_conf_channel(&tc_settings_0, TC0, 0);
	tc_conf_channel(&tc_settings_1, TC1, 0);
	tc_conf_channel(&tc_settings_2, TC2, 0);

	tc_enable_clock(TC0, TC_CHANNEL_0);
	tc_enable_clock(TC1, TC_CHANNEL_0);
	tc_enable_clock(TC2, TC_CHANNEL_0);
}

void run(){
	uint32_t delay_us = 1000000;
	while(1){
		PIOB->PIO_CODR = (0x1u << 27);	//clear pin
		delay_TC_0(delay_us);
		PIOB->PIO_SODR = (0x1u << 27);	//set pin
		delay_TC_0(delay_us);

		PIOB->PIO_CODR = (0x1u << 27);	//clear pin
		delay_TC_1(delay_us*2);
		PIOB->PIO_SODR = (0x1u << 27);	//set pin
		delay_TC_1(delay_us*2);

		PIOB->PIO_CODR = (0x1u << 27);	//clear pin
		delay_TC_2(delay_us*3);
		PIOB->PIO_SODR = (0x1u << 27);	//set pin
		delay_TC_2(delay_us*3);
	}
}

void delay_TC_0(uint32_t us)
{
	tc_start_clock(TC0, TC_CHANNEL_0);
	while (tc_read_counter_value(TC0, TC_CHANNEL_0) < us*42);
	tc_stop_clock(TC0, TC_CHANNEL_0);
}

void delay_TC_1(uint32_t us)
{
	tc_start_clock(TC1, TC_CHANNEL_0);
	while (tc_read_counter_value(TC1, TC_CHANNEL_0) < us*10); //(us*10.5*10)/10);
	tc_stop_clock(TC1, TC_CHANNEL_0);
}

void delay_TC_2(uint32_t us)
{
	tc_start_clock(TC2, TC_CHANNEL_0);
	while (tc_read_counter_value(TC2, TC_CHANNEL_0) < us*2); //(us*2.625*1000)/1000);
	tc_stop_clock(TC2, TC_CHANNEL_0);
}
