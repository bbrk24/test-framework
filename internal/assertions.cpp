#define __STDC_WANT_LIB_EXT2__ 1
#include "assertions.hh"
#include <cstring>
#include "test_failure.hh"
#include "test_skipped.hh"

void test_fail(const char* reason) {
    throw test::test_failure(nullptr, strdup(reason));
}

void test_skip(const char* reason) {
    throw test::test_skipped(nullptr, strdup(reason));
}

void test_assert(bool condition, const char* reason) {
    if (!condition) {
        throw test::test_failure(nullptr, strdup(reason));
    }
}
