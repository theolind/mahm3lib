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

	uint32_t *p_pusr = (uint32_t *)(PIO_PORTB->PIO_PUSR); //Pullup status Register B
	pio_conf_pin(PIO_PORTB, 31, 1, 1); //PIO_PUSR
	TEST_ASSERT_FALSE(*p_pusr & (0x1u << 31));
}

void test_pio_output(void) {
	uint32_t *p_osr = (uint32_t *)(PIO_PORTB->PIO_OSR); //Output status Register B
	pio_conf_pin(PIO_PORTB, 31, 0, 1); //PIO_PUSR
	TEST_ASSERT_TRUE(*p_osr & (0x1u << 31));
}

void test_pio_read_pin(void) {
	uint32_t *p_pmc_pcer0 = (uint32_t *)0x400E0610;
	*p_pmc_pcer0 = (1<<12);

<<<<<<< HEAD
	//uint32_t *p_pusr = (uint32_t *)(PIO_PORTB + PIO_PUSR); //Pullup status Register B
=======
	uint32_t *p_pusr = (uint32_t *)(PIO_PORTB->PIO_PUSR); //Pullup status Register B
>>>>>>> 3664a69f54353f06bc53bdd6834f6f06459712fe
	pio_conf_pin(PIO_PORTB, 15, 1, 1); //PIO_PUSR

	uint8_t value = pio_read_pin(PIO_PORTB, 15);
	TEST_ASSERT_TRUE(value);
}

void test_pio_set_output(void) {
<<<<<<< HEAD
	uint32_t *p_odsr = (uint32_t *)(PIO_PORTB + PIO_ODSR);
=======

	uint32_t *p_odsr = (uint32_t *)(PIO_PORTB->PIO_ODSR);
>>>>>>> 3664a69f54353f06bc53bdd6834f6f06459712fe
	pio_set_pin(PIO_PORTB, 17, 1);
	TEST_ASSERT_TRUE(*p_odsr & (1<<17));
}
