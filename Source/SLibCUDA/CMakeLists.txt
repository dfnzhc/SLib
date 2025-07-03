file(GLOB_RECURSE SOURCE_FILES ./*.hpp ./*.cpp)
AssignSourceGroup(${SOURCE_FILES})

add_library(SLibCUDA STATIC ${SOURCE_FILES})
add_library(SLib::CUDA ALIAS SLibCUDA)

target_compile_features(SLibCUDA
        PUBLIC
        cxx_std_20
)

target_include_directories(SLibCUDA
        PUBLIC
        ${SLIB_CUDA_INCLUDE_DIR}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)