cmake_minimum_required(VERSION 3.23)

project(SLibTest LANGUAGES CXX)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_package(GTest CONFIG REQUIRED)
#find_package(benchmark CONFIG REQUIRED)

set(${CMAKE_CURRENT_BINARY_DIR})

