#pragma once

/**
 * Indicate that a test has failed.
 * @param[in] reason Optional string describing why the test failed.
 */
[[noreturn]] void test_fail(const char* reason = "test_fail() called");

/**
 * Indicate that a test should be skipped.
 * @param[in] reason Optional string describing why the test is skipped.
 */
[[noreturn]] void test_skip(const char* reason = "test_skip() called");

/**
 * Check that the condition is true.
 * @param condition  The condition to test.
 * @param[in] reason Optional string to be shown if the assertion fails.
 */
void test_assert(bool condition, const char* reason = "test assertion failed");
