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
    template <class T>
    friend test_group operator*=(
        std::pair<test_name, T> lhs,
        std::function<void(typename T::value_type::second_type)> rhs
    );
    friend int run_all_tests() noexcept;
public:
    int run_tests() const noexcept;
    int run_test(const char* name) const;
private:
    test_group(
        const char* name,
        std::initializer_list<test_case> list
    ) noexcept;

    template <class T>
    test_group(
        const char* name,
        const T& cases,
        std::function<void(typename T::value_type::second_type)> body
    )
        : m_name(name), m_list() {
        for (const auto& p : cases) {
            m_list.push_back(test_name(p.first) + [=]() { body(p.second); });
        }
        if (!all_tests) {
            all_tests = new std::vector<test_group*>();
        }
        all_tests->push_back(this);
    }

    struct counters;

    void run_tests(counters& c) const noexcept;

    static std::vector<test_group*>* all_tests;

    const char* m_name;
    std::vector<test_case> m_list;
};

template <class T>
test_group operator*=(
    std::pair<test_name, T> lhs,
    std::function<void(typename T::value_type::second_type)> rhs
) {
    return test_group(lhs.first.m_name, lhs.second, rhs);
}
}  // namespace test
