cmake_minimum_required(VERSION 3.10.2)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C)

if (MSVC)
    # MSVC 现在对 C11 做了部分支持，反而导致 tinycthread 无法通过编译，因此我们还是以 C99 的模式运行本章示例
    set(CMAKE_C_STANDARD 99)
else()
    set(CMAKE_C_STANDARD 11)
endif ()

include_directories("include")
include_directories("tinycthread/include")

if (!MSVC)
    set(CMAKE_C_FLAGS "-O3")
endif ()

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach(file ${files})
    get_filename_component(name ${file} NAME)
    add_executable(${name} ${file} tinycthread/tinycthread.c)

    if (UNIX OR Linux)
        target_link_libraries(${name} pthread)
    endif ()
endforeach()