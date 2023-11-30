#include "test_failure.hh"
#include <cstdlib>

using namespace test;

test_failure::test_failure(const char* test_name, char* reason) noexcept
    : m_test_name(test_name), m_reason(reason) { }

test_failure::~test_failure() noexcept {
    free(m_reason);
}

const char* test_failure::what() const noexcept {
    return this->m_reason;
}

const char*& test_failure::test_name() noexcept {
    return this->m_test_name;
}

const char* test_failure::test_name() const noexcept {
    return this->m_test_name;
}
