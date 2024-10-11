cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 显示编译时间
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")



# 添加 gflags 和 glog
add_subdirectory(external/gflags)
add_subdirectory(external/glog)
# 添加external目录
add_subdirectory(external/jrtplib3)
add_subdirectory(external/jthread)

# 安装路径
set(PJSIP_INSTALL_DIR ${CMAKE_SOURCE_DIR}/install)

include(ExternalProject)

ExternalProject_Add(pjsip
  PREFIX ${CMAKE_SOURCE_DIR}/external
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/pjsip
  CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/external/pjsip/configure --prefix=${PJSIP_INSTALL_DIR} 
  BUILD_COMMAND make
  INSTALL_COMMAND make install
  BUILD_IN_SOURCE 1
)



# 添加可执行文件
add_executable(my_app app/main.cpp)
target_include_directories(my_app PRIVATE ${PJSIP_INSTALL_DIR}/include)
target_include_directories(my_app PRIVATE
    ${CMAKE_SOURCE_DIR}/external/jrtplib3/src
    ${CMAKE_SOURCE_DIR}/external/jthread/src
)

# 确保 my_app 在 pjsip 安装后才进行构建
add_dependencies(my_app pjsip)

# 包含和链接 pjsip 库
target_link_directories(my_app PRIVATE ${PJSIP_INSTALL_DIR}/lib)
# 链接 gflags 和 glog
# 链接库
target_link_libraries(my_app PRIVATE
    gflags
    glog
    ${CMAKE_BINARY_DIR}/external/jrtplib3/src/libjrtp.a
    ${CMAKE_BINARY_DIR}/external/jthread/src/libjthread.a
    ${PJSIP_INSTALL_DIR}/lib/libpjsua-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjsip-ua-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjsip-simple-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjsip-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjmedia-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjmedia-codec-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjmedia-videodev-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjmedia-audiodev-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjnath-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjlib-util-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpj-x86_64-unknown-linux-gnu.a
    ${PJSIP_INSTALL_DIR}/lib/libpjsdp-x86_64-unknown-linux-gnu.a #手动粘贴，pjsip的makefile文件不会自动粘贴
)



