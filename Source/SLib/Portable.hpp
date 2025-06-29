/**
 * @File Portable.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/28
 * @Brief This file is part of SLib.
 */

#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
#  include <Windows.h>
#  include <intrin.h>
#  define SLIB_IN_WINDOWS
#elif defined(__unix__) || defined(__unix) || defined(__linux__)
#  define SLIB_IN_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
#  define SLIB_IN_MAC
#else
#  error Unsupport Platform
#endif

// -------------------------
// Compiler

#if defined(_MSC_VER) && !defined(__clang__)
#  define SLIB_COMPILER_MSVC 1
#elif defined(__clang__)
#  define SLIB_COMPILER_CLANG 1
#elif defined(__GNUC__) && !defined(__clang__)
#  define SLIB_COMPILER_GCC 1
#elif defined(__CUDA_ARCH__) || defined(__CUDACC__)
#  define SLIB_COMPILER_CUDA 1
#else
#  error Unknown Compiler
#endif

// noinline
#if SLIB_COMPILER_MSVC
#  define SLIB_NOINLINE __declspec(noinline)
#elif SLIB_COMPILER_CLANG
#  define SLIB_NOINLINE __attribute__((__noinline__))
#else
#  define SLIB_NOINLINE
#endif

// always inline
#if SLIB_COMPILER_MSVC
#  define SLIB_ALWAYS_INLINE __forceinline
#elif SLIB_COMPILER_CLANG
#  define SLIB_ALWAYS_INLINE inline __attribute__((__always_inline__))
#else
#  define SLIB_ALWAYS_INLINE inline
#endif

#if SLIB_COMPILER_MSVC
#  define SLIB_MSVC_DECLSPEC(...) __declspec(__VA_ARGS__)
#else
#  define SLIB_MSVC_DECLSPEC(...)
#endif

#if SLIB_COMPILER_MSVC
#  define SLIB_CPLUSPLUS _MSVC_LANG
#else
#  define SLIB_CPLUSPLUS __cplusplus
#endif

static_assert(SLIB_CPLUSPLUS >= 202'002L, "__cplusplus >= 202002L: C++20 at least");

// Generalize warning push/pop.
#if SLIB_COMPILER_CLANG || SLIB_COMPILER_GCC
// Clang & GCC
#  define SLIB_PUSH_WARNING                               _Pragma("GCC diagnostic push")
#  define SLIB_POP_WARNING                                _Pragma("GCC diagnostic pop")
#  define SLIB_GNU_DISABLE_WARNING_INTERNAL2(warningName) #warningName
#  define SLIB_GNU_DISABLE_WARNING(warningName)           _Pragma(SLIB_GNU_DISABLE_WARNING_INTERNAL2(GCC diagnostic ignored warningName))
#  ifdef __clang__
#    define SLIB_CLANG_DISABLE_WARNING(warningName) SLIB_GNU_DISABLE_WARNING(warningName)
#    define SLIB_GCC_DISABLE_WARNING(warningName)
#  else
#    define SLIB_CLANG_DISABLE_WARNING(warningName)
#    define SLIB_GCC_DISABLE_WARNING(warningName) SLIB_GNU_DISABLE_WARNING(warningName)
#  endif
#  define SLIB_MSVC_DISABLE_WARNING(warningNumber)
#elif SLIB_COMPILER_MSVC
#  define SLIB_PUSH_WARNING __pragma(warning(push))
#  define SLIB_POP_WARNING  __pragma(warning(pop))
// Disable the GCC warnings.
#  define SLIB_GNU_DISABLE_WARNING(warningName)
#  define SLIB_GCC_DISABLE_WARNING(warningName)
#  define SLIB_CLANG_DISABLE_WARNING(warningName)
#  define SLIB_MSVC_DISABLE_WARNING(warningNumber) __pragma(warning(disable : warningNumber))
#else
#  define SLIB_PUSH_WARNING
#  define SLIB_POP_WARNING
#  define SLIB_GNU_DISABLE_WARNING(warningName)
#  define SLIB_GCC_DISABLE_WARNING(warningName)
#  define SLIB_CLANG_DISABLE_WARNING(warningName)
#  define SLIB_MSVC_DISABLE_WARNING(warningNumber)
#endif

// has builtin
#ifdef __has_builtin
#  define SLIB_HAS_BUILTIN(x) __has_builtin(x)
#else
#  define SLIB_HAS_BUILTIN(x) 0
#endif

// force inline
#if SLIB_COMPILER_MSVC
#  define SLIB_FORCE_INLINE __forceinline
#elif SLIB_COMPILER_GCC || SLIB_COMPILER_CLANG
#  define SLIB_FORCE_INLINE __attribute__((always_inline)) inline
#else
#  define SLIB_FORCE_INLINE inline
#endif

// no inline
#if SLIB_COMPILER_MSVC
#  define SLIB_NO_INLINE __declspec(noinline)
#elif SLIB_COMPILER_GCC || SLIB_COMPILER_CLANG
#  define SLIB_NO_INLINE __attribute__((noinline))
#else
#  define SLIB_NO_INLINE
#endif

// likely & unlikely
#if SLIB_COMPILER_GCC || SLIB_COMPILER_CLANG
#  define SLIB_LIKELY(x)   __builtin_expect(!!(x), 1)
#  define SLIB_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#  define SLIB_LIKELY(x)   (x)
#  define SLIB_UNLIKELY(x) (x)
#endif

// assume
#if SLIB_COMPILER_MSVC
#  define SLIB_ASSUME(condition) __assume(condition)

#elif SLIB_COMPILER_CLANG
#  if SLIB_HAS_BUILTIN(__builtin_assume)
#    define SLIB_ASSUME(condition) __builtin_assume(condition)
#  else
#    define SLIB_ASSUME(condition)       \
        do {                             \
            if (!(condition))            \
                __builtin_unreachable(); \
        } while (0)
#  endif

#elif SLIB_COMPILER_GCC
#  define SLIB_ASSUME(condition)           \
      do {                                 \
          if (SLIB_UNLIKELY(!(condition))) \
              __builtin_unreachable();     \
      } while (0)
#else
#  define SLIB_ASSUME(condition) ((void)0)
#endif

// alignas
#if SLIB_COMPILER_MSVC
#  define SLIB_ALIGNAS(N) __declspec(align(N))
#elif SLIB_COMPILER_GCC || SLIB_COMPILER_CLANG
#  define SLIB_ALIGNAS(N) __attribute__((aligned(N)))
#else
#  define SLIB_ALIGNAS(N) alignas(N)
#endif

// debug break
#if SLIB_ENABLE_DEBUG && !defined(SLIB_COMPILER_CUDA) // Debug break in device code is tricky/different

#  if defined(SLIB_IN_WINDOWS) && defined(SLIB_COMPILER_MSVC)
#    define SLIB_DEBUG_BREAK() __debugbreak()
#  elif SLIB_COMPILER_GCC
#    if SLIB_HAS_BUILTIN(__builtin_trap)
#      define SLIB_DEBUG_BREAK() __builtin_trap()
#    else
#      define SLIB_DEBUG_BREAK() __asm__ volatile("int $0x03")
#    endif

#  elif SLIB_COMPILER_CLANG
#    if SLIB_HAS_BUILTIN(__builtin_debugtrap)
#      define SLIB_DEBUG_BREAK() __builtin_debugtrap()
#    else
#      define SLIB_DEBUG_BREAK() __asm__ volatile("int $0x03")
#    endif

#  else
#    include <cassert> // Required for assert
#    define SLIB_DEBUG_BREAK() assert(false && "SLIB_DEBUG_BREAK: Reached generic breakpoint")
#  endif

#else
#  define SLIB_DEBUG_BREAK() ((void)0) // No-op in release or CUDA device code by default
#endif

// restrict
#if SLIB_COMPILER_MSVC
#  define SLIB_RESTRICT __restrict
#elif SLIB_COMPILER_GCC || SLIB_COMPILER_CLANG
#  define SLIB_RESTRICT __restrict__
#else
#  define SLIB_RESTRICT
#endif

#define SLIB_NO_UNIQUE_ADDRESS [[no_unique_address]]
#define SLIB_UNUSED            [[maybe_unused]]
#define SLIB_NODISCARD         [[nodiscard]]
#define SLIB_NORETURN          [[noreturn]]
#define SLIB_DEPRECATED(...)   [[deprecated(__VA_ARGS__)]]