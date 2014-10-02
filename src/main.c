#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/pio.h"
#include "sam3x8e/delay.h"


int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	//run_tests();

	// run delay tests
	//test_delay_l_led(5000000);
	test_delay_pin_46(1);

	return 0;
}

void test_delay_l_led(uint32_t delay){
	pio_conf_pin(PIOB, 27, 0, 0);
	for(;;){
		PIOB->PIO_SODR = (0x1u << 27);	//set pin
		delay_micros(delay);
		PIOB->PIO_CODR = (0x1u << 27);	//clear pin
		delay_micros(delay);
	}
}

void test_delay_pin_46(uint32_t delay){
	pio_conf_pin(PIOC, 17,  0, 0);
	for(;;){
		PIOC->PIO_SODR = (0x1u << 17);	//set pin
		delay_micros(delay);
		PIOC->PIO_CODR = (0x1u << 17);	//clear pin
	}
}
