# chapter12 - C++底层实现学习

# 获取当前目录下所有的 .cpp 文件
file(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 为每个 .cpp 文件创建一个可执行文件
foreach(CPP_FILE ${CPP_FILES})
    # 获取文件名（不含路径和扩展名）
    get_filename_component(FILE_NAME ${CPP_FILE} NAME_WE)
    
    # 创建可执行文件目标
    add_executable(chapter12_${FILE_NAME} ${CPP_FILE})
    
    # 设置C++17标准
    set_property(TARGET chapter12_${FILE_NAME} PROPERTY CXX_STANDARD 17)
    
    # 关闭优化，方便查看汇编和调试
    if(MSVC)
        target_compile_options(chapter12_${FILE_NAME} PRIVATE /Od /Zi)
    else()
        target_compile_options(chapter12_${FILE_NAME} PRIVATE -O0 -g)
    endif()
    
    # 启用RTTI（用于type_id和dynamic_cast）
    if(MSVC)
        target_compile_options(chapter12_${FILE_NAME} PRIVATE /GR)
    else()
        target_compile_options(chapter12_${FILE_NAME} PRIVATE -frtti)
    endif()
endforeach()

# 显示所有创建的目标
message(STATUS "Chapter12 C++ internals demos configured:")
foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(FILE_NAME ${CPP_FILE} NAME_WE)
    message(STATUS "  - chapter12_${FILE_NAME}")
endforeach()
