# C++ Learning Project with CLion

这是一个使用CLion进行C++学习的多章节项目。

## 项目结构

```
ProgramInCpp-Clion/
├── CMakeLists.txt          # 根配置文件
├── chapter1/               # 第1章学习代码
├── chapter2/               # 第2章学习代码
│   ├── CMakeLists.txt
│   └── 2-types.cpp
└── ...                     # 后续章节
```

## 快速开始

1. **在CLion中打开项目**
   - File → Open → 选择项目根目录

2. **重新加载CMake项目**（如果提示）
   - 右键点击 `CMakeLists.txt` → "Reload CMake Project"

3. **运行代码**
   - 在CLion右上角选择要运行的目标（如 `chapter2_types`）
   - 点击绿色运行按钮或按 `Shift+F10`

## 添加新章节

1. 创建章节文件夹，如 `chapter3`
2. 在该文件夹中创建 `CMakeLists.txt`：
   ```cmake
   # Chapter 3 - 章节名称
   add_executable(chapter3_example example.cpp)
   ```
3. 在根目录 `CMakeLists.txt` 中添加：
   ```cmake
   add_subdirectory(chapter3)
   ```
4. 在CLion中重新加载CMake项目

## 注意事项

- 每个可执行文件需要唯一的名称，建议使用 `chapterX_名称` 格式
- 子目录的 `CMakeLists.txt` 只需包含 `add_executable()` 命令
- 修改CMake配置后，记得重新加载CMake项目

## 详细文档

查看完整的配置指南和常见问题解答，请参考项目文档。

## 学习资源

- [CMake官方文档](https://cmake.org/documentation/)
- [C++参考手册](https://en.cppreference.com/)
