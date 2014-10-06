#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/bitwise_operations.h"
#include "sam3x8e/pwm.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/pmc.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	run_tests();

	/**
	 * enable the PWM clock in PMC
	 * initialize peripheral by selecting a prescaler of clk register with PREA
	 * Select a clock for channel_0
	 * Select alignment for channel_0
	 * Select polarity for channel_0
	 *
	 *
	 */
	pmc_enable_peripheral_clock(ID_PIOC);
	// MCU pin = PC3   -   DUE pin = 35    -    PWM pin = PWMH0
	pio_conf_pin_to_peripheral(PIOC, PIO_PERIPH_B, 3);
	pwm_init_peripheral_default();

	pwm_channel_setting channel_0;
	channel_0.alignment = PWM_CHANNEL_ALIGN_LEFT;
	channel_0.polarity = PWM_CHANNEL_POLARITY_HIGH;
	channel_0.prescaler = PWM_PRES_MCK_DIV_64;
	channel_0.duty_cycle = 0;
	channel_0.channel = PWM_CHANNEL_0_MASK;
	channel_0.use_prescaler = TRUE;

	pwm_init_channel(channel_0);

	pwm_set_channel_period(PWM_CHANNEL_0_MASK, 65535);
	pwm_set_channel_duty_cycle(PWM_CHANNEL_0_MASK, 30000);
	pwm_channel_enable(PWM_CHANNEL_0_MASK);


	return 0;
}
