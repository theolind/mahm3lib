#include "test/test_dacc.h"
#include "sam3x8e/dacc.h"
#include "unity/unity.h"

void test_dacc_init() {
	const dacc_settings_t dacc_settings = {
		.speed_mode = 0,
		.refresh = 1,
		.startup_time = 0,
		.trigger_mode = 0,
		.word_transfer = 0
	};
	TEST_ASSERT_TRUE(dacc_init(&dacc_settings));
}

void test_dacc_channel_0_enable() {
	TEST_ASSERT_TRUE(dacc_enable_channel(0));
}

void test_dacc_channel_1_enable() {
	TEST_ASSERT_TRUE(dacc_enable_channel(1));
}

void test_dacc_channel_0_write() {
	TEST_ASSERT_TRUE(dacc_write(0, 2048));
}

void test_dacc_channel_1_write() {
	TEST_ASSERT_TRUE(dacc_write(1, 2048));
}

void test_dacc_channel_0_disable() {
	TEST_ASSERT_TRUE(dacc_disable_channel(0));
}

void test_dacc_channel_1_disable() {
	TEST_ASSERT_TRUE(dacc_disable_channel(1));
}
