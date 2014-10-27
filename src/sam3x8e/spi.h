/**
 * @file

 * @author Theodor Lindquist
 * @author Jonathan Bjarnarsson
 * @author Soded Alatia
 * @version 0.1
 * @date 28 sep 2014
 *
 * @brief First draft of the SPI interface
 */

#ifndef SPI_H_
#define SPI_H_

#include <inttypes.h>

//base addresses to SPI registers
#define SPI0 ((spi_reg_t *) 0x40008000U)
#define SPI1 ((spi_reg_t *) 0x4000C000U)

///\cond
/*
 * Mapping of SPI registers
 */
typedef struct spi_reg_t {
	uint32_t SPI_CR;		//0x00, control register
	uint32_t SPI_MR;		//0x04, mode register
	uint32_t SPI_RDR;		//0x08, receive data register
	uint32_t SPI_TDR;		//0x0c, transmit data register
	uint32_t SPI_SR;		//0x10, status register
	uint32_t SPI_IER;		//0x14, interrupt enable register
	uint32_t SPI_IDR;		//0x18, interrupt disable register
	uint32_t SPI_IMR;		//0x1c, interrupt mask register
	uint32_t reserved0[4];	//0x20-0x2c, reserved
	uint32_t SPI_CSR0;		//0x30, chip select register 0
	uint32_t SPI_CSR1;		//0X34, chip select register 1
	uint32_t SPI_CSR2;		//0X38, chip select register 2
	uint32_t SPI_CSR3;		//0X3C, chip select register 3
	uint32_t reserved1[41];	//0x40 - 0xe0, reserved
	uint32_t SPI_WPMR;		//0xE4, write protection control register
	uint32_t SPI_WPSR;		//0xE8, write protection status register
	//registers 0xec - 0xfc reserved
} spi_reg_t;
///\endcond

typedef struct {
	uint32_t master;
	uint32_t CPOL;
	uint32_t NCPHA;
	uint32_t baud[4];
	uint32_t bits[4];
	uint32_t DLYBCT;
	uint32_t DLYBS;
} spi_settings_t;

//this would start configure the pins etc.
//return 0 (1 as error code in the future)

/**
 * Initialize SPI
 * @param spi
 * @param settings
 */
uint8_t spi_init(spi_reg_t *spi, const spi_settings_t *settings);

// deselects the current slave then selects a new slave
// this either requires a global variable,
// or it requires another function spi_deselect_periphial(uint8_t periphial)
// or the two functions could be in one: spi_select_periphial(uint8_t old, uint8_t new)
void spi_select_slave(spi_reg_t *spi, uint8_t slave);

/*
 * Write 8 bits of data (a char). This fills the receive register with data sent to the processor
 * After each write a spi_read has to be performed to clear the receive register
 * @param spi
 * @param data the data to send
 */
void spi_write(spi_reg_t *spi, uint16_t data);

/**
 * Reads data that has been received
 * @param spi
 * @pre You need to spi_write_char before you can spi_read_char
 * @return received char
 */
uint16_t spi_read(spi_reg_t *spi);

/**
 * Test if we are able to send data
 * @param spi
 * @return true if all data has been sent and we are ready to send new data
 */
uint32_t spi_write_ready(spi_reg_t *spi);

/**
 * We want to test if we are able to read data. It is good to do this before you read data.
 * @param spi
 * @return true if we have data in the receive register
 */
uint8_t spi_read_ready(spi_reg_t *spi);

/**
 * We want to be sure that we have completed the transmission. Good thing to do after you write data.
 * @param spi
 * @return true if transmission is completed.
 */
uint32_t spi_write_complete(spi_reg_t *spi);

#endif /* SPI_H_ */
