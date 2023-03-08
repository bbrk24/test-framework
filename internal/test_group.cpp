#include "test_group.hh"
#include "test_failure.hh"
#include "test_skipped.hh"
#include "test_case.hh"
#include <stdexcept>
#include <cstring>

using namespace test;

struct test_group::counters {
    size_t passed;
    size_t failed;
    size_t not_run;
};

static std::vector<test_group*>* all_tests;

test_group::test_group(
    const char* name,
    std::initializer_list<test_case> list
) noexcept : m_name(name), m_list(list) {
    if (!all_tests) {
        all_tests = new std::vector<test_group*>();
    }
    all_tests->push_back(this);
}

int test_group::run_test(const char* name) const {
    const test_case* test = nullptr;

    for (const auto& member : this->m_list) {
        if (!strcmp(member.name(), name)) {
            test = &member;
            break;
        }
    }

    if (!test) {
        throw std::logic_error("Specified test case does not exist in group.");
    }

    try {
        test->run();
        return 0;
    } catch (const test_failure& e) {
        std::cout
            << "Test "
            << e.test_name()
            << " failed: "
            << e.what()
            << std::endl;
    } catch (const test_skipped& e) {
        std::cout << "Test " << e.test_name() << " skipped." << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout
            << "Test failed with uncaught exception:\n\t"
            << e.what()
            << std::endl;
    } catch (...) {
        std::cout << "Test failed with uncaught error." << std::endl;
    }
    return 1;
}

void test_group::run_tests(counters& c) const noexcept {
    std::cout << "Running test group " << this->m_name << "..." << std::endl;

    c.not_run += this->m_list.size();
    size_t passed = 0;

    for (const auto& test : this->m_list) {
        try {
            test.run();
            --c.not_run;
            ++passed;
        } catch (const test_failure& e) {
            std::cout
                << "Test "
                << e.test_name()
                << " failed: "
                << e.what()
                << std::endl;
            --c.not_run;
            ++c.failed;
        } catch (const test_skipped& e) {
            std::cout << "Test " << e.test_name() << " skipped." << std::endl;
        } catch (const std::exception& e) {
            std::cout
                << "Test failed with uncaught exception:\n\t"
                << e.what()
                << std::endl;
            --c.not_run;
            ++c.failed;
            break;
        } catch (...) {
            std::cout << "Test failed with uncaught error." << std::endl;
            --c.not_run;
            ++c.failed;
            break;
        }
    }

    std::cout
        << passed
        << "/"
        << this->m_list.size()
        << " tests passed."
        << std::endl;
    c.passed += passed;
}

int test_group::run_tests() const noexcept {
    counters c = { 0, 0, 0 };
    this->run_tests(c);
    return c.failed ? 1 : 0;
}

test_group test::operator+=(
    const test_name& lhs,
    const std::initializer_list<test_case>& rhs
) noexcept {
    return test_group(lhs.m_name, rhs);
}

int test::run_all_tests() noexcept {
    test_group::counters c = { 0, 0, 0 };
    for (auto group : *all_tests) {
        group->run_tests(c);
        std::cout << "\n";
    }
    std::cout
        << c.passed
        << " passed, "
        << c.failed
        << " failed, "
        << c.not_run
        << " skipped ("
        << c.passed + c.failed + c.not_run
        << " total)"
        << std::endl;

    return c.failed ? 1 : 0;
}
