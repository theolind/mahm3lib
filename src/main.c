#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/pio.h"
#include "sam3x8e/delay.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	//run_tests();

	test_delay_pin_33(6);

	return 0;
}


void test_delay_pin_33(uint32_t delay){
	pio_conf_pin(PIOC, 1,  0, 0);
	for(;;){
		PIOC->PIO_SODR = 2;//(0x1u << 1);	//set pin
		delay_micros(delay);
		PIOC->PIO_CODR = 2;//(0x1u << 1);	//clear pin
		delay_micros(delay);
	}
}
