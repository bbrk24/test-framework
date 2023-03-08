#pragma once

#include <initializer_list>
#include <functional>

namespace test {
    class test_group;
    class test_case;

    class test_name {
        friend test_group operator+=(
            const test_name& lhs,
            const std::initializer_list<test_case>& rhs
        ) noexcept;
        friend test_case operator+(
            const test_name& lhs,
            const std::function<void()>& rhs
        ) noexcept;
    public:
        constexpr explicit test_name(const char* name) noexcept
            : m_name(name)
        { }
    private:
        const char* m_name;
    };
}
