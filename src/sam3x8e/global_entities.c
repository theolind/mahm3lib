/**
 * global_entities.c
 *
 * This file contains functions that the developers in this group will at
 * some point use. This file helps us to avoid recreating function with the
 * same functionality. Mostly intended for bitwise operations and other small
 * operations.
 *
 * Created by: Saeed Ghasemi, 2014-09-22
 */

/**
 * @file global_entities
 * @brief A storage place for globally used entities
 * @details This class holds some globally important definitions and functions
 * @details of bitwise operation and generally functions that are common to the
 * @details different APIs but not linked to the tasks of any API.
 * @author Saeed Ghasemi
 * @version 0.2
 * @date 25 sep 2014
 * @pre These function can be used both internally as well as externally by the
 * @pre end programmer. Its functions fall into the definition of stand-alone
 * @pre and independent of any API. These are mainly a collection of tested
 * @pre bitwise operations on registers or memory.
 * @bug Tests are being put in place....
 */


#include "global_entities.h"


/*
 * This function can be used to check for the state of a single bit in a
 * register.
 *
 * @param reg a 32bit long register value to be examined
 * @param bit the bit-number to be examined
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

/*
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
 */
uint8_t set_section_in_register2(uint32_t *reg, uint8_t start_bit,
		uint8_t length, uint32_t value){
	uint32_t mask;
	// Creating the mask for the section in the register
	mask = ~(((2^length)-1)<<start_bit);
	// Retrieving the register and modifying it
	*reg = (mask & *reg) | (value << start_bit);
	return SUCCESS;
}


/**
 * This function return the bit-number of the first bit being high in a 32-bit
 * long value. The main porpose of this function is to find the start-bit of a
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
	return (31 - j);
}


/*
 * This function will only return the value of a specified section in a given
 * register.
 * @param reg This specifies a pointer to the register
 * @param mask The area for which the value must be returned (high bit are read)
 * @return The value of the section in the register
 */
uint8_t get_value_of_register(uint32_t *reg, uint32_t mask){

	return mask; // temp
}

