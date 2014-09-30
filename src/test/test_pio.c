/*
 * PIO unit tests
 *
 * Author:	Theodor Lindquist
 * 			Soded Alatia
 *
 * Date:	18 September 2014
 *
 * Comment from Mathias B:
 * The tests could verify a little bit more. Should be improved when
 * extending the API.
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/pio.h"
#include "test_pio.h"



void test_pio_enable_pin(void) {

	pio_enable_pin(PIOB, 31);

	uint32_t pin = PIOB->PIO_PSR & (0x01u << 31); // Read pio status register

	// Reset
	pio_disable_pin(PIOB, 31);

	TEST_ASSERT_TRUE(pin)
}

void test_pio_disable_pin(void) {

	pio_enable_pin(PIOB, 31);
	pio_disable_pin(PIOB, 31);

	uint32_t pin = PIOB->PIO_PSR & (0x01u << 31); // Read pio status register

	TEST_ASSERT_FALSE(pin);

}

void test_pio_pullup(void) {
	pio_enable_pin(PIOB, 31);
	pio_conf_pin(PIOB, 31, 1, 1);

	uint32_t pin = PIOB->PIO_PUSR & (0x1u << 31); // Read pull-up status register

	// Reset
	pio_disable_pin(PIOB,31);

	TEST_ASSERT_FALSE(pin);	// When PIO_PUSR == 0 pull-up is enabled!
}

void test_pio_output(void) {
	pio_enable_pin(PIOB, 31);
	pio_conf_pin(PIOB, 31, 0, 1);

	uint32_t pin = PIOB->PIO_OSR & (0x1u << 31); // Read output status register

	// Reset
	pio_disable_pin(PIOB, 31);

	TEST_ASSERT_TRUE(pin);
}

void test_pio_read_pin(void) {
	pio_enable_pin(PIOB, 15);
	pmc_enable_peripheral_clock(ID_PIOB);

	pio_conf_pin(PIOB, 15, 1, 1);
	uint32_t pin = pio_read_pin(PIOB, 15);

	// Reset
	pmc_disable_peripheral_clock(ID_PIOB);
	pio_disable_pin(PIOB, 15);

	TEST_ASSERT_TRUE(pin);
}

void test_pio_set_output(void) {
	pio_set_pin(PIOB, 17, 1);
	uint32_t pin = (PIOB->PIO_ODSR & (1<<17));	// Read Output data status register

	// Reset
	pio_set_pin(PIOB, 17, 0);

	TEST_ASSERT_TRUE(pin);
}

void test_pio_conf_multiple_pins(void){

	pio_enable_pin(PIOB,15);
	pio_enable_pin(PIOB,16);
	pio_enable_pin(PIOB,17);

	pio_conf_pins(PIOB, (0x01u << 15)|(0x01u << 16)|(0x01u << 17),0,0);

	uint32_t pin = PIOB->PIO_OSR & ((0x01u << 15)|(0x01u << 16)|(0x01u << 17)); // Read output status register

	pio_disable_pin(PIOB,15);
	pio_disable_pin(PIOB,16);
	pio_disable_pin(PIOB,17);

	TEST_ASSERT_TRUE(pin);
}


