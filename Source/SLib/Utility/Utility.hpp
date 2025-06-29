/**
 * @File Utility.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <optional>
#include <expected>

#include <SLib/String/StringType.hpp>
#include <SLib/Enum/Enum.hpp>

namespace slib {

// Optional
template<typename T>
using Opt = std::optional<T>;

// Result
enum class FailureType
{
    Failed = 0, ///> General Failed.
};

constexpr std::string_view FailureName(FailureType failure)
{
    return me::enum_name(failure);
}

using UnexpectedType = std::pair<FailureType, String>;

inline std::unexpected<UnexpectedType> Unexpected(FailureType failure, StringView msg)
{
    return std::unexpected<UnexpectedType>{
      {failure, String(msg)}
    };
}

template<typename... Args>
std::unexpected<UnexpectedType> Unexpected(FailureType failure, std::format_string<Args...> fmt, Args&&... args)
{
    return std::unexpected<UnexpectedType>{
      {failure, String(std::format(fmt, std::forward<Args>(args)...))}
    };
}

template<typename T>
using Result = std::expected<T, UnexpectedType>;

} // namespace slib