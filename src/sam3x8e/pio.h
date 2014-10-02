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

/*
// port register offsets
#define PIO_PER 0x0000	//PIO enable register
#define PIO_PDR 0x0004	//PIO disable register
#define PIO_PSR 0x0008  //PIO status register

#define PIO_OER 0x0010	//output enable register
#define PIO_ODR 0x0014	//output disable register
#define PIO_OSR 0x0018 	//output status register

#define PIO_SODR 0x0030	//set output data register
#define PIO_CODR 0x0034	//clear output data register
#define PIO_ODSR 0x0038 //output data status register
#define PIO_PDSR 0x003C	//pin data status register

#define PIO_PUDR 0x0060	//pull-up disable register
#define PIO_PUER 0x0064	//pull-up enable register
#define PIO_PUSR 0x0068	//pull-up status register

#define PIO_ABSR 0x0070	//Peripheral AB Select Register

#define PIO_OWER 0x00A0	//Output Write Enable
#define PIO_OWDR 0x00A4	//Output Write Disable
#define PIO_OWSR 0x00A8	//Output Write Status Register
*/


////////////////////////////////////////////////////////
// External (to be used by the user) (temporarily)
//Physical pin mapping
//PIO_PIN_[package pin number]_[port and bit number]
#define PIN_PIO_1_PB26			(26)
#define PIN_PIO_42_PA19			(19)
#define PIN_PIO_59_PC2			(2)
#define PIN_PIO_60_PC3			(3)
#define PIN_PIO_63_PC5			(5)
#define PIN_PIO_64_PC6			(6)
#define PIN_PIO_65_PC7			(7)
#define PIN_PIO_66_PC8			(8)
#define PIN_PIO_67_PC9			(9)
#define PIN_PIO_72_PA20			(20)
#define PIN_PIO_95_PC13			(13)
#define PIN_PIO_97_PC15			(15)
#define PIN_PIO_99_PC17			(17)
#define PIN_PIO_100_PC18		(18)
#define PIN_PIO_101_PBC19		(19)
#define PIN_PIO_116_PC4			(4)
#define PIN_PIO_140_PB14		(14)
// These should be extended (These are MCU pin mappings and not arduino pin mappings)
////////////////////////////////////////////////////////

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
void pio_conf_pin(pio_reg_t *port, uint32_t pin_number, uint32_t input, uint32_t pullup);

/**
* Configure multiple pins to be either inputs or outputs
* @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
* @param pin_numbers the pin numbers (on the port) to configure (1 means, will be configured, 0 = will not be configured)
* @param input set to 1 to configure pin as an input, 0 to configure as an output (default)
* @param pullup set to 1 to configure pin with internal pullup (default), 0 to configure without
*/
void pio_conf_pins(pio_reg_t *port, uint32_t pin_numbers, uint32_t input, uint32_t pullup);

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
* @param levels set a bit to 1 to set a high level for the correspondingpin, 0 to set a low level
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
 * @author {Saeed Ghasemi}
 * @param port {This is the pio port of the pin to be multiplexed.}
 * @param periph {Point to your chosen peripheral. PERIPH_A or B}
 * @param pin_number {This is the pin number in the port register.
 * Start with prefix: PIN_[peripheral] to get to predefined pins.}
 * @return error (1  = SUCCESS, 0 = FAIL)
 * @bug {Not yet tested. All ports will be included after initial testing.}
 */
uint8_t pio_conf_pin_to_peripheral(pio_reg_t *port,
		uint32_t periph, uint32_t pin_number);

#endif
