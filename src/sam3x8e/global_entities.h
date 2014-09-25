/*
 * global_entities.c
 *
 * This file contains definitions that the developers in this group will at
 * some point use. This file helps us to avoid collision of redefinition of
 * some commonly used defines.
 *
 *
 * Created by: Saeed Ghasemi, 2014-09-18
 */


#ifndef _GLOBAL_ENT_H_
#define _GLOBAL_ENT_H_

#include <stdint.h>

/**
 * These are identifiers and may be used in several APIs and therefore
 * placed here.
 * @ Author: Saeed Ghasemi
 */
// PHERIPHERAL IDENTIFIERS //
#define ID_SUPC  		(0) ///<Peripheral Supply Controller
#define ID_RSTC  		(1) ///<Peripheral Reset Controller
#define ID_RTC   		(2) ///<Peripheral Real Time Clock
#define ID_RTT   		(3) ///<Peripheral Real Time Timer
#define ID_WDG   		(4) ///<Peripheral Watchdog Timer
#define ID_PMC   		(5) ///<Peripheral Power Management Controller
#define ID_EEFC0 		(6) ///<Peripheral Enhanced Flash Controller 0
#define ID_EEFC1 		(7) ///<Peripheral Enhanced Flash Controller 1
#define ID_UART 		(8) ///<Peripheral Universal Asynchronous Receiver Transceiver
#define ID_SMC_SDRAMC 	(9) ///<Peripheral Static, Synchronous Dynamic RAM Controller
#define ID_SDRAMC 		(10) ///<Peripheral Synchronous Dynamic RAM Controller
#define ID_PIOA 		(11) ///<Peripheral Parallel I/O Controller A
#define ID_PIOB 		(12) ///<Peripheral Parallel I/O Controller B
#define ID_PIOC 		(13) ///<Peripheral Parallel I/O Controller C
#define ID_PIOD 		(14) ///<Peripheral Parallel I/O Controller D
#define ID_PIOE 		(15) ///<Peripheral Parallel I/O Controller E
#define ID_PIOF 		(16) ///<Peripheral Parallel I/O Controller F
#define ID_USART0 		(17) ///<Peripheral USART 0
#define ID_USART1 		(18) ///<Peripheral USART 1
#define ID_USART2 		(19) ///<Peripheral USART 2
#define ID_USART3 		(20) ///<Peripheral USART 3
#define ID_HSMCI 		(21) ///<Peripheral HIGH SPEED MULTIMEDIA CARD INTERFACE
#define ID_TWI0 		(22) ///<Peripheral TWO WIRE INTERFACE 0
#define ID_TWI1 		(23) ///<Peripheral TWO WIRE INTERFACE 1
#define ID_SPI0 		(24) ///<Peripheral SERIAL PERIPHERAL INTERFACE 0
#define ID_SPI1 		(25) ///<Peripheral SERIAL PERIPHERAL INTERFACE 1
#define ID_SSC 			(26) ///<Peripheral SYNCHROUNIOUS SERIAL CONTROLLER
#define ID_TC0 			(27) ///<Peripheral TIMER COUNTER 0
#define ID_TC1 			(28) ///<Peripheral TIMER COUNTER 1
#define ID_TC2 			(29) ///<Peripheral TIMER COUNTER 2
#define ID_TC3 			(30) ///<Peripheral TIMER COUNTER 3
#define ID_TC4 			(31) ///<Peripheral TIMER COUNTER 4
#define ID_TC5 			(32) ///<Peripheral TIMER COUNTER 5
#define ID_TC6 			(33) ///<Peripheral TIMER COUNTER 6
#define ID_TC7 			(34) ///<Peripheral TIMER COUNTER 7
#define ID_TC8 			(35) ///<Peripheral TIMER COUNTER 8
#define ID_PWM 			(36) ///<Peripheral PULSE WIDTH MODULATION CONTROLLER
#define ID_ADC 			(37) ///<Peripheral ADC CONTROLLER
#define ID_DACC 		(38) ///<Peripheral DAC CONTROLLER
#define ID_DMAC 		(39) ///<Peripheral DMA CONTROLLER
#define ID_UOTGHS	 	(40) ///<Peripheral USB OTG HIGH SPEED
#define ID_TRNG 		(41) ///<Peripheral TRUE RANDOM NUMBER GENERATOR
#define ID_EMAC 		(42) ///<Peripheral ETHERNET MAC
#define ID_CAN0 		(43) ///<Peripheral CAN CONTROLLER 0
#define ID_CAN1 		(44) ///<Peripheral CAN CONTROLLER 1

//////////////////////////

#define SUCCESS		1
#define FAIL		0

#define TRUE		1
#define FALSE		0

#define HIGH		1
#define LOW			0

//////////////////////////

// Prototypes
/**
 * This function will test to see if a specified bit in a register is set high.
 *
 * @param reg This specifies a pointer to the register
 * @param bit Specifies the bit-number in the register
 * @return The return will be TRUE or FLASE
 */
uint8_t is_bit_high(uint32_t *reg, uint8_t bit);

/**
 * This function will modify a section of a given register as indicated by
 * start_bit and length with the value specified with 'value'.
 *
 * Define the parameters like this:
 * Ex: Having -> 0b00011000 -> start_bit = 3, length = 2
 *
 * @param reg This specifies a pointer to the register
 * @param start_bit The position of the first bit of the section
 * @param length The length of the section
 * @param value The value the section must store
 * @return error Can either be SUCCES or FAIL
 */
uint8_t set_section_in_register(uint32_t *reg, uint8_t start_bit,
		uint8_t length, uint32_t value);

/**
 * This function will modify a section of a given register as indicated by
 * start_bit and length with the value specified with 'value'.
 *
 * @param reg This specifies a pointer to the register
 * @param mask It must have the same length as the register, with ones across the section
 * @param value The value the section must store
 * @return error Can either be SUCCES or FAIL
 */
uint8_t set_section_in_register2(uint32_t *reg, uint8_t mask, uint32_t value);

/**
 * This function will return the value of a specified section in a given
 * register.
 *
 * @param reg The pointer to the register (not its value)
 * @param mask The area for which the value must be returned (high bit are read)
 * @return The value of the section in the register
 */
uint8_t get_value_of_register2(uint32_t *reg, uint32_t mask);

#endif
