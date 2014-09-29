/*
 * Test runner, add your tests here
 *
 * Author:	Theodor Lindquist
 *
 * Date: 10 September 2014
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

	// Run PIO tests
	Unity.TestFile = "test/test_pio.c";
	RUN_TEST(test_pio_pullup, 10);
	RUN_TEST(test_pio_output, 10);
	RUN_TEST(test_pio_read_pin, 10);
	RUN_TEST(test_pio_set_output, 10);

	// Run PMC tests
	Unity.TestFile = "test/test_pmc.c";
	RUN_TEST(test_pmc_PIOB_disabled, 20);
	RUN_TEST(test_pmc_enabled_function_OK, 20);
	RUN_TEST(test_pmc_disable_function_OK, 20);
	/*
	RUN_TEST(test_pmc_status_peripheral_clock_when_inactive, 20);
	RUN_TEST(test_pmc_status_peripheral_clock_when_active, 20);
	RUN_TEST(test_pmc_stop_peripheral_clock_when_successful, 20);
	*/
/*
	// Run DACC tests
	Unity.TestFile = "test/test_dacc.c";
	RUN_TEST(test_dacc_init, 30);
	RUN_TEST(test_dacc_channel_0_enable, 30);
	RUN_TEST(test_dacc_channel_1_enable, 30);
	RUN_TEST(test_dacc_channel_0_write, 30);
	RUN_TEST(test_dacc_channel_1_write, 30);
	RUN_TEST(test_dacc_channel_0_disable, 30);
	RUN_TEST(test_dacc_channel_1_disable, 30);

	// Run ADC tests
	Unity.TestFile = "test/test_adc.c";
	RUN_TEST(test_adc_init, 30);
	RUN_TEST(test_adc_channel_enabled, 30);
	RUN_TEST(test_adc_channel_disabled, 30);
	RUN_TEST(test_adc_channel_status, 30);
	RUN_TEST(test_adc_set_resolution_12_bit, 30);
	RUN_TEST(test_adc_set_resolution_10_bit, 30);
*/
	UnityEnd();
}
