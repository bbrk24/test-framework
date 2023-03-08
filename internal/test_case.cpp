#include "test_case.hh"
#include "test_name.hh"
#include "test_failure.hh"
#include "test_skipped.hh"
#include <iostream>

using namespace test;

test_case::test_case(
    const char* name,
    const std::function<void()>& test
) noexcept : m_name(name), m_test(test) { }

test_case test::operator+(
    const test_name& lhs,
    const std::function<void()>& rhs
) noexcept {
    return test_case(lhs.m_name, rhs);
}

void test_case::run() const {
    try {
        this->m_test();
    } catch (test_failure& e) {
        e.test_name() = this->m_name;
        throw;
    } catch (test_skipped& e) {
        e.test_name() = this->m_name;
        throw;
    }
}

const char* test_case::name() const noexcept {
    return this->m_name;
}
