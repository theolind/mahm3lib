/**
 * @file spi.h
 * @brief Serial Peripheral Interface (SPI)
 * @details An API for controlling the two SPI peripherals inside a SAM3X8E MCU.
 * This API has implemented all of the peripherals setting flexibility and is
 * suitable for all SPI communicating modules.
 * This SPI peripheral is fast and can go up to 84 MHz and is suitable to be
 * used with External Co-Processors. The lowest transfer speed of this
 * peripheral is 84Hz / 255 = 329412.
 * @author Saeed Ghasemi
 * @author Sodet
 * @date 24 okt 2014
 * @pre The API does not handle its dependencies on other peripherals
 * internally and wont start the necessary clocks for it own operation. The
 * programmer refer to the documentation for PMC and PIO to deal with the
 * dependencies of this API on them. The programmer must first turn on its
 * clock in PMC and program the pins of this peripheral t be in its control
 * using PIO.
 * @bug Manually tested all functions to comply with all demands.
 */

#ifndef PWM_H_
#define PWM_H_

#include <inttypes.h>

/**
 * Masks for SPI_CR
 */
#define SPI_CR_SPIEN_MASK
#define SPI_CR_SPIDIS_MASK
#define SPI_CR_SWRST_MASK
#define SPI_CR_LASTXFER_MASK

/**
 * Masks for SPI_MR
 */
#define SPI_MR_MSTR_MASK
#define SPI_MR_PS_MASK
#define SPI_MR_MODFDIS_MASK
#define SPI_MR_WDRBT_MASK
#define SPI_MR_LLB_MASK
#define SPI_MR_PCS_MASK
#define SPI_MR_DLYBCS_MASK

/**
 * Masks for SPI_RDR
 */
#define SPI_RDR_RD_MASK
#define SPI_RDR_PCS_MASK

/**
 * Masks for SPI_TDR
 */
#define SPI_TDR_TD_MASK
#define SPI_TDR_PCS_MASK
#define SPI_TDR_LASTXFER_MASK

/**
 * Masks for SPI_SR
 */
#define SPI_SR_RDRF_MASK
#define SPI_SR_TDRF_MASK
#define SPI_SR_MODF_MASK
#define SPI_SR_OVRES_MASK
#define SPI_SR_NSSR_MASK
#define SPI_SR_TXEMPTY_MASK
#define SPI_SR_UNDES_MASK
#define SPI_SR_SPIENS_MASK

/**
 * Masks for SPI_IER
 */
#define SPI_IER_RDRF_MASK
#define SPI_IER_TDRE_MASK
#define SPI_IER_MODF_MASK
#define SPI_IER_OVRES_MASK
#define SPI_IER_NSSR_MASK
#define SPI_IER_TXEMPTY_MASK
#define SPI_IER_UNDES_MASK

/**
 * Masks for SPI_IDR
 */
#define SPI_IDR_RDRF_MASK
#define SPI_IDR_TDRE_MASK
#define SPI_IDR_MODF_MASK
#define SPI_IDR_OVRES_MASK
#define SPI_IDR_NSSR_MASK
#define SPI_IDR_TXEMPTY_MASK
#define SPI_IDR_UNDES_MASK

/**
 * Masks for SPI_IMR (Read-Only)
 */
#define SPI_IMR_RDRF_MASK
#define SPI_IMR_TDRE_MASK
#define SPI_IMR_MODF_MASK
#define SPI_IMR_OVRES_MASK
#define SPI_IMR_NSSR_MASK
#define SPI_IMR_TXEMPTY_MASK
#define SPI_IMR_UNDES_MASK

/**
 * Masks for SPI_CSRx
 */
#define SPI_CSRx_CPOL_MASK
#define SPI_CSRx_NCPHA_MASK
#define SPI_CSRx_CSNAAT_MASK
#define SPI_CSRx_CSAAT_MASK
#define SPI_CSRx_BITS_MASK
#define SPI_CSRx_SCBR_MASK
#define SPI_CSRx_DLYBS_MASK
#define SPI_CSRx_DLYBCT_MASK




/**
 * These are the base addresses for the two SPI peripherals
 */
#define SPI0 ((spi_reg_t *) 0x40008000U)
#define SPI1 ((spi_reg_t *) 0x4000C000U)

///\cond
/**
 * SPI register mapping
 */
typedef struct spi_reg {
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

/**
 * This function initializes the SPI peripheral.
 *
 * @param spi
 * @param settings
 */
uint8_t spi_init(spi_reg_t *spi, const spi_settings_t *settings);

// deselects the current slave then selects a new slave
// this either requires a global variable,
// or it requires another function spi_deselect_periphial(uint8_t peripheral)
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




#endif
