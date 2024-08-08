cmake_minimum_required(VERSION 3.26)
project(BooAsyncLog)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(boo)

# 添加可执行文件
add_executable(BooAsyncLog main.cpp)

# 链接 boo 库
target_link_libraries(BooAsyncLog PRIVATE boo)