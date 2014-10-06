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
	pio_conf_pin_to_peripheral(PIOC, PIO_PERIPH_B, 5);

	pwm_init_peripheral_default();

	pwm_channel_setting channel_0;
	channel_0.channel = PWM_CHANNEL_0_MASK;
	channel_0.alignment = PWM_CHANNEL_ALIGN_LEFT;
	channel_0.polarity = PWM_CHANNEL_POLARITY_HIGH;
	channel_0.duty_cycle = 0;
	channel_0.use_CLKx = FALSE;
	channel_0.frequency = 2;

	pwm_channel_setting channel_1;
	channel_1.channel = PWM_CHANNEL_1_MASK;
	channel_1.alignment = PWM_CHANNEL_ALIGN_LEFT;
	channel_1.polarity = PWM_CHANNEL_POLARITY_HIGH;
	channel_1.duty_cycle = 0;
	channel_1.use_CLKx = FALSE;
	channel_1.frequency = 2;

	pwm_init_channel(channel_0);
	pwm_init_channel(channel_1);

	//pwm_set_channel_period(PWM_CHANNEL_0_MASK, 65535);
//	pwm_set_channel_duty_cycle(PWM_CHANNEL_0_MASK,
//			pwm_get_max_duty_cycle(PWM_CHANNEL_0_MASK)/2);
	pwm_set_channel_duty_cycle(PWM_CHANNEL_0_MASK, pwm_get_max_duty_cycle(PWM_CHANNEL_0_MASK)/2);
	pwm_channel_enable(PWM_CHANNEL_0_MASK);
	pwm_set_channel_duty_cycle(PWM_CHANNEL_1_MASK, 5000);
	pwm_channel_enable(PWM_CHANNEL_1_MASK);


	return 0;
}
