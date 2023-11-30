#pragma once

#include <exception>

namespace test {
class test_failure : public std::exception {
public:
    test_failure(const char* test_name, char* reason) noexcept;
    ~test_failure() noexcept;
    virtual const char* what() const noexcept override;
    const char*& test_name() noexcept;
    const char* test_name() const noexcept;
private:
    const char* m_test_name;
    char* m_reason;
};
}  // namespace test
