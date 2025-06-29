/**
 * @File Memory.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <memory>
#include <new>

#include <SLib/Math/Numeric.hpp>

namespace slib {

// clang-format off
template<class T> using RawPtr      = T*;
template<class T> using Ptr         = std::shared_ptr<T>;
template<class T> using WeakPtr     = std::weak_ptr<T>;
template<class T> using UniquePtr   = std::unique_ptr<T>;
template<class T> using StdRef      = std::reference_wrapper<T>;
// clang-format on

template<typename T, typename... Args>
    requires std::is_constructible_v<T, Args...>
auto MakePtr(Args&&... args) -> Ptr<T>
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
    requires std::is_constructible_v<T, Args...>
auto MakeUnique(Args&&... args) -> UniquePtr<T>
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

#define SLIB_SAFE_RESET_PTR(ptr) \
    do {                         \
        if (ptr) {               \
            ptr.reset();         \
            ptr = nullptr;       \
        }                        \
    } while (0)

/// ==========================

namespace detail {

template<u8 Level, Size Mul>
constexpr Size MemorySize(Size sz)
{
    if constexpr (Level == 0)
        return sz;
    else {
        return Mul * MemorySize<Level - 1, Mul>(sz);
    }
}
} // namespace detail

// clang-format off

constexpr Size KB(Size sz) { return detail::MemorySize<1, 1000z>(sz); }
constexpr Size MB(Size sz) { return detail::MemorySize<2, 1000z>(sz); }
constexpr Size GB(Size sz) { return detail::MemorySize<3, 1000z>(sz); }

constexpr Size KiB(Size sz) { return detail::MemorySize<1, 1024z>(sz); }
constexpr Size MiB(Size sz) { return detail::MemorySize<2, 1024z>(sz); }
constexpr Size GiB(Size sz) { return detail::MemorySize<3, 1024z>(sz); }

// clang-format on

/// ==========================

constexpr Size kMaxAllocationSize = GiB(16);
constexpr Size kMaxDynamicSize    = MiB(32);

} // namespace slib