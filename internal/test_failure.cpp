#include "test_failure.hh"

using namespace test;

test_failure::test_failure(const char* test_name, const char* reason) noexcept
    : m_test_name(test_name), m_reason(reason)
{ }

const char* test_failure::what() const noexcept {
    return this->m_reason;
}

const char*& test_failure::test_name() noexcept {
    return this->m_test_name;
}

const char* test_failure::test_name() const noexcept {
    return this->m_test_name;
}
