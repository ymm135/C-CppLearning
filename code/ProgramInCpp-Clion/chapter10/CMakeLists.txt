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
    set(EXECUTABLE_NAME "chapter10_${TEST_NAME}")
    add_executable(${EXECUTABLE_NAME} ${TEST_SOURCE})
endforeach()