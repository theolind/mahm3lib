/*
 * Test runner, add your tests here
 *
 * Created by: Theodor Lindquist
 * Date: 2014-09-10
 */

#include "unity/unity.h"
#include "test_runner.h"

#include "test/test_pmc.h"
#include "test/test_pio.h"
#include "test/test_adc.h"
#include "test/test_dacc.h"

void run_tests(void) {
	UnityBegin();

	// Run PIO tests
	Unity.TestFile = "test/test_pio.c";
	RUN_TEST(test_pio_pullup, 0);
	RUN_TEST(test_pio_output, 0);
	RUN_TEST(test_pio_read_pin, 0);
	RUN_TEST(test_pio_set_output, 0);

	// Run PMC tests
	Unity.TestFile = "test/test_pmc.c";
	RUN_TEST(test_pmc_start_peripheral_clock_when_successful, 10);
	RUN_TEST(test_pmc_status_peripheral_clock_when_inactive, 10);
	RUN_TEST(test_pmc_status_peripheral_clock_when_active, 10);
	RUN_TEST(test_pmc_stop_peripheral_clock_when_successful, 10);

	// Run DACC tests
	Unity.TestFile = "test/test_dacc.c";
	RUN_TEST(test_dacc_init, 20);
	RUN_TEST(test_dacc_channel_0_enable, 20);
	RUN_TEST(test_dacc_channel_1_enable, 20);
	RUN_TEST(test_dacc_channel_0_write, 20);
	RUN_TEST(test_dacc_channel_1_write, 20);
	RUN_TEST(test_dacc_channel_0_disable, 20);
	RUN_TEST(test_dacc_channel_1_disable, 20);

	// Run ADC tests
	Unity.TestFile = "test/test_adc.c";
	RUN_TEST(test_adc_init, 30);
	RUN_TEST(test_adc_channel_enabled, 30);
	RUN_TEST(test_adc_channel_disabled, 30);
	RUN_TEST(test_adc_channel_status, 30);
	RUN_TEST(test_adc_set_resolution_12_bit, 30);
	RUN_TEST(test_adc_set_resolution_10_bit, 30);

	UnityEnd();
}
