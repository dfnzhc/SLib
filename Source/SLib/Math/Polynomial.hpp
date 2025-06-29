/**
 * @File Polynomial.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <SLib/Math/Math.hpp>
#include <SLib/Math/Constant.hpp>

namespace slib {

template<typename T, typename C>
SLIB_FUNC SLIB_CONSTEXPR T EvaluatePolynomial(T, C c)
{
    return CastTo<T>(c);
}

template<typename T, typename C, typename... Args>
SLIB_FUNC SLIB_CONSTEXPR T EvaluatePolynomial(T t, C c, Args... cRemaining)
{
    return FMA(t, EvaluatePolynomial(t, cRemaining...), c);
}

/**
 * @brief (a * b) - (c * d)
 */
template<typename T>
SLIB_FUNC SLIB_CONSTEXPR auto DifferenceOfProducts(T a, T b, T c, T d)
{
    auto cd    = c * d;
    auto dop   = FMA(a, b, -cd);
    auto error = FMA(-c, d, cd);
    return dop + error;
}

/**
 * @brief (a * b) + (c * d)
 */
template<cArithmeticType Ta, cArithmeticType Tb, cArithmeticType Tc, cArithmeticType Td>
SLIB_FUNC SLIB_CONSTEXPR auto SumOfProducts(Ta a, Tb b, Tc c, Td d)
{
    auto cd    = c * d;
    auto sop   = FMA(a, b, cd);
    auto error = FMA(c, d, -cd);
    return sop + error;
}

template<cFloatType T>
SLIB_FUNC bool Quadratic(T a, T b, T c, T* t0, T* t1)
{
    auto disc = DifferenceOfProducts(b, b, T(4) * a, c);
    if (disc < 0)
        return false;

    auto rootDisc = Sqrt(disc);
    if (Approx(rootDisc, Zero<T>())) {
        *t0 = *t1 = T(-0.5) * b / a;
        return true;
    }

    *t0 = T(-0.5) * (b - rootDisc);
    *t1 = T(-0.5) * (b + rootDisc);
    if (*t0 > *t1) {
        using std::swap;
        swap(*t0, *t1);
    }

    return true;
}

} // namespace slib