#include "unity/unity.h"
#include "test_runner.h"
#include "sam3x8e/mux.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/delay.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();
//
//	// run unit tests
//	run_tests();
//	uint32_t pin = 0;
//	uint32_t mux = 6;
//
//	pio_conf_pin(PIOC, 25, 0, 0);
//	pio_conf_pin(PIOC, 26, 0, 0);
//	pio_conf_pin(PIOC, 28, 0, 0);
//	pio_conf_pin(PIOB, 25, 0, 0);
//
//	pio_conf_pin(PIOA, 23, ((mux&7)>>2), 0);		// A2
//	pio_conf_pin(PIOA, 24,((mux&3)>>1) , 0); 		// A1
//	pio_conf_pin(PIOA, 16, (mux&1), 0); 			// A0
//
//
//	pio_set_pin(PIOC, 25, ((pin&15)>>3)); // S3
//	pio_set_pin(PIOC, 26, ((pin&7)>>2)); // S2
//	pio_set_pin(PIOC, 28, ((pin&3)>>1)); // S1
//	pio_set_pin(PIOB, 25, (pin&1)); // S0

	enable_mux_pin(mux0, 0);

	while(1){
	pio_set_pin(PIOB, 27, 1);
	pio_set_pin(PIOA, 16, 1);
//	delay_ms(101);
//	pio_set_pin(PIOB, 16, 0);
//	delay_ms(101);
}
}
