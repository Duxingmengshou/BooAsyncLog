cmake_minimum_required(VERSION 3.26)

# 设置项目名称
project(boo)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子目录
add_subdirectory(booAsyncLog)
add_subdirectory(booFile)
add_subdirectory(booThread)
add_subdirectory(booTime)

# 创建库
add_library(boo STATIC
        # 这里可以添加需要编译的源文件
        booAsyncLog/asyncLog.cpp
        booAsyncLog/asyncLogBase.cpp
        booAsyncLog/logBuffer.h
        booAsyncLog/logFile.cpp
        booFile/fileName.cpp
        booFile/fileWrite.cpp
        booThread/countDownLatch.cpp
        booTime/booDate.cpp
)

# 链接子模块
target_link_libraries(boo
        PRIVATE booAsyncLog
        PRIVATE booFile
        PRIVATE booThread
        PRIVATE booTime
)

# 包含头文件目录
target_include_directories(boo
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/booAsyncLog
        ${CMAKE_CURRENT_SOURCE_DIR}/booFile
        ${CMAKE_CURRENT_SOURCE_DIR}/booThread
        ${CMAKE_CURRENT_SOURCE_DIR}/booTime
)
