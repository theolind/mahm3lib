/*
 * @file test_spi.c
 * @brief Serial Peripheral Interface (SPI) unit tests
 * @details This class is used to test SPI capabilities of this API
 *
 * @author Jonathan Bjarnason
 * @author Soded Alatia
 * @date 2 October 2014
 */

#include "unity/unity.h"
#include "sam3x8e/id.h"
#include "sam3x8e/spi.h"
#include "sam3x8e/pio.h"
#include "test/test_spi.h"

#include "sam3x8e/delay.h"

void test_spi_setup(void) {
	const spi_settings_t spi_settings_t = {
		.master = 1,
		.CPOL = 0,
		.NCPHA = 0,
		.baud[1] = 255,
		.bits[1] = 0
	};

	pmc_enable_peripheral_clock(ID_SPI0);

	pio_conf_pin_to_peripheral(PIOA, 0, 25);	//MISO
	pio_conf_pin_to_peripheral(PIOA, 0, 26);	//MOSI
	pio_conf_pin_to_peripheral(PIOA, 0, 27);	//SPCK
	pio_conf_pin_to_peripheral(PIOA, 0, 28);	//NPCS0
	pio_conf_pin_to_peripheral(PIOA, 0, 29);	//NPCS1
	pio_conf_pin_to_peripheral(PIOA, 0, 30);	//NPSC2
	pio_conf_pin_to_peripheral(PIOA, 0, 31);	//NPSC3

	spi_init(SPI0, &spi_settings_t);
}

void test_spi_init(void) {
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_SPIENS));
}

void test_spi_select_slave(void) {
	spi_select_slave(SPI0, 0);
	//TODO write a test for this
}

void test_spi_write_ready() {
	TEST_ASSERT_TRUE( spi_write_ready(SPI0) );
}

void test_spi_write() {
	spi_select_slave(SPI0, 1);

	TEST_ASSERT_TRUE( SPI0->SPI_SR & (0x1u << 9) );
	spi_write(SPI0, 0b00110101);
	TEST_ASSERT_FALSE(SPI0->SPI_SR & (0x1u << 9));
}

void test_spi_read_ready() {
	TEST_ASSERT_FALSE( spi_read_ready(SPI0) );
	spi_select_slave(SPI0, 1);
	spi_write(SPI0, 0b00110101);

	uint32_t timeout = 1000;
	while(!spi_read_ready(SPI0)) {
		delay_ms(1);
		if(--timeout <= 0) {
			TEST_ASSERT_TRUE(0);
			return;
		}
	}
	TEST_ASSERT_TRUE(1);
}

void test_spi(void) {
	while(!spi_write_ready(SPI0));

	TEST_ASSERT_FALSE(spi_read(SPI0) == 0b00110101);

	spi_write(SPI0, 0b00110101);

	while(!spi_write_ready(SPI0));

	TEST_ASSERT_TRUE(spi_read(SPI0) == 0b00110101);
}
/*
void test_spi_0_write(void){
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Write new data
	spi_write(SPI0, CHAR_TEST_VALUE);
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_RDRF));
	// TDRE should give out 0
}

void test_spi_0_read(void){
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Read data
	TEST_ASSERT_TRUE(spi_read(ID_SPI0) == CHAR_TEST_VALUE);
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
}*/
