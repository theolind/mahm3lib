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
#include "test/test_spi.h"
#include "test/test_eefc.h"
#include "test/test_pwm.h"
#include "test/test_tc.h"
#include "test/test_twi.h"

void run_tests(void) {
	UnityBegin();

	// Run UART tests
	Unity.TestFile = "test/test_uart.c";
	RUN_TEST(test_uart_send_receive_char_local_loopback_mode, 0);
	HORIZONTAL_LINE_BREAK();

	// Run EEFC tests
	Unity.TestFile = "test/test_eefc.c";
	RUN_TEST(test_eefc_set_flash_wait_state, 10);
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
	RUN_TEST(test_pio_enable_pin, 30);
	RUN_TEST(test_pio_disable_pin, 30);
	RUN_TEST(test_pio_pullup, 30);
	RUN_TEST(test_pio_output, 30);
	RUN_TEST(test_pio_read_pin, 30);
	RUN_TEST(test_pio_set_output, 30);
	RUN_TEST(test_pio_set_outputs, 30);
	RUN_TEST(test_pio_conf_multiple_pins, 30);
	HORIZONTAL_LINE_BREAK();

	// Run DACC tests
	Unity.TestFile = "test/test_dacc.c";
	RUN_TEST(test_dacc_channel_0_disabled1, 40);
	RUN_TEST(test_dacc_channel_1_disabled1, 40);
	RUN_TEST(test_dacc_enable_channel_0, 40);
	RUN_TEST(test_dacc_enable_channel_1, 40);
	RUN_TEST(test_dacc_disable_channel_0, 40);
	RUN_TEST(test_dacc_disable_channel_1, 40);
	RUN_TEST(test_dacc_channel_0_disabled2, 40);
	RUN_TEST(test_dacc_channel_1_disabled2, 40);
	HORIZONTAL_LINE_BREAK();

	// Run ADC tests
	Unity.TestFile = "test/test_adc.c";
	RUN_TEST(test_adc_channel_enabled, 50);
	RUN_TEST(test_adc_channel_disabled, 50);
	RUN_TEST(test_adc_channel_status, 50);
	RUN_TEST(test_adc_set_resolution_10_bit, 50);
	RUN_TEST(test_adc_set_resolution_12_bit, 50);
	HORIZONTAL_LINE_BREAK();

	// Run PWM tests
	Unity.TestFile = "test/test_pwm.c";
	RUN_TEST(test_pwm_channel_enabled, 60);
	RUN_TEST(test_pwm_channel_disabled, 60);
	RUN_TEST(test_pwm_channel_prescaler, 60);
	RUN_TEST(test_pwm_channel_duty_cycle, 60);
	RUN_TEST(test_pwm_channel_polarity, 60);
	RUN_TEST(test_pwm_channel_alignment, 60);
	RUN_TEST(test_pwm_channel_period, 60);
	RUN_TEST(test_pwm_set_clkx, 60);
	RUN_TEST(test_pwm_set_frequency, 60);

	// Run TC tests
	Unity.TestFile = "test/test_tc.c";
	RUN_TEST(test_tc_conf_channel, 70);
	RUN_TEST(test_tc_conf_block, 70);
	RUN_TEST(test_tc_enable_clock, 70);
	RUN_TEST(test_tc_disable_clock, 70);
	RUN_TEST(test_tc_start_clock, 70);
	RUN_TEST(test_tc_counter_stopped, 70);
	RUN_TEST(test_tc_read_counter_value, 70);
	RUN_TEST(test_tc_sync, 70);
	RUN_TEST(test_register, 70);
	HORIZONTAL_LINE_BREAK();

	// Run TWI tests
	Unity.TestFile = "test/test_twi.c";
	RUN_TEST(test_twi_init_slave, 80);
	RUN_TEST(test_twi_set_device_address, 80);
	RUN_TEST(test_twi_set_internal_address, 80);
	RUN_TEST(test_twi_set_clock_invalid_parameters, 80);
	RUN_TEST(test_twi_set_clock_valid_parameters, 80);
	//RUN_TEST(test_twi_send_receive_SEMI_AUTOMATIC, 80);
	HORIZONTAL_LINE_BREAK();

	// Run SPI tests
	// Have yet to run tests due to error messages
	Unity.TestFile = "test/test_spi.c";
	// Initial test
	spi_setup();
	RUN_TEST(test_spi_initial_state, 90);
	RUN_TEST(test_spi_after_init, 90);
	// Incremental tests
	RUN_TEST(test_spi_select_slave, 90);
	RUN_TEST(test_spi_write_ready, 90);
	RUN_TEST(test_spi_write, 90);
	RUN_TEST(test_spi_read_ready, 90);
	RUN_TEST(test_spi_transmission_complete, 90);
	RUN_TEST(test_spi_correct_transmission, 90);
	RUN_TEST(test_spi_variable_bit_lenght_transmission, 90);
	RUN_TEST(test_spi_polarity_phase_change, 90);
	RUN_TEST(test_spi_baud_rate_change, 90);
	HORIZONTAL_LINE_BREAK();

	UnityEnd();
}
