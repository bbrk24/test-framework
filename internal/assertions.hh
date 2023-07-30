#pragma once

[[noreturn]] void test_fail(const char* reason = "test_fail() called");
[[noreturn]] void test_skip(const char* reason = "test_skip() called");
void test_assert(bool condition, const char* reason = "test assertion failed");
