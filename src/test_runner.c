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
#include "test/test_eefc.h"
#include "test/test_bitwise_operations.h"
#include "test/test_pwm.h"

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
	RUN_TEST(test_pmc_PWM_disabled1, 20);
	RUN_TEST(test_pmc_enable_PWM, 20);
	RUN_TEST(test_pmc_PWM_enabled, 20);
	RUN_TEST(test_pmc_disable_PWM, 20);
	RUN_TEST(test_pmc_PWM_disabled2, 20);
	HORIZONTAL_LINE_BREAK();

	// Run PIO tests
	Unity.TestFile = "test/test_pio.c";
	RUN_TEST(test_pio_enable_pin, 30);
	RUN_TEST(test_pio_disable_pin, 30);
	RUN_TEST(test_pio_pullup, 30);
	RUN_TEST(test_pio_output, 30);
	RUN_TEST(test_pio_read_pin, 30);
	RUN_TEST(test_pio_set_output, 30);
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

	// Run bitwise_operations tests
	Unity.TestFile = "test/test_bitwise_operations.c";
	RUN_TEST(test_is_bit_high, 60);
	RUN_TEST(test_get_position_of_first_highbit, 60);
	RUN_TEST(test_get_section_in_register, 60);
	RUN_TEST(test_set_section_in_register, 60);
	RUN_TEST(test_set_section_in_register2, 60);
	RUN_TEST(test_clear_register, 60);
	RUN_TEST(test_set_register, 60);
	RUN_TEST(test_clear_bit_in_register, 60);
	RUN_TEST(test_set_bit_in_register, 60);
	HORIZONTAL_LINE_BREAK();

	// Run PWM tests
	Unity.TestFile = "test/test_pwm.c";
	RUN_TEST(test_pwm_channel_enabled, 30);
	RUN_TEST(test_pwm_channel_disabled, 30);
	RUN_TEST(test_pwm_channel_prescaler, 30);
	RUN_TEST(test_pwm_channel_duty_cycle, 30);
	RUN_TEST(test_pwm_channel_polarity, 30);
	RUN_TEST(test_pwm_channel_alignment, 30);
	RUN_TEST(test_pwm_channel_period, 30);
	RUN_TEST(test_pwm_set_clkx, 30);
	RUN_TEST(test_set_frequency, 30);

	UnityEnd();
}
