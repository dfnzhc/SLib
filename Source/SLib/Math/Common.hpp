/**
 * @File Common.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <SLib/Math/Math.hpp>
#include <SLib/Math/Constant.hpp>
#include <SLib/Error.hpp>

namespace slib {

#define SLIB_DEFINE_COMMON_FUNC(Type, Name, Func) \
    template<Type T>                              \
    SLIB_FUNC SLIB_CONSTEXPR T Name(T x) noexcept \
    {                                             \
        return std::Func(x);                      \
    }

SLIB_DEFINE_COMMON_FUNC(cFloatType, Floor, floor)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Ceil, ceil)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Trunc, trunc)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Round, round)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Sqrt, sqrt)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Exp, exp)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Exp2, exp2)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Log, log)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Log2, log2)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Sin, sin)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Cos, cos)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Tan, tan)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Sinh, sinh)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Cosh, cosh)
SLIB_DEFINE_COMMON_FUNC(cFloatType, Tanh, tanh)
SLIB_DEFINE_COMMON_FUNC(cFloatType, ASin, asin)
SLIB_DEFINE_COMMON_FUNC(cFloatType, ACos, acos)
SLIB_DEFINE_COMMON_FUNC(cFloatType, ATan, atan)
SLIB_DEFINE_COMMON_FUNC(cFloatType, ASinh, asinh)
SLIB_DEFINE_COMMON_FUNC(cFloatType, ACosh, acosh)
SLIB_DEFINE_COMMON_FUNC(cFloatType, ATanh, atanh)

#undef SLIB_DEFINE_COMMON_FUNC

template<cFloatType T>
SLIB_CONSTEXPR T Log10(T x) noexcept
{
    return std::log10(x);
}

template<cFloatType T>
SLIB_CONSTEXPR T ATan2(T y, T x) noexcept
{
    return std::atan2(y, x);
}

template<cSignedType T>
SLIB_FUNC SLIB_CONSTEXPR T Abs(T x) noexcept
{
    return std::abs(x);
}

template<cSignedType T>
SLIB_FUNC SLIB_CONSTEXPR T Sign(T x) noexcept
{
    return x;
}

template<typename T, typename... Ts>
SLIB_FUNC SLIB_CONSTEXPR auto Min(T a, T b, Ts... vals)
{
    const auto m = a < b ? a : b;
    if constexpr (sizeof...(vals) > 0) {
        return Min(m, T(vals)...);
    }

    return m;
}

template<typename T, typename... Ts>
SLIB_FUNC SLIB_CONSTEXPR auto Max(T a, T b, Ts... vals)
{
    const auto m = a > b ? a : b;
    if constexpr (sizeof...(vals) > 0) {
        return Max(m, T(vals)...);
    }

    return m;
}

template<cArithmeticType T>
SLIB_FUNC SLIB_CONSTEXPR bool Equal(T x, T y) noexcept
{
    return x == y;
}

template<cArithmeticType T>
SLIB_FUNC SLIB_CONSTEXPR bool NotEqual(T x, T y) noexcept
{
    return not Equal(x, y);
}

template<cFloatType T>
SLIB_FUNC SLIB_CONSTEXPR bool Approx(T x, T y, f32 eps = kEpsilonF) noexcept
{
    return Abs(x - y) < eps;
}

template<cFloatType T>
SLIB_FUNC SLIB_CONSTEXPR bool NotApprox(T x, T y, f32 eps = kEpsilonF) noexcept
{
    return not Approx(x, y, eps);
}

SLIB_FUNC SLIB_CONSTEXPR bool IsNaN(std::floating_point auto v)
{
    return std::isnan(v);
}

SLIB_FUNC SLIB_CONSTEXPR bool IsNaN(auto)
{
    return false;
}

SLIB_FUNC SLIB_CONSTEXPR bool IsInf(std::floating_point auto v)
{
    return std::isinf(v);
}

SLIB_FUNC SLIB_CONSTEXPR bool IsInf(auto)
{
    return false;
}

SLIB_FUNC SLIB_CONSTEXPR bool IsFinite(std::floating_point auto v)
{
    return std::isfinite(v);
}

SLIB_FUNC SLIB_CONSTEXPR bool IsFinite(auto)
{
    return true;
}

template<cFloatType T>
SLIB_FUNC SLIB_CONSTEXPR T FMA(T a, T b, T c)
{
    return std::fma(a, b, c);
}

SLIB_FUNC SLIB_CONSTEXPR f32 ApproxSqrt(f32 x0)
{
    SLIB_DEBUG_ASSERT(x0 >= 0);

    union
    {
        i32 ix;
        f32 x;
    } u{};

    u.x  = x0;
    u.ix = 0x1fbb3f80 + (u.ix >> 1);
    u.x  = 0.5f * (u.x + x0 / u.x);
    u.x  = 0.5f * (u.x + x0 / u.x);
    return u.x;
}

SLIB_FUNC SLIB_CONSTEXPR f32 ApproxCbrt(f32 x0)
{
    SLIB_DEBUG_ASSERT(x0 >= 0);

    union
    {
        i32 ix;
        f32 x;
    } u{};

    u.x  = x0;
    u.ix = u.ix / 4 + u.ix / 16;
    u.ix = u.ix + u.ix / 16;
    u.ix = u.ix + u.ix / 256;
    u.ix = 0x2a5137a0 + u.ix;
    u.x  = 0.33333333f * (2.0f * u.x + x0 / (u.x * u.x));
    u.x  = 0.33333333f * (2.0f * u.x + x0 / (u.x * u.x));
    return u.x;
}

template<cFloatType T>
SLIB_FUNC SLIB_CONSTEXPR T RecipSqrtFast(T x0)
{
    SLIB_DEBUG_ASSERT(x0 > 0);

    if constexpr (sizeof(T) == 4) {
        union
        {
            i32 ix;
            f32 x;
        } u{};

        u.x       = x0;
        f32 xHalf = 0.5f * u.x;
        u.ix      = 0x5f37599e - (u.ix >> 1);
        u.x       = u.x * (1.5f - xHalf * u.x * u.x);
        u.x       = u.x * (1.5f - xHalf * u.x * u.x);
        return u.x;
    }
    else {
        union
        {
            i64 ix;
            f64 x;
        } u{};

        u.x  = x0;
        u.ix = 0x5fe6ec85e8000000LL - (u.ix >> 1);
        return u.x;
    }
}

SLIB_FUNC SLIB_CONSTEXPR u32 RoundUp(u32 x, u32 y)
{
    if (x == 0)
        return y;
    return ((x + y - 1) / y) * y;
}

SLIB_FUNC SLIB_CONSTEXPR Size AlignUp(Size value, Size alignment)
{
    // Assumes alignment is a power of two
    return (value + alignment - 1) & ~(alignment - 1);
}

} // namespace slib