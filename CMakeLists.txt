cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# 显示编译时间
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")


# 设置调试的指令
add_compile_options(-Wall -Wextra -Wshadow -Wpedantic) # fsanitize=undefined -fsanitize=address


# 添加 gflags 和 glog
add_subdirectory(external/gflags)
add_subdirectory(external/glog)

# 添加可执行文件
add_executable(my_app app/main.cpp)

# 链接 gflags 和 glog
target_link_libraries(my_app gflags glog)
