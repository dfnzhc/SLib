﻿/**
 * @File Hash.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <SLib/Math/Math.hpp>

namespace slib {

template<typename T>
SLIB_CONSTEXPR void HashCombine(size_t& seed, const T& val)
{
    using std::hash;
    seed ^= hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

} // namespace slib