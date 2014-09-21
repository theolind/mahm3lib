#include "test_dacc.h"

void test_dacc_channel_0_enable() {
	TEST_ASSERT_TRUE(dacc_enable_channel(0));
}

void test_dacc_channel_1_enable() {
	TEST_ASSERT_TRUE(dacc_enable_channel(1));
}

void test_dacc_channel_0_disabled() {
	TEST_ASSERT_TRUE(dacc_disable_channel(0));
}

void test_dacc_channel_1_disable() {
	TEST_ASSERT_TRUE(dacc_disable_channel(1));
}

void test_dacc_channel_0_write() {
	TEST_ASSERT_TRUE(dacc_write(0, 2048));
}

void test_dacc_channel_1_write() {
	TEST_ASSERT_TRUE(dacc_write(1, 2048));
}

void test_dacc_init() {

	struct dacc_settings dacc_settings_t;

	dacc_settings_t.speed_mode = 0;
	dacc_settings_t.refresh = 1;
	dacc_settings_t.startup_time = 0;
	dacc_settings_t.trigger_mode = 0;
	dacc_settings_t.word_transfer = 0;

	TEST_ASSERT_TRUE(dacc_init(&dacc_settings_t));
}

