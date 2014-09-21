#include "unity.h"
#include "test_foobar.h"

#include <stdint.h>

#include "pmc.h"

void setUp(void) {

}

void tearDown(void) {

}

void resetTest(void) {
	tearDown();
	setUp();
}

void test_foobar(void) {
	TEST_ASSERT(1);
}
