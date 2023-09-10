#pragma once

#include "internal/assertions.hh"
#include "internal/test_case.hh"
#include "internal/test_group.hh"

/**
 * Declare a group of tests. Invocation of this macro must be followed by an
 * initializer list of test cases.
 * @param name The name of the test group. Must be a valid identifier.
 */
#define testgroup(name) const test::test_group name = test::test_name(#name) +=

/**
 * Define a single test. Invocation of this macro must be followed by a function
 * body.
 * @param name The name of the test case.
 */
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

/**
 * Check that a statement or expression throws when run.
 * @param call        The statement or expression to run.
 * @param[in] message Optional string to be shown if the expression does not
 *                    throw.
 */
#define test_throws(...) \
    _TEST_THROWS_( \
        __VA_ARGS__, \
        "Expected exception but none was thrown.", \
        (void)0 \
    )

/**
 * Define a single test to be called with multiple values. Invocation of this
 * macro must be followed by a function body.
 * @param name The name of the test group. Must be a valid identifier.
 * @param cases A constant-initialized list of cases. Each element must be a
 * `std::pair<const char*, T>`. The first item of the pair describes the value,
 * and the second item of the pair is the actual value passed to the function
 * (must be copyable).
 * @param arg The name of the argument to be used inside the function body. Must
 * be a valid identifier.
 */
#define test_iter(name, cases, arg) \
    const test::test_group name = \
        std::pair<test::test_name, decltype(cases)>{ #name, cases } *= \
        [](auto arg)
