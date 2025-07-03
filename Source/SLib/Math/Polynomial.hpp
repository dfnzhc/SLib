/**
 * @File Polynomial.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <array>

#include <SLib/Math/Math.hpp>
#include <SLib/Math/Constant.hpp>

namespace slib {

/**
 * 多项式类型
 */
class Polynomial
{
    std::array<f32, 16> _coefficients{}; ///< 索引表示变量幂次，0 是常数项
public:
    // clang-format off
    Polynomial&  c0(f32 coeff) { _coefficients[0]  = coeff; return *this; }
    Polynomial&  c1(f32 coeff) { _coefficients[1]  = coeff; return *this; }
    Polynomial&  c2(f32 coeff) { _coefficients[2]  = coeff; return *this; }
    Polynomial&  c3(f32 coeff) { _coefficients[3]  = coeff; return *this; }
    Polynomial&  c4(f32 coeff) { _coefficients[4]  = coeff; return *this; }
    Polynomial&  c5(f32 coeff) { _coefficients[5]  = coeff; return *this; }
    Polynomial&  c6(f32 coeff) { _coefficients[6]  = coeff; return *this; }
    Polynomial&  c7(f32 coeff) { _coefficients[7]  = coeff; return *this; }
    Polynomial&  c8(f32 coeff) { _coefficients[8]  = coeff; return *this; }
    Polynomial&  c9(f32 coeff) { _coefficients[9]  = coeff; return *this; }
    Polynomial& c10(f32 coeff) { _coefficients[10] = coeff; return *this; }
    Polynomial& c11(f32 coeff) { _coefficients[11] = coeff; return *this; }
    Polynomial& c12(f32 coeff) { _coefficients[12] = coeff; return *this; }
    Polynomial& c13(f32 coeff) { _coefficients[13] = coeff; return *this; }
    Polynomial& c14(f32 coeff) { _coefficients[14] = coeff; return *this; }
    Polynomial& c15(f32 coeff) { _coefficients[15] = coeff; return *this; }

    Polynomial& constant(f32 coeff) { _coefficients[0] = coeff; return *this; }
    // clang-format on
};

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