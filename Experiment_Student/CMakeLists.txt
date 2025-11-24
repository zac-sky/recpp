cmake_minimum_required(VERSION 3.5)

PROJECT("Experiment_Student")

SET(CMAKE_CXX_STANDARD 17)

# --- 解决 MSVC 编译错误 D8021 的关键修改 ---

# 定义一组适用于 GCC/Clang 的警告/错误标志
SET(GCC_CLANG_WARNINGS 
    "-Wno-deprecated-declarations" 
    "-Wall" 
    "-Werror" 
    "-Wnon-virtual-dtor" 
    "-Woverloaded-virtual"
)

# 使用 target_compile_options PUBLIC 来将这些选项应用到所有目标
# 但仅在非 MSVC 编译器上应用 (即 Windows 上的 Visual Studio 之外)
if(NOT MSVC)
    # 将这些选项应用于本项目中定义的所有目标（src, tests 等）
    add_compile_options(${GCC_CLANG_WARNINGS})
else()
    # 如果是 MSVC，设置 /W4 (最高警告级别) 和 /WX (将警告视为错误)
    add_compile_options("/W4" "/WX")
endif()

# --- 结束关键修改 ---


#可执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#构建的库的输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

#构建test 目标
ENABLE_TESTING()
#向当前项目添加一个子目录，并且使得 CMake 在构建过程中进入该子目录继续处理其中的 CMakeLists.txt 文件。
#这个命令通常用于管理项目中的多个模块或子项目。
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)