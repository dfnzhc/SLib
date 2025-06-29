/**
 * @File Bits.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <SLib/Math/Math.hpp>
#include <SLib/Math/Constant.hpp>

namespace slib {
namespace detail {

/**
 * @brief 返回类型 T 的比特大小.
 */
template<typename T>
SLIB_FUNC SLIB_CONSTEXPR int BitSize()
{
    static_assert(std::is_unsigned_v<T>, "Type T must be an unsigned integer.");
    return std::numeric_limits<T>::digits;
}
} // namespace detail

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR int CountLeadingZeros(T value)
{
    if (value == 0)
        return detail::BitSize<T>();

#if SLIB_USE_STL_BIT

    return std::countl_zero(value);
#elif SLIB_HAS_GCC_CLANG_INTRINSICS
    if constexpr (sizeof(T) == sizeof(unsigned int))
        return __builtin_clz(value);
    if constexpr (sizeof(T) == sizeof(unsigned long))
        return __builtin_clzl(value);
    if constexpr (sizeof(T) == sizeof(unsigned long long))
        return __builtin_clzll(value);
    // Fallback for types not directly supported by __builtin_clz* (e.g. uint8_t, uint16_t)
    // Promote to unsigned int, count, then adjust.
    if constexpr (sizeof(T) < sizeof(unsigned int)) {
        return __builtin_clz(static_cast<unsigned int>(value)) - (detail::BitSize<unsigned int>() - detail::BitSize<T>());
    }
#elif SLIB_HAS_MSVC_INTRINSICS
    unsigned long index;
    if constexpr (sizeof(T) <= sizeof(unsigned long)) { // Handles uint8_t, uint16_t, uint32_t
        if (_BitScanReverse(&index, static_cast<unsigned long>(value)))
            return detail::BitSize<T>() - 1 - index;
    }
    else if constexpr (sizeof(T) == sizeof(unsigned __int64)) {
        if (_BitScanReverse64(&index, value))
            return detail::BitSize<T>() - 1 - index;
    }
#endif
    // Fallback implementation
    int count  = 0;
    T msb_mask = static_cast<T>(1) << (detail::BitSize<T>() - 1);
    while (msb_mask != 0 && (value & msb_mask) == 0) {
        count++;
        msb_mask >>= 1;
    }
    return count;
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR int CountTrailingZeros(T value)
{
    if (value == 0)
        return detail::BitSize<T>();

#if SLIB_USE_STL_BIT
    return std::countr_zero(value);
#elif SLIB_HAS_GCC_CLANG_INTRINSICS
    if constexpr (sizeof(T) == sizeof(unsigned int))
        return __builtin_ctz(value);
    if constexpr (sizeof(T) == sizeof(unsigned long))
        return __builtin_ctzl(value);
    if constexpr (sizeof(T) == sizeof(unsigned long long))
        return __builtin_ctzll(value);
    // For smaller types, __builtin_ctz on the value itself should work as it looks at lower bits.
    if constexpr (sizeof(T) < sizeof(unsigned int))
        return __builtin_ctz(static_cast<unsigned int>(value));
#elif SLIB_HAS_MSVC_INTRINSICS
    unsigned long index;
    if constexpr (sizeof(T) <= sizeof(unsigned long)) {
        if (_BitScanForward(&index, static_cast<unsigned long>(value)))
            return index;
    }
    else if constexpr (sizeof(T) == sizeof(unsigned __int64)) {
        if (_BitScanForward64(&index, value))
            return index;
    }
#endif
    // Fallback implementation
    int count = 0;
    for (int i = 0; i < detail::BitSize<T>(); ++i) {
        if (!((value >> i) & 1)) {
            count++;
        }
        else {
            break;
        }
    }
    return count;
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR int Popcount(T value)
{
#if SLIB_USE_STL_BIT
    return std::popcount(value);
#elif SLIB_HAS_GCC_CLANG_INTRINSICS
    if constexpr (sizeof(T) == sizeof(unsigned int))
        return __builtin_popcount(value);
    if constexpr (sizeof(T) == sizeof(unsigned long))
        return __builtin_popcountl(value);
    if constexpr (sizeof(T) == sizeof(unsigned long long))
        return __builtin_popcountll(value);
    // For smaller types, __builtin_popcount should work.
    if constexpr (sizeof(T) < sizeof(unsigned int))
        return __builtin_popcount(static_cast<unsigned int>(value));
#elif SLIB_HAS_MSVC_INTRINSICS
    if constexpr (sizeof(T) == sizeof(unsigned short))
        return __popcnt16(static_cast<unsigned short>(value));
    if constexpr (sizeof(T) == sizeof(unsigned int))
        return __popcnt(static_cast<unsigned int>(value));
    if constexpr (sizeof(T) == sizeof(unsigned __int64))
        return __popcnt64(value);
#endif
    // Fallback (Brian Kernighan's algorithm)
    int count = 0;
    while (value != 0) {
        value &= (value - 1);
        count++;
    }
    return count;
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR int CountSetBits(T value)
{
    return Popcount(value);
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR int CountClearedBits(T value)
{
    return detail::BitSize<T>() - Popcount(value);
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR int Parity(T value)
{
#if SLIB_HAS_GCC_CLANG_INTRINSICS && !defined(__clang__) // __builtin_parity seems more common in GCC
    // Clang might not always have __builtin_parity for all types, or it's less documented.
    // For GCC:
    if constexpr (sizeof(T) == sizeof(unsigned int))
        return __builtin_parity(value);
    if constexpr (sizeof(T) == sizeof(unsigned long))
        return __builtin_parityl(value);
    if constexpr (sizeof(T) == sizeof(unsigned long long))
        return __builtin_parityll(value);
#endif
    return Popcount(value) % 2;
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR bool HasSingleBit(T value)
{
#if SLIB_USE_STL_BIT
    return std::has_single_bit(value);
#else
    return value != 0 && (value & (value - 1)) == 0;
#endif
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR bool IsPowerOfTwo(T value)
{
    return HasSingleBit(value);
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T BitFloor(T value)
{
    if (value == 0)
        return 0;
#if SLIB_USE_STL_BIT
    return std::bit_floor(value);
#else
    // Fallback: set all bits below MSB to 1, then (value XOR (value >> 1))
    // Or more simply: find MSB and return 1 << position_of_MSB
    // Or, using CLZ:
    return static_cast<T>(1) << (detail::BitSize<T>() - 1 - CountLeadingZeros(value));
#endif
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T PreviousPowerOfTwo(T value)
{
    return BitFloor(value);
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR int FloorLog2(T value)
{
    if (value == 0)
        return -1;
    return detail::BitSize<T>() - 1 - CountLeadingZeros(value);
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR int BitWidth(T value)
{
#if SLIB_USE_STL_BIT
    return std::bit_width(value);
#else
    if (value == 0)
        return 0;
    return FloorLog2(value) + 1;
#endif
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T BitCeil(T value)
{
    if (value <= 1)
        return 1;
#if SLIB_USE_STL_BIT
    return std::bit_ceil(value);
#else
    // TODO: ...
#endif
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T NextPowerOfTwo(T value)
{
    return BitCeil(value);
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T ClosestPowerOfTwo(T value)
{
    auto nx = NextPowerOfTwo(value);
    auto px = PreviousPowerOfTwo(value);
    return (nx - value) > (value - px) ? px : nx;
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T ReverseBits(T value)
{
    T v = value;
    if constexpr (sizeof(T) == 1) {
        // 8-bit
        v = ((v & 0xF0) >> 4) | ((v & 0x0F) << 4);
        v = ((v & 0xCC) >> 2) | ((v & 0x33) << 2);
        v = ((v & 0xAA) >> 1) | ((v & 0x55) << 1);
    }
    else if constexpr (sizeof(T) == 2) {
        // 16-bit
        v = ((v & 0xFF00) >> 8) | ((v & 0x00FF) << 8);
        v = ((v & 0xF0F0) >> 4) | ((v & 0x0F0F) << 4);
        v = ((v & 0xCCCC) >> 2) | ((v & 0x3333) << 2);
        v = ((v & 0xAAAA) >> 1) | ((v & 0x5555) << 1);
    }
    else if constexpr (sizeof(T) == 4) {
        // 32-bit
        v = ((v & 0xFFFF0000) >> 16) | ((v & 0x0000FFFF) << 16);
        v = ((v & 0xFF00FF00) >> 8) | ((v & 0x00FF00FF) << 8);
        v = ((v & 0xF0F0F0F0) >> 4) | ((v & 0x0F0F0F0F) << 4);
        v = ((v & 0xCCCCCCCC) >> 2) | ((v & 0x33333333) << 2);
        v = ((v & 0xAAAAAAAA) >> 1) | ((v & 0x55555555) << 1);
    }
    else if constexpr (sizeof(T) == 8) {
        // 64-bit
        v = ((v & 0xFFFFFFFF00000000) >> 32) | ((v & 0x00000000FFFFFFFF) << 32);
        v = ((v & 0xFFFF0000FFFF0000) >> 16) | ((v & 0x0000FFFF0000FFFF) << 16);
        v = ((v & 0xFF00FF00FF00FF00) >> 8) | ((v & 0x00FF00FF00FF00FF) << 8);
        v = ((v & 0xF0F0F0F0F0F0F0F0) >> 4) | ((v & 0x0F0F0F0F0F0F0F0F) << 4);
        v = ((v & 0xCCCCCCCCCCCCCCCC) >> 2) | ((v & 0x3333333333333333) << 2);
        v = ((v & 0xAAAAAAAAAAAAAAAA) >> 1) | ((v & 0x5555555555555555) << 1);
    }

    return v;
}

template<std::unsigned_integral T>
SLIB_FUNC SLIB_CONSTEXPR T BitSwap(T value)
{
    T v = value;
    if constexpr (sizeof(T) == 1) {
        return v;
    }
    else if constexpr (sizeof(T) == 2) {
        return (v >> 8) | (v << 8);
    }
    else if constexpr (sizeof(T) == 4) {
        return ((v << 24) | ((v << 8) & 0x00FF0000) | ((v >> 8) & 0x0000FF00) | (v >> 24));
    }
    else {
        v = (v & 0x00000000FFFFFFFF) << 32 | (v & 0xFFFFFFFF00000000) >> 32;
        v = (v & 0x0000FFFF0000FFFF) << 16 | (v & 0xFFFF0000FFFF0000) >> 16;
        v = (v & 0x00FF00FF00FF00FF) << 8 | (v & 0xFF00FF00FF00FF00) >> 8;
        return v;
    }
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T RotateLeft(T value, int count)
{
    constexpr int bits = detail::BitSize<T>();
    if (bits == 0)
        return value;  // Should not happen for standard unsigned types

    count %= bits;     // Normalize count to be within [-(bits-1), bits-1]
    if (count < 0) {
        count += bits; // Convert negative count to positive equivalent for right rotation becoming left
    }
    // Now count is in [0, bits-1]

#if SLIB_USE_STL_BIT
    return std::rotl(value, count);
#else
    if (count == 0)
        return value;
    return (value << count) | (value >> (bits - count));
#endif
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T RotateRight(T value, int count)
{
    constexpr int bits = detail::BitSize<T>();
    if (bits == 0)
        return value;

    count %= bits;
    if (count < 0) {
        count += bits;
    }
    // Now count is in [0, bits-1]

#if SLIB_USE_STL_BIT
    return std::rotr(value, count);
#else
    if (count == 0)
        return value;
    return (value >> count) | (value << (bits - count));
#endif
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T SetBit(T value, int pos)
{
    // if (pos < 0 || pos >= detail::BitSize<T>()) throw std::out_of_range("Bit position out of range.");
    return value | (static_cast<T>(1) << pos);
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T ClearBit(T value, int pos)
{
    // if (pos < 0 || pos >= detail::BitSize<T>()) throw std::out_of_range("Bit position out of range.");
    return value & ~(static_cast<T>(1) << pos);
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T ToggleBit(T value, int pos)
{
    // if (pos < 0 || pos >= detail::BitSize<T>()) throw std::out_of_range("Bit position out of range.");
    return value ^ (static_cast<T>(1) << pos);
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR bool CheckBit(T value, int pos)
{
    // if (pos < 0 || pos >= detail::BitSize<T>()) throw std::out_of_range("Bit position out of range.");
    return (value >> pos) & 1;
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T RoundUp(T x, T y)
{
    if (x == 0)
        return y;
    if (y == 0) {
        return y;
    }

    return ((x + y - 1) / y) * y;
}

template<cUnsignedType T>
SLIB_FUNC SLIB_CONSTEXPR T AlignUp(T value, T alignment)
{
    return (value + alignment - 1) & ~(alignment - 1);
}
} // namespace slib