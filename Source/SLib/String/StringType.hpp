/**
 * @File StringType.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <string>
#include <string_view>
#include <fmt/format.h>
#include <stringzilla/stringzilla.hpp>

namespace slib {

namespace sz     = ashvardanian::stringzilla;
using String     = sz::string;
using StringView = sz::string_view;

} // namespace slib

template<>
struct fmt::formatter<slib::String>
{
    constexpr auto parse(const format_parse_context& ctx) { return ctx.begin(); }

    template<typename Context>
    constexpr auto format(const slib::String& bs, Context& ctx) const
    {
        return format_to(ctx.out(), "{}", bs.data());
    }
};

template<>
struct fmt::formatter<slib::StringView>
{
    constexpr auto parse(const format_parse_context& ctx) { return ctx.begin(); }

    template<typename Context>
    constexpr auto format(const slib::StringView& bsv, Context& ctx) const
    {
        return format_to(ctx.out(), "{}", bsv.data());
    }
};