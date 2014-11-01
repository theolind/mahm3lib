/**
 * @file test_spi.h
 * @brief Serial Peripheral Interface (SPI) unit tests
 * @details This class is used to test the capabilities of the SPI API
 *
 * @author Jonathan Bjarnason
 * @date 2 October 2014
 */
#ifndef TEST_SPI_H_
#define TEST_SPI_H_

#define CHAR_TEST_VALUE		255
#define TEST_VALUE_16_BIT	4095

// Bit addresses in the SPI status register
/* RDRF (Receive data register full)
 * 1: Data has been received and placed in SPI_RDR since last read
 * 0: No data has been received since last read
 */
#define SPI_SR_RDRF			0
/* TDRE (Transmit data register empty)
 * 1: The last data written to SPI_TDR has been transfered to the serializer
 * 0: Data has been written to SPI_TDR but not been transfered to the serializer
 */
#define SPI_SR_TDRE			1
/* SPIENS (SPI enable status)
 * 1: SPI enabled
 * 0: SPI disabled
 */
#define SPI_SR_SPIENS		16
// Setup
void spi_setup(void);
void spi_selector_init(void);
// Initial test
void test_spi_initial_state(void);
void test_spi_after_init(void);
// Incremental tests
void test_spi_select_slave(void);
void test_spi_write_ready(void);
void test_spi_write(void);
void test_spi_read_ready(void);
void test_spi_transmission_complete(void);
void test_spi_correct_transmission(void);
void test_spi_variable_bit_lenght_transmission(void);
void test_spi_polarity_phase_change(void);
void test_spi_baud_rate_change(void);

#endif
