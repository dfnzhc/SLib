cmake_minimum_required(VERSION 3.21)

project(CudaTest LANGUAGES CXX CUDA)

enable_language(CUDA)

include(CheckLanguage)
check_language(CUDA)

if(NOT CMAKE_CUDA_COMPILER)
    message(WARNING "Not found CUDA!")
    return()
endif()

add_executable(CuTest main.cpp CuTests.hpp CuTests.cu)

set_target_properties(CuTest PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(CuTest PRIVATE SLib::CUDA)

target_include_directories(CuTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
