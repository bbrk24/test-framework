#pragma once

#include <exception>

namespace test {
class test_skipped : public std::exception {
public:
    test_skipped(const char* test_name, char* reason) noexcept;
    ~test_skipped() noexcept;
    virtual const char* what() const noexcept;
    const char*& test_name() noexcept;
    const char* test_name() const noexcept;
private:
    const char* m_test_name;
    char* m_reason;
};
}  // namespace test
