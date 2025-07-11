﻿file(GLOB_RECURSE SOURCE_FILES ./*.hpp ./*.cpp)
AssignSourceGroup(${SOURCE_FILES})

add_library(SLib STATIC ${SOURCE_FILES})
add_library(SLib::SLib ALIAS SLib)

SetCompilerFlags(SLib)
SetDefaultCompileDefinitions(SLib)

target_compile_options(SLib
        PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/DEBUG /Zc:preprocessor> # MSVC
)

target_compile_features(SLib
        PUBLIC
        cxx_std_23
)

target_compile_definitions(SLib
        PRIVATE
        "$<$<CONFIG:Debug,RelWithDebInfo>:SLIB_ENABLE_DEBUG>"
)

target_include_directories(SLib
        PUBLIC
        ${SLIB_INCLUDE_DIR}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(SLib
        PUBLIC
        MagicEnum
        Mimalloc
        Stringzilla
)
