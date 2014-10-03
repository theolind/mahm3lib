#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/pwm.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/pmc.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	//run_tests();

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
	pio_conf_pin_to_peripheral(PIOC, PERIPH_B, 3);
	pwm_init_peripheral_default();

	pwm_channel_setting channel_0;
	channel_0.alignment = PWM_ALIGN_LEFT;
	channel_0.polarity = PWM_POLARITY_HIGH;
	channel_0.prescaler = PWM_CLK_PRES_1024;
	channel_0.high_polarity_pin = 0;
	channel_0.low_polarity_pin = 0;
	channel_0.duty_cycle = 0;

	pwm_

//	pwm_init_channel()





	return 0;
}

