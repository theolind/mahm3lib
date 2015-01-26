/**
 * @file
 * @brief PIO - Parallel input/output controller
 * @details The functions in this file controls the digital input and output of the processor
 *
 * @pre Initialize the system clock.
 * @pre If want to use all of the PIO peripheral features, then you must enable
 * the Peripheral Clock for the corresponding port (PIOA-PIOF). See data sheet
 * for more details.
 *
 * @author Theodor Lindquist
 * @author Soded Alatia
 * @author Felix Ruponen
 * @author Saeed Ghasemi
 *
 * @date 29 September 2014
 *
 */

#ifndef PIO_H_
#define PIO_H_

#include <inttypes.h>

// \brief Pointer to registers of the PIOA peripheral.
#define PIOA ((pio_reg_t *) 0x400E0E00)
// \brief Pointer to registers of the PIOB peripheral.
#define PIOB ((pio_reg_t *) 0x400E1000)
// \brief Pointer to registers of the PIOC peripheral.
#define PIOC ((pio_reg_t *) 0x400E1200)
// \brief Pointer to registers of the PIOD peripheral.
#define PIOD ((pio_reg_t *) 0x400E1400)
// \brief Pointer to registers of the PIOE peripheral.
#define PIOE ((pio_reg_t *) 0x400E1600)
// \brief Pointer to registers of the PIOF peripheral.
#define PIOF ((pio_reg_t *) 0x400E1800)

///@{
/**
 * These definitions are used in connection with multiplexing pins to their
 * secondary function which are the peripherals that they are connected to.
 */
#define PIO_PERIPH_A			0
#define PIO_PERIPH_B			1
///@}
///@{
/**
 * These are mapped pins of the MCU relative to their respective package
 * pin number.
 *
 * PIO_PIN_[package pin number]_[port and bit number]
 */
#define PIO_PIN_1_PB26			(26)
#define PIO_PIN_42_PA19			(19)
#define PIO_PIN_59_PC2			(2)
#define PIO_PIN_60_PC3			(3)
#define PIO_PIN_63_PC5			(5)
#define PIO_PIN_64_PC6			(6)
#define PIO_PIN_65_PC7			(7)
#define PIO_PIN_66_PC8			(8)
#define PIO_PIN_67_PC9			(9)
#define PIO_PIN_72_PA20			(20)
#define PIO_PIN_95_PC13			(13)
#define PIO_PIN_97_PC15			(15)
#define PIO_PIN_99_PC17			(17)
#define PIO_PIN_100_PC18		(18)
#define PIO_PIN_101_PBC19		(19)
#define PIO_PIN_116_PC4			(4)
#define PIO_PIN_140_PB14		(14)
#define PIO_PIN_8_PA15			(15)
///@}

#define PIO_SLOW_CLOCK_FREQ			(32768)

///@cond
/*
 * Mapping of PIO registers
 * Base address differs from different ports.
 */
typedef struct {
	// PIO Enable Register, offset: 0x0000
	uint32_t PIO_PER;
	// PIO Disable Register, offset: 0x0004
	uint32_t PIO_PDR;
	// PIO Status Register, offset: 0x0008
	uint32_t PIO_PSR;
	uint32_t reserved1;
	// PIO Output Enable Register, offset: 0x0010
	uint32_t PIO_OER;
	// PIO Output Disable Register, offset: 0x0014
	uint32_t PIO_ODR;
	// Output Status Register, offset: 0x0018
	uint32_t PIO_OSR;
	uint32_t reserved2;
	// Glitch Input Filter Enable Register, offset: 0x0020
	uint32_t PIO_IFER;
	// Glitch Input Filter Disable Register, offset: 0x0024
	uint32_t PIO_IFDR;
	// Glitch Input Filter Status Register, offset: 0x0028
	uint32_t PIO_IFSR;
	uint32_t reserved3;
	// Set Output Data Register, offset: 0x0030
	uint32_t PIO_SODR;
	// Clear Output Data Register, offset: 0x0034
	uint32_t PIO_CODR;
	// Output Data Status Register, offset: 0x0038
	uint32_t PIO_ODSR;
	// Pin Data Status Register, offset: 0x003C
	uint32_t PIO_PDSR;
	// Interrupt Enable Register, offset: 0x0040
	uint32_t PIO_IER;
	// Interrupt Disable Register, offset: 0x0044
	uint32_t PIO_IDR;
	// Interrupt Mask Register, offset: 0x0048
	uint32_t PIO_IMR;
	// Interrupt Status Register, offset: 0x004C
	uint32_t PIO_ISR;
	// Multi-driver Enable Register, offset: 0x0050
	uint32_t PIO_MDER;
	// Multi-driver Disable Register, offset: 0x0054
	uint32_t PIO_MDDR;
	// Multi-driver Status Register, offset: 0x0058
	uint32_t PIO_MDSR;
	uint32_t reserved4;
	// Pull-up Disable Register, offset: 0x0060
	uint32_t PIO_PUDR;
	// Pull-up Enable Register, offset: 0x0064
	uint32_t PIO_PUER;
	// Pad Pull-up Status Register, offset: 0x0068
	uint32_t PIO_PUSR;
	uint32_t reserved5;
	// Peripheral AB Select Register, offset: 0x0070
	uint32_t PIO_ABSR;
	uint32_t reserved6[3];
	// System Clock Glitch Input Filter Select Register, offset: 0x0080
	uint32_t PIO_SCIFSR;
	// Debouncing Input Filter Select Register, offset: 0x0084
	uint32_t PIO_DIFSR;
	/*
	 * Glitch or Debouncing Input Filter Clock Selection Status Register,
	 * offset: 0x0088
	 */
	uint32_t PIO_IFDGSR;
	// Slow Clock Divider Debouncing Register, offset: 0x008C
	uint32_t PIO_SCDR;
	uint32_t reserved7[4];
	// Output Write Enable, offset: 0x00A0
	uint32_t PIO_OWER;
	// Output Write Disable, offset: 0x00A4
	uint32_t PIO_OWDR;
	// Output Write Status Register, offset: 0x00A8
	uint32_t PIO_OWSR;
	uint32_t reserved8;
	// Additional Interrupt Modes Enable Register, offset: 0x00B0
	uint32_t PIO_AIMER;
	// Additional Interrupt Modes Disables Register, offset: 0x00B4
	uint32_t PIO_AIMDR;
	// Additional Interrupt Modes Mask Register, offset: 0x00B8
	uint32_t PIO_AIMMR;
	uint32_t reserved9;
	// Edge Select Register, offset: 0x00C0
	uint32_t PIO_ESR;
	// Level Select Register, offset: 0x00C4
	uint32_t PIO_LSR;
	// Edge/Level Status Register, offset: 0x00C8
	uint32_t PIO_ELSR;
	uint32_t reserved10;
	// Falling Edge/Low Level Select Register, offset: 0x00D0
	uint32_t PIO_FELLSR;
	// Rising Edge/ High Level Select Register, offset: 0x00D4
	uint32_t PIO_REHLSR;
	// Fall/Rise - Low/High Status Register, offset: 0x00D8
	uint32_t PIO_FRLHSR;
	uint32_t reserved11;
	// Lock Status, offset: 0x00E0
	uint32_t PIO_LOCKSR;
	// Write Protect Mode Register, offset: 0x00E4
	uint32_t PIO_WPMR;
	// Write Protect Status Register, offset: 0x00E8
	uint32_t PIO_WPSR;
} pio_reg_t;
///@endcond

/**
 * Enable the PIO to control the pin (disable peripheral control of the pin).
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin the pin to enable
 */
void pio_enable_pin(pio_reg_t *port, uint32_t pin);

/**
 * Disable the PIO from controlling the pin (enable peripheral control of the pin).
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin the pin to disable
 */
void pio_disable_pin(pio_reg_t *port, uint32_t pin);

/**
 * Configure a pin to be either an input or an output
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_number the pin number (on the port) to configure
 * @param input set to 1 to configure pin as an input, 0 to configure as an output (default)
 * @param pullup set to 1 to configure pin with internal pullup (default), 0 to configure without
 */
void pio_conf_pin(pio_reg_t *port, uint32_t pin_number, uint32_t input,
		uint32_t pullup);

/**
 * Configure multiple pins to be either inputs or outputs
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_numbers the pin numbers (on the port) to configure (1 means, will be configured, 0 = will not be configured)
 * @param input set to 1 to configure pin as an input, 0 to configure as an output (default)
 * @param pullup set to 1 to configure pin with internal pullup (default), 0 to configure without
 */
void pio_conf_pins(pio_reg_t *port, uint32_t pin_numbers, uint32_t input,
		uint32_t pullup);

/**
 * Configure a whole to be either inputs or outputs, this will reset the whole port
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param inputs set a bit to 1 to configure the corresponding pin as an input, 0 to configure as output
 * @param pullups set a bit to 1 to configure the corresponding pin with an internal pullup, 0 to configure without internal pullup
 */
void pio_conf_port(pio_reg_t *port, uint32_t inputs, uint32_t pullups);

/**
 * Set a pin to either a high or a low level
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_number the pin number (on the port) to configure
 * @param level 1 is high, 0 is low
 */
void pio_set_pin(pio_reg_t *port, uint32_t pin_number, uint32_t level);

/**
 * Set multiple pins to either a high or a low level
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_numbers the pin numbers (on the port) to configure (1= configure the pin, 0= do not configure the pin)
 * @param level 1 is high, 0 is low
 */
void pio_set_pins(pio_reg_t *port, uint32_t pin_numbers, uint32_t level);

/**
 * Set an entire port to either high or low levels
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param levels set a bit to 1 to set a high level for the corresponding pin, 0 to set a low level
 */
void pio_set_port(pio_reg_t *port, uint32_t levels);

/**
 * Check if a pin is either high or low
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_number the pin number (on the port) to check
 * @return 1 if high, 0 if low
 */
uint32_t pio_read_pin(pio_reg_t *port, uint32_t pin_number);

/**
 * Check the levels of an entire port
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @return A bit with value 1 means the corresponding pin is high, bit with 0 means the pin is low
 */
uint32_t pio_read_port(pio_reg_t *port);

/**
 * This function will set the multiplexer inside the PIO peripheral to point
 * one of its pins to an embedded peripheral inside the MCU. The pin will after
 * this configuration no longer be controllable by the PIO.
 *
 * There is only one parameter to this function and that is the pin in question.
 * You can't use any pin for every purpose. Every pin has a digital function (PIO)
 * and a peripheral function. The pin mapping of this API includes all pins and
 * their secondary function. These pins are predefined. Start by writing
 * PIN_[peripheral][additional property and numbering]_[package pin number]
 * example:
 * PIN_PWMH0_60    or    PIN_PWML0_59
 * (These refer to the board independent pin mapping and will be available when
 * the API is included.)
 *
 * @author Saeed Ghasemi
 * @param port This is the pio port of the pin to be multiplexed.
 * @param periph Point to your chosen peripheral. PIO_PERIPH_A or B.
 * @param pin_number This is the pin number in the port register.
 * Start with prefix: PIN_[peripheral] to get to predefined pins.
 * @return error (1  = SUCCESS, 0 = FAIL)
 */
uint8_t pio_conf_pin_to_peripheral(pio_reg_t *port, uint32_t periph,
		uint8_t pin_number);


/**
 * Checks if debounce filter is enabled for a specific pin
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_number the pin number (on the port) to check if debounce is enabled on
 * @return 1 if debounce filter is selected
 */
uint8_t pio_debounce_filter_selected(pio_reg_t *port, uint32_t pin_number);

/**
 *
 * Selects debounce filter  to use for a pin
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_number the pin number (on the port) to enable filter on
 * @pre The peripheral clock must be enabled for this to work
 */
void pio_select_debounce_filter(pio_reg_t *port, uint32_t pin_number);

/**
 * Decides the clock settings used by all debounce filters.
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param slow_clock This value decides the period that the filter uses for sampling
 * (low value = longer sampling time, high value = shorter sampling time).
 * Expects a value between 1 and 16384 (2^0 =< slow_clock =< 2^14).
 */
void pio_set_debounce_frequency(pio_reg_t *port, uint32_t slow_clock);

/**
 * Enables glitch filter for a specified port/pin
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_number the pin number (on the port) to enable filter on
 * @pre The peripheral clock must be enabled for this to work
 */
void pio_enable_input_filter(pio_reg_t *port, uint32_t pin_number);

/**
 * Disable glitch filter for a specified port and pin
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_number the pin number (on the port) to enable filter on
 * @pre The peripheral clock must be enabled for this to work
 */
void pio_disable_input_filter(pio_reg_t *port, uint32_t pin_number);

/**
 * Checks if glitch filter is enabled on the selected pin/port
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_number the pin number (on the port) to enable filter on
 * @return 1 if input filter is enabled
 */
uint32_t pio_input_filter_enabled(pio_reg_t *port, uint32_t pin_number);



#endif
