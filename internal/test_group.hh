#pragma once

#include <string>
#include <vector>
#include "test_name.hh"

namespace test {
class test_case;

int run_all_tests() noexcept;

class test_group {
    friend test_group operator+=(
        const test_name& lhs,
        const std::initializer_list<test_case>& rhs
    ) noexcept;
    friend int run_all_tests() noexcept;
public:
    int run_tests() const noexcept;
    int run_test(const char* name) const;
private:
    test_group(
        const char* name,
        std::initializer_list<test_case> list
    ) noexcept;

    struct counters;

    void run_tests(counters& c) const noexcept;

    const char* m_name;
    std::vector<test_case> m_list;
};
}  // namespace test
