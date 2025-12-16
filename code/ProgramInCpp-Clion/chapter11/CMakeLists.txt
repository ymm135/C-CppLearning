# Chapter 4 - 多个测试用例示例

# 方法1: 手动添加每个测试用例
# add_executable(chapter4_test1 test1.cpp)
# add_executable(chapter4_test2 test2.cpp)
# add_executable(chapter4_test3 test3.cpp)

# 方法2: 自动发现所有 .cpp 文件并为每个创建可执行文件（推荐）
# 获取当前目录下所有的 .cpp 文件
file(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 为每个 .cpp 文件创建一个可执行文件
foreach(CPP_FILE ${CPP_FILES})
    # 获取文件名（不含路径和扩展名）
    get_filename_component(FILE_NAME ${CPP_FILE} NAME_WE)
    
    # 创建可执行文件目标
    add_executable(chapter11_${FILE_NAME} ${CPP_FILE})
    
    # 设置C++17标准
    set_property(TARGET chapter11_${FILE_NAME} PROPERTY CXX_STANDARD 17)
    
    # 链接线程库（跨平台）
    if(UNIX)
        target_link_libraries(chapter11_${FILE_NAME} pthread)
    endif()
endforeach()

# 显示所有创建的目标
message(STATUS "Chapter11 concurrency demos configured:")
foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(FILE_NAME ${CPP_FILE} NAME_WE)
    message(STATUS "  - chapter11_${FILE_NAME}")
endforeach()