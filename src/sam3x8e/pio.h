/**
 * @file
 * @brief Digital IO controller
 * @details The functions in this file controls the digital input and output of the processor
 *
 * @author Theodor Lindquist
 * @author Soded Alatia
 * @author Felix Ruponen
 *
 * @date 18 September 2014
 *
 * @pre First initialize the board, if you want to read inputs,
 * @pre you need to call pmc_enable_peripheral_clock() for the
 * @pre correct peripheral. See pmc.h for details
 */

#ifndef PIO_H_
#define PIO_H_

#include <stdint.h>

/** \brief Port A peripheral. Contains all register information about this port. */
#define PIO_PORTA 	((pio_reg_t *) 0x400E0E00)
/** \brief Port B peripheral. Contains all register information about this port. */
#define PIO_PORTB 	((pio_reg_t *) 0x400E1000)
/** \brief Port C peripheral. Contains all register information about this port. */
#define PIO_PORTC 	((pio_reg_t *) 0x400E1200)
/** \brief Port D peripheral. Contains all register information about this port. */
#define PIO_PORTD 	((pio_reg_t *) 0x400E1400)
/** \brief Port E peripheral. Contains all register information about this port. */
#define PIO_PORTE 	((pio_reg_t *) 0x400E1600)
/** \brief Port F peripheral. Contains all register information about this port. */
#define PIO_PORTF 	((pio_reg_t *) 0x400E1800)


///\cond
/** \brief Pio hardware registers */
typedef struct pio_reg_t {
  uint32_t PIO_PER;       /**< \brief (Pio Offset: 0x0000) PIO Enable Register */
  uint32_t PIO_PDR;       /**< \brief (Pio Offset: 0x0004) PIO Disable Register */
  uint32_t PIO_PSR;       /**< \brief (Pio Offset: 0x0008) PIO Status Register */
  uint32_t Reserved1[1];
  uint32_t PIO_OER;       /**< \brief (Pio Offset: 0x0010) Output Enable Register */
  uint32_t PIO_ODR;       /**< \brief (Pio Offset: 0x0014) Output Disable Register */
  uint32_t PIO_OSR;       /**< \brief (Pio Offset: 0x0018) Output Status Register */
  uint32_t Reserved2[1];
  uint32_t PIO_IFER;      /**< \brief (Pio Offset: 0x0020) Glitch Input Filter Enable Register */
  uint32_t PIO_IFDR;      /**< \brief (Pio Offset: 0x0024) Glitch Input Filter Disable Register */
  uint32_t PIO_IFSR;      /**< \brief (Pio Offset: 0x0028) Glitch Input Filter Status Register */
  uint32_t Reserved3[1];
  uint32_t PIO_SODR;      /**< \brief (Pio Offset: 0x0030) Set Output Data Register */
  uint32_t PIO_CODR;      /**< \brief (Pio Offset: 0x0034) Clear Output Data Register */
  uint32_t PIO_ODSR;      /**< \brief (Pio Offset: 0x0038) Output Data Status Register */
  uint32_t PIO_PDSR;      /**< \brief (Pio Offset: 0x003C) Pin Data Status Register */
  uint32_t PIO_IER;       /**< \brief (Pio Offset: 0x0040) Interrupt Enable Register */
  uint32_t PIO_IDR;       /**< \brief (Pio Offset: 0x0044) Interrupt Disable Register */
  uint32_t PIO_IMR;       /**< \brief (Pio Offset: 0x0048) Interrupt Mask Register */
  uint32_t PIO_ISR;       /**< \brief (Pio Offset: 0x004C) Interrupt Status Register */
  uint32_t PIO_MDER;      /**< \brief (Pio Offset: 0x0050) Multi-driver Enable Register */
  uint32_t PIO_MDDR;      /**< \brief (Pio Offset: 0x0054) Multi-driver Disable Register */
  uint32_t PIO_MDSR;      /**< \brief (Pio Offset: 0x0058) Multi-driver Status Register */
  uint32_t Reserved4[1];
  uint32_t PIO_PUDR;      /**< \brief (Pio Offset: 0x0060) Pull-up Disable Register */
  uint32_t PIO_PUER;      /**< \brief (Pio Offset: 0x0064) Pull-up Enable Register */
  uint32_t PIO_PUSR;      /**< \brief (Pio Offset: 0x0068) Pad Pull-up Status Register */
  uint32_t Reserved5[1];
  uint32_t PIO_ABSR;      /**< \brief (Pio Offset: 0x0070) Peripheral AB Select Register */
  uint32_t Reserved6[3];
  uint32_t PIO_SCIFSR;    /**< \brief (Pio Offset: 0x0080) System Clock Glitch Input Filter Select Register */
  uint32_t PIO_DIFSR;     /**< \brief (Pio Offset: 0x0084) Debouncing Input Filter Select Register */
  uint32_t PIO_IFDGSR;    /**< \brief (Pio Offset: 0x0088) Glitch or Debouncing Input Filter Clock Selection Status Register */
  uint32_t PIO_SCDR;      /**< \brief (Pio Offset: 0x008C) Slow Clock Divider Debouncing Register */
  uint32_t Reserved7[4];
  uint32_t PIO_OWER;      /**< \brief (Pio Offset: 0x00A0) Output Write Enable */
  uint32_t PIO_OWDR;      /**< \brief (Pio Offset: 0x00A4) Output Write Disable */
  uint32_t PIO_OWSR;      /**< \brief (Pio Offset: 0x00A8) Output Write Status Register */
  uint32_t Reserved8[1];
  uint32_t PIO_AIMER;     /**< \brief (Pio Offset: 0x00B0) Additional Interrupt Modes Enable Register */
  uint32_t PIO_AIMDR;     /**< \brief (Pio Offset: 0x00B4) Additional Interrupt Modes Disables Register */
  uint32_t PIO_AIMMR;     /**< \brief (Pio Offset: 0x00B8) Additional Interrupt Modes Mask Register */
  uint32_t Reserved9[1];
  uint32_t PIO_ESR;       /**< \brief (Pio Offset: 0x00C0) Edge Select Register */
  uint32_t PIO_LSR;       /**< \brief (Pio Offset: 0x00C4) Level Select Register */
  uint32_t PIO_ELSR;      /**< \brief (Pio Offset: 0x00C8) Edge/Level Status Register */
  uint32_t Reserved10[1];
  uint32_t PIO_FELLSR;    /**< \brief (Pio Offset: 0x00D0) Falling Edge/Low Level Select Register */
  uint32_t PIO_REHLSR;    /**< \brief (Pio Offset: 0x00D4) Rising Edge/ High Level Select Register */
  uint32_t PIO_FRLHSR;    /**< \brief (Pio Offset: 0x00D8) Fall/Rise - Low/High Status Register */
  uint32_t Reserved11[1];
  uint32_t PIO_LOCKSR;    /**< \brief (Pio Offset: 0x00E0) Lock Status */
  uint32_t PIO_WPMR;      /**< \brief (Pio Offset: 0x00E4) Write Protect Mode Register */
  uint32_t PIO_WPSR;      /**< \brief (Pio Offset: 0x00E8) Write Protect Status Register */
} pio_reg_t;

///\endcond


/**
 * Configure a pin to be either an input or an output
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_number the pin number (on the port) to configure
 * @param input set to 1 to configure pin as an input, 0 to configure as an output (default)
 * @param pullup set to 1 to configure pin with internal pullup (default), 0 to configure without
 */
void pio_conf_pin(pio_reg_t *port, uint8_t pin_number, uint8_t input, uint8_t pullup);

/**
 * Configure multiple pins to be either inputs or outputs
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_numbers the pin numbers (on the port) to configure (1 means, will be configured, 0 = will not be configured)
 * @param input set to 1 to configure pin as an input, 0 to configure as an output (default)
 * @param pullup set to 1 to configure pin with internal pullup (default), 0 to configure without
 */
void pio_conf_pins(pio_reg_t *port, uint32_t pin_numbers, uint8_t input, uint8_t pullup);

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
void pio_set_pin(pio_reg_t *port, uint8_t pin_number, uint8_t level);

/**
 * Set multiple pins to either a high or a low level
 * @param port the port you want to configure. Expects: PIO_PORTA - F. Defined in pio.h
 * @param pin_numbers the pin numbers (on the port) to configure (1= configure the pin, 0= do not configure the pin)
 * @param level 1 is high, 0 is low
 */
void pio_set_pins(pio_reg_t *port, uint32_t pin_numbers, uint8_t level);

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



#endif /* PIO_H_ */
