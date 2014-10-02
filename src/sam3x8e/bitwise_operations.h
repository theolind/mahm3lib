/**
 * @file bitwise_operations.h
 * @anchor <bitwise_operations>
 * @brief A storage place for commonly used bitwise operation.
 * @details {This class holds some commonly used bitwise operation.
 * This file helps avoiding recreation of function with the same functionality.
 * Mostly intended for bitwise operation and other small operations and
 * generally functions that are common for the different APIs but not linked to
 * the tasks of any API.
 * These function can be used both internally and as well as externally by the
 * end programmer. Its functions fall into the definition of stand-alone and
 * independent of any API. These are mainly a collection of tested bitwise
 * operations on registers or memory.}
 * @author {Saeed Ghasemi}
 * @version {v0.4}
 * @since {Since v0.3, first_bit_position_of_mask() has been added. And mask is
 * the preferred way of editing a register section and the use of start_bit is
 * deprecated.}
 * @date {25 sep 2014}
 * @pre {Since they are stand-alone, there are no preconditions for their use.}
 * @bug {Not yet fully tested.}
 */

#ifndef _BITWISE_OPE_H_
#define _BITWISE_OPE_H_

#include <stdint.h>

#define SYS_CLK_FREQ		84000000

/**
 * This function will test to see if the specified bit in a register is set
 * high.
 *
 * @param reg This specifies a pointer to the register
 * @param bit Specifies the bit-number in the register
 * @return The return will be TRUE or FLASE
 */
uint8_t is_bit_high(uint32_t *reg, uint8_t bit);
/**
 * This function return the bit-number of the first bit being high in a 32-bit
 * long value. The main porpose of this function is to find the start-bit of a
 * given mask. The start-bit can then be used to left-bit-shift a value into
 * position relative to a section in a register.
 *
 * @param mask The mask to be examined
 * @return Bit-number of the first position
 */
uint32_t get_position_of_first_highbit(uint32_t mask);
/**
 * This function will modify a section of a given register as indicated by
 * mask with the value specified in 'value'.
 *
 * @param reg This specifies a pointer to the register
 * @param mask It must have the same length as the register, with ones across the section
 * @param value The value the section must store
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t set_section_in_register(uint32_t *reg, uint32_t mask, uint32_t value);
/**
 * This function will modify a section of a given register as indicated by
 * start_bit and length with the value specified in 'value'.
 *
 * Define the parameters like this:
 * Ex: Having -> 0b00011000 -> start_bit = 3, length = 2
 *
 * @param reg This specifies a pointer to the register
 * @param start_bit The position of the first bit of the section
 * @param length The length of the section
 * @param value The value the section must store
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t set_section_in_register2(uint32_t *reg, uint8_t start_bit,
		uint32_t length, uint32_t value);
/**
 * This function will only return the value of a specified section in a given
 * register. The value in the section will be right-shifted so that the value
 * returned is the value stored in the section.
 *
 * @param reg This specifies a pointer to the register
 * @param mask The area for which the value must be returned (high bit are read)
 * @return The value of the section in the register
 */
uint32_t get_section_in_register(uint32_t *reg, uint32_t mask);
/**
 * This function will clear the entire register.
 *
 * @param reg The pointer to the register to be cleared.
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t clear_register(uint32_t *reg);
/**
 * This function will set the entire register.
 *
 * @param reg The pointer to the register to be set.
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t set_register(uint32_t *reg);

#endif /* _BITWISE_OPE_H_ */
