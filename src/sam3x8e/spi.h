/**
 * @file spi.h
 * @brief Serial Peripheral Interface (SPI)
 * @details An API for controlling the two SPI peripherals inside a SAM3X8E MCU.
 * This API has implemented all of the peripherals setting flexibility and is
 * suitable for all SPI communicating modules.
 * This SPI peripheral is fast and can go up to 84 MHz and is suitable to be
 * used with External Co-Processors. The lowest transfer speed of this
 * peripheral is 84Hz / 255 = 329412 baud rate.
 * @author Saeed Ghasemi
 * @author Soded Alatia
 * @date 1 November 2014
 * @pre The API does not handle its dependencies on other peripherals
 * internally and wont start the necessary clocks for it own operation. The
 * programmer refer to the documentation for PMC and PIO to deal with the
 * dependencies of this API on them. The programmer must first turn on its
 * clock in PMC and program the pins of this peripheral to be in its control
 * using PIO.
s */

#ifndef SPI_H_
#define SPI_H_

#ifndef INTTYPES_H_
#define INTTYPES_H_
#include <inttypes.h>
#endif /* INTTYPES_H_ */

///\cond
/**
 * These are the base addresses for the two SPI peripherals
 */
#define SPI0				((spi_reg_t *) 0x40008000u)
#define SPI1				((spi_reg_t *) 0x4000C000u)
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
/**
 * @typedef spi_settings_t
 * This structure defines the input variable to be used with the spi_init()
 * function.
 */
typedef struct spi_settings {
	/**
	 * This defines the Delay Between Chip Selects. The delay time guarantees
	 * non-overlapping chip selects and solves bus contentions in case of
	 * peripherals having long data float times. The minimum is 71 ns and
	 * maximum is 3036 ns. (Value must be a multiply of 12 ns, or it will be
	 * rounded down.
	 */
	uint8_t delay_between_cs;	///< Used to set the delay between chip selects
} spi_settings_t;
/**
 * @typedef spi_selector_settings_t
 * This structure is used to initialize a selector of the SPI. There is a
 * total of 4 selectors.
 */
typedef struct spi_selector_settings {
	/**
	 * This will define the selector to initialize out of 4 in total.
	 * The values are going from 0 till 3.
	 * (Use the predefines values with prefix: SPI_SELECTOR_)
	 */
	uint8_t selector;
	/**
	 * This will define the baud rate for the given selector. The value must be between 0 and 255 and the baud rate will be defined with
	 * (MCK / baudR) were MCK is the main clock with 84MHz (84000000 Hz).
	 */
	uint8_t baud_rate;			///< Used to set the baud rate of the selector
	/**
	 * This will define the polarity of the SPI clock. The values are 0 or 1.
	 * Set it to 1 to define the inactive state value of SPCK to be logic level
	 * one and vice versa if it's set to 0.
	 */
	uint8_t CPOL;				///< CPOL: Clock polarity
	/**
	 * This will define the phase of the SPI clock. The values are 0 or 1.
	 * Set it to 1 to define that data is captured on the leading edge of SPCK
	 * and changed on the following edge of SPCK and vice versa if it's set to 0.
	 */
	uint8_t NCPHA;				///< NCPHA: Clock phase
	/**
	 * This will define the Delay Between Consecutive Transfers and must be set
	 * between 0 and 97143 ns.
	 */
	uint32_t delay_transfers;///< Used to set the delay between consecutive transfers
	/**
	 * This will define the Delay between the assertion of chip select line and
	 * when the the SPI clock starts and must be set between 0 and 3036 ns.
	 */
	uint16_t delay_clk;			///< Used to set the Delay Before SPCK starts
	/**
	 * This variable defines the width of data to be transmitted. The width can
	 * be between 8 bits and 16 bits. This variable must be set between 0 and 8,
	 * were 0 means 8 bits and 8 means 16 bits.
	 */
	uint8_t bits_pr_transfer;///< The amount of bits to be transmitted on each transfer
	uint8_t reserved;
} spi_selector_settings_t;
///@}

///@{
/**
 * Masks for SPI_CR
 */
#define SPI_CR_SPIEN_MASK			(1u << 0)
#define SPI_CR_SPIDIS_MASK			(1u << 1)
#define SPI_CR_SWRST_MASK			(1u << 7)
#define SPI_CR_LASTXFER_MASK		(1u << 24)
///@}
///@{
/**
 * Masks for SPI_MR
 */
#define SPI_MR_MSTR_MASK			(1u << 0)
#define SPI_MR_PS_MASK				(1u << 1)
#define SPI_MR_PCSDEC_MASK			(1u << 2)
#define SPI_MR_MODFDIS_MASK			(1u << 4)
#define SPI_MR_WDRBT_MASK			(1u << 5)
#define SPI_MR_LLB_MASK				(1u << 7)
#define SPI_MR_PCS_MASK				(0xFu << 16)
#define SPI_MR_DLYBCS_MASK			(0xFFu << 24)
///@}
///@{
/**
 * Masks for SPI_RDR
 */
#define SPI_RDR_RD_MASK				(0xFFFFu << 0)
#define SPI_RDR_PCS_MASK			(0xFu << 16)
///@}
///@{
/**
 * Masks for SPI_TDR
 */
#define SPI_TDR_TD_MASK				(0xFFFFu << 0)
///@}
///@{
/**
 * Masks for SPI_SR
 */
#define SPI_SR_RDRF_MASK			(1u << 0)
#define SPI_SR_TDRF_MASK			(1u << 1)
#define SPI_SR_TXEMPTY_MASK			(1u << 9)
#define SPI_SR_SPIENS_MASK			(1u << 16)
///@}
///@{
/**
 * Masks for SPI_CSRx
 */
#define SPI_CSRx_CPOL_MASK			(1u << 0)
#define SPI_CSRx_NCPHA_MASK			(1u << 1)
#define SPI_CSRx_CSNAAT_MASK		(1u << 2)
#define SPI_CSRx_CSAAT_MASK			(1u << 3)
#define SPI_CSRx_BITS_MASK			(0xFu << 4)
#define SPI_CSRx_SCBR_MASK			(0xFFu << 8)
#define SPI_CSRx_DLYBS_MASK			(0xFFu << 16)
#define SPI_CSRx_DLYBCT_MASK		(0xFFu << 24)
///@}
///@{
/**
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
#define SPI_SELECTOR_0				(0u) //(0b1110)
#define SPI_SELECTOR_1				(1u) //(0b1101)
#define SPI_SELECTOR_2				(2u) //(0b1011)
#define SPI_SELECTOR_3				(3u) //(0b0111)
#define SPI_SELECTOR_NONE			(4u) //(0b1111)
///@}
///@{
/**
 * These are variables used with the
 */
#define SPI_OPTION_KEEP_CS_ACTIVE			(0u)
#define SPI_OPTION_DONT_KEEP_CS_ACTIVE		(1u)
#define SPI_OPTION_DISABLE_CS_OPTIONS		(2u)
///@}
///@{
/**
 * These variable define the inactive state value of the SPI clock
 */
#define SPI_POLARITY_HIGH			(0x1u)
#define SPI_POLARITY_LOW			(0x0u)
///@}
///@{
/**
 * These variable define the actions taken at different time relative to the
 * SPI clock.
 * 0 = Data is changed on the leading edge of SPCK and captured on the
 * following edge of SPCK.
 * 1 = Data is captured on the leading edge of SPCK and changed on the
 * following edge of SPCK.
 */
#define SPI_PHASE_HIGH				(0x1u)
#define SPI_PHASE_LOW				(0x0u)
///@}
///@{
/**
 * These variable define the amount of bits to be tranfered on each
 * transmission.
 */
#define SPI_BITS_8					(0u)
#define SPI_BITS_9					(1u)
#define SPI_BITS_10					(2u)
#define SPI_BITS_11					(3u)
#define SPI_BITS_12					(4u)
#define SPI_BITS_13					(5u)
#define SPI_BITS_14					(6u)
#define SPI_BITS_15					(7u)
#define SPI_BITS_16					(8u)
///@}

/**
 * This function initializes the SPI peripheral.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param settings This is a struct of type spi_settings_t with different
 * setting for the initialization of the peripheral.
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_init(spi_reg_t *spi, const spi_settings_t *settings);
/**
 * This function will initialize a given selector.
 * Consider the selectors as channels of the SPI peripheral. With this function
 * one can set the SPI channel/selector with different settings and simply
 * select one of the selectors for the next transfer when needed. The selector
 * pins themselves can be used for selecting different devices connected to the
 * peripheral. This way SPI peripheral can be seen merely like servicing the
 * different selectors. The selector pins are also called "chip select" or just
 * short 'cs'.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param settings This is a struct of type spi_selector_settings_t with the
 * needed parameters for the initialization of the selector.
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_init_selector(spi_reg_t *spi,
		const spi_selector_settings_t *settings);
/**
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_enable(spi_reg_t *spi);
/**
 * This function will return 1 if the SPI peripheral is enabled.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return Returns 1 if the SPI peripheral is enabled
 */
uint8_t spi_enable_status(spi_reg_t *spi);
/**
 * This function will set the baud rate for the given selector.
 * The value for baud_rate must be between 0 and 255 and the baud rate will be
 * defined by (MCK / baudR) [Hz] were MCK is the main clock with 84MHz
 * (84000000 Hz). If baud rate 84MHz is set by setting baud_rate = 1, then all
 * the other selectors must use the same baud rate. This is only true for
 * baud rate = 1 or in frequency 84MHz.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param selector The selector to be modified.
 * (Use the predefined with prefix: SPI_SELECTOR_)
 * @param baud_rate
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_set_selector_baud_rate(spi_reg_t *spi, uint8_t selector,
		uint32_t baud_rate);
/**
 * This function will set the polarity of the SPI clock and indicates what the inactive
 * state of the SPI clock is.
 * Set it to SPI_POLARITY_HIGH to define the inactive state value of SPCK to be
 * logic level 1 and vice versa if it's set to SPI_POLARITY_LOW.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param selector The selector to be modified.
 * (Use the predefined with prefix: SPI_SELECTOR_)
 * @param polarity The polarity of the SPI clock.
 * (Use the predefined with prefix: SPI_POLARITY_)
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_set_selector_clk_polarity(spi_reg_t *spi, uint8_t selector,
		uint32_t polarity);
/**
 * This function will set the phase of the SPI clock and indicate when
 * capturing and shifting should occur.
 * The values are 0 or 1.
 * Set it to SPI_PHASE_HIGH to define that data is captured on the leading edge
 * of SPCK (SPI clock) and changed on the following edge of SPCK and vice versa
 * if it's set to SPI_PHASE_LOW.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param selector The selector to be modified.
 * (Use the predefined with prefix: SPI_SELECTOR_)
 * @param phase The phase of the SPI clock.
 * (Use the predefined with prefix: SPI_PHASE_)
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_set_selector_clk_phase(spi_reg_t *spi, uint8_t selector,
		uint32_t phase);
/**
 * This function can control two options of the selectors.
 * (1)
 * Chip Select Active After Transfer.
 * If the transfer buffer is continuously filled with data, the chip select (cs)
 * line will not be deasserted before the new transfer is begun. This function
 * explicitly tells the peripheral not to deassert the cs-line when a transfer
 * is done, even if no new data is placed in the transfer buffer. The line will
 * however be deasserted when another selector is selected or when
 * spi_last_transfer() is invoked.
 * Certain devices require this option to be set.
 * (2)
 * Chip Select Not Active After Transfer.
 * Even if the transfer buffer is continuously filled with data, the chip select
 * line will deassert between transfers.
 * This function explicitly tells the peripheral to deassert the CS-line between
 * all transfers, even if new data is placed in the transfer buffer.
 * Certain devices require this option to be set to indicate end of byte.
 *
 * (Use one of the predefined settings with prefix: SPI_OPTION_)
 *
 * At default both settings are off and the behavior is something of a mix.
 * The CS line will not be deasserted if the transmit-buffer is continuously
 * filled, but it will if the writing to the buffer is delayed.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param selector The selector to be modified.
 * (Use the predefined with prefix: SPI_SELECTOR_)
 * @param option The option to use for setting.
 * (Use the predefined with prefix: SPI_OPTION_)
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_set_selector_option(spi_reg_t *spi, uint8_t selector,
		uint32_t option);
/**
 * This function set the amount of bits that a single transfer will transfer.
 * At default this option is set to 8 bit on each transfer (1 byte), but the
 * peripheral can handle up to 16 bits on each transfer.
 * The bit_count parameter must be set between 0 and 8 for 8 till 16 bits.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param selector The selector to be modified.
 * (Use the predefined with prefix: SPI_SELECTOR_)
 * @param bit_count The amount of bits to be transfered when transfering.
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_set_selector_bit_length(spi_reg_t *spi, uint8_t selector,
		uint32_t bit_count);
/**
 * This function will set the Delay Between Chip Selects.
 * The delay time guarantees non-overlapping chip selects and solves bus
 * contentions in case of peripherals having long data float times.
 * The delay can be set between 12 and 3036 ns with a resolution of 255.
 * Therefore, the actual set values will be a multiply of 12 ns.
 * A higher value than 3036 will be reduced to 3036 ns.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param delay
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_set_delay_between_cs(spi_reg_t *spi, uint16_t delay);
/**
 * This function will set the delay between when the chip select (CS) line is
 * asserted and when the clk starts for the transfer.
 * This may be necessary for a particular device.
 * The delay must be between 0 and 3036 ns with a resolution of 255.
 * Therefore, the actual set values will be a multiply of about 12 ns.
 * A higher value than 3036 will be reduced to 3036 ns.
 * An error is produced if the selector is higher than 3. No change will take
 * effect.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param selector The selector to be modified.
 * (Use the predefined with prefix: SPI_SELECTOR_)
 * @param delay The delay to be set. (Set between 12 and 3036)
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_set_selector_delay_clk_start(spi_reg_t *spi, uint8_t selector,
		uint16_t delay);
/**
 * This function will set the delay between consecutive transfers.
 * This may be necessary for a particular device.
 * The delay must be between 0 and 97143 ns with a resolution of 255.
 * Therefore, the actual set values will be a multiply of 381 ns.
 * A higher value than 97143 will not be processed and will return an error.
 * The same is true if selector is higher than 3.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param selector The selector to be modified.
 * (Use the predefined with prefix: SPI_SELECTOR_)
 * @param delay The delay to be set. (Set between 0 and 97143)
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_set_selector_delay_transfers(spi_reg_t *spi, uint8_t selector,
		uint32_t delay);
/**
 * This function is only useful when in master mode and is used to select a
 * slave using the selector-pins. This function will check first to see if a
 * transfer is in progress before it selects the next selector.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param slave This parameter defines which selector to assert.
 * (Use one of the predefines values with prefix: SPI_SELECTOR_)
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_select_slave(spi_reg_t *spi, uint8_t slave);
/**
 * Write a data of max 16 bits in length.
 * If subsequent write are performed, be sure to check the if transfer buffer
 * is ready with spi_tx_ready() before writing.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @param data The data to be transmitted of max length 16-bit
 * @return error (1 = SUCCESS, 0 = FAIL)
 */
uint8_t spi_write(spi_reg_t *spi, uint16_t data);
/**
 * This function will read a previously received byte with an earlier
 * transmission.
 * Keep in mind that the spi_write() function can also be used to read the
 * previously received data.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return Returns the data that is received with the last transmission
 */
uint16_t spi_read(spi_reg_t *spi);
/**
 * We want to test if we are able to read data. It is good to do this before
 * you read data.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return Returns 1 if there is data in the receive register that is not read
 */
uint8_t spi_rx_ready(spi_reg_t *spi);
/**
 * This function will check and see that a new byte can be placed in the
 * transmit buffer of the peripheral.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return Returns 1 if the transmit buffer is empty and new data can be send
 */
uint8_t spi_tx_ready(spi_reg_t *spi);
/**
 * This function returns 1 if the write buffer and the shift-registers for
 * transfer are empty. This means that no transmission is taking place and is
 * used primarily in master-mode.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return Return 1 if transmissions are complete or 0 if there are
 * pending or ongoing transmission.
 */
uint8_t spi_transmission_done(spi_reg_t *spi);
/**
 * This function will disable the SPI-peripheral. As soon as this function is
 * run, SPI finishes its transfer. All pins are set in input mode and no data
 * is received or transmitted. If a transfer is in progress, the transfer is
 * finished before the SPI is disabled.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
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
uint8_t spi_enable_loopback(spi_reg_t *spi);
/**
 * run this to disconnect MOSI from MISO in the peripheral internally.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_disable_loopback(spi_reg_t *spi);
/**
 * This function will tell the peripheral to generate a software reset of the
 * entire peripheral.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_reset(spi_reg_t *spi);
/**
 * This will indicate that the last transfer is done for now and will raise the
 * chip select pin to high and deassert the slave device connected to it. If
 * spi_selector_keep_cs_active() is used, then this will close the open line to
 * the device by raising the CS-line and indicate an end of transfer. If a
 * transfer is ongoing this change will take effect after that the current
 * transfer is complete.
 *
 * @param spi The base-address of the SPI-peripheral that shall be used.
 * (Use one of predefined values with prefix: SPI)
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t spi_close_selector(spi_reg_t *spi);


#endif /* SPI_H_ */
