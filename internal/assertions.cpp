#include "assertions.hh"
#include "test_failure.hh"
#include "test_skipped.hh"

void test_fail(const char* reason) {
    throw test::test_failure(nullptr, reason);
}

void test_skip(const char* reason) {
    throw test::test_skipped(nullptr, reason);
}

void test_assert(bool condition, const char* reason) {
    if (!condition) {
        throw test::test_failure(nullptr, reason);
    }
}
