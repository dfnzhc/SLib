/**
 * @File Error.cpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#include "Error.hpp"
#include <stacktrace>

using namespace slib;

void slib::ThrowException(const std::source_location& loc, StringView msg)
{
    std::string fullMsg  = std::format("{}\n\n{}:{} ({})", msg.data(), loc.file_name(), loc.line(), loc.function_name());
    fullMsg             += std::format("\n\nStacktrace:\n{}", std::stacktrace::current(1));

    throw slib::RuntimeError(fullMsg);
}

void slib::ReportAssertion(const std::source_location& loc, StringView cond, StringView msg)
{
    // clang-format off
    std::string fullMsg = std::format("'{}'\n{}\n{}:{} ({})",
                                      cond, msg,
                                      loc.file_name(), loc.line(), loc.function_name());
    // clang-format on
    fullMsg += std::format("\n\nStacktrace:\n{}", std::stacktrace::current(1));

    throw slib::AssertionError(fullMsg);
}