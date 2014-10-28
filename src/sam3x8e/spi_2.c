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

uint8_t spi_init(spi_reg_t *spi, const spi_settings_t *settings);

uint8_t spi_init_selector(spi_reg_t *spi, const spi_selector_settings_t *settings);

uint8_t spi_set_master(spi_reg_t *spi);

uint8_t spi_set_slave(spi_reg_t *spi);

uint8_t spi_enable(spi_reg_t *spi);

uint8_t spi_disable(spi_reg_t *spi);



uint8_t spi_selector_set_baud_rate(spi_reg_t *spi, uint8_t selector, uint8_t baud_rate);

uint8_t spi_selector_set_clk_polarity(spi_reg_t *spi, uint8_t selector, uint8_t polarity);

uint8_t spi_selector_set_clk_phase(spi_reg_t *spi, uint8_t selector, uint8_t phase);

uint16_t spi_master_tranceive(spi_reg_t *spi, uint16_t data);

uint8_t spi_select_slave(spi_reg_t *spi, uint8_t slave);

uint8_t spi_master_write(spi_reg_t *spi, uint16_t data);

uint8_t spi_slave_write(spi_reg_t *spi, uint16_t data);

uint16_t spi_master_read(spi_reg_t *spi, uint16_t dummy_data);

uint8_t spi_write_ready(spi_reg_t *spi);

uint8_t spi_transmission_done(spi_reg_t *spi);

uint8_t spi_read_ready(spi_reg_t *spi);

uint8_t spi_software_reset(spi_reg_t *spi);

uint8_t spi_interrupt_enable(spi_reg_t *spi, uint8_t interrupt);

uint8_t spi_interrupt_disable(spi_reg_t *spi, uint8_t interrupt);


uint8_t spi_loopback_enable(spi_reg_t *spi);

uint8_t spi_loopback_disable(spi_reg_t *spi);

uint8_t spi_selector_close(void);

