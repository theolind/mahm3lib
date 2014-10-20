/**
 * @brief TWI, Two Wire Interface
 *
 * @author Jonathan Bjarnason
 * @author Mathias Beckius
 * @date 20 October 2014
 */

#ifndef TWI_H_
#define TWI_H_

#include <inttypes.h>

// Base addresses to TWI registers
#define TWI0 ((twi_reg_t *) 0x4008C000U)
#define TWI1 ((twi_reg_t *) 0x40090000U)

#define TWI_STANDARD_MODE_SPEED 100000U
#define TWI_FAST_MODE_SPEED 400000U

// Control Register
#define TWI_CR_START (0x1u << 0)
#define TWI_CR_STOP (0x1u << 1)
#define TWI_CR_MSEN (0x1u << 2)
#define TWI_CR_MSDIS (0x1u << 3)
#define TWI_CR_SVEN (0x1u << 4)
#define TWI_CR_SVDIS (0x1u << 5)
#define TWI_CR_SWRST (0x1u << 7)

// Status Register
#define TWI_SR_TXCOMP (0x1u << 0)
#define TWI_SR_RXRDY (0x1u << 1)
#define TWI_SR_TXRDY (0x1u << 2)
#define TWI_SR_SVREAD (0x1u << 3)
#define TWI_SR_SVACC (0x1u << 4)
#define TWI_SR_GACC (0x1u << 5)
#define TWI_SR_NACK (0x1u << 8)
#define TWI_SR_EOSACC (0x1u << 11)

// Slave Mode Register
#define TWI_SMR_SADR(value) (value << 16)

// Master Mode Register
#define TWI_MMR_IADRSZ(iadrsz)	(((iadrsz) & 3u) << 8)
#define TWI_MMR_MREAD_WRITE		(0u)
#define TWI_MMR_MREAD_READ		(1u)
#define TWI_MMR_MREAD(value)	(((value) & 1u) << 12)
#define TWI_MMR_DADR(dadr)		(((dadr) & 127u) << 16)

// Internal Address Register
#define TWI_IADR(iadr)			((iadr) & 0xFFFFFFu)

// Transmit Holding Register
#define TWI_THR_TXDATA(value) (value << 0)

// Receive Holding Register
#define TWI_RHR_RXDATA ((255) << 0)

// Clock Waveform Generator Register
/*
 * Tmck = 1 / mck
 * T = 1 / bus_speed
 * Tlow = (1 / bus_speed) / 2 = 1 / (2 * bus_speed)
 *
 * Frequency Ratio:
 * (Tlow / Tmck) = mck / (2 * bus_speed) = (mck / 2) / bus_speed
 */
#define TWI_CWGR_FREQ_RATIO(busclk, mck)	(((mck) >> 1) / (busclk))
#define TWI_CWGR_MIN_FREQ_RATIO				(4)
#define TWI_CWGR_CLDIV_MAX_VALUE			(0xFFu)
#define TWI_CWGR_CLDIV(value)				((value) & TWI_CWGR_CLDIV_MAX_VALUE)
#define TWI_CWGR_CHDIV(value) 				(TWI_CWGR_CLDIV(value) << 8)
#define TWI_CWGR_CKDIV_MAX_VALUE			(7u)
#define TWI_CWGR_CKDIV(value) 				\
	(((value) & TWI_CWGR_CKDIV_MAX_VALUE) << 16)

// Mapping of TWI registers
typedef struct twi_reg {
	// Control Register, offset: 0x00
	uint32_t TWI_CR;
	// Master Mode Register, offset: 0x04
	uint32_t TWI_MMR;
	// Slave Mode Register, offset: 0x08
	uint32_t TWI_SMR;
	// Internal Address Register, offset 0x0C
	uint32_t TWI_IADR;
	// Waveform Generator Register, offset 0x10
	uint32_t TWI_CWGR;
	// Reserved, offset: 0x14-0x1C
	uint32_t reserved[2];
	// Status Register, offset: 0x20
	uint32_t TWI_SR;
	// Interrupt Enable Register, offset: 0x24
	uint32_t TWI_IER;
	// Interrupt Disable Register, offset: 0x28
	uint32_t TWI_IDR;
	// Interrupt Mask Register, offset: 0x2C
	uint32_t TWI_IMR;
	// Receive Holding Register, offset: 0x30
	uint32_t TWI_RHR;
	// Transmit Holding Register, offset: 0x34
	uint32_t TWI_THR;
} twi_reg_t;

// Settings for the clocks
typedef struct twi_settings {
	// The baud rate of the TWI bus (Hz)
	uint32_t baudrate;
	// The master clock for TWI (Hz)
	uint32_t master_clk;
} twi_settings_t;

// Information used for data transmission
typedef struct twi_packet {
	// Internal address of the selected chip
	uint8_t address[3];
	// The number of bytes in the internal address segment (1-3 bytes)
	uint8_t address_length;
	// Where to store data if used in a read function.
	// What data to write if used in a write function.
	uint32_t *buffer;
	// How many bytes do we want to store/write.
	uint32_t data_length;
	// TWI chip address to communicate with
	uint32_t chip;
} twi_packet_t;

/**
 * Set address of the slave device.
 * @param twi Pointer to a TWI instance.
 * @param dadr Device address of slave device
 * @param iadrsz Internal Device Address Size (0-3 bytes)
 */
void twi_set_device_address(twi_reg_t *twi, uint32_t dadr, uint32_t iadrsz);

/**
 * Set the internal address of the slave device.
 * @param twi Pointer to a TWI instance.
 * @param iadr Internal address of the slave device.
 */
void twi_set_internal_address(twi_reg_t *twi, uint32_t iadr);

/**
 * @brief Set the TWI bus speed in conjunction with the master clock frequency.
 * @param twi Pointer to a TWI instance.
 * @param bus_speed The desired TWI bus speed (Hz)
 * @param mck Master Clock frequency (Hz)
 * @return 0 = Success, 1 = Failure (depends on invalid parameters)
 */
uint8_t twi_set_clock(twi_reg_t *twi, uint32_t bus_speed, uint32_t mck);

/**
 * @brief Initialize the chosen TWI instance as master.
 * @param twi Pointer to a TWI instance.
 * @param settings Settings for initializing the TWI module.
 * @return 1=pass, 0=unaccepted values in settings variable
 */
uint8_t twi_init_master(twi_reg_t *twi, twi_settings_t *settings);

/**
 * @brief Read multiple bytes from a slave device.
 * @param twi Pointer to a TWI instance.
 * @param packet Which address to read from and where to store the data.
 * @return 1=pass, 0=NACK detected or illegal values
 */
uint8_t twi_master_read(twi_reg_t *twi, twi_packet_t *packet);

/**
 * @brief Write multiple bytes to a slave device.
 * @param twi Pointer to a TWI instance.
 * @param packet Which address to write to and what data to write.
 * @return 1=pass, 0=NACK detected
 */
uint8_t twi_master_write(twi_reg_t *twi, twi_packet_t *packet);

/**
 * @brief Initialize the chosen TWI instance as slave.
 * @param twi Pointer to a TWI instance.
 * @param slave_adress Device address of the SAM slave device on the TWI bus.
 */
void twi_slave_init(twi_reg_t *twi, uint8_t slave_adress);

/**
 * @brief Read data from master.
 * @param twi Pointer to a TWI instance.
 * @param data Where to store data from read.
 * @return Number of bytes read
 */
void twi_slave_read(twi_reg_t *twi, uint8_t *data);

/**
 * @brief Write data to the TWI bus.
 * @param twi Pointer to a TWI instance.
 * @param data What data to write.
 */
void twi_slave_write(twi_reg_t *twi, uint8_t *data);

/**
 * @brief Converts an array of addresses into a 32 bit variable.
 * @param address Pointer to the array of addresses.
 * @param address_length The amount of bytes the address array contains.
 * @return A 32 bit variable containing address data.
 */
uint32_t twi_convert_address(uint8_t *address, uint8_t address_length);

/**
 * @brief Reset the TWI peripheral.
 * @param twi Pointer to a TWI instance.
 */
void twi_reset(twi_reg_t *twi);

#endif
