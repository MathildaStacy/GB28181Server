cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# 添加 gflags 和 glog
add_subdirectory(external/gflags)
add_subdirectory(external/glog)

# 添加可执行文件
add_executable(my_app app/main.cpp)

# 链接 gflags 和 glog
target_link_libraries(my_app gflags glog)
