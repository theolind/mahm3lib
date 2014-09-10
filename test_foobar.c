#include "unity.h"
#include "test_foobar.h"

void setUp(void) {
}

void tearDown(void) {
}

void resetTest(void) {
	tearDown();
	setUp();
}

void test_foobar(void) {
	TEST_ASSERT_TRUE(1);
}