/**
 * test_tft.c
 *
 * @author Theodor Lindquist
 * @date 1 November 2014
 *
 */
#include "unity/unity.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/tft.h"
#include "sam3x8e/delay.h"
#include "test_tft.h"

tft_screen tft;

void test_tft_setup(void) {
	tft.PORT_CS = (uint32_t)PIOA;
	tft.PIN_CS = 22;
	tft.PORT_WR = (uint32_t)PIOA;
	tft.PIN_WR = 6;
	tft.PORT_RS = (uint32_t)PIOA;
	tft.PIN_RS = 4;
	tft.PORT_D0 = (uint32_t)PIOA;
	tft.PIN_D0 = 8;
	tft.PORT_D1 = (uint32_t)PIOA;
	tft.PIN_D1 = 9;
	tft.PORT_D2 = (uint32_t)PIOB;
	tft.PIN_D2 = 25;
	tft.PORT_D3 = (uint32_t)PIOC;
	tft.PIN_D3 = 28;
	tft.PORT_D4 = (uint32_t)PIOC;
	tft.PIN_D4 = 26;
	tft.PORT_D5 = (uint32_t)PIOC;
	tft.PIN_D5 = 25;
	tft.PORT_D6 = (uint32_t)PIOC;
	tft.PIN_D6 = 24;
	tft.PORT_D7 = (uint32_t)PIOC;
	tft.PIN_D7 = 23;
	tft.width = 239;
	tft.height = 319;
}

void test_tft_setup2(void) {
	pio_enable_pin(tft.PORT_CS, tft.PIN_CS); pio_conf_pin(tft.PORT_CS, tft.PIN_CS, 0, 1);
	pio_enable_pin(tft.PORT_WR, tft.PIN_WR); pio_conf_pin(tft.PORT_WR, tft.PIN_WR, 0, 1);
	pio_enable_pin(tft.PORT_RS, tft.PIN_RS); pio_conf_pin(tft.PORT_RS, tft.PIN_RS, 0, 1);
	pio_enable_pin(tft.PORT_D0, tft.PIN_D0); pio_conf_pin(tft.PORT_D0, tft.PIN_D0, 0, 1);
	pio_enable_pin(tft.PORT_D1, tft.PIN_D1); pio_conf_pin(tft.PORT_D1, tft.PIN_D1, 0, 1);
	pio_enable_pin(tft.PORT_D2, tft.PIN_D2); pio_conf_pin(tft.PORT_D2, tft.PIN_D2, 0, 1);
	pio_enable_pin(tft.PORT_D3, tft.PIN_D3); pio_conf_pin(tft.PORT_D3, tft.PIN_D3, 0, 1);
	pio_enable_pin(tft.PORT_D4, tft.PIN_D4); pio_conf_pin(tft.PORT_D4, tft.PIN_D4, 0, 1);
	pio_enable_pin(tft.PORT_D5, tft.PIN_D5); pio_conf_pin(tft.PORT_D5, tft.PIN_D5, 0, 1);
	pio_enable_pin(tft.PORT_D6, tft.PIN_D6); pio_conf_pin(tft.PORT_D6, tft.PIN_D6, 0, 1);
	pio_enable_pin(tft.PORT_D7, tft.PIN_D7); pio_conf_pin(tft.PORT_D7, tft.PIN_D7, 0, 1);
}

void test_tft_init(void) {
	// Screen should display "garbage" after this
	tft_init(&tft);
	delay_ms(3000);
	TEST_ASSERT_TRUE(1);
}

void test_tft_clear(void) {
	// Screen should be black after this
	tft_clear(&tft);
	delay_ms(3000);
	TEST_ASSERT_TRUE(1);
}

void test_tft_write(void) {
	// Screen should have a white line after this
	for(uint16_t i = 0; i < 100; i++) {
		tft_write(&tft, i, i, 0xFFFF);
	}
	delay_ms(3000);
	TEST_ASSERT_TRUE(1);
}

void test_tft_set_bus(void) {
	tft_set_bus(&tft, 0b11010011);

	TEST_ASSERT_TRUE( PIOC->PIO_ODSR & (0x1u << tft.PIN_D7) );
	TEST_ASSERT_FALSE( PIOC->PIO_ODSR & (0x1u << tft.PIN_D5) );
}

void test_tft_clear_bus(void) {
	tft_set_bus(&tft, 0b11111111);
	tft_clear_bus(&tft);

	TEST_ASSERT_FALSE( PIOC->PIO_ODSR & (0x1u << tft.PIN_D5) );
}
