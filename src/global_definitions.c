/**
 * global_definitions.c
 *
 * This file contains functions that the developers in this group will at
 * some point use. This file helps us to avoid recreating function with the
 * same functionality.
 *
 *
 * Created by: Saeed Ghasemi, 2014-09-22
 */

#include "global_definitions.h"


/**
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
 * This function sets or clear or modifies a section of a register, reg,
 * defined by 'mask' with 'value'.
 * This will only work for read/write register.
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
uint8_t set_section_in_register(uint32_t *reg, uint8_t start_bit, uint8_t length, uint32_t value){
	uint32_t mask;
	// Creating the mask for the section in the register
	mask = ~(((2^length)-1)<<start_bit);
	// Retrieving the register and modifying it
	*reg = (mask & *reg) | (value << start_bit);
	return SUCCESS;
}

/**
 * This function will only return the value of a specified section in a given
 * register.
 * @param reg The pointer to the register (not its value)
 * @param mask The area for which the value must be returned (high bit are read)
 * @return The value of the section in the register
 */
uint8_t get_value_of_register(uint32_t *reg, uint32_t mask){

}

