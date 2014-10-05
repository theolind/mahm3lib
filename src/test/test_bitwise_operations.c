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

void test_is_bit_high(void) {
	uint32_t reg = 0x01001001;
	TEST_ASSERT_TRUE(is_bit_high(&reg, 0) == 1);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 3) == 1);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 6) == 1);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 7) == 0);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 2) == 0);
	TEST_ASSERT_TRUE(is_bit_high(&reg, 1) == 0);
}

void test_get_position_of_first_highbit(void) {
	uint32_t reg = 0x00100000;
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 5);
	reg = 0x00000100;
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 2);
	reg = 0x00101000;
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 3);
	reg = 0x00000001; // This returns no error but the return value is still = 0
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 0);
	reg = 0x00000000; // This returns error = 0
	TEST_ASSERT_TRUE(get_position_of_first_highbit(reg) == 0);
}

void test_get_section_in_register(void) {
	uint32_t reg = 0x00000000;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x00110000) == 0x00000000);
	reg = 0x00FF0000;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x00110000) == 0x000000FF);
	reg = 0x0FF00000;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x00110000) == 0x000000F0);
	reg = 0x01463400;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x00011110) == 0x00006340);
	reg = 0xF0F0F0F0;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x11111111) == 0xF0F0F0F0);
	reg = 0xF0F0F0F0;
	TEST_ASSERT_TRUE(get_section_in_register(&reg, 0x11111111) == 0xF0F0F0F0);
	TEST_ASSERT_EQUAL_HEX32(0xF0F0F0F0,
			get_section_in_register(&reg, 0x11111111));
}

void test_set_section_in_register(void) {
	uint32_t reg = 0x00000000;
	set_section_in_register(&reg, 0x00000011, 3);
	TEST_ASSERT_TRUE(reg == 0x00000011);
	set_section_in_register(&reg, 0x00000011, 1);
	TEST_ASSERT_TRUE(reg == 0x00000001);
	set_section_in_register(&reg, 0x00000011, 2);
	TEST_ASSERT_TRUE(reg == 0x00000010);
	set_section_in_register(&reg, 0x00000110, 3);
	TEST_ASSERT_TRUE(reg == 0x00000110);
	set_section_in_register(&reg, 0x00000110, 2);
	TEST_ASSERT_TRUE(reg == 0x00000100);
	set_section_in_register(&reg, 0x00000110, 1);
	TEST_ASSERT_TRUE(reg == 0x00000010);
}

void test_set_section_in_register2(void) {
	uint32_t reg = 0x00000000;
	set_section_in_register2(&reg, 0, 2, 3);
	TEST_ASSERT_TRUE(reg == 0x00000011);
	set_section_in_register(&reg,  0, 2, 1);
	TEST_ASSERT_TRUE(reg == 0x00000001);
	set_section_in_register(&reg,  0, 2, 2);
	TEST_ASSERT_TRUE(reg == 0x00000010);
	set_section_in_register(&reg,  1, 2, 3);
	TEST_ASSERT_TRUE(reg == 0x00000110);
	set_section_in_register(&reg, 1, 2, 2);
	TEST_ASSERT_TRUE(reg == 0x00000100);
	set_section_in_register(&reg, 1, 2, 1);
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

///////////

