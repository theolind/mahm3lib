/*
 * bitwise_operations unit tests
 *
 * Author:	Saeed Ghasemi
 *
 * Date:	01 October 2014
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/bitwise_operations.h"
#include "test_bitwise_operations.h"

void test_is_bit_high(void);
void test_get_position_of_first_highbit(void);
void test_get_section_in_register(void);
void test_set_section_in_register(void);
void test_set_section_in_register2(void);
void test_clear_register(void);
void test_set_register(void);
