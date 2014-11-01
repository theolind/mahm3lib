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
#include "sam3x8e/pmc.h"
#include "sam3x8e/id.h"
#include "sam3x8e/spi_2.h"
#include "sam3x8e/pio.h"
#include "test/test_spi.h"
#include "sam3x8e/delay.h"

// TODO We will be needing a test for all functions.
// and tests for functionality that are largely done so far.

void print_register(uint32_t reg, char *name) {
	uart_write_str("\n\r");
	uart_write_str(name);
	uart_write_str(" = ");
	char chr;
	for (int i = 31; i >= 0; i--) {
		chr = (char) (48u + (((reg & (1u << i)) >> i)));
		uart_write_char(chr);
		uart_write_str(" ");
	}
	uart_write_str("\n\r");
}

void spi_setup(void) {
	pmc_enable_peripheral_clock(ID_SPI0);
	pmc_enable_peripheral_clock(ID_PIOA);

	pio_conf_pin_to_peripheral(PIOA, 0, 25);	//MISO
	pio_conf_pin_to_peripheral(PIOA, 0, 26);	//MOSI
	pio_conf_pin_to_peripheral(PIOA, 0, 27);	//SPCK
	pio_conf_pin_to_peripheral(PIOA, 0, 28);	//NPCS0
	pio_conf_pin_to_peripheral(PIOA, 0, 29);	//NPCS1
	pio_conf_pin_to_peripheral(PIOA, 0, 30);	//NPSC2
	pio_conf_pin_to_peripheral(PIOA, 0, 31);	//NPSC3

	spi_software_reset(SPI0);
}

void test_spi_initial_state(void) {
	// Testing initial values of status register
	TEST_ASSERT_FALSE(spi_enable_status(SPI0));
	TEST_ASSERT_TRUE((SPI0->SPI_SR & SPI_SR_RDRF_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_SR & SPI_SR_TDRF_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_SR & SPI_SR_TXEMPTY_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_SR & SPI_SR_SPIENS_MASK) == 0);
	// Testing initial values of mode register
	TEST_ASSERT_TRUE((SPI0->SPI_MR & SPI_MR_PCS_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_MR & SPI_MR_LLB_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_MR & SPI_MR_DLYBCS_MASK) == 0);
	// Testing initial values of selector 0
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_CPOL_MASK) == SPI_POLARITY_LOW);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_NCPHA_MASK) == SPI_PHASE_LOW);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_SCBR_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_BITS_MASK) == SPI_BITS_8);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_DLYBS_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_DLYBCT_MASK) == 0);
	// Testing initial values of selector 1
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_CPOL_MASK) == SPI_POLARITY_LOW);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_NCPHA_MASK) == SPI_PHASE_LOW);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_SCBR_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_BITS_MASK) == SPI_BITS_8);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_DLYBS_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_DLYBCT_MASK) == 0);
}

void spi_selector_init(void) {
	// Initialize ///////////////////////////////////////////
	const spi_settings_t setting = { .delay_between_cs = 12, };

	// initialize selector 0
	spi_selector_settings_t selector_0;
	selector_0.selector = SPI_SELECTOR_0;
	selector_0.CPOL = SPI_POLARITY_LOW;
	selector_0.NCPHA = SPI_PHASE_LOW;
	selector_0.baud_rate = 255;
	selector_0.bits_pr_transfer = SPI_BITS_8;
	selector_0.delay_clk = 492; // 41*12ns = 492 ns
	selector_0.delay_transfers = 381;

	// initialize selector 1
	spi_selector_settings_t selector_1;
	selector_1.selector = SPI_SELECTOR_1;
	selector_1.CPOL = SPI_POLARITY_HIGH;
	selector_1.NCPHA = SPI_PHASE_HIGH;
	selector_1.baud_rate = 128;
	selector_1.bits_pr_transfer = SPI_BITS_9;
	selector_1.delay_clk = 1000; // 41*12ns = 492 ns
	selector_1.delay_transfers = 1000;

	spi_init(SPI0, &setting);
	spi_init_selector(SPI0, &selector_0);
	spi_init_selector(SPI0, &selector_1);

	spi_enable(SPI0);

	spi_enable_loopback(SPI0);

	spi_select_slave(SPI0, SPI_SELECTOR_1); // Slave 0
	/////////////////////////////
}

void test_spi_after_init(void) {
	spi_selector_init();
	// Testing initial values of status register
	TEST_ASSERT_TRUE(spi_enable_status(SPI0));
	TEST_ASSERT_TRUE((SPI0->SPI_SR & SPI_SR_RDRF_MASK) == 0);
	TEST_ASSERT_TRUE((SPI0->SPI_SR & SPI_SR_TDRF_MASK) >> 1 == 1);
	TEST_ASSERT_TRUE((SPI0->SPI_SR & SPI_SR_TXEMPTY_MASK) >> 9 == 1);
	TEST_ASSERT_TRUE((SPI0->SPI_SR & SPI_SR_SPIENS_MASK) >> 16 == 1);
	// Testing initial values of mode register
	TEST_ASSERT_TRUE((SPI0->SPI_MR & SPI_MR_PCS_MASK) >> 16 == 0b0001);
	TEST_ASSERT_TRUE((SPI0->SPI_MR & SPI_MR_LLB_MASK) >> 7 == 1);
	TEST_ASSERT_TRUE((SPI0->SPI_MR & SPI_MR_DLYBCS_MASK) >> 24 > 0);
	// Testing initial values of selector 0
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_CPOL_MASK) == SPI_POLARITY_LOW);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_NCPHA_MASK) >> 1 == SPI_PHASE_LOW);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_SCBR_MASK) >> 8 == 255);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_BITS_MASK) >> 4 == SPI_BITS_8);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_DLYBS_MASK) >> 16 > 0);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR0 & SPI_CSRx_DLYBCT_MASK) >> 24 > 0);
	// Testing initial values of selector 1
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_CPOL_MASK) >> 0 == SPI_POLARITY_HIGH);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_NCPHA_MASK) >> 1 == SPI_PHASE_HIGH);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_SCBR_MASK) >> 8 == 128);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_BITS_MASK) >> 4 == SPI_BITS_9);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_DLYBS_MASK) >> 16 > 0);
	TEST_ASSERT_TRUE((SPI0->SPI_CSR1 & SPI_CSRx_DLYBCT_MASK) >> 24 > 0);
}

void test_spi_select_slave(void) {
	spi_select_slave(SPI0, SPI_SELECTOR_0);
	TEST_ASSERT_TRUE((SPI0->SPI_MR & SPI_MR_PCS_MASK) >> 16 == 0b0000);
	spi_select_slave(SPI0, SPI_SELECTOR_1);
	TEST_ASSERT_TRUE((SPI0->SPI_MR & SPI_MR_PCS_MASK) >> 16 == 0b0001);
	spi_select_slave(SPI0, SPI_SELECTOR_2);
	TEST_ASSERT_TRUE((SPI0->SPI_MR & SPI_MR_PCS_MASK) >> 16 == 0b0011);
}

void test_spi_write_ready() {
	spi_enable(SPI0);
	spi_select_slave(SPI0, SPI_SELECTOR_0);
	spi_write(SPI0, 0x34);
	TEST_ASSERT_FALSE(spi_tx_ready(SPI0));
	delay_ms(1);
	TEST_ASSERT_TRUE(spi_tx_ready(SPI0));
}

void test_spi_write() {
	delay_ms(1);
	spi_select_slave(SPI0, SPI_SELECTOR_0);
	TEST_ASSERT_TRUE(spi_tx_ready(SPI0));
	spi_write(SPI0, 0b01011010);
	TEST_ASSERT_FALSE(spi_tx_ready(SPI0));
	delay_ms(1);
//	TEST_ASSERT_TRUE(spi_tx_ready(SPI0));
}

void test_spi_transmission_complete() {
	delay_ms(1);
	spi_write(SPI0, 0b01011010);
	spi_write(SPI0, 0b01011011);
	TEST_ASSERT_FALSE(SPI0->SPI_SR & (0x1u << 1));
	delay_ms(1);
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << 1));
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << 9));
}

void test_spi_read_ready() {
	delay_ms(1);
	spi_read(SPI0);
	spi_write(SPI0, 0b00000000);
	delay_ms(1);
	TEST_ASSERT_TRUE(spi_rx_ready(SPI0));
}

void test_spi_correct_transmission(void) {
	while (!spi_tx_ready(SPI0))
		;
	// We wish to see if the byte transmitted is the same as the one received.
	uint16_t data1 = 0b10101010;
	uint16_t data2 = 0b10101011;
	spi_write(SPI0, data1);
	delay_ms(1);
	TEST_ASSERT_FALSE(spi_read(SPI0) == ~data1);
	TEST_ASSERT_TRUE(spi_read(SPI0) == data1);
	// We also want to see the behavior when an overrun is occurred.
	spi_write(SPI0, data1);
	spi_write(SPI0, data2);
	delay_ms(1);
	TEST_ASSERT_FALSE(spi_read(SPI0) == ~data2);
	TEST_ASSERT_TRUE(spi_read(SPI0) == data2);
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
