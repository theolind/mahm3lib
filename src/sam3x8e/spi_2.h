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
 * @date 24 okt 2014
 * @pre The API does not handle its dependencies on other peripherals
 * internally and wont start the necessary clocks for it own operation. The
 * programmer refer to the documentation for PMC and PIO to deal with the
 * dependencies of this API on them. The programmer must first turn on its
 * clock in PMC and program the pins of this peripheral t be in its control
 * using PIO.
 * @bug Manually tested all functions to comply with all demands.
 */

#ifndef SPI_H_
#define SPI_H_

#include <inttypes.h>

///@{
/**
 * @def
 * Masks for SPI_CR
 */
#define SPI_CR_SPIEN_MASK			(1 << 0)
#define SPI_CR_SPIDIS_MASK			(1 << 1)
#define SPI_CR_SWRST_MASK			(1 << 7)
#define SPI_CR_LASTXFER_MASK		(1 << 24)
///@}
///@{
/**
 * @def
 * Masks for SPI_MR
 */
#define SPI_MR_MSTR_MASK			(0b01)(1 << 0)
//#define SPI_MR_MODFDIS_MASK			(0x10)(1 << 4)
#define SPI_MR_LLB_MASK				(0x80)(1 << 7)
#define SPI_MR_PCS_MASK				(0xF << 16)
#define SPI_MR_DLYBCS_MASK			(0xFF << 24)
///@}
///@{
/**
 * @def
 * Masks for SPI_RDR
 */
#define SPI_RDR_RD_MASK				(0xFFFF << 0)
#define SPI_RDR_PCS_MASK			(0xF << 16)
///@}
///@{
/**
 * @def
 * Masks for SPI_TDR
 */
#define SPI_TDR_TD_MASK				(0xFFFF << 0)
///@}
///@{
/**
 * @def
 * Masks for SPI_SR
 */
#define SPI_SR_RDRF_MASK			(1 << 0)
#define SPI_SR_TDRF_MASK			(1 << 1)
//#define SPI_SR_NSSR_MASK			(1 << 8)
#define SPI_SR_TXEMPTY_MASK			(1 << 9)
//#define SPI_SR_UNDES_MASK			(1 << 10) // Slave mode only
#define SPI_SR_SPIENS_MASK			(1 << 16)
///@}
///@{
/**
 * @def
 * Masks for SPI_IER
 */
/*
#define SPI_IER_RDRF_MASK			(1 << 0)
#define SPI_IER_TDRE_MASK			(1 << 1)
#define SPI_IER_MODF_MASK			(1 << 2)
#define SPI_IER_OVRES_MASK			(1 << 3)
#define SPI_IER_NSSR_MASK			(1 << 8)
#define SPI_IER_TXEMPTY_MASK		(1 << 9)
#define SPI_IER_UNDES_MASK			(1 << 10)
*/
///@}
///@{
/**
 * @def
 * Masks for SPI_IDR
 */
/*
#define SPI_IDR_RDRF_MASK			(1 << 0)
#define SPI_IDR_TDRE_MASK			(1 << 1)
#define SPI_IDR_MODF_MASK			(1 << 2)
#define SPI_IDR_OVRES_MASK			(1 << 3)
#define SPI_IDR_NSSR_MASK			(1 << 8)
#define SPI_IDR_TXEMPTY_MASK		(1 << 9)
#define SPI_IDR_UNDES_MASK			(1 << 10)
*/
///@}
///@{
/**
 * @def
 * Masks for SPI_IMR (Read-Only)
 */
/*
#define SPI_IMR_RDRF_MASK			(1 << 0)
#define SPI_IMR_TDRE_MASK			(1 << 1)
#define SPI_IMR_MODF_MASK			(1 << 2)
#define SPI_IMR_OVRES_MASK			(1 << 3)
#define SPI_IMR_NSSR_MASK			(1 << 8)
#define SPI_IMR_TXEMPTY_MASK		(1 << 9)
#define SPI_IMR_UNDES_MASK			(1 << 10)
*/
///@}
///@{
/**
 * @def
 * Masks for SPI_CSRx
 */
#define SPI_CSRx_CPOL_MASK			(1 << 0)
#define SPI_CSRx_NCPHA_MASK			(1 << 1)
#define SPI_CSRx_CSNAAT_MASK		(1 << 2)
#define SPI_CSRx_CSAAT_MASK			(1 << 3)
#define SPI_CSRx_BITS_MASK			(0xF << 4)
#define SPI_CSRx_SCBR_MASK			(0xFF << 8)
#define SPI_CSRx_DLYBS_MASK			(0xFF << 16)
#define SPI_CSRx_DLYBCT_MASK		(0xFF << 24)
///@}
///@{
/**
 * @def
 * These are the different possible slaves that can be selected in master mode.
 * There is a method for selecting as many devices as needed. The method is as
 * followed:
 * Use the first selector, but don't wire it to any device. Instead use the PIO
 * to pull the 'Slave Select' pin of the device low instead of using this of
 * the peripheral. Then for each device that you want to select, modify the
 * appropriate register of the selector and set the baud rate and clock polarity
 * and phase as needed for the device you intent to communicate with, and then
 * select it with Selector_1 and pull its PIO-pin low at the same time. Now you
 * have selected the device but not using the actual Selector_1 pin. With this
 * method you can have as many devices connected to the peripheral as there are
 * pins to use.
 */
#define SPI_SELECTOR_1			(0b1110)
#define SPI_SELECTOR_2			(0b1101)
#define SPI_SELECTOR_3			(0b1011)
#define SPI_SELECTOR_4			(0b0111)
#define SPI_SELECTOR_NONE		(0b1111)
///@}

///\cond
/**
 * @def
 * These are the base addresses for the two SPI peripherals
 */
#define SPI0		((spi_reg_t *) 0x40008000U)
#define SPI1		((spi_reg_t *) 0x4000C000U)
/**
 * SPI register mapping
 */
typedef struct spi_reg {
	uint32_t SPI_CR;		///< 0x00, Control Register
	uint32_t SPI_MR;		///< 0x04, Mode Register
	uint32_t SPI_RDR;		///< 0x08, Receive Data Register
	uint32_t SPI_TDR;		///< 0x0c, Transmit Data Register
	uint32_t SPI_SR;		///< 0x10, Status Register
	uint32_t SPI_IER;		///< 0x14, Interrupt Enable Register
	uint32_t SPI_IDR;		///< 0x18, Interrupt Disable Register
	uint32_t SPI_IMR;		///< 0x1c, Interrupt Mask Register
	uint32_t reserved0[4];	///< 0x20-0x2c, Reserved
	uint32_t SPI_CSR0;		///< 0x30, Chip Select Register 0
	uint32_t SPI_CSR1;		///< 0X34, Chip Select Register 1
	uint32_t SPI_CSR2;		///< 0X38, Chip Select Register 2
	uint32_t SPI_CSR3;		///< 0X3C, Chip Select Register 3
	uint32_t reserved1[41];	///< 0x40 - 0xe0, Reserved
	uint32_t SPI_WPMR;		///< 0xE4, Write Protection Control Register
	uint32_t SPI_WPSR;		///< 0xE8, Write Protection Status Register
	//registers 0xec - 0xfc reserved
} spi_reg_t;
///\endcond
///@{
typedef struct spi_settings {
	uint8_t master;				///< Used to set the peripheral in slave or master mode
	uint8_t perip_select_mode;	///< Used to set the peripheral in fixed or variable chip select
	uint8_t DLYBCS;				///< Used to set the delay between chip selects

}spi_settings_t;
/**
 * @typedef
 * This structure is used to initialize a selector of the SPI. There is a
 * total of 4 selectors.
 */
typedef struct spi_selector_settings {
	uint8_t baudR;				///< Used to set the baud rate of the selector
	uint8_t CPOL;				///< CPOL: Clock polarity
	uint8_t NCPHA;				///< NCPHA: Clock phase
	uint8_t BITS_pr_transfer;	///< The amount of bits to be transmitted
	uint8_t DLYBCT;				///< Used to set the delay between consecutive transfers
	uint8_t DLYBS;				///< Used to set the Delay Before SPCK starts
}spi_selector_settings_t;
///@}

/////// PROTOTYPES ////////////////////////////////////////////////
/**
 * This function initializes the SPI peripheral.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param settings This is a struct of type spi_settings_t with different
 * setting for the initialization of the peripheral.
 */
uint8_t spi_init(spi_reg_t *spi, const spi_settings_t *settings);
/**
 * This function will initialize a given selector.
 * Consider the selectors as channels of the SPI peripheral. With this function
 * one can set the SPI channel/selector with different settings and simply
 * select one of the selectors for the next transfer when needed. The selector
 * pins themselves can be used for selecting different devices connected to the
 * peripheral. This way SPI peripheral can be seen merely like servicing the
 * different selectors.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param settings This is a struct of type spi_selector_settings_t with the
 * needed setting for the initialization of the selector.
 * @return
 */
uint8_t spi_init_selector(spi_reg_t *spi, const spi_selector_settings_t *settings);
/**
 * Sets the peripheral into master-mode.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return
 */
uint8_t spi_set_master(spi_reg_t *spi);
/**
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return
 */
uint8_t spi_set_slave(spi_reg_t *spi);
/**
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return
 */
uint8_t spi_enable(spi_reg_t *spi);//2
/**
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param selector
 * @param baud_rate
 * @return
 */
uint8_t spi_selector_set_baud_rate(spi_reg_t *spi, uint8_t selector, uint8_t baud_rate);

uint8_t spi_selector_set_clk_polarity(spi_reg_t *spi, uint8_t selector, uint8_t polarity);

uint8_t spi_selector_set_clk_phase(spi_reg_t *spi, uint8_t selector, uint8_t phase);
/**
 * This function  is the primary function for sending and receiving data with
 * the SPI-peripheral. SPI is a true full-duplex communication peripheral and
 * this function makes use of this ability. The function spi_read() and
 * spi_write() are for one-way transmitions if they are needed.
 *
 * @param spi
 * @param data
 * @return
 */
uint16_t spi_master_tranceive(spi_reg_t *spi, uint16_t data);
/**
 * This function is only useful when in master mode and is used to select a
 * slave using the selector-pins. This function will check first to see if a
 * transfer is in progress before it selects the next selector.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param slave This parameter defines which selector to assert.
 * (Use one of the predefines values with prefix: SPI_SELECTOR_)
 */
uint8_t spi_select_slave(spi_reg_t *spi, uint8_t slave);
/**
 * Write a data of max 16 bits in length. This will make the SPI receive a
 * equally long data that it will discard and avoid overrun error in the
 * peripheral.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param data The data to be transmitted of max length 16-bit
 */
uint8_t spi_master_write(spi_reg_t *spi, uint16_t data);
/**
 * This function is only intended for the slave mode of this peripheral and
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param data Data to be placed on the shift-registers for sending.
 * @return
 */
uint8_t spi_slave_write(spi_reg_t *spi, uint16_t data);
/**
 * This function will requenst a but by sending a dummy data to the remote
 * device and return the received data.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param dummy_data Any data of your choice (Choose something that is ignored by the slave-device)
 * @return Returns the data that is received when transferring the dummy_data
 */
uint16_t spi_master_read(spi_reg_t *spi, uint16_t dummy_data);
/**
 * This function will check and see that a new byte can be placed in the
 * transmit buffer of the peripheral.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return Returns 1 if the transmit buffer is empty and new data can be send
 */
uint8_t spi_write_ready(spi_reg_t *spi);
/**
 * This function returns 1 if the write buffer and the shift-registers for
 * transfer are empty. This means that no transmission is taking place and is
 * used primarily in master-mode.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return Will return 1 if transmissions are complete or 0 if there are
 * pending or ongoing transmission.
 */
uint8_t spi_transmission_done(spi_reg_t *spi);
/**
 * We want to test if we are able to read data. It is good to do this before you read data.
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return returns 1 if we have data in the receive register
 */
uint8_t spi_read_ready(spi_reg_t *spi);
/**
 * This function will generate a software reset of the entire peripheral.
 * This function is used in spi_init()
 *
 * @param spi
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_software_reset(spi_reg_t *spi);
/**
 * This enables an interrupts.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param interrupt
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_interrupt_enable(spi_reg_t *spi, uint8_t interrupt);
/**
 * This function disables interrupts.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param interrupt
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_interrupt_disable(spi_reg_t *spi, uint8_t interrupt);
/**
 * This function will disable the SPI-peripheral. As soon as this function is
 * run, SPI finishes its transfer. All pins are set in input mode and no data
 * is received or transmitted. If a transfer is in progress, the transfer is
 * finished before the SPI is disabled.
 *
 * @param spi
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_disable(spi_reg_t *spi);
/**
 * Used only in test purposes. Enable this to connect MOSI to MISO in the
 * peripheral.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_loopback_enable(spi_reg_t *spi);
/**
 * run this to disconnect MOSI from MISO in the peripheral internally.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_loopback_disable(spi_reg_t *spi);
/**
 * Indicates that the last transfer or the current transfer is the last one.
 * This will make the chip select line become deasserted (raised) regardless of
 * the setting for keeping the device asserted between transfers as set by
 * spi_keep_line_assertion().
 *
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_selector_close(void);

#endif
