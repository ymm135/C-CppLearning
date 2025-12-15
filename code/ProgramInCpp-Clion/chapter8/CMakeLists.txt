# Chapter 8 - 通用构建配置
# 规则：
# 1. xxx.cpp + xxx.h = 库文件（不单独编译）
# 2. xxx_main.cpp 或 N-xxx_main.cpp = 可执行文件（自动包含所有库）
# 3. 其他 .cpp = 独立可执行文件

# 收集所有源文件
file(GLOB CPP_FILES "*.cpp")
file(GLOB H_FILES "*.h")

# 分类：库文件 vs 可执行文件
set(LIBRARY_SOURCES "")
set(EXECUTABLE_SOURCES "")

foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(BASE_NAME ${CPP_FILE} NAME_WE)
    
    # 检查是否有对应的 .h 文件
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${BASE_NAME}.h")
        list(APPEND LIBRARY_SOURCES ${CPP_FILE})
        message(STATUS "  [Library] ${BASE_NAME}.cpp + ${BASE_NAME}.h")
    else()
        list(APPEND EXECUTABLE_SOURCES ${CPP_FILE})
    endif()
endforeach()

# 为每个可执行文件创建目标
foreach(EXEC_SOURCE ${EXECUTABLE_SOURCES})
    get_filename_component(EXEC_NAME ${EXEC_SOURCE} NAME_WE)
    
    # 检查是否包含 _main 后缀
    if(EXEC_NAME MATCHES "_main$")
        # 包含所有库文件
        add_executable(chapter8_${EXEC_NAME} ${EXEC_SOURCE} ${LIBRARY_SOURCES})
        message(STATUS "  [Executable] ${EXEC_NAME} (with all libraries)")
    else()
        # 独立可执行文件
        add_executable(chapter8_${EXEC_NAME} ${EXEC_SOURCE})
        message(STATUS "  [Executable] ${EXEC_NAME} (standalone)")
    endif()
endforeach()


