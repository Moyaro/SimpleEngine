cmake_minimum_required (VERSION 3.19)

project ("SimpleEngine")

# C++编译器配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#不构建共享库
set(BUILD_SHARED_LIBS OFF)
#设置-V标记
set(GLSL_VALIDATOR_ARGS "-V")

#输出compile_commands.json
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CMakeDependentOption)

#防止项目构建在资源文件中造成混乱
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "不能在项目中直接构建，请新建文件夹进行构建"
  )
endif()

#主目录、安装目录、构建目录的路径设置
set(MAIN_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${ENGINE_ROOT_DIR}/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")

# 包含子项目。
add_subdirectory ("engine")
