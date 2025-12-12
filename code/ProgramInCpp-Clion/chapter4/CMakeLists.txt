# Chapter 4 - 多个测试用例示例

# 方法1: 手动添加每个测试用例
# add_executable(chapter4_test1 test1.cpp)
# add_executable(chapter4_test2 test2.cpp)
# add_executable(chapter4_test3 test3.cpp)

# 方法2: 自动发现所有 .cpp 文件并为每个创建可执行文件（推荐）
file(GLOB TEST_SOURCES "*.cpp")
foreach(TEST_SOURCE ${TEST_SOURCES})
    # 获取文件名（不含扩展名）
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    # 创建可执行文件，命名格式: chapter4_文件名
    set(EXECUTABLE_NAME "chapter4_${TEST_NAME}")
    add_executable(${EXECUTABLE_NAME} ${TEST_SOURCE})
    
    # 为整数溢出示例链接 Boost
    if(TEST_NAME STREQUAL "4-c_cpp_integer_overflow")
        if(TARGET Boost::headers)
            target_link_libraries(${EXECUTABLE_NAME} PRIVATE Boost::headers)
            # 使用add_definitions确保所有构建类型都有这个定义
            target_compile_definitions(${EXECUTABLE_NAME} PRIVATE BOOST_FOUND=1)
            # 添加包含路径
            target_include_directories(${EXECUTABLE_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
            message(STATUS "    链接 Boost 到 ${EXECUTABLE_NAME}")
        else()
            message(WARNING "    Boost 未找到，${EXECUTABLE_NAME} 将不使用 cpp_int")
        endif()
    endif()
    
    message(STATUS "  添加测试用例: ${EXECUTABLE_NAME}")
endforeach()