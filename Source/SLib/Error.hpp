/**
 * @File Error.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/28
 * @Brief This file is part of SLib.
 */

#pragma once

#include <cassert>
#include <csignal>
#include <cstdlib>
#include <exception>
#include <format>
#include <iostream>
#include <source_location>

#include <SLib/Portable.hpp>
#include <SLib/Memory/Memory.hpp>
#include <SLib/String/StringType.hpp>

namespace slib {

// clang-format off
class Exception : public std::exception
{
public:
    Exception() noexcept = default;
    Exception(const Exception& other) noexcept : exception(other) { _pWhat = other._pWhat; }
    explicit Exception(StringView what) : _pWhat(std::make_shared<String>(what)) { }
    ~Exception() override = default;

    Exception& operator=(const Exception&) = delete;
    SLIB_NODISCARD const char* what() const noexcept override { return _pWhat ? _pWhat->c_str() : ""; }

protected:
    std::shared_ptr<String> _pWhat;
};

class RuntimeError : public Exception
{
public:
    RuntimeError() noexcept = default;
    RuntimeError(const RuntimeError& other) noexcept : Exception(other) { _pWhat = other._pWhat; }
    explicit RuntimeError(StringView what) : Exception(what) { }

    ~RuntimeError() override = default;
};

class AssertionError : public Exception
{
public:
    AssertionError() noexcept = default;
    AssertionError(const AssertionError& other) noexcept : Exception(other) { _pWhat = other._pWhat; }
    explicit AssertionError(StringView what) : Exception(what) { }

    ~AssertionError() override = default;
};

// clang-format on

SLIB_NORETURN void ThrowException(const std::source_location& loc, StringView msg);
SLIB_NORETURN void ReportAssertion(const std::source_location& loc, StringView cond, StringView msg = {});

namespace details {
SLIB_NORETURN inline void ThrowException(const std::source_location& loc, StringView msg)
{
    ::slib::ThrowException(loc, msg);
}

template<typename... Args>
SLIB_NORETURN inline void ThrowException(const std::source_location& loc, std::format_string<Args...> fmt, Args&&... args)
{
    ::slib::ThrowException(loc, std::format(fmt, std::forward<Args>(args)...));
}

SLIB_NORETURN inline void ReportAssertion(const std::source_location& loc, StringView cond)
{
    ::slib::ReportAssertion(loc, cond);
}

SLIB_NORETURN inline void ReportAssertion(const std::source_location& loc, StringView cond, StringView msg)
{
    ::slib::ReportAssertion(loc, cond, msg);
}

template<typename... Args>
SLIB_NORETURN inline void ReportAssertion(const std::source_location& loc, StringView cond, std::format_string<Args...> fmt, Args&&... args)
{
    ::slib::ReportAssertion(loc, cond, std::format(fmt, std::forward<Args>(args)...));
}
} // namespace details

#define SLIB_THROW(...) ::slib::details::ThrowException(std::source_location::current(), __VA_ARGS__)

#define SLIB_CHECK(cond, ...)        \
    do {                             \
        if (!(cond)) {               \
            SLIB_DEBUG_BREAK();      \
            SLIB_THROW(__VA_ARGS__); \
        }                            \
    } while (0)

#define SLIB_UNIMPLEMENTED() SLIB_THROW("Not Implemented!!")

#define SLIB_UNREACHABLE() SLIB_THROW("You shall not PASS!!!")

#define SLIB_ASSERT(cond, ...)                                                                                   \
    do {                                                                                                         \
        if (!(cond)) {                                                                                           \
            ::slib::details::ReportAssertion(std::source_location::current(), #cond __VA_OPT__(, ) __VA_ARGS__); \
        }                                                                                                        \
    } while (0)

#define SLIB_ASSERT_OP(a, b, OP)                                                                                                           \
    do {                                                                                                                                   \
        if (!((a)OP(b))) {                                                                                                                 \
            ::slib::details::ReportAssertion(std::source_location::current(), std::format("{} {} {} ({} {} {})", #a, #OP, #b, a, #OP, b)); \
        }                                                                                                                                  \
    } while (0)

#define SLIB_ASSERT_EQ(a, b) SLIB_ASSERT_OP(a, b, ==)
#define SLIB_ASSERT_NE(a, b) SLIB_ASSERT_OP(a, b, !=)
#define SLIB_ASSERT_GE(a, b) SLIB_ASSERT_OP(a, b, >=)
#define SLIB_ASSERT_GT(a, b) SLIB_ASSERT_OP(a, b, >)
#define SLIB_ASSERT_LE(a, b) SLIB_ASSERT_OP(a, b, <=)
#define SLIB_ASSERT_LT(a, b) SLIB_ASSERT_OP(a, b, <)

#ifdef SLIB_ENABLE_DEBUG

#  define SLIB_DEBUG_ASSERT(cond, ...)   SLIB_ASSERT(cond, __VA_ARGS__)
#  define SLIB_DEBUG_ASSERT_OP(a, b, OP) SLIB_ASSERT_OP(a, b, OP)

#  define SLIB_DEBUG_ASSERT_EQ(a, b) SLIB_DEBUG_ASSERT_OP(a, b, ==)
#  define SLIB_DEBUG_ASSERT_NE(a, b) SLIB_DEBUG_ASSERT_OP(a, b, !=)
#  define SLIB_DEBUG_ASSERT_GE(a, b) SLIB_DEBUG_ASSERT_OP(a, b, >=)
#  define SLIB_DEBUG_ASSERT_GT(a, b) SLIB_DEBUG_ASSERT_OP(a, b, >)
#  define SLIB_DEBUG_ASSERT_LE(a, b) SLIB_DEBUG_ASSERT_OP(a, b, <=)
#  define SLIB_DEBUG_ASSERT_LT(a, b) SLIB_DEBUG_ASSERT_OP(a, b, <)

#else // SLIB_ENABLE_DEBUG

#  define SLIB_DEBUG_ASSERT(cond, ...) \
      do {                             \
          {                            \
          }                            \
      } while (0)
#  define SLIB_DEBUG_ASSERT_OP(a, b, OP) \
      do {                               \
          {                              \
          }                              \
      } while (0)
#  define SLIB_DEBUG_ASSERT_EQ(a, b) SLIB_DEBUG_ASSERT_OP(a, b, ==)
#  define SLIB_DEBUG_ASSERT_NE(a, b) SLIB_DEBUG_ASSERT_OP(a, b, !=)
#  define SLIB_DEBUG_ASSERT_GE(a, b) SLIB_DEBUG_ASSERT_OP(a, b, >=)
#  define SLIB_DEBUG_ASSERT_GT(a, b) SLIB_DEBUG_ASSERT_OP(a, b, >)
#  define SLIB_DEBUG_ASSERT_LE(a, b) SLIB_DEBUG_ASSERT_OP(a, b, <=)
#  define SLIB_DEBUG_ASSERT_LT(a, b) SLIB_DEBUG_ASSERT_OP(a, b, <)

#endif // SLIB_ENABLE_DEBUG

// ==================
// Error callback
// ==================

namespace details {
SLIB_NORETURN inline void CustomTerminateHandler()
{
    if (auto eptr = std::current_exception()) {
        std::rethrow_exception(eptr);
    }

    SLIB_THROW("Exiting without exception.");
}

SLIB_NORETURN inline void SignalHandler(int signal)
{
    if (signal == SIGABRT)
        SLIB_THROW("'SIGABRT' received!");

    SLIB_THROW("Unexpected signal '{}' received!", signal);
}
} // namespace details

// ==================
// Guardian callback
// ==================

// TODO: How to handle the error? (Error handler, recovery...
template<typename F, class... Args>
inline bool Guardian(F callback, Args&&... args)
{
    static_assert(std::is_invocable_v<F, Args...>);
    std::set_terminate(details::CustomTerminateHandler);
    std::signal(SIGABRT, details::SignalHandler);

    bool bResult = false;
    try {
        if constexpr (std::is_void_v<std::invoke_result_t<F, Args...>>) {
            std::invoke(callback, std::forward<Args>(args)...);
            bResult = true;
        }
        else {
            bResult = static_cast<bool>(std::invoke(callback, std::forward<Args>(args)...));
        }
    } catch (const AssertionError& e) {
        std::cerr << "Assertion Failed: " << e.what();
        SLIB_DEBUG_ASSERT(bResult);
        // LogFatal("Assertion Failed:\n{}", e.what()); // FIXME: logger not working
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what();
        // LogFatal("Exception:\n{}", e.what());
    } catch (...) {
        std::cerr << "Unknown Exception";
        // LogFatal("Unknown Exception");
    }

    return bResult;
}

} // namespace slib