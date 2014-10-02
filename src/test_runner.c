/*
 * Test runner, add your tests here
 *
 * Author:	Theodor Lindquist
 *
 * Date: 	29 September 2014
 */

#include "unity/unity.h"
#include "test_runner.h"

// test files
#include "test/test_pmc.h"
#include "test/test_pio.h"
#include "test/test_adc.h"
#include "test/test_dacc.h"
#include "test/test_uart.h"

void run_tests(void) {
	UnityBegin();

	// Run UART tests
	Unity.TestFile = "test/test_uart.c";
	RUN_TEST(test_uart_send_receive_char_local_loopback_mode, 0);
	HORIZONTAL_LINE_BREAK();

	// Run PMC tests
	Unity.TestFile = "test/test_pmc.c";
	RUN_TEST(test_pmc_PIOB_disabled1, 20);
	RUN_TEST(test_pmc_enable_PIOB, 20);
	RUN_TEST(test_pmc_PIOB_enabled, 20);
	RUN_TEST(test_pmc_disable_PIOB, 20);
	RUN_TEST(test_pmc_PIOB_disabled2, 20);
	HORIZONTAL_LINE_BREAK();

	// Run PIO tests
	Unity.TestFile = "test/test_pio.c";
	RUN_TEST(test_pio_enable_pin, 10);
	RUN_TEST(test_pio_disable_pin, 10);
	RUN_TEST(test_pio_pullup, 10);
	RUN_TEST(test_pio_output, 10);
	RUN_TEST(test_pio_read_pin, 10);
	RUN_TEST(test_pio_set_output, 10);
	RUN_TEST(test_pio_conf_multiple_pins, 10);
	HORIZONTAL_LINE_BREAK();

	// Run DACC tests
	Unity.TestFile = "test/test_dacc.c";
	RUN_TEST(test_dacc_channel_0_disabled1, 30);
	RUN_TEST(test_dacc_channel_1_disabled1, 30);
	RUN_TEST(test_dacc_enable_channel_0, 30);
	RUN_TEST(test_dacc_enable_channel_1, 30);
	RUN_TEST(test_dacc_disable_channel_0, 30);
	RUN_TEST(test_dacc_disable_channel_1, 30);
	RUN_TEST(test_dacc_channel_0_disabled2, 30);
	RUN_TEST(test_dacc_channel_1_disabled2, 30);
	HORIZONTAL_LINE_BREAK();

	// Run ADC tests
	Unity.TestFile = "test/test_adc.c";
	RUN_TEST(test_adc_channel_enabled, 30);
	RUN_TEST(test_adc_channel_disabled, 30);
	RUN_TEST(test_adc_channel_status, 30);
	RUN_TEST(test_adc_set_resolution_10_bit, 30);
	RUN_TEST(test_adc_set_resolution_12_bit, 30);

	UnityEnd();
}
