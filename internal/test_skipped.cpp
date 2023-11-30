#include "test_skipped.hh"
#include <cstdlib>

using namespace test;

test_skipped::test_skipped(const char* test_name, char* reason) noexcept
    : m_test_name(test_name), m_reason(reason) { }

test_skipped::~test_skipped() noexcept {
    free(m_reason);
}

const char* test_skipped::what() const noexcept {
    return this->m_reason;
}

const char*& test_skipped::test_name() noexcept {
    return this->m_test_name;
}

const char* test_skipped::test_name() const noexcept {
    return this->m_test_name;
}
