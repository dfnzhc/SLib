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
#ConfigureInterfaceLibrary(mimalloc mimalloc-static Mimalloc)
#if (MSVC)
#    target_compile_options(Mimalloc INTERFACE /INCLUDE:mi_version)
#endif ()
