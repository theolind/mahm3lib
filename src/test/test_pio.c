/* test_pio.c
*
*  Created on: Sep 18, 2014
*      Author: Theodor Lindquist
*      Author: Soded Alatia
*/

#include "unity/unity.h"
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
	uint32_t *p_pmc_pcer0 = (uint32_t *)0x400E0610;
	*p_pmc_pcer0 = (1<<12);

	pio_conf_pin(PIOB, 15, 1, 1); //PIO_PUSR

	uint8_t value = pio_read_pin(PIOB, 15);
	TEST_ASSERT_TRUE(value);
}

void test_pio_set_output(void) {

	pio_set_pin(PIOB, 17, 1);
	TEST_ASSERT_TRUE(PIOB->PIO_ODSR & (1<<17));

}
