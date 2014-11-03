#include "unity/unity.h"
#include "unity/unity_hw_setup.h"
#include "test_runner.h"

#include "sam3x8e/pmc.h"
#include "sam3x8e/arduino_due/due_pwm.h"
#include "sam3x8e/arduino_due/arduino_due.h"
#include "sam3x8e/uart.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	//run_tests();

	pmc_enable_peripheral_clock(ID_PWM);
	pmc_enable_peripheral_clock(ID_TC0);
	pmc_enable_peripheral_clock(ID_PIOC);

	pio_conf_pin_to_peripheral(PIOC, PIO_PERIPH_B, PWM_LOW7_PC24_B);
	pio_conf_pin_to_peripheral(PIOC, PIO_PERIPH_B, PWM_LOW6_PC23_B);
	pio_conf_pin_to_peripheral(PIOC, PIO_PERIPH_B, PWM_LOW5_PC22_B);
	pio_conf_pin_to_peripheral(PIOC, PIO_PERIPH_B, PWM_LOW4_PC21_B);

	due_pwm_init_channel(PWM7);
	due_pwm_enable_channel(PWM7);
	uint32_t period = pwm_get_channel_period(PWM7);
	due_pwm_set_duty_cycle(PWM7, (period * 50) / 100);

	return 0;
}
