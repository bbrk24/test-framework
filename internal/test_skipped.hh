#pragma once

#include <exception>

namespace test {
    class test_skipped : public std::exception {
    public:
        test_skipped(const char* test_name, const char* reason) noexcept;
        virtual const char* what() const noexcept;
        const char*& test_name() noexcept;
        const char* test_name() const noexcept;
    private:
        const char* m_test_name;
        const char* m_reason;
    };
}
