/**
 * @File Math.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/hash.hpp>

#include <SLib/Math/Numeric.hpp>

namespace slib {

#define DEFINE_VECTOR_ALIAS(type)      \
    using type##1 = glm::vec<1, type>; \
    using type##2 = glm::vec<2, type>; \
    using type##3 = glm::vec<3, type>; \
    using type##4 = glm::vec<4, type>;

DEFINE_VECTOR_ALIAS(float)
DEFINE_VECTOR_ALIAS(double)
DEFINE_VECTOR_ALIAS(int)
DEFINE_VECTOR_ALIAS(uint)

#undef DEFINE_VECTOR_ALIAS

// Prefer to use matrix by 'row-col' ordered.
template<int R, int C, typename T>
using mat_t = glm::mat<C, R, T>;

// clang-format off
template<typename T> using mat1x1_t = mat_t<1, 1, T>;
template<typename T> using mat1x2_t = mat_t<1, 2, T>;
template<typename T> using mat1x3_t = mat_t<1, 3, T>;
template<typename T> using mat1x4_t = mat_t<1, 4, T>;

template<typename T> using mat2x1_t = mat_t<2, 1, T>;
template<typename T> using mat2x2_t = mat_t<2, 2, T>;
template<typename T> using mat2x3_t = mat_t<2, 3, T>;
template<typename T> using mat2x4_t = mat_t<2, 4, T>;

template<typename T> using mat3x1_t = mat_t<3, 1, T>;
template<typename T> using mat3x2_t = mat_t<3, 2, T>;
template<typename T> using mat3x3_t = mat_t<3, 3, T>;
template<typename T> using mat3x4_t = mat_t<3, 4, T>;

template<typename T> using mat4x1_t = mat_t<4, 1, T>;
template<typename T> using mat4x2_t = mat_t<4, 2, T>;
template<typename T> using mat4x3_t = mat_t<4, 3, T>;
template<typename T> using mat4x4_t = mat_t<4, 4, T>;

template<typename T> using mat1_t = mat_t<1, 1, T>;
template<typename T> using mat2_t = mat_t<2, 2, T>;
template<typename T> using mat3_t = mat_t<3, 3, T>;
template<typename T> using mat4_t = mat_t<4, 4, T>;
// clang-format on

#define DEFINE_MATRIX_ALIAS(type, suffix)  \
    using mat1x1##suffix = mat1x1_t<type>; \
    using mat1x2##suffix = mat1x2_t<type>; \
    using mat1x3##suffix = mat1x3_t<type>; \
    using mat1x4##suffix = mat1x4_t<type>; \
    using mat2x1##suffix = mat2x1_t<type>; \
    using mat2x2##suffix = mat2x2_t<type>; \
    using mat2x3##suffix = mat2x3_t<type>; \
    using mat2x4##suffix = mat2x4_t<type>; \
    using mat3x1##suffix = mat3x1_t<type>; \
    using mat3x2##suffix = mat3x2_t<type>; \
    using mat3x3##suffix = mat3x3_t<type>; \
    using mat3x4##suffix = mat3x4_t<type>; \
    using mat4x1##suffix = mat4x1_t<type>; \
    using mat4x2##suffix = mat4x2_t<type>; \
    using mat4x3##suffix = mat4x3_t<type>; \
    using mat4x4##suffix = mat4x4_t<type>;

DEFINE_MATRIX_ALIAS(float, )
DEFINE_MATRIX_ALIAS(int, i)
DEFINE_MATRIX_ALIAS(uint, u)

#undef DEFINE_MATRIX_ALIAS

#define DEFINE_MATRIX_ALIAS(type)     \
    using type##1x1 = mat1x1_t<type>; \
    using type##1x2 = mat1x2_t<type>; \
    using type##1x3 = mat1x3_t<type>; \
    using type##1x4 = mat1x4_t<type>; \
    using type##2x1 = mat2x1_t<type>; \
    using type##2x2 = mat2x2_t<type>; \
    using type##2x3 = mat2x3_t<type>; \
    using type##2x4 = mat2x4_t<type>; \
    using type##3x1 = mat3x1_t<type>; \
    using type##3x2 = mat3x2_t<type>; \
    using type##3x3 = mat3x3_t<type>; \
    using type##3x4 = mat3x4_t<type>; \
    using type##4x1 = mat4x1_t<type>; \
    using type##4x2 = mat4x2_t<type>; \
    using type##4x3 = mat4x3_t<type>; \
    using type##4x4 = mat4x4_t<type>;

DEFINE_MATRIX_ALIAS(float)
DEFINE_MATRIX_ALIAS(double)
DEFINE_MATRIX_ALIAS(int)
DEFINE_MATRIX_ALIAS(uint)

#undef DEFINE_MATRIX_ALIAS

using mat1 = mat1_t<f32>;
using mat2 = mat2_t<f32>;
using mat3 = mat3_t<f32>;
using mat4 = mat4_t<f32>;

#define SLIB_INLINE    GLM_INLINE
#define SLIB_FUNC      GLM_FUNC_QUALIFIER
#define SLIB_CONSTEXPR GLM_CONSTEXPR

} // namespace slib