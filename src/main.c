#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/pmc.h"
#include "sam3x8e/arduino_due/due_pwm.h"
#include "sam3x8e/arduino_due/arduino_due.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	//run_tests();

	pmc_enable_peripheral_clock(ID_PWM);
	pmc_enable_peripheral_clock(ID_TC0);
	pmc_enable_peripheral_clock(ID_PIOC);

	due_pwm_init_channel(PWM6);
	due_pwm_set_duty_cycle(PWM6, 50);
	due_pwm_enable_channel(PWM6);

	return 0;
}
