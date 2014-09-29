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

void test_pio_pullup(void) {

	pio_conf_pin(PIOB, 31, 1, 1); //PIO_PUSR
	TEST_ASSERT_FALSE(PIOB->PIO_PUSR & (0x1u << 31));
}

void test_pio_output(void) {

	pio_conf_pin(PIOB, 31, 0, 1); //PIO_PUSR
	TEST_ASSERT_TRUE(PIOB->PIO_OSR & (0x1u << 31));
}

void test_pio_read_pin(void) {
	pmc_enable_peripheral_clock(ID_PIOB);
	pio_conf_pin(PIOB, 15, 1, 1); //PIO_PUSR
	TEST_ASSERT_TRUE(pio_read_pin(PIOB, 15));
}

void test_pio_set_output(void) {

	pio_set_pin(PIOB, 17, 1);
	TEST_ASSERT_TRUE(PIOB->PIO_ODSR & (1<<17));

	pmc_disable_peripheral_clock(ID_PIOB);
}
