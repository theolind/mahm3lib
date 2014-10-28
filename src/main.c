#include "unity/unity.h"
#include "test_runner.h"
#include "sam3x8e/mux.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/delay.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/adc.h"


int main(void) {
	// basic initialization of hardware and UART communication.
//	unity_hw_setup();
//
//	// run unit tests
//	run_tests();
	uint32_t mux = 6;
	uint32_t pin = 5;

	// Enable Peripheral clock for ADC
	pmc_enable_peripheral_clock(37);

	// Initialize the ADC
	adc_settings_t adc_settings = {
		.startup_time = 0,
		.prescaler = 0
	};
	adc_init(&adc_settings);

	// Enable channel 0 and start reading
	uint32_t channel = ADC_CHANNEL_6;
	adc_enable_channel(channel);

	pio_conf_pin(PIOC, 25, 0, 0);
	pio_conf_pin(PIOC, 26, 0, 0);
	pio_conf_pin(PIOC, 28, 0, 0);
	pio_conf_pin(PIOB, 25, 0, 0);

	pio_conf_pin(PIOB, 26, 1, 0);		// TODO: D26
	pio_conf_pin(PIOA, 15, 0, 0); 		// TODO: D24
	pio_conf_pin(PIOD, 1, 1, 0); 		// TODO: D22

	pio_set_pin(PIOC, 25, 0); // S3
	pio_set_pin(PIOC, 26, 1); // S2
	pio_set_pin(PIOC, 28, 0); // S1
	pio_set_pin(PIOB, 25, 1); // S0

	while(1){
	}


}
