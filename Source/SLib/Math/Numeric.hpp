/**
 * @File Numeric.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <cstdint>
#include <cstddef>

// -------------------------
// Invalid Some Defines

#ifdef max
#  undef max
#endif
#ifdef min
#  undef min
#endif
#ifdef isnan
#  undef isnan
#endif
#ifdef isinf
#  undef isinf
#endif
#ifdef log2
#  undef log2
#endif

// -------------------------
// Host and device macros

#if defined(__CUDA_ARCH__) || defined(__CUDACC__)
#  ifndef SLIB_GPU_CODE
#    define SLIB_GPU_CODE 1
#  endif
#else
#  ifndef SLIB_HOST_CODE
#    define SLIB_HOST_CODE 1
#  endif
#endif

#if SLIB_HOST_CODE

// -------------------------
// Host defines and includes

#  include <limits>

template<typename T>
using numeric_limits = std::numeric_limits<T>;

#  include <type_traits>

// C++20 <bit>
#  if __cplusplus >= 202'002L && __has_include(<bit>)
#    include <bit>
#    define SLIB_USE_STL_BIT 1
#  else
#    define SLIB_USE_STL_BIT 0
#  endif

// Compiler detection for intrinsics
#  if defined(__clang__) || defined(__GNUC__)
#    define SLIB_HAS_GCC_CLANG_INTRINSICS 1
#  else
#    define SLIB_HAS_GCC_CLANG_INTRINSICS 0
#  endif

#  if defined(_MSC_VER)
#    define SLIB_HAS_MSVC_INTRINSICS 1
#    include <intrin.h> // For MSVC intrinsics (_BitScanForward, _BitScanReverse, __popcnt etc.)
#  else
#    define SLIB_HAS_MSVC_INTRINSICS 0
#  endif

#else

// -------------------------
// Device defines and includes

#  include <cuda/std/limits>
template<typename T>
using numeric_limits = ::cuda::std::numeric_limits<T>;

#endif

#include <concepts>

namespace slib {
// -------------------------
// Aliases

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using u64  = uint64_t;
using uint = unsigned int;

using f32 = float;
using f64 = double;

using Size = std::size_t;

#ifdef SLIB_DOUBLE_PRECISION
using Float     = f64;
using FloatBits = u64;
#else
using Float     = f32;
using FloatBits = u32;
#endif // SLIB_DOUBLE_PRECISION

// clang-format off
template<typename T> concept cBoolType = std::is_same_v<bool, T>;
template<typename T> concept cU32Type  = std::is_same_v<u32, T>;
template<typename T> concept cU64Type  = std::is_same_v<u64, T>;
template<typename T> concept cF32Type  = std::is_same_v<f32, T>;
template<typename T> concept cF64Type  = std::is_same_v<f64, T>;

template<typename T> concept cSignedType     = std::is_signed_v<T>;
template<typename T> concept cUnsignedType   = std::is_unsigned_v<T>;
template<typename T> concept cIntegralType   = std::is_integral_v<T>;
template<typename T> concept cFloatType      = std::is_floating_point_v<T>;
template<typename T> concept cArithmeticType = std::is_arithmetic_v<T>;
// clang-format on

template<typename T, typename U>
concept cConvertible = (not std::is_same_v<T, U>) and std::is_convertible_v<T, U> and std::is_convertible_v<U, T>;

template<typename T, typename U>
concept cBothIntegral = cIntegralType<T> and cIntegralType<U>;

template<class>
inline constexpr bool kAlwaysFalse = false;

template<cArithmeticType T>
constexpr T CastTo(cArithmeticType auto f) noexcept
    requires std::is_nothrow_convertible_v<decltype(f), T>
{
    return static_cast<T>(f);
}

} // namespace slib