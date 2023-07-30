#pragma once

#include <functional>

namespace test {
class test_name;
class test_case;

test_case operator+(
    const test_name& lhs,
    const std::function<void()>& rhs
) noexcept;

class test_case {
    friend test_case operator+(
        const test_name& lhs,
        const std::function<void()>& rhs
    ) noexcept;
public:
    void run() const;
    const char* name() const noexcept;
private:
    test_case(const char* name, const std::function<void()>& test) noexcept;
    const char* m_name;
    std::function<void()> m_test;
};
}  // namespace test
