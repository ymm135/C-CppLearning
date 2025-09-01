#CMakeLists.txt
# 设置cmake最低版本
cmake_minimum_required(VERSION 2.8.0)
# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
# 项目名称
project(cmake_test)
# 包含的头文件目录
include_directories(./include)
set(SRC_DIR ./src)
# 指定生成链接库
add_library(reply ${SRC_DIR}/reply.cpp)
add_library(main ${SRC_DIR}/main.cpp)
# 设置变量
set(LIBRARIES reply main)
set(OBJECT main_test)
# 生成可执行文件
add_executable(${OBJECT} ${SRC_DIR}/main.cpp)
# 为可执行文件链接目标库
target_link_libraries(${OBJECT} ${LIBRARIES})
