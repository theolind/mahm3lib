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

void test_spi(void) {
	const spi_settings_t spi_settings_t = {
		.master = 1,
		.CPOL = 0,
		.NCPHA = 0,
		.baud[0] = 128,
		.bits[0] = 8
	};

	pmc_enable_peripheral_clock(ID_SPI0);

	TEST_ASSERT_FALSE(SPI0->SPI_SR & (0x1u << SPI_SR_SPIENS));
	TEST_ASSERT_TRUE(spi_init(SPI0, &spi_settings_t));
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_SPIENS));

	pio_conf_pin_to_peripheral(PIOA, 1, 25);
	pio_conf_pin_to_peripheral(PIOA, 1, 26);

	//spi_select_slave(SPI0, 1);

	spi_write(SPI0, 0b00110101);

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
