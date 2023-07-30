#pragma once

#include "internal/assertions.hh"
#include "internal/test_case.hh"
#include "internal/test_group.hh"

#define testgroup(name) const test::test_group name = test::test_name(#name) +=
#define testcase(name) test::test_name(#name) + []()

#define _TEST_THROWS_(call, message, ...) \
    do { \
        bool __thrown = false; \
        try { \
            call; \
        } catch (...) { \
            __thrown = true; \
        } \
        test_assert(__thrown, message); \
    } while (false)
#define test_throws(...) \
    _TEST_THROWS_( \
        __VA_ARGS__, \
        "Expected exception but none was thrown.", \
        (void)0 \
    )
