/*
 * Serial Peripheral Interface (SPI)
 * An API for controlling the two SPI peripherals inside a SAM3X8E MCU.
 * This API has implemented all of the peripherals setting flexibility and is
 * suitable for all SPI communicating modules.
 * This SPI peripheral is fast and can go up to 84 MHz and is suitable to be
 * used with External Co-Processors. The lowest transfer speed of this
 * peripheral is 84Hz / 255 = 329412 baud rate.
 *
 * The API does not handle its dependencies on other peripherals
 * internally and wont start the necessary clocks for it own operation. The
 * programmer refer to the documentation for PMC and PIO to deal with the
 * dependencies of this API on them. The programmer must first turn on its
 * clock in PMC and program the pins of this peripheral to be in its control
 * using PIO.
 *
 *  author: Saeed Ghasemi
 *  author: Soded Alatia
 *
 *  date: 1 November 2014
 *
 */

#include "spi.h"

uint8_t spi_init(spi_reg_t *spi, const spi_settings_t *settings) {
	// These settings are not implemented in this API and are therefore
	// hardcoded to the following:
	// -> set to master
	spi->SPI_MR |= (0x1U << 0);
	// -> set to fixed peripheral select
	spi->SPI_MR &= ~(0x1U << 1);
	// -> set chip select decoding 'off'
	spi->SPI_MR &= ~(0x1U << 2);
	// -> set mode fault detection 'off'
	spi->SPI_MR |= (0x1U << 4);
	// -> set Wait Data Read Before Transfer 'off' (send data at any time)
	spi->SPI_MR &= ~(0x1U << 5);

	// set Delay Between Chip Selects
	spi_set_delay_between_cs(spi, settings->delay_between_cs);
	// Initially select none of the selectors (slaves)
	spi_select_slave(spi, SPI_SELECTOR_NONE);
	return 1;
}

uint8_t spi_init_selector(spi_reg_t *spi,
		const spi_selector_settings_t *settings) {
	// Set the clock polarity for the transfer
	spi_set_selector_clk_polarity(spi, settings->selector, settings->CPOL);
	// Set the clock phase for the transfer
	spi_set_selector_clk_phase(spi, settings->selector, settings->NCPHA);
	// Set the baud rate of the transfer
	spi_set_selector_baud_rate(spi, settings->selector, settings->baud_rate);
	// Set the amount of bits to transfer
	spi_set_selector_bit_length(spi, settings->selector,
			settings->bits_pr_transfer);
	// Set delay before spi clock starts after CS assertion
	spi_set_selector_delay_clk_start(spi, settings->selector,
			settings->delay_clk);
	// Set delay between consecutive transfers
	spi_set_selector_delay_transfers(spi, settings->selector,
			settings->delay_transfers);
	return 1;
}

uint8_t spi_enable(spi_reg_t *spi) {
	// Set the enable pin in control register
	spi->SPI_CR |= SPI_CR_SPIEN_MASK;
	return 1;
}

uint8_t spi_enable_status(spi_reg_t *spi) {
	// read the status bit of SPI being enabled in status register
	return (spi->SPI_SR & SPI_SR_SPIENS_MASK) > 0;
}

uint8_t spi_set_selector_baud_rate(spi_reg_t *spi, uint8_t selector,
		uint32_t baud_rate) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (selector > 3) {
		return 0; // Error
	}
	if (baud_rate > 255) {
		baud_rate = 255;
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_SCBR_MASK) & *p_reg) | (baud_rate << 8);
	return 1; // No error
}

uint8_t spi_set_selector_clk_polarity(spi_reg_t *spi, uint8_t selector,
		uint32_t polarity) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (selector > 3 || polarity > 1) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + (uint32_t) selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_CPOL_MASK) & *p_reg) | (polarity << 0);
	return 1; // No error
}

uint8_t spi_set_selector_clk_phase(spi_reg_t *spi, uint8_t selector,
		uint32_t phase) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (selector > 3 || phase > 1) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_NCPHA_MASK) & *p_reg) | (phase << 1);
	return 1; // No error
}

uint8_t spi_set_selector_option(spi_reg_t *spi, uint8_t selector,
		uint32_t option) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (option > 2 || selector > 3) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the option for the calculated register to use
	if (option == SPI_OPTION_DONT_KEEP_CS_ACTIVE) {
		*p_reg |= SPI_CSRx_CSNAAT_MASK;
		*p_reg &= ~SPI_CSRx_CSAAT_MASK;

	} else if (option == SPI_OPTION_KEEP_CS_ACTIVE) {
		*p_reg &= ~SPI_CSRx_CSNAAT_MASK;
		*p_reg |= SPI_CSRx_CSAAT_MASK;

	} else if (option == SPI_OPTION_DISABLE_CS_OPTIONS) {
		*p_reg &= ~SPI_CSRx_CSNAAT_MASK;
		*p_reg &= ~SPI_CSRx_CSAAT_MASK;
	}
	return 1; // No error
}

uint8_t spi_set_selector_bit_length(spi_reg_t *spi, uint8_t selector,
		uint32_t bit_count) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if ((bit_count > 8) || (selector > 3)) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.

	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_BITS_MASK) & *p_reg) | (bit_count << 4);
	return 1; // No error
}

uint8_t spi_set_delay_between_cs(spi_reg_t *spi, uint16_t delay) {
	uint32_t divisor;
	// If the value is below 12 ns, it's OK. The MCU will adjust it itself to
	// the minimum value of 12 ns.
	if (delay > 3036) {
		delay = 3036;
	}
	// Calculate the divisor having though of round-downs with integers
	divisor = ((delay * 84U) / 1000U);
	// Bitwise operation to set the delay for the calculated register to use
	spi->SPI_MR = ((~SPI_MR_DLYBCS_MASK) & spi->SPI_MR) | (divisor << 24);
	return 1; // No error
}

uint8_t spi_set_selector_delay_clk_start(spi_reg_t *spi, uint8_t selector,
		uint16_t delay) {
	uint32_t *p_reg;
	uint32_t divisor;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (selector > 3) {
		return 0; // Error
	}
	if (delay > 3036) {
		delay = 3036;
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Calculate the divisor having though of round-downs with integers
	divisor = ((delay * 84U) / 1000U);
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_DLYBS_MASK) & *p_reg) | (divisor << 16);
	return 1; // No error
}

uint8_t spi_set_selector_delay_transfers(spi_reg_t *spi, uint8_t selector,
		uint32_t delay) {
	uint32_t *p_reg;
	uint32_t divisor;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (selector > 3) {
		return 0; // Error
	}
	if (delay > 97143) {
		delay = 97143;
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Calculate the divisor having though of round-downs with integers
	divisor = ((delay * 84U) / 32U) / 1000U;
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_DLYBCT_MASK) & *p_reg) | (divisor << 24);
	return 1; // No error
}

uint8_t spi_select_slave(spi_reg_t *spi, uint8_t slave) {
	spi->SPI_MR = ((~SPI_MR_PCS_MASK) & spi->SPI_MR);
	spi->SPI_MR = ((~SPI_MR_PCS_MASK) & spi->SPI_MR)
			| ((0b1111u >> (4 - slave)) << 16);
	return 1;
}

uint8_t spi_write(spi_reg_t *spi, uint16_t data) {
	// transfer begins when processor writes to spi->SPI_TDR
	// before writing SPI_TDR, PCS field in SPI_MR must be set in order to select slave

	//if SPI_RDR has not been read OVRES in SPI_SR will be set after this transfer
	//user has to read SPI_SR to clear OVRES

	// Retrieving the register and modifying it (Storing error output in shift)
	spi->SPI_TDR = (spi->SPI_TDR & (~SPI_TDR_TD_MASK)) | (uint32_t) data;
	return 1;
}

uint16_t spi_read(spi_reg_t *spi) {
	// SPI_RDR holds received data, this register is full when RDRF bit in SPI_SR is set
	//When data is read, this bit is cleared
	return (spi->SPI_RDR & SPI_RDR_RD_MASK);
}

uint8_t spi_rx_ready(spi_reg_t *spi) {
	return (spi->SPI_SR & SPI_SR_RDRF_MASK);
}

uint8_t spi_tx_ready(spi_reg_t *spi) {
	// transfer of data to shift register is indicated by TDRE bit in SPI_SR
	return (uint8_t)((spi->SPI_SR & SPI_SR_TDRF_MASK) >> 1);
}

uint8_t spi_transmission_done(spi_reg_t *spi) {
	// transmission completion is indicated by TXEMPTY bit in SPI_SR
	return (spi->SPI_SR & SPI_SR_TXEMPTY_MASK) > 0;
}

uint8_t spi_disable(spi_reg_t *spi) {
	// Set the disable pin in control register
	spi->SPI_CR |= SPI_CR_SPIDIS_MASK;
	return 1;
}

uint8_t spi_enable_loopback(spi_reg_t *spi) {
	// Set the loopback bit in mode register
	spi->SPI_MR |= SPI_MR_LLB_MASK;
	return 1;
}

uint8_t spi_disable_loopback(spi_reg_t *spi) {
	// Clear the loopback bit in mode register
	spi->SPI_MR &= ~SPI_MR_LLB_MASK;
	return 1;
}

uint8_t spi_reset(spi_reg_t *spi) {
	// Set the software reset bit in control register
	spi->SPI_CR |= SPI_CR_SWRST_MASK;
	return 1;
}

uint8_t spi_close_selector(spi_reg_t *spi) {
	// Set the last transfer bit in control register
	spi->SPI_CR |= SPI_CR_LASTXFER_MASK;
	return 1;
}

