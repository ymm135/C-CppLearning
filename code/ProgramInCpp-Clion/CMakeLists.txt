cmake_minimum_required(VERSION 3.20)
project(ProgramInCpp_Clion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
