/*
 * bitwise_operations unit tests
 *
 * Author:	Saeed Ghasemi
 *
 * Date:	01 October 2014
 */

#include <sam3x8e/bitwise_operations.h>
#include <stdint.h>
#include <unity/unity.h>
#include <unity/unity_internals.h>
#include "test_bitwise_operations.h"

void test_is_bit_high(void) {
	uint32_t reg = 0x01001001; // first bit in nibble = 28 24 20 16 12 8 4 0
	TEST_ASSERT_TRUE(is_bit_high(&reg, 0) == 1);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 12) == 1);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 24) == 1);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 7) == 0);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 2) == 0);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 31) == 0);
}

void test_get_position_of_first_highbit(void) {
	uint32_t reg = 0x00100000; // first bit in nibble = 28 24 20 16 12 8 4 0
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 20);
	reg = 0x00000100;
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 8);
	reg = 0x00101000;
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 12);
	reg = 0x00000001; // This returns no error but the return value is still = 0
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 0);
	reg = 0x00000000; // This returns error = 0
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 0);
	reg = 0xF0000000;
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 28);
}

void test_get_section_in_register(void) {
	uint32_t reg = 0x00000000;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x00FF0000) == 0x00000000);
	reg = 0x00FF0000;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x00FF0000) == 0x000000FF);
	reg = 0x0FF00000;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x00FF0000) == 0x000000F0);
	reg = 0x01463400;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x000FFFF0) == 0x00006340);
	reg = 0xF0F0F0F0;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0xFFFFFFFF) == 0xF0F0F0F0);
	reg = 0xF030F000;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0xFFFFFFFF) == 0xF030F000);
	TEST_ASSERT_EQUAL_HEX32(0xF030F000,
			get_section_in_register(&reg, 0xFFFFFFFF));
}

void test_set_section_in_register(void) {
	uint32_t reg;
	reg = 0x00000000;
	set_section_in_register(&reg, 0x000000FF, 3);
	TEST_ASSERT_TRUE(reg == 0x00000003);
	reg = 0x00000000;
	set_section_in_register(&reg, 0x00000001, 1);
	TEST_ASSERT_TRUE(reg == 0x00000001);
	reg = 0x00000000;
	set_section_in_register(&reg, 0xF0000000, 2);
	TEST_ASSERT_TRUE(reg == 0x20000000);
//	set_section_in_register(&reg, 0x00000030, 3);
//	TEST_ASSERT_TRUE(reg == 0x00000030);
//	set_section_in_register(&reg, 0x00700000, 2);
//	TEST_ASSERT_TRUE(reg == 0x00200000);
//	set_section_in_register(&reg, 0x00000C00, 4);
//	TEST_ASSERT_TRUE(reg == 0x00000400);
//	set_section_in_register(&reg, 0x00000C00, 8);
//	TEST_ASSERT_TRUE(reg == 0x00000800);
}

void test_set_section_in_register2(void) {
	uint32_t reg = 0x00000000;
	set_section_in_register2(&reg, 0, 2, 3);
	TEST_ASSERT_TRUE(reg == 0x00000011);
	set_section_in_register2(&reg, 0, 2, 1);
	TEST_ASSERT_TRUE(reg == 0x00000001);
	set_section_in_register2(&reg, 0, 2, 2);
	TEST_ASSERT_TRUE(reg == 0x00000010);
	set_section_in_register2(&reg, 1, 2, 3);
	TEST_ASSERT_TRUE(reg == 0x00000110);
	set_section_in_register2(&reg, 1, 2, 2);
	TEST_ASSERT_TRUE(reg == 0x00000100);
	set_section_in_register2(&reg, 1, 2, 1);
	TEST_ASSERT_TRUE(reg == 0x00000010U);
}

void test_clear_register(void) {
	uint32_t reg = 123;
	clear_register(&reg);
	TEST_ASSERT_TRUE(reg == 0x00000000);
	TEST_ASSERT_EQUAL_UINT32(0x00000000, reg);
	reg = 0x12334413;
	clear_register(&reg);
	TEST_ASSERT_TRUE(reg == 0x00000000);
	TEST_ASSERT_EQUAL_UINT32(0, reg);
	reg = 0x00000000;
	clear_register(&reg);
	TEST_ASSERT_TRUE(reg == 0x00000000);
	TEST_ASSERT_EQUAL_UINT32(0, reg);
}

void test_set_register(void) {
	uint32_t reg = 0;
	set_register(&reg);
	TEST_ASSERT_TRUE(reg == 0xFFFFFFFF);
	reg = 0x12334413;
	set_register(&reg);
	TEST_ASSERT_TRUE(reg == 0xFFFFFFFF);
}

