# vcpkg
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif ()

# Helper macros
macro(ConfigureInterfaceLibrary LIB_NAME LINK_NAME TARGET_NAME)
    find_package(${LIB_NAME} CONFIG REQUIRED)
    add_library(${TARGET_NAME} INTERFACE)
    target_link_libraries(${TARGET_NAME} INTERFACE ${LINK_NAME})
    set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "External")
endmacro()

macro(ConfigurePathLibrary INCLUDE_VAR HEADER_PATH TARGET_NAME)
    find_path(${INCLUDE_VAR} ${HEADER_PATH})
    add_library(${TARGET_NAME} INTERFACE)
    target_include_directories(${TARGET_NAME} INTERFACE ${${INCLUDE_VAR}})
    set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "External")
endmacro()

# mimalloc
ConfigureInterfaceLibrary(mimalloc mimalloc-static Mimalloc)
if (MSVC)
    target_compile_options(Mimalloc INTERFACE /INCLUDE:mi_version)
endif ()

# magic_enum
ConfigureInterfaceLibrary(magic_enum magic_enum::magic_enum MagicEnum)

# glm
ConfigureInterfaceLibrary(glm glm::glm GLM)
target_compile_definitions(GLM
        INTERFACE
        GLM_FORCE_CXX17
        GLM_FORCE_SWIZZLE
        GLM_FORCE_RADIANS
        GLM_FORCE_RIGHT_HANDED
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        GLM_ENABLE_EXPERIMENTAL
)
if (MSVC)
    target_compile_options(GLM INTERFACE "/Zc:__cplusplus")
endif ()

# stringzilla
ConfigurePathLibrary(STRINGZILLA_INCLUDE_DIRS "stringzilla/drafts.h" Stringzilla)