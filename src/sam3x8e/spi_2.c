/**
 * @file pwm.c
 * @brief Pulse Width Modulation (PWM)
 * @details An API for controlling the PWM peripheral inside a SAM3X8E MCU.
 * This peripheral is an embedded macrocell within the MCU and all of its 44
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * This API implements all 8 independent channels and their change of polarity,
 * alignment, PWM frequency and handles the pin multiplexing for all 16 outputs
 * of the peripheral. The API does not stop any clock once it has started them.
 * @author Saeed Ghasemi
 * @date 28 sep 2014
 * @pre The API handles all of its dependencies on other peripherals
 * internally and will start other clocks in order to properly operate.
 * @bug Manually tested all functions to comply with all demands.
 * The only problem is that the register set defined below is not working when
 * implemented. The register mapping currently working is non conventional.
 */

#include "spi_2.h"

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
	spi_selector_set_delay_between_cs(spi, settings->delay_between_cs);
	//TODO deselect all selectors

	return 1;
}

uint8_t spi_init_selector(spi_reg_t *spi,
		const spi_selector_settings_t *settings) {
	// TODO

	return 1;
}

uint8_t spi_selector_set_clk_polarity(spi_reg_t *spi, uint8_t selector,
		uint8_t polarity) {
	// TODO
	return 1;
}

uint8_t spi_selector_set_clk_phase(spi_reg_t *spi, uint8_t selector,
		uint8_t phase) {
	// TODO
	return 1;
}

uint8_t spi_selector_set_baud_rate(spi_reg_t *spi, uint8_t selector,
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

uint8_t spi_selector_do_not_keep_cs_active(spi_reg_t *spi, uint8_t selector,
		uint32_t option) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (option > 1 || selector > 3) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_CSNAAT_MASK) & *p_reg) | (option << 2);
	return 1; // No error
}

uint8_t spi_selector_keep_cs_active(spi_reg_t *spi, uint8_t selector,
		uint32_t option) {
	uint32_t *p_reg;
	// Boundary test. Higher than these values will result in error or
	// register corruption, because the selector is used to calculate a
	// pointer.
	if (option > 1 || selector > 3) {
		return 0; // Error
	}
	// Calculate the pointer for the selector based on the first
	// selector register being the offset.
	p_reg = (&spi->SPI_CSR0) + selector; // pointer increment of 0 to 3.
	// Bitwise operation to set the delay for the calculated register to use
	*p_reg = ((~SPI_CSRx_CSAAT_MASK) & *p_reg) | (option << 3);
	return 1; // No error
}

uint8_t spi_selector_set_bit_length(spi_reg_t *spi, uint8_t selector,
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

uint8_t spi_selector_set_delay_between_cs(spi_reg_t *spi, uint16_t delay) {
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

uint8_t spi_selector_set_delay_clk_start(spi_reg_t *spi, uint8_t selector,
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

uint8_t spi_selector_set_delay_transfers(spi_reg_t *spi, uint8_t selector,
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

uint8_t spi_loopback_enable(spi_reg_t *spi) {
	// Set the loopback bit in mode register
	spi->SPI_MR |= SPI_MR_LLB_MASK;
	return 1;
}

uint8_t spi_loopback_disable(spi_reg_t *spi) {
	// Clear the loopback bit in mode register
	spi->SPI_MR &= ~SPI_MR_LLB_MASK;
	return 1;
}

uint8_t spi_enable(spi_reg_t *spi) {
	// Set the enable pin in control register
	spi->SPI_CR = SPI_CR_SPIEN_MASK;
	return 1;
}

uint8_t spi_disable(spi_reg_t *spi) {
	// TODO
	return 1;
}

uint8_t spi_enable_status(spi_reg_t *spi) {
	// TODO
	return 1;
}

uint8_t spi_select_slave(spi_reg_t *spi, uint8_t slave) {
	// TODO Change this later into one line (update spi_mr once)
	spi->SPI_MR = ((~SPI_MR_PCS_MASK) & spi->SPI_MR); //clear bit 16 to 19 in SPI_MR
	spi->SPI_MR |= ((0b111u >> (3 - slave)) << 16); //set bit 16 to 18 in SPI_MR (could be predefined)
	return 1;
}

uint8_t spi_tx_ready(spi_reg_t *spi) {
	// transfer of data to shift register is indicated by TDRE bit in SPI_SR
	return (spi->SPI_SR & SPI_SR_TDRF_MASK) > 0;
}

uint8_t spi_rx_ready(spi_reg_t *spi) {
	return (spi->SPI_SR & SPI_SR_RDRF_MASK);
}

uint8_t spi_write(spi_reg_t *spi, uint16_t data) {
	// transfer begins when processor writes to spi->SPI_TDR
	// before writing SPI_TDR, PCS field in SPI_MR must be set in order to select slave

	//if SPI_RDR has not been read OVRES in SPI_SR is set
	//user has to read SPI_SR to clear OVRES

	// Retrieving the register and modifying it (Storing error output in shift)
	spi->SPI_TDR = (spi->SPI_TDR & (~SPI_TDR_TD_MASK)) | data;
	return 1;
}

uint8_t spi_transmission_done(spi_reg_t *spi) {
	// transmission completion is indicated by TXEMPTY bit in SPI_SR
	return (spi->SPI_SR & SPI_SR_TXEMPTY_MASK) > 0;
}

uint16_t spi_read(spi_reg_t *spi) {
	// SPI_RDR holds received data, this register is full when RDRF bit in SPI_SR is set
	//When data is read, this bit is cleared
	return (spi->SPI_RDR & SPI_RDR_RD_MASK);
}

uint8_t spi_software_reset(spi_reg_t *spi) {
	// Set the software reset bit in control register
	spi->SPI_CR |= SPI_CR_SWRST_MASK;
	return 1;
}

uint8_t spi_selector_close(spi_reg_t *spi) {
	// Set the last transfer bit in control register
	spi->SPI_CR |= SPI_CR_LASTXFER_MASK;
	return 1;
}

