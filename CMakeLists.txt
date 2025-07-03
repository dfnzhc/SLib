cmake_minimum_required(VERSION 3.23)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)


project(SLib
        VERSION 0.0.1
		LANGUAGES CXX
		DESCRIPTION "A C++ toolkit."
		HOMEPAGE_URL "https://github.com/dfnzhc/SLib"
        )

# --------------------------------------------------------------
# Project Configuration
# --------------------------------------------------------------

include(HelperFunctions)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(SLIB_IS_TOP_LEVEL TRUE)
else()
    set(SLIB_IS_SUBPROJECT TRUE)
endif()

if (SLIB_IS_TOP_LEVEL)
    set(SLIB_BUILD_TESTS ON CACHE BOOL "Build test programs")
endif()


# --------------------------------------------------------------
# Global settings
# --------------------------------------------------------------

set(SLIB_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(SLIB_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(SLIB_VERSION_PATCH ${PROJECT_VERSION_PATCH})


# --------------------------------------------------------------
# Sources
# --------------------------------------------------------------

######################################
# Third-Party Library
add_subdirectory(External)

######################################
# Sources
set(SLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(SLIB_CUDA_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
add_subdirectory(Source/SLib)
add_subdirectory(Source/SLibCUDA)

######################################
# Tests
if (SLIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif ()
