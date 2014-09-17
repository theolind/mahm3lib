#include "unity_hw_setup.h"
#include "test_runner.h"
#include "adc.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// Needed for running tests?
	adc_init(1);
	adc_enable_channel(ADC_CHANNEL_4);

	run_tests();

	while (1);
    return 0;
}
