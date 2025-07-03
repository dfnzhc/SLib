file(GLOB_RECURSE SOURCE_FILES ./*.hpp ./*.cpp)

AssignSourceGroup(${SOURCE_FILES})

add_library(Math STATIC ${SOURCE_FILES})

target_compile_features(SLib
        PRIVATE
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
        GLM
        MagicEnum
        Mimalloc
        Stringzilla
)

add_library(SLib::SLib ALIAS SLib)