/**
 * @file global_entities.c
 * @anchor <global_entities>
 * @brief A storage place for globally used entities
 * @details {This class holds some globally important definitions and functions.
 * This file helps us avoid recreating function with the same functionality.
 * Mostly intended for bitwise operation and other small operations and
 * generally functions that are common for the different APIs but not linked to
 * the tasks of any API.
 * These function can be used both internally and as well as externally by the
 * end programmer. Its functions fall into the definition of stand-alone and
 * independent of any API. These are mainly a collection of tested bitwise
 * operations on registers or memory.}
 * @author {Saeed Ghasemi}
 * @version {v0.3}
 * @since {Since v0.3, first_bit_position_of_mask() has been added. And mask is
 * the preferred way of editing a register section and the use of start_bit is
 * deprecated.}
 * @date {25 sep 2014}
 * @pre {Since they are stand-alone, there are no preconditions for thier use.}
 * @bug {Not yet fully tested.}
 */

#include "global_entities.h"

/**
 * This function can be used to check for the state of a single bit in a
 * register.
 *
 * @param reg A 32bit long register value to be examined
 * @param bit The bit-number to be examined
 * @return The state of the bit in HIGH or LOW
 */
uint8_t is_bit_high(uint32_t *reg, uint8_t bit){
	return ((*reg >> bit) & 0x01U) == HIGH;
}

/**
 * This function will modify a section of a given register as indicated by
 * mask with the value specified in 'value'.
 *
 * @param reg This specifies a pointer to the register
 * @param mask The mask for the section in question (it may not be inverted)
 * @param value The value the section must store
 * @return error Can either be SUCCES or FAIL
 */
uint8_t set_section_in_register(uint32_t *reg, uint32_t mask, uint32_t value){
	// Retrieving the register and modifying it
	*reg = (~mask & *reg) | (value << first_bit_position_of_mask(mask));
	return SUCCESS;
}

/**
 * This function modifies a section of a register, reg, defined by 'mask' with
 * the value in 'value'.
 * It will only work for read/write registers.
 *
 * Define the parameters like  this example:
 * Ex: 0b00011000 -> start_bit = 3, length = 2
 *
 * @param reg The pointer to the register (not its value)
 * @param start_bit Position of the first bit of the section in the register
 * @param length The length of the section
 * @param value The value to be inserted in the register-section
 * @return
 * @deprecated (see How and When To Deprecate APIs)
 * @deprecated  As of JDK 1.1, replaced by
 *             {@link #set_section_in_register(uint32_t,uint32_t,uint32_t)}
 */
uint8_t set_section_in_register2(uint32_t *reg, uint8_t start_bit,
		uint32_t length, uint32_t value){
	uint32_t mask;
	// Creating the mask for the section in the register
	mask = ~(( (2^length)-1) << start_bit);
	// Retrieving the register and modifying it
	*reg = (mask & *reg) | (value << start_bit);
	return SUCCESS;
}


/**
 * This function return the bit-number of the first bit being high in a 32-bit
 * long value. The main purpose of this function is to find the start-bit of a
 * given mask. The start-bit can then be used to left-bit-shift a value into
 * position relative to a section in a register.
 *
 * @param mask The mask to be examined
 * @return Bit-number of the first position
 */
uint32_t first_bit_position_of_mask(uint32_t mask){
	uint8_t j = 0;
	// 0x80000000 has one bit to the far left only
	while(mask != 0x80000000){
		mask = (mask << 1);
		j++;
	}
	return (31U - j);
}


/*
 * This function will only return the value of a specified section in a given
 * register.
 * @param reg This specifies a pointer to the register
 * @param mask The area for which the value must be returned (high bit are read)
 * @return The value of the section in the register
 */
uint8_t get_value_of_register(uint32_t *reg, uint32_t mask){

	return 1; // temp
}

