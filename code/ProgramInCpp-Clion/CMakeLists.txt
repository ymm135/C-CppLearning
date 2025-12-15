cmake_minimum_required(VERSION 3.20)

# Conan integration - must be before project()
# 支持多个构建目录：build（手动构建）和 cmake-build-debug（CLion）
if(EXISTS ${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
    include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
elseif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conan_toolchain.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/conan_toolchain.cmake)
endif()

project(ProgramInCpp_Clion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set paths for Conan-generated files
# 支持CLion的cmake-build-debug和手动的build目录
if(EXISTS ${CMAKE_BINARY_DIR}/BoostConfig.cmake)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")
else()
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build")
endif()

# Find Boost package
find_package(Boost REQUIRED)

# 自动包含所有 chapter 开头的子目录
file(GLOB CHAPTER_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "chapter*")
foreach(CHAPTER_DIR ${CHAPTER_DIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CHAPTER_DIR})
        # 检查子目录是否包含 CMakeLists.txt
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${CHAPTER_DIR}/CMakeLists.txt)
            message(STATUS "添加章节目录: ${CHAPTER_DIR}")
            add_subdirectory(${CHAPTER_DIR})
        endif()
    endif()
endforeach()