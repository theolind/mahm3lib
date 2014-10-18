/**
 * @brief TWI, Two Wire Interface
 *
 * @author Jonathan Bjarnason
 * @date 10 October 2014
 */

#ifndef TWI_H_
#define TWI_H_

#include <inttypes.h>

// Base addresses to TWI registers
#define TWI0 ((twi_reg_t *) 0x4008C000U)
#define TWI1 ((twi_reg_t *) 0x40090000U)

// Bit addresses in Control Register
#define TWI_CR_MSEN(value) (value << 2)
#define TWI_CR_MSDIS(value) (value << 3)
#define TWI_CR_SVEN(value) (value << 4)
#define TWI_CR_SVDIS(value) (value << 5)
#define TWI_CR_SWRST(value) (value << 7)

// Bit addresses in Slave Mode Register
#define TWI_SMR_SADR(value) (value << 22)

#define SET_BIT 0x1u
#define CLEAR_BIT 0x0u

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
	uint32_t address[3];
	// The number of bytes in the internal address segment (1-3 bytes)
	uint32_t address_length;
	// Where to store data if used in a read function.
	// What data to write if used in a write function.
	uint32_t *buffer;
	// How many bytes do we want to store/write.
	uint32_t length;
	// TWI chip address to communicate with
	uint32_t chip;
} twi_packet_t;

/**
 * @brief Initialize the chosen TWI instance as master.
 * @param twi Pointer to a TWI instance.
 * @param settings Settings for initializing the TWI module.
 */
void twi_master_init(twi_reg_t *twi, twi_settings_t *settings);

/**
 * @brief Read multiple bytes from a slave device.
 * @param twi Pointer to a TWI instance.
 * @param packet Which address to read from and where to store the data.
 */
void twi_master_read(twi_reg_t *twi, twi_packet_t *packet);

/**
 * @brief Write multiple bytes to a slave device.
 * @param twi Pointer to a TWI instance.
 * @param packet Which address to write to and what data to write.
 */
void twi_master_write(twi_reg_t *twi, twi_packet_t *packet);

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
 */
void twi_slave_read(twi_reg_t *twi, uint8_t *data);

/**
 * @brief Write data to the TWI bus.
 * @param twi Pointer to a TWI instance.
 * @param data What data to write.
 */
void twi_slave_write(twi_reg_t *twi, uint8_t *data);

/**
 * @brief Writes a byte of data along the TWI bus.
 * @param twi Pointer to a TWI instance.
 * @param data What data to write.
 */
void twi_write_byte(twi_reg_t *twi, uint8_t data);

/**
 * @brief Reads a byte on the TWI bus.
 * @param twi Pointer to a TWI instance.
 * @return Received data.
 */
uint8_t twi_read_byte(twi_reg_t *twi);

/**
 * @brief Set the TWI bus speed in conjunction with the master clock frequency.
 * @param twi Pointer to a TWI instance.
 * @param baudrate The desired TWI bus speed. (Hz)
 * @param master_clk Speed of the main clock of the device. (Hz)
 */
void twi_set_clocks(twi_reg_t *twi, twi_settings_t *settings);

/**
 * @brief Reset TWI
 * @param twi Pointer to a TWI instance.
 */
void twi_reset(twi_reg_t *twi);

#endif
